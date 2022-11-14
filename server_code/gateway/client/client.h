#pragma once
#include <list>

#define SEND_PACKET_MAX 1024*1024*8
#define DEFAULT_TAG 0xCA0FFFFF

enum WebSocketOpcode { //操作码定义类型
	OPCODE_MID = 0x0,//标识一个中间数据包
	OPCODE_TXT = 0x1,//标识一个text类型数据包
	OPCODE_BIN = 0x2,//标识一个binary类型数据包
	//0x3 - 7：保留
	OPCODE_CLR = 0x8,//标识一个断开连接类型数据包
	OPCODE_PIN = 0x9,//标识一个ping类型数据包
	OPCODE_PON = 0xA,//表示一个pong类型数据包
};

#pragma pack(push,1)
struct WebSocketHead {
	uint8_t fin : 1;//标识是否为此消息的最后一个数据包
	uint8_t rsv1 : 1;//保留位1
	uint8_t rsv2 : 1;//保留位2
	uint8_t rsv3 : 1;//保留位3
	uint8_t opcode : 4;//操作码

	uint8_t mask : 1; //是否需要掩码
	uint8_t len : 7;//长度
	union {
		uint16_t v16;//长度为126时
		uint64_t v64;//长度为127时
	} ex_len;
	uint8_t mkey[4];
	uint8_t rh : 1;//head读取完成
	uint8_t rl : 1;//len读取完成
	uint8_t rk : 1;//mkey读取完成
	uint8_t rs : 5;//扩展保留
	WebSocketHead(void) { reset(); }
	void reset(void) { memset(this,0,sizeof(WebSocketHead)); }
	inline uint64_t GetLen(void) {
		if (len == 126) {
			return ex_len.v16;
		} else if (len == 127) {
			return ex_len.v64;
		}
		return len;
	}
	inline uint8_t GetLenNeedByte(void) {
		if (len == 126) {
			return 2;
		} else if (len == 127) {
			return 8;
		} 
		return 0;
	}
};
#pragma pack(pop)

enum ConnStatusDef {
	CS_CONNED,//连接上
	CS_COMMUNICATE,//通信状态
};
typedef std::list<DataPacket*> DataPacketList;
class Client {
public:
	Client(GameClientMgr *cli_mgr, SOCKET s, sockaddr_in* addr);
	~Client();

	//设置阻塞模式。true表示阻塞，false表示非阻塞，返回值为socket错误号，0表示成功
	int SetBlockMode(const bool block);
	void SetSessionId(const uint16_t sid) { net_id_.index_ = sid; }
	uint16_t GetSessionId(void) { return net_id_.index_; }
	NetId &GetNetId(void) { return net_id_; }
	void RecvData(void);
	bool SendData(void);
	void WriteEvent(void);
	void Flush(const char *buf, size_t len);
	void SendNewSession(void);
	void SendSessionClose(void);
	void Close(void);
	bool OnRecv(const char* buf, size_t size);
	void FlushWsPack(const char* buf, size_t size);
	void OnGameWorldRecv(const char* buf, size_t size);
	inline SOCKET GetFd(void) { return fd_; }
	inline bool IsClose(void) { return is_close_; }
	void PacketHandle(void);
protected:
	void ShakeHandsHandle(const char* buf, int buflen);
private:
	inline bool MergePacketList(std::list<DataPacket*>::iterator &dpit);
	bool FindHttpParam(const char* param, const char* buf);

	bool shake_hands_;//是否已经握手
	SOCKET fd_;		 //套接字
	bool is_close_;	//是否已经关闭连接
	sockaddr_in	remote_addr_;//远程地址
	DataPacketList recv_list_;//收到的包列表
	DataPacket* send_packet_;//需要发包的缓冲区
	DataPacketList gw_recv_list_;//从游戏服收到的包列表
	WebSocketHead ws_head_;//包头
	NetId net_id_;
	uint8_t conn_status_;//连接状态
	uint32_t skey_;//服务端KEY
	static BaseAllocator alloc;
	GameClientMgr* cli_mgr_;
};
