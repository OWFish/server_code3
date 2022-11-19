#pragma once

class GameClientMgr;

class GateServer {
public:
	GateServer();
	~GateServer();

	//启动服务器
	bool StartServer();
	//停止服务器
	void StopServer();

	//获取同步的逻辑短日期时间值
	inline unsigned int getMiniDateTime() {
		GetSystemTime(cur_sys_time_);
		now_sec_.encode(cur_sys_time_); 
		return now_sec_;
	}
	
	GameClientMgr* AddGameClientMgr(const char *name);

public:
	static GateServer* Instance;

private:
	std::vector<GameClientMgr*> game_client_mgr_;//游戏客户端管理类
	SystemTime cur_sys_time_;
	SecondTime now_sec_; //当前短日期时间
};