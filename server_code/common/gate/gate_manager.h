#ifndef _GATE_MANAGER_H_
#define _GATE_MANAGER_H_

class GateSession;

using namespace container;

class GateManager
	: public ServerSocket
{
public:
	typedef ServerSocket Inherited;
	static const int MaxGateCount = 1;

public:
	GateManager(const char* name);
	~GateManager();

	virtual void Initialize() = 0;
	virtual void Uninitialize() = 0;

	bool Startup();

	inline GateSession* GetGate(int idx)
	{
		if (idx >= 0 && idx < (int)ArrayCount(gate_list_))
			return gate_list_[idx];

		return NULL;
	}

	inline GateUser* GetUser(NetId& netid)
	{
		GateSession* gate = GetGate(netid.gate_id_);
		return gate ? gate->GetUser(netid) : NULL;
	}

	inline void PostCloseUser(NetId& netid, const char* reason, int p1 = 0, int p2 = 0)
	{
		OutputMsg(rmWarning, "GateManager::PostCloseUser %s:%d:%d", reason ? reason : "", p1, p2);

		GateSession* gate = GetGate(netid.gate_id_);

		if (gate)
		{
			gate->PostCloseUser(netid, 0, reason, p1, p2);
		}
	}

protected:
	NetSession* NewSession(SOCKET socket, sockaddr_in* addrin);
	void DestroySession(NetSession* client);

protected:
	GateSession* gate_list_[MaxGateCount];	//Íø¹ØÁÐ±í
};


#endif

