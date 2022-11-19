#ifndef _GATE_CONNECTION_H_
#define _GATE_CONNECTION_H_

class GateManager;
class GateUser;

using namespace container;

class GateSession
	: public NetSession
{
	friend class GateManager;
public:
	typedef NetSession Inherited;

public:

	DataPacket& AllocGateSendPacket(uint16_t cmd, NetId& netid);
	DataPacket& AllocGateSendPacket(NetId& netid);

	inline void PostCloseUser(NetId& netid, int accountId, const char* reason, int p1 = 0, int p2 = 0)
	{
		OutputMsg(rmWarning, "GateSession::PostCloseUser %s:%d:%d", reason ? reason : "", p1, p2);

		PostMsg(CLOSE_GATE_SESSION, LOINT32(netid.socket_), HIINT32(netid.socket_), MAKEINT32(netid.index_, netid.gate_id_), accountId);
	}

	GateUser* GetUser(NetId& netid);

protected:
	virtual void OnOpenUser(GateUser* user);
	virtual void OnCloseUser(GateUser* user, const char* reason);

	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA regData);

protected:
	void Disconnected();
	void OnRecvSysMsg(unsigned int msg, size_t p1, size_t p2, size_t p3, size_t p4);
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	NetId* OpenNewUser(NetId& netid, const char* addr);
	bool CloseUser(NetId& netid, const char* reason);

	void CloseAllUser();

	virtual void OnRecv(NetId& netid, char* buf, int size) = 0;

	void SendGateCloseUser(NetId& netid);

	void FreeBuffers();
public:
	GateSession(const char* name);
	~GateSession();

protected:
	static const int MAX_GATE_USER = 8192;	//最大网关用户数
	static const unsigned int CLOSE_GATE_SESSION = 102;

	int	gate_idx_;			//网关编号
	GateUser user_list_[MAX_GATE_USER];
};

#endif
