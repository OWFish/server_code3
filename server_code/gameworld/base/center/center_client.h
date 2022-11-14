#ifndef _CENTER_CLIENT_H_
#define	_CENTER_CLIENT_H_

/***
	������Ҫ�����߼��������������ķ���������������Ϣ
*/

class GameServer;

class CenterClient:
	public NetClient
{
public:
	CenterClient(GameServer* srv);
	~CenterClient();
public:
	/*
	* Comments: ����������ͼ򵥵�����
		����Ǹ�������ʹ�� allocProtoPacket��Ȼ��д�����ݣ���flushProtoPacket
	* Param int nCmd: ������,��dcLoadQuest
	* Param T data: ���ݣ��������κ����͵�
	* @Return void:
	*/
	template<class T>
	inline void SendServerData(int cmd, const T& data)
	{
		DataPacket& pack = allocProtoPacket((uint16_t)cmd);
		pack.writeBuf(&data, sizeof(data));
		flushProtoPacket(pack);
	}


	// ���տ��е�CDataPacket��
	void FreeBackUserDataPacket(DataPacket* pack);

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
	int								serverId_;
};
#endif

