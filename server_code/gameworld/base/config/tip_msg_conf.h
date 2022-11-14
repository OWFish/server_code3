#ifndef _TIP_MSG_CONF_H_
#define _TIP_MSG_CONF_H_

class TIPMSGCONFIG
{
public:
	static const int MAX_COUNT = 1024;
	char data_[MAX_COUNT][256];
	int count_;
	/*
	* Comments: ͨ��ϵͳ��ʾ��ID��ȡϵͳ��ʾ������
	*/
	inline const char *GetTip(int id)
	{
		if(id <0 || id >= count_ ) 
			return NULL;
		else return data_[id];		
	}
public:
	static TIPMSGCONFIG* config_;
};



#endif


