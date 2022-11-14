#include "StdAfx.h"
#include "ws_gate_config.h"

const char WsGateConfig::ConfigFileName[] = ("GateWay.txt");

WsGateConfig::WsGateConfig(){
}


WsGateConfig::~WsGateConfig() {

}

void WsGateConfig::showError(const char* err) {
	SetErrDesc(err);
	RefString s = ("[Config Error]");
	s += err;
	throw s;
}

bool WsGateConfig::loadServerConfig(GateServer * gate_srv)
{
	using namespace stream;

	MemoryStream ms(NULL);

	try	{
		if (ms.loadFromFile(ConfigFileName) <= 0) {
			showError("unable to load config from file GateWay.txt");
			return false;
		}

		if (!setScript((const char*)ms.getMemory())) {
			showError("parse config script failed");
			return false;
		}

		if (openGlobalTable("GateServer")) {
			if (enumTableFirst()) {
				char str[32];
				GameClientMgr* gcmgr = NULL;
				do {
					if (openFieldTable("LocalService")) {
						
						getFieldStringBuffer(("ServerName"), str, sizeof(str));
						gcmgr = gate_srv->AddGameClientMgr(str);
						
						getFieldStringBuffer(("Address"), str, sizeof(str));
						gcmgr->SetServiceHost(str);

						int port = getFieldInt("Port");
						gcmgr->SetServicePort(port);
						gcmgr->SetMaxSession(getFieldInt("MaxSession"));

						closeTable();
					}

					if (gcmgr && openFieldTable("BackServer")) {
						getFieldStringBuffer(("Host"), str, sizeof(str));
						int port = getFieldInt("Port");

						gcmgr->InitGameWorldClient(str, port);
						closeTable();
					}

				} while (enumTableNext());
			}

			closeTable();
		}
	} catch (RefString& s) {
		OutputMsg(rmNormal, s.rawStr());
	} catch (...) {
		MSG_ERR("unexpected error on load config");
	}

	return true;
}
