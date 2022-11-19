#ifndef _GLOBAL_VAR_MGR_H_
#define _GLOBAL_VAR_MGR_H_

/****************************************
	�ṩ���ű�����ȫ�����ݵ����
*****************************************/

#include "timer.h"

class GlobalVarMgr
{
public:
	/*
	* Comments:��db��ȡ����
	* @Return void:
	*/
	void Load();

	/*
	* Comments:���ڼ��
	* @Return void:
	*/
	void RunOne(int64_t now_t);

	//����
	void Save();

	inline void Destroy()
	{
		var_.clear();
	}

	//��ȡ��������
	inline CLVariant& GetVar()
	{
		return var_;
	}

public:
	GlobalVarMgr();
	~GlobalVarMgr();
private:
	CLVariant var_;
	bool inited_;	//�Ƿ��Ѿ���������
	Timer timer_;	//
};

#endif

