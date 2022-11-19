#pragma once


class Role;
class Item;
class Equip;
class Attribute;
class ExAttribute;
class ImbaSystem
{
public:
	ImbaSystem(Actor* actor);
	~ImbaSystem();

	void Destroy();

	bool Init();

	void Save();

	const Attribute& GetBattleAttr() { return attribute_; }
	void AddAttr(int type, int value);
	void AddExAttr(int type, int value);
	void ClearAttr();

	void ClearActId() { act_id_.clear(); }
	void AddActId(int id) { act_id_.insert(id); }
	bool IsActId(int id) { return act_id_.find(id) != act_id_.end(); }
	void appendActId(std::set<int> &set) {
		set.clear();
		set.insert(act_id_.begin(), act_id_.end());
	}

	Attribute* GetAttr() { return &attribute_; }
	ExAttribute& GetExAttr() { return ex_attribute_; }


private:
	Actor*	actor_;
	Attribute attribute_;
	ExAttribute ex_attribute_;
	std::set<int> act_id_;
};

