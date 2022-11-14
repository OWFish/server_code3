#include "StdAfx.h"
#include "client.h"
#include "base/sha1.h"
#include "base64.h"

BaseAllocator Client::alloc("ClientAlloc");
Client::Client(GameClientMgr *cli_mgr, SOCKET s, sockaddr_in* addr) {
	shake_hands_ = false;
	fd_ = s;
	cli_mgr_ = cli_mgr;
	send_packet_ = new DataPacket(&alloc);
	send_packet_->reserve(SEND_PACKET_MAX);
	send_packet_->setLength(0);
	memcpy(&remote_addr_, addr, sizeof(sockaddr_in));
	net_id_.socket_ = s;
	conn_status_ = ConnStatusDef::CS_CONNED;
	skey_ = 0;
	is_close_ = false;
}

Client ::~Client() {
	for (auto it : recv_list_) {
		SafeDelete(it);
	}
	SafeDelete(send_packet_);
	recv_list_.clear();
	for (auto it : gw_recv_list_) {
		SafeDelete(it);
	}
}

int Client::SetBlockMode(const bool block) {
	unsigned long flag = block ? 0 : 1;
#ifdef _MSC_VER
	return ioctlsocket(fd_, FIONBIO, &flag);
#else
	return ioctl(fd_, FIONBIO, &flag);//改为非阻塞;
#endif
}

void Client::RecvData(void) {
	if (is_close_) return;
	static char buf[1024];
	while (true) {
		int buflen = recv(fd_, buf, sizeof(buf), 0);
		if (buflen < 0) {
			// 由于是非阻塞的模式,所以当errno为EAGAIN时,表示当前缓冲区已无数据可读
			// 在这里就当作是该次事件已处理
#ifdef _MSC_VER
			if (WSAGetLastError() == WSAECONNABORTED) {
				Close();
				return;
			} else if (WSAGetLastError() == WSAEWOULDBLOCK) {
#else
			if (WSAGetLastError() == EINPROGRESS || WSAGetLastError() == EAGAIN) {
#endif
				break;
			} else {
				MSG_ERR("not handle errno:[%d]%s", WSAGetLastError(), strerror(WSAGetLastError()));
				Close();
				return;
			}
		} else if (buflen == 0) {
			// 这里表示对端的socket已正常关闭.
			Close();
			return;
		}
		if (shake_hands_) {
			DataPacket* dp = new DataPacket(&alloc);
			dp->writeBuf(buf, buflen);
			dp->setPosition(0);
			recv_list_.push_back(dp);
		} else {
			//进行websocket握手
			ShakeHandsHandle(buf, buflen);
			return;
		}
	}
}

bool Client::SendData(void) {
	size_t splen = send_packet_->getAvaliableLength();
	if (splen <= 0) { return true; }
	int lsed = send(fd_, send_packet_->getOffsetPtr(), (int)splen, 0);
	if(lsed <= 0) { return true; }
	if (lsed < splen) {
		send_packet_->setPosition(send_packet_->getPosition() + lsed);
		return false;
	} else {
		send_packet_->setLength(0);
	}
	return true;
}

void Client::WriteEvent(void) {
	if (is_close_) return;
	DataPacket* dp = NULL;
	while (true) {
		if (gw_recv_list_.empty()) { break; }
		dp = *(gw_recv_list_.begin());
		gw_recv_list_.pop_front();
		FlushWsPack(dp->getOffsetPtr(), dp->getAvaliableLength());
		SafeDelete(dp);
	}
	if(send_packet_->getAvaliableLength() > 0) {
		cli_mgr_->HaveData(this);
	}
}

void Client::Flush(const char *buf, size_t len) {
	if (send_packet_->getAvaliableLength() + len > SEND_PACKET_MAX) {
		MSG_ERR("send packet is max, fd:%d", fd_);
		Close();
		return;
	} else {
		size_t pos = send_packet_->getPosition();
		send_packet_->setPosition(pos + send_packet_->getAvaliableLength());
		send_packet_->writeBuf(buf, len);
		send_packet_->setPosition(pos);
	}
}

void Client::SendNewSession(void) {
	static GameWorldClient* wgc = cli_mgr_->GetGameWorldClient();
	DataPacket &dp = wgc->allocProtoPacket(GW_OPEN);
	dp << net_id_;
	dp.writeBuf(inet_ntoa(remote_addr_.sin_addr), 32);
	wgc->flushProtoPacket(dp);
}

void Client::SendSessionClose(void) {
	static GameWorldClient* wgc = cli_mgr_->GetGameWorldClient();
	DataPacket &dp = wgc->allocProtoPacket(GW_CLOSE);
	dp << net_id_;
	wgc->flushProtoPacket(dp);
}

void Client::Close(void) {
	MSG_ERR("close client, fd:%d,index:%d", net_id_.socket_, net_id_.index_);
	cli_mgr_->CloseClient(this);
	SendSessionClose();
	is_close_ = true;
}

#define WEB_SOCKET_HANDS_RE "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n"
#define MAGIC_KEY "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
void Client::ShakeHandsHandle(const char* buf, int buflen) {
	char key[512]; memset(key, 0, 512);
	for (int i = 0; i < buflen; ++i)
	{
		if (FindHttpParam("Sec-WebSocket-Key", buf+i)) {
			short k = i + 17, ki = 0;
			while(*(buf + k) != '\r' && *(buf + k) != '\n') {
				if (*(buf + k) == ':' || *(buf + k) == ' '){
					++k; continue;
				} else {
					key[ki++] = *(buf + k);
				}
				++k;
			}
			break;
		}
	}
	//MSG_LOG("key:%s...", key);
	memcpy(key + strlen(key), MAGIC_KEY, sizeof(MAGIC_KEY));
	//MSG_LOG("megerkey:%s...", key);
	//求哈希1
	SHA1 sha;
	unsigned int message_digest[5];
	sha.Reset();
	sha << key;
	sha.Result(message_digest);
	for (int i = 0; i < 5; i++) {
		message_digest[i] = htonl(message_digest[i]);
	}

	memset(key, 0, 512);
	base64_encode(key, reinterpret_cast<const char*>(message_digest), 20);
	char http_res[512] = "";
	sprintf(http_res, WEB_SOCKET_HANDS_RE, key);
	Flush(http_res, strlen(http_res));
	//MSG_LOG("res:%s...",http_res);//fkYTdNEVkParesYkrM4S
	SendData();
	shake_hands_ = true;
	SendNewSession();//发送到gameworld新增连接
}

void Client::PacketHandle(void) {
	if (is_close_) return;
	while (!recv_list_.empty()) {
		auto dpit = recv_list_.begin();
		DataPacket* dp = *dpit;
		//读取websocket固定包头
		if (!ws_head_.rh) {
			//这个包不够一个头部的大小
			if (dp->getAvaliableLength() < 2) {
				if (MergePacketList(dpit)) continue;
				else break;
			}
			//读取
			uint8_t head = 0;
			dp->readBuf(&head, 1);
			ws_head_.fin = head >> 7;
			ws_head_.opcode = head & 0xF;
			dp->readBuf(&head, 1);
			ws_head_.len = head & 0x7F;
			ws_head_.mask = head >> 7;
			ws_head_.rh = 1;//标记头部读取完成
		}
		//读取长度
		if (!ws_head_.rl) {
			uint8_t nsize = ws_head_.GetLenNeedByte();
			if (nsize) {
				//这个包不够一个长度
				if (dp->getAvaliableLength() < nsize) {
					if (MergePacketList(dpit)) continue;
					else break;
				}
				if (nsize == 2) {
					(*dp) >> ws_head_.ex_len.v16;
					ws_head_.ex_len.v16 = ntohs(ws_head_.ex_len.v16);
				} else {
					(*dp) >> ws_head_.ex_len.v64;
					ws_head_.ex_len.v64 = ntohl((u_long)ws_head_.ex_len.v64);
				}
			}
			ws_head_.rl = 1;
		}
		//读取MKEY
		if (!ws_head_.rk) {
			if (ws_head_.mask) {
				//这个包不够一个key
				if (dp->getAvaliableLength() < 4) {
					if (MergePacketList(dpit)) continue;
					else break;
				}
				(*dp) >> ws_head_.mkey[0];
				(*dp) >> ws_head_.mkey[1];
				(*dp) >> ws_head_.mkey[2];
				(*dp) >> ws_head_.mkey[3];
			}
			ws_head_.rk = 1;
		}
		//读取数据段
		uint64_t data_len = ws_head_.GetLen();
		if (dp->getAvaliableLength() < data_len) {
			if (MergePacketList(dpit)) continue;
			else break;
		}

		if (ws_head_.mask) {
			char* dptr = dp->getOffsetPtr();
			for (size_t i = 0; i < data_len; ++i) {
				dptr[i] = dptr[i] ^ ws_head_.mkey[i % 4];
			}
		}

		if (!OnRecv(dp->getOffsetPtr(), data_len)) {
			return;
		}
		ws_head_.reset();
		dp->adjustOffset(data_len);
		//这个包读取完了
		if (dp->getAvaliableLength() <= 0) {
			recv_list_.pop_front();
			SafeDelete(dp);
		}
	}
}

bool Client::OnRecv(const char* buf, size_t size) {

	if (conn_status_ == CS_COMMUNICATE) {
		if (ws_head_.opcode == OPCODE_CLR) {
			Close();
			return false;
		}
		if (size < 4) {
			MSG_ERR("size is min");
			return true;
		}
		uint32_t tag = *((uint32_t*)buf);
		if (tag != skey_) {
			Close();
			return false;
		}
		//发送给游戏服
		static GameWorldClient* wgc = cli_mgr_->GetGameWorldClient();
		DataPacket& pack = wgc->allocProtoPacket(GW_DATA);
		pack << net_id_;
		uint8_t nsize = sizeof(uint32_t);
		pack.writeBuf(buf + nsize, size - nsize);
		wgc->flushProtoPacket(pack);
		MSG_ERR("size is [%d]", size);
		return true;
	}

	if (conn_status_ == CS_CONNED) { //刚连接上来
		uint32_t tag = *((uint32_t*)buf);
		if (tag != DEFAULT_TAG) {
			Close();
			return false;
		}
		skey_ = wrand(INT_MAX);
		FlushWsPack((char *)&skey_, 4);
		SendData();
		conn_status_ = CS_COMMUNICATE;
	}
	return true;
}

void Client::FlushWsPack(const char* buf, size_t size) {
	static DataPacket pack(&alloc);
	pack.setLength(0);
	pack << (uint8_t)0x82;//写头部
	//写长度
	if (size >= 126) {//7位放不下
		if (size <= 0xFFFF) {//16位放
			pack << (uint8_t)126;
			pack << (uint16_t)htons((u_short)size);
		} else {//64位放
			pack << (uint8_t)127;
			pack << (uint64_t)OrderSwap64(size);
		}
	} else {
		pack << (uint8_t)size;
	}
	//写数据
	pack.writeBuf(buf, size);
	pack.setPosition(0);
	Flush(pack.getOffsetPtr(), pack.getAvaliableLength());
}

void Client::OnGameWorldRecv(const char* buf, size_t size) {
	DataPacket *dp = new DataPacket(&alloc);
	(*dp) << (uint32_t)skey_;
	dp->writeBuf(buf, size);
	dp->setPosition(0);
	gw_recv_list_.push_back(dp);
}

bool Client::MergePacketList(std::list<DataPacket*>::iterator &dpit) {
	auto sdpit = ++dpit;
	if (sdpit == recv_list_.end()) return false;
	DataPacket* sdp = *sdpit;
	//合并第二个到第一个
	(*dpit)->writeBuf(sdp->getOffsetPtr(), sdp->getAvaliableLength());
	SafeDelete(sdp);
	recv_list_.erase(sdpit);
	return true;
}

bool Client::FindHttpParam(const char * param, const char * buf) {
	while (*param == *buf) {
		if (*(param + 1) == '\0') return true;
		++param; ++buf;
	}
	return false;
}

