#pragma once

class BaseLuaConfig;

class WsGateConfig :
	public BaseLuaConfig {
public:
	WsGateConfig();
	~WsGateConfig();
	static const char ConfigFileName[];	//定义配置文件名称

	//加载并读取服务器服务配置
	bool loadServerConfig(GateServer *gate_srv);

protected:
	void showError(const char* err);
};

