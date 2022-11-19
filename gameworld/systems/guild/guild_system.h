#pragma once
#include "attr/attribute.h"

class Actor;

// 公会系统

class GuildSystem
{
public:
	GuildSystem(Actor* actor);
	~GuildSystem();

	friend class Guild;
public:
	void OnInit();
	void OnLogout();
	void OnLogin(void);

	Attribute* GetAttr() { return &attribute_; }

	int GetGuildId();
	Guild* GetGuildPtr();
	int GetGuildPos();
	const char* GetGuildName() const;

	// 加入公会后的处理
	void OnJoinGuild(Guild* guild, int pos);
	// 离开公会后的处理
	void OnLeftGuild();

	void OnApplyInfo(void);

private:
	void SetGuildPos(int pos, const char* reson);
	void SetGuildInfo(int guildId, const char* name);

private:
	Actor *actor_;
	Attribute attribute_;
	int guild_pos_;
};