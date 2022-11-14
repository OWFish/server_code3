#pragma  once
#include "../item.h"


class Equip : public Item
{
public:
	friend class ItemPoll;
	~Equip();

	void AddAttr(Attribute& attr);
	void AddExAttr(ExAttribute& ex_attr);
	inline const EquipConfig* GetConfig(void) { return equip_config_; };

	virtual bool Init();

private:
	const EquipConfig*	equip_config_;
	float GetRange();
};