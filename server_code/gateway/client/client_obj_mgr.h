#pragma once
#include <map>
class ClientObjMgr {
public:
	ClientObjMgr();
	~ClientObjMgr();

	void SetMaxSession(int max_session);
	bool setNewClient(Client *cli);
	void flush(void);
	std::map<uint16_t, Client*> &getClientMap(void) {
		return client_list_;
	}
	Client* get(uint16_t index);
	Client* remove(uint16_t index);
private:
	uint16_t max_session_;//���ͻ���������
	uint16_t cur_idx_;
	std::list<uint16_t> free_cli_idx_;//���еĿͻ�������
	std::vector<Client*> client_append_list_;
	Mutex client_lock_;		//�ͻ����б�����append_list��
	std::map<uint16_t, Client*> client_list_;
};

