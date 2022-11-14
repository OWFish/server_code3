#include <new>
#include <stdio.h>
#include <time.h>
#include "os_def.h"
#include <_ast.h>
#include <x_lock.h>
#include <container/queue_list.h>
#include <x_thread.h>
#include <ref_class.hpp>
#include "share_util.h"
#include <memory/buffer_allocator.h>
#include "data_packet.hpp"
#include "flog/file_logger.h"

using namespace lock;
using namespace container;

class OPMToFile :
	protected thread::BaseThread
{
private:
	char fn_[256];
	
public:
	OPMToFile(const char* filename):
		BaseThread(),
		allocator_("filelogger")
	{
		memset(fn_, 0, sizeof(fn_));
		_STRNCPY_S(fn_, filename, sizeof(fn_) - 1);

		write_msg_list_.setLock(&write_lock_);
		free_msg_list_.setLock(&free_lock_);
		Start();
	}

	~OPMToFile()
	{
		//终止数据写入线程
		Stop();

		//销毁写入列表中的数据包
		write_msg_list_.flush();

		for (int i = write_msg_list_.count() - 1; i > -1; --i)
		{
			write_msg_list_[i]->~DataPacket();
		}

		write_msg_list_.empty();

		//销毁空闲列表中的数据包
		for (int i = free_msg_list_.count() - 1; i > -1; --i)
		{
			free_msg_list_[i]->~DataPacket();
		}

		free_msg_list_.empty();

		//释放数据包内存
		for (int i = pack_list_.count() - 1; i > -1; --i)
		{
			allocator_.FreeBuffer(pack_list_[i]);
		}

		pack_list_.empty();
	}

	void addMsg(SHAREOUTPUTMSGTYPE eMsgType, const char* sText, int)
	{
		static const int PackBlockSize = 256;
		DataPacket* msg_pack;

		free_msg_list_.lock();
		int cnt = free_msg_list_.count();

		//如果空闲数据包队列没有数据了则申请PackBlockSize个数据包
		if (cnt <= 0)
		{
			msg_pack = (DataPacket*)allocator_.AllocBuffer(sizeof(*msg_pack) * PackBlockSize);
			pack_list_.add(msg_pack);

			for (int i = 0; i < PackBlockSize; ++i)
			{
				new(msg_pack)DataPacket(&allocator_);
				free_msg_list_.add(msg_pack);
				msg_pack++;
			}

			cnt = PackBlockSize;
		}

		//从空闲数据包队列中取出最后一个
		cnt--;
		msg_pack = free_msg_list_[cnt];
		free_msg_list_.trunc(cnt);
		free_msg_list_.unlock();

		//清空数据
		msg_pack->setPosition(0);
		//写入消息类型
		*msg_pack << eMsgType;
		//写入时间
		//写入消息内容
		msg_pack->writeString(sText);
		//数据包追加到写数据列表中
		write_msg_list_.append(msg_pack);
	}

protected:
	void OnRoutine()
	{
		while (!terminated())
		{
			ProcessMessages();
			Sleep(16);
		}
	}

	//处理所有日志记录
	void ProcessMessages()
	{
		write_msg_list_.flush();

		int cnt = write_msg_list_.count();

		if (cnt > 0)
		{
			SystemTime sysTime;
			GetSystemTime(sysTime);

			char fn[256];

			SNPRINTFA(fn, sizeof(fn_) - 1, "%s%d%d%d.txt", fn_, sysTime.year_, sysTime.mon_, sysTime.mday_);

			FILE* fp = fopen(fn, "a+");

			for (int i = 0; i < cnt; ++i)
			{
				SHAREOUTPUTMSGTYPE msgType;
				const char* log_msg;
				DataPacket& pack = *(write_msg_list_[i]);
				pack.setPosition(0);
				pack >> msgType;
				pack >> log_msg;

				if (log_msg)
				{
					size_t msgLen = strlen(log_msg);
					char sTimeStr[64];
					size_t nTmsLen = SNPRINTFA(sTimeStr, sizeof(sTimeStr), 
						("[%02d-%02d-%02d %02d:%02d:%02d]"), 
						sysTime.year_, sysTime.mon_, sysTime.mday_, sysTime.hour_, sysTime.min_, sysTime.sec_);
					//向文件写入此消息
					writeMessage(fp, msgType, sTimeStr, nTmsLen, log_msg, msgLen);

					//转换为ASC编码
#ifdef _MSC_VER
					char msg_buf[2048];
					size_t msg_len = convertToACP(log_msg, strlen(log_msg), msg_buf, ArrayCount(msg_buf));
					log_msg = msg_buf;
#endif
					//显示此消息
					displayMessage(msgType, sTimeStr, log_msg, msgLen);
				}
			}

			//将写入列表的数据包全部还原回空闲列表中
			free_msg_list_.lock();
			free_msg_list_.addArray(write_msg_list_, cnt);
			write_msg_list_.trunc(0);
			free_msg_list_.unlock();

			if (fp) fclose(fp);
		}
	}

	//向文件写入消息记录
	void writeMessage(FILE* fp, SHAREOUTPUTMSGTYPE, const char* time_str, const size_t, const char* buf, const size_t)
	{
		if (!fp) return;

		fputs(time_str, fp);
		fputs(buf, fp);
		fputs("\r\n", fp);
	}

	//显示日志消息
	void displayMessage(SHAREOUTPUTMSGTYPE msgType, const char* time_str, const char* buf, const size_t)
	{
		printf("%s", time_str);

		switch (msgType)
		{
		case rmWarning:
			printf(("[WRN]"));
			break;

		case rmTip:
			printf(("[TIP]"));
			break;

		case rmError:
			printf(("[ERR]"));
			break;
		default:
			break;
		}

		printf("%s", buf);
		printf("\n");
	}

#ifdef _MSC_VER
	//转换文字编码为ASC
	size_t convertToACP(const char* msg, const size_t len, char* buf, const size_t buf_len)
	{
		WCHAR wbuf[4096];
		int cch = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, msg, (int)len, wbuf, ArrayCount(wbuf) - 1);

		if (cch > 0)
		{
			cch = WideCharToMultiByte(CP_ACP, 0, wbuf, cch, buf, (int)buf_len - 1, NULL, NULL);

			if (cch > 0)
			{
				buf[cch] = 0;
				return cch;
			}
		}
		//本身就是ACP
		else
		{
			cch = (int)(__min(buf_len - 1, len));
			memcpy(buf, msg, cch);
			buf[cch] = 0;
			return cch;
		}

		return 0;
	}
#endif

private:
	BufferAllocator				allocator_;	//内存管理器
	Mutex						write_lock_;	//待写入到文件的消息列表锁
	Mutex						free_lock_;	//空闲消息包列表锁
	QueueList<DataPacket*>		write_msg_list_;	//待写入到文件的消息列表
	LockList<DataPacket*>		free_msg_list_;	//空闲消息包列表
	Vector<DataPacket*>			pack_list_;//消息包列表内存头指针列表
};

OPMToFile*		g_pOPMToFile;
SHAREOUTPUTMSGFN oldOutputMsgFn;

int STDCALL OutputMsgToFileFn(SHAREOUTPUTMSGTYPE MsgType, const char* lpMsg, int nMsgLen)
{
	g_pOPMToFile->addMsg(MsgType, lpMsg, nMsgLen);
	return nMsgLen;
}

FileLogger::FileLogger(const char* sLogFileNamePattern)
{
	if (!g_pOPMToFile)
	{
		g_pOPMToFile = new OPMToFile(sLogFileNamePattern);
		oldOutputMsgFn = SetOutputMsgFn(OutputMsgToFileFn);
	}
}

FileLogger::~FileLogger()
{
	if (g_pOPMToFile)
	{
		SetOutputMsgFn(oldOutputMsgFn);
		delete g_pOPMToFile;
		g_pOPMToFile = NULL;
	}
}


