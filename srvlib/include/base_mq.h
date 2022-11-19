#ifndef _BASE_MQ_H_
#define _BASE_MQ_H_

#include "os_def.h"
#include "container/binary_list.h"


template <typename MSG_T, typename RESP_T>
class BaseMQ
{
public:

	struct MsgData
	{
		uint64_t id_;
		MSG_T msg_;
		time_t timeout_;
		//重载相等判断的运算符
		inline bool operator == (const MsgData& data) const
		{
			return id_ == data.id_;
		}
		//重载不等判断的运算符
		inline bool operator != (const MsgData& data) const
		{
			return id_ != data.id_;
		}
		inline bool operator > (const MsgData& data) const
		{
			return id_ > data.id_;
		}
		inline bool operator >= (const MsgData& data) const
		{
			return id_ >= data.id_;
		}
		inline bool operator < (const MsgData& data) const
		{
			return id_ < data.id_;
		}
		inline bool operator <= (const MsgData& data) const
		{
			return id_ <= data.id_;
		}
	};

	BaseMQ():msgid_(0xffffffff), timeout_t_(10)
	{
	}

	BaseMQ(int timeout):msgid_(0xffffffff), timeout_t_(timeout)
	{
	}

	virtual ~BaseMQ()
	{

	}

	void Run()
	{
		time_t curr_t = NOW_T;
		for (int i = msg_list_.count() - 1; i >= 0; --i)
		{
			MsgData& data = msg_list_[i];
			if (curr_t > data.timeout_)
			{
				msg_list_.remove(i);
			}
		}
	}

	uint64_t AddMsg(MSG_T& msg)
	{
		++msgid_;

		MsgData data;
		data.msg_ = msg;
		data.id_ = msgid_;
		data.timeout_ = NOW_T + timeout_t_;

		msg_list_.add_item(data);

		return msgid_;
	}

	void RemoveMsg(uint64_t id)
	{
		MsgData data;
		data.id_ = id;
		msg_list_.remove_item(data);
	}

	void RecvResp(uint64_t id, RESP_T& resp)
	{
		MsgData data;
		data.id_ = id;
		int idx = msg_list_.find(data);
		if (idx >= 0)
		{
			MsgData& msg_data = msg_list_[idx];
			OnResp(msg_data.msg_, resp);
			msg_list_.remove(idx);
		}
	}

	virtual void OnResp(MSG_T& data, RESP_T& resp) = 0;

private:
	uint64_t msgid_;
	int	timeout_t_;
	BinaryList<MsgData>	msg_list_;
};

#endif
