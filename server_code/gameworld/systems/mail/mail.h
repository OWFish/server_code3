#pragma once
#include "db/mail_data.h"


class Mail
{
public:
	friend class MailPool;
	Mail(){};
	virtual ~Mail(){};

	virtual bool	Init(){ return true; };

	int GetUId() { return data_.uid; }
	void setUId(int uid){ data_.uid = uid; }

	const MailData& GetMailData(){ return data_; }
	void changeReadStatus(int status){ data_.readStatus = status; }
	void changeAwardStatus(int status){ data_.awardStatus = status; }

	void	WriteData(DataPacket &pack) { data_.writeData(pack); }
	void	WriteData(void *data) { memcpy(data, &data_, sizeof(MailData)); }
	void	ReadData(DataPacket &pack) { data_.readData(pack); }


protected:
	MailData				data_;			// 物品数据
};


