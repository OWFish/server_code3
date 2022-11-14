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

	// 加载数据
	void Load();
	// 数据是否加载完整
	inline bool isLoad()
	{
		return sysVarCount_ == curSysVarCount_;
	}
	// 读取数据
	void OnDbReturnData(int cmd, DataPacketReader& reader);
	// 创建数据
	unsigned int createSysVar(int ownerId, const char* ownerName, int type);
	// 获取数据指针
	inline SysVar* getPtrByHandle(unsigned int hdl)
	{
		return mgr_.GetPtr(hdl);
	}
	// 保存数据
	void saveSysVar(int ownerId, int type, unsigned int hdl);
	// 重新加载数据
	void reloadSysVar();
	// 销毁
	void Destroy();
	// 清除数据
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
