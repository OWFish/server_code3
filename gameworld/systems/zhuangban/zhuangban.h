#pragma once
#include "attr/attribute.h"

class Role;

struct ZhuangBanData
{
	int pos1id = 0;
	int pos2id = 0;
	int pos3id = 0;
};

class ZhuangBanSystem
{
public:
	ZhuangBanSystem(Role* role): role_(role) {}
	~ZhuangBanSystem() {}

	inline Attribute* GetAttr() { return &attribute_; }
	inline Role* getRole() { return role_; }
	inline ZhuangBanData* GetZhuangBanData() { return &data_; }

private:
	Role*	  role_;
	Attribute attribute_;
	ZhuangBanData data_;
};
