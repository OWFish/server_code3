#pragma once

#include "attr/attribute.h"
#include "attr/ex_attr.h"
#include "common/system_param_def.h"

//class Role;
class AttrsSystem
{
public:
	AttrsSystem(Role* role);
	~AttrsSystem();

	void ClearBaseAttr(AttrSystemId attrSysId);  //清空基本属性
	inline void ClearBaseAttr(int attrSysId) { ClearBaseAttr(AttrSystemId(attrSysId)); }
	//void ClearExaAttr(AttrSystemId attrSysId);  //清空额外属性
	//inline void ClearExaAttr(int attrSysId) { ClearExaAttr(AttrSystemId(attrSysId)); }

	void AddBaseAttr(AttrSystemId attrSysId, int type, int value);  //增加基本属性
	inline void AddBaseAttr(int attrSysId, int type, int value) { AddBaseAttr(AttrSystemId(attrSysId), type, value); }
	//void AddExaAttr(AttrSystemId attrSysId, int type, int value);  //增加额外属性
	//inline void AddExaAttr(int attrSysId, int type, int value) { AddExaAttr(AttrSystemId(attrSysId), type, value); }
	void AddExaPower(AttrSystemId attrSysId, int value);  //增加额外战力
	inline void AddExaPower(int attrSysId, int value) { AddExaPower(AttrSystemId(attrSysId), value); }

	void JoinBaseAttr(Attribute &attr, AttrSystemId attrSysId);
	void JoinBaseAttr(Attribute &attr, AttrSystemId asfrom, AttrSystemId asto);
	void JoinAllBaseAttr(Attribute &attr) { JoinBaseAttr(attr, AttrSystemId(1), AttrSystemId(asCount-1)); }
	//void GetExaAttr(ExAttribute &attr);

	//bool Init(RoleData* data);

	Attribute* GetBaseAttr(AttrSystemId attrSysId);  //返回attr对象指针
	inline Attribute* GetBaseAttr(int attrSysId) { return GetBaseAttr(AttrSystemId(attrSysId)); }

private:
	Attribute base_attr_[AttrSystemId::asCount];
	//ExAttribute exa_attr_[AttrSystemId::asCount];  //需要时再使用
	Role* role_;

};