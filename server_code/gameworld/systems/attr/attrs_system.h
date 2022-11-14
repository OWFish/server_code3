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

	void ClearBaseAttr(AttrSystemId attrSysId);  //��ջ�������
	inline void ClearBaseAttr(int attrSysId) { ClearBaseAttr(AttrSystemId(attrSysId)); }
	//void ClearExaAttr(AttrSystemId attrSysId);  //��ն�������
	//inline void ClearExaAttr(int attrSysId) { ClearExaAttr(AttrSystemId(attrSysId)); }

	void AddBaseAttr(AttrSystemId attrSysId, int type, int value);  //���ӻ�������
	inline void AddBaseAttr(int attrSysId, int type, int value) { AddBaseAttr(AttrSystemId(attrSysId), type, value); }
	//void AddExaAttr(AttrSystemId attrSysId, int type, int value);  //���Ӷ�������
	//inline void AddExaAttr(int attrSysId, int type, int value) { AddExaAttr(AttrSystemId(attrSysId), type, value); }
	void AddExaPower(AttrSystemId attrSysId, int value);  //���Ӷ���ս��
	inline void AddExaPower(int attrSysId, int value) { AddExaPower(AttrSystemId(attrSysId), value); }

	void JoinBaseAttr(Attribute &attr, AttrSystemId attrSysId);
	void JoinBaseAttr(Attribute &attr, AttrSystemId asfrom, AttrSystemId asto);
	void JoinAllBaseAttr(Attribute &attr) { JoinBaseAttr(attr, AttrSystemId(1), AttrSystemId(asCount-1)); }
	//void GetExaAttr(ExAttribute &attr);

	//bool Init(RoleData* data);

	Attribute* GetBaseAttr(AttrSystemId attrSysId);  //����attr����ָ��
	inline Attribute* GetBaseAttr(int attrSysId) { return GetBaseAttr(AttrSystemId(attrSysId)); }

private:
	Attribute base_attr_[AttrSystemId::asCount];
	//ExAttribute exa_attr_[AttrSystemId::asCount];  //��Ҫʱ��ʹ��
	Role* role_;

};