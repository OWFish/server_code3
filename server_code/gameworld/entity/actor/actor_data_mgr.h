#pragma once

#include <map>
#include <vector>


struct ActorBasicData;
class ActorDataMgr
{
	friend Actor;
public:
	ActorDataMgr(){}
	~ActorDataMgr(){}

	void Destroy();
	bool Load();
	size_t GetSize() { return data_list_.size(); }
	const ActorBasicData* GetData(int id) const;
	int GetId(const char* name);
	int GetIdByAccountName(const char* name);
	int getActorIdByName(const char* name);
	
	const std::vector<ActorBasicData*>& GetDatas() { return data_list_; }

private:
	ActorBasicData* GetData(int id);

private:
	std::map<int, int>			  data_index_;
	std::map<const char*, int>	  name_index_;
	std::vector<ActorBasicData*>  data_list_;
};