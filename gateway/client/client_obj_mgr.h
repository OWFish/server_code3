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
	uint16_t max_session_;//最大客户端连接数
	uint16_t cur_idx_;
	std::list<uint16_t> free_cli_idx_;//空闲的客户端索引
	std::vector<Client*> client_append_list_;
	Mutex client_lock_;		//客户端列表锁给append_list用
	std::map<uint16_t, Client*> client_list_;
};

