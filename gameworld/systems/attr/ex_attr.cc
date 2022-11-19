#include "StdAfx.h"
#include "ex_attr.h"


ExAttribute::ExAttribute()
{
	Reset();
}

ExAttribute::ExAttribute(const ExAttribute& attrs)
{
	memcpy(values_, attrs.values_, sizeof(values_));
}

ExAttribute& ExAttribute::operator= (const ExAttribute& attrs)
{
	memcpy(values_, attrs.values_, sizeof(values_));
	return *this;
}

ExAttribute& ExAttribute::operator+= (const ExAttribute& otherAttrs)
{
	for (int i = 0; i < eatCount; ++i)
		values_[i] += otherAttrs.values_[i];
	return *this;
}


ExAttribute& ExAttribute::operator*= (float rate)
{
	for (int i = 0; i < eatCount; ++i)
		values_[i] = (int)(values_[i] * rate);
	return *this;
}

void ExAttribute::Add(int type, int value)
{
	if (type < 0 || type >= eatCount) return;
	values_[type] += value;
}

void ExAttribute::Set(int type, int value)
{
	if (type < 0 || type >= eatCount) return;
	values_[type] = value;
}

int ExAttribute::Get(int type)
{
	if (type < 0 || type >= eatCount) return 0;
	return values_[type];
}

void ExAttribute::GetValues(int data[]) const
{
	memcpy(data, values_, sizeof(values_));
}