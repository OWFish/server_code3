#ifndef _GAME_CLIENT_H_
#define	_GAME_CLIENT_H_

/***
	������Ҫ������������gameworld����������Ϣ����Ҫ������վ
*/

class GameServer;

class GameClient:
	public NetClient
{
public:
	GameClient(GameServer* game);
	~GameClient();
public:
	// ���º��������߼������������ݷ��������Ͳ�ѯ��Ϣ

	/*
	* Comments: ��db���������ͼ򵥵�����
		����Ǹ�������ʹ�� allocProtoPacket��Ȼ��д�����ݣ���flushProtoPacket
	* Param int nCmd: ������,��dcLoadQuest
	* Param T data: ���ݣ��������κ����͵�
	* @Return void:
	*/
	template<class T>
	inline void SendDbServerData(int cmd, T& data)
	{
		DataPacket& pack = allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(&data, sizeof(data));
		flushProtoPacket(pack);
	}

	// ���տ��е�CDataPacket��
	void FreeBackUserDataPacket(DataPacket* pack);

	// �����¸���ĺ�������Щ�����õĴ���
	DataPacket& allocProtoPacket(uint16_t cmd);

	// ����ڴ�ռ�����
	void printStat();

	void SetTargetSid(int sid)
	{
		target_sid_ = sid;
	}

	bool IsLianfuClient();

	int GetTargetSid()
	{
		return target_sid_;
	}
	//void SetGateMgr(GameGateMgr* mgr)
	//{
	//	gate_mgr_ = mgr;
	//}
protected:
	// ������ʵ�ֻ�����麯��
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	virtual int GetLocalServerType();

	/* ���ѯ���ط����������ƣ��Ա���ȷ�ķ���ע������ */
	virtual const char* GetLocalServerName();
	/* ���ѯ���ط�����ID���Ա���ȷ�ķ���ע�����ݣ�Ĭ�ϵķ���ֵ��0 */
	virtual int GetLocalServerIndex();

	//�ṩ��������߼�֪ͨ���ӽ������¼�
	virtual void OnConnected();
	virtual void OnDisconnected();
private:
	// ����һ��������������ݸ���Ϸ���߼�����
	DataPacket* AllocPostPacket();
	void OnGatewayInfo(DataPacketReader& reader);
	void OnRegResp(DataPacketReader& reader);
	void OnUserLogin(DataPacketReader& reader);
	void OnUserExit(DataPacketReader& reader);
	void OnBatchLogin(DataPacketReader& reader);
	void OnCloseUser(DataPacketReader& reader);
	void OnKeyReq(DataPacketReader& reader);
	void OnKeyResp(DataPacketReader& reader);
	void OnCommonMsg(DataPacketReader& reader);
	void OnTtDataToGame(DataPacketReader& reader, uint16_t cmd);
private:
	QueueList<DataPacket*>			free_;	//������ſ��е����ݰ�
	Mutex							lock_;
	int								target_sid_;	// ���ӵĶԷ���gameworld��serverid
	int								is_battle_;		// �Է��Ƿ�ս����
	GameServer* game_server_;
	//GameGateMgr*			    gate_mgr_;
};
#endif

