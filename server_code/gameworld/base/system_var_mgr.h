#ifndef SYSTEM_VAR_MGR_H
#define SYSTEM_VAR_MGR_H

struct SysVar
{
	ActorId		id_;
	ACTORNAME	name_;
	int			sysId_;
	CLVariant	var_;
};

#define SYS_VAR_COUNT 100000

class SysVarMgr
{
public:
	SysVarMgr();

	typedef memory::Handle SysVarHandle;
	typedef memory::HandleMgr<SysVar, SysVarHandle> SysVarHdlMgr;

	// ��������
	void Load();
	// �����Ƿ��������
	inline bool isLoad()
	{
		return sysVarCount_ == curSysVarCount_;
	}
	// ��ȡ����
	void OnDbReturnData(int cmd, DataPacketReader& reader);
	// ��������
	unsigned int createSysVar(int ownerId, const char* ownerName, int type);
	// ��ȡ����ָ��
	inline SysVar* getPtrByHandle(unsigned int hdl)
	{
		return mgr_.GetPtr(hdl);
	}
	// ��������
	void saveSysVar(int ownerId, int type, unsigned int hdl);
	// ���¼�������
	void reloadSysVar();
	// ����
	void Destroy();
	// �������
	void clearSysVar();

	container::Vector<CLVariant*>& getTmpList()
	{
		return tmpList_;
	}

private:
	SysVarHdlMgr mgr_;
	container::Vector<SysVarHandle> list_;
	int sysVarCount_;
	int curSysVarCount_;

	container::Vector<CLVariant*> tmpList_;
};

#endif
