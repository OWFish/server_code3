#pragma once
#include "attr/attribute.h"

class Actor;

// ����ϵͳ

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

	// ���빫���Ĵ���
	void OnJoinGuild(Guild* guild, int pos);
	// �뿪�����Ĵ���
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