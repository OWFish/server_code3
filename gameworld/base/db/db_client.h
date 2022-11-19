#ifndef _DB_CLIENT_H_
#define	_DB_CLIENT_H_

/***
	������Ҫ�����߼��������������ݷ���������������Ϣ
*/

class GameServer;

class DBClient:
	public NetClient
{
public:
	DBClient(GameServer* pLogicServer);
	~DBClient();
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
	inline void SendDbServerData(int cmd, const T& data)
	{
		DataPacket& pack = allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(&data, sizeof(data));
		flushProtoPacket(pack);
	}

	virtual bool Startup();
	virtual void Stop();
	virtual bool ConnectToServer();

	//�ȴ����ݷ��ͻ�ת�����
	void WaitFor();

	// ���տ��е�CDataPacket��
	void FreeBackUserDataPacket(DataPacket* pack);

	// �����¸���ĺ�������Щ�����õĴ���
	DataPacket& allocProtoPacket(uint16_t cmd);

	// ����ڴ�ռ�����
	void printStat();

	void SetServerId(int sid)
	{
		serverId_ = sid;
	}
	int GetServerId()
	{
		return serverId_;
	}
protected:
	// ������ʵ�ֻ�����麯��
	virtual void OnRecv(const uint16_t cmd, char* buf, int size);

	virtual int GetLocalServerType();

	/* ���ѯ���ط����������ƣ��Ա���ȷ�ķ���ע������ */
	virtual const char* GetLocalServerName();
	/* ���ѯ���ط�����ID���Ա���ȷ�ķ���ע�����ݣ�Ĭ�ϵķ���ֵ��0 */
	virtual int GetLocalServerIndex();

	GameServer* game_server_;

	//�ṩ��������߼�֪ͨ���ӽ������¼�
	virtual void OnConnected();
private:
	// ����һ��������������ݸ���Ϸ���߼�����
	DataPacket* AllocPostPacket();

private:
	QueueList<DataPacket*>			free_;	//������ſ��е����ݰ�
	Mutex							lock_;

	int dbg_list_[0xffff];

	int								serverId_;

	time_t	select_time_out_;
};
#endif

