#pragma once


class Role;
class Item;
class Equip;
class Attribute;
class ExAttribute;
class GodWeaponSystem
{
public:
	GodWeaponSystem(Actor* actor);
	~GodWeaponSystem();

	void Destroy();

	bool Init();

	void Save();

	const Attribute& GetBattleAttr() { return attribute_; }
	void AddAttr(int type, int value);
	void AddExAttr(int type, int value);
	void ClearAttr();

	void ClearActId() { weapon_list_.clear(); }
	void AddActId(int idx, int id);
	bool IsActId(int id) { return weapon_list_.find(id) != weapon_list_.end(); }
	const std::set<int>* getIdList(int idx);
	void setPeak(int peak) { peak > 0 ? isPeak_ = true: isPeak_ = false; };
	bool getPeak() { return isPeak_; };
	void setLevel(int level) { level_ = level; };
	int getLevel() { return level_; };
	void setPower(int job, int power);
	int getPower(int job);
	void clearPower() { memset(ex_power_, 0, sizeof(ex_power_)); };

	void appendActId(std::map<int, std::set<int>>& list) {
		list.clear();
		list.insert(weapon_list_.begin(), weapon_list_.end());
	}

	Attribute* GetAttr() { return &attribute_; }
	ExAttribute& GetExAttr() { return ex_attribute_; }


private:
	Actor*	actor_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
	bool isPeak_;//是否开启巅峰技能
	int level_; //神兵总等级
	std::map<int, std::set<int>> weapon_list_;
	int ex_power_[JobType_Max];
};

