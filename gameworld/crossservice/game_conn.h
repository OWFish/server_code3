#ifndef _GAME_CONN_H_
#define _GAME_CONN_H_

class GameConnMgr;
class DataPacket;

class GameConn
	: public NetSession
{
	friend class GameConnMgr;
public:
	typedef NetSession Inherited;
public:
	GameConn(GameConnMgr* mgr, SOCKET s, sockaddr_in* addr);
	~GameConn();

	inline const char* serverName()
	{
		return srv_name_;
	}

	int GetTargetSid()
	{
		return target_sid_;
	}

	void SetTargetSid(int sid)
	{
		target_sid_ = sid;
	}
	void SetBattleFlag(int flag)
	{
		is_battle_ = flag;
	}
	int GetBattleFlag()
	{
		return is_battle_;
	}
protected:
	//�������ӶϿ��ĺ���
	void OnDisconnected();

	void OnRecvSysMsg(UINT uMsg, size_t uParam1, size_t uParam2, size_t uParam3, size_t uParam4);

	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	virtual bool OnValidateRegData(const SrvDef::PSERVER_REGDATA pRegData);
protected:

	virtual void OnRun();
private:
	void OnRegReq(DataPacketReader& reader);
	void OnGatewayInfo(DataPacketReader& reader);

	void OnUserLogin(DataPacketReader& reader);
	void OnUserExit(DataPacketReader& reader);
	void OnCloseUser(DataPacketReader& reader);
	void OnBatchLogin(DataPacketReader& reader);
	void OnKeyReq(DataPacketReader& reader);
	void OnKeyResp(DataPacketReader& reader);
	void OnCommonMssg(DataPacketReader& reader);
	void OnTtDataToGame(DataPacketReader& reader, uint16_t cmd);
	// �������ظ���¼
	void OnCrossRelogin(DataPacketReader &reader);
private:
	char						srv_name_[128];
	GameConnMgr*				client_mgr_;			//�������ݷ�����

	int							target_sid_;
	int							is_battle_;		// �Է��Ƿ�ս����
};

#endif

