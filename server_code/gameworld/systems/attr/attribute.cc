#include "StdAfx.h"
#include "attribute.h"


Attribute::Attribute()
{
	Reset();
}

Attribute::Attribute(const Attribute& attrs)
{
	memcpy(values_, attrs.values_, sizeof(values_));
	extra_power_ = attrs.extra_power_;
}

Attribute& Attribute::operator= (const Attribute& attrs)
{
	memcpy(values_, attrs.values_, sizeof(values_));
	extra_power_ = attrs.extra_power_;
	return *this;
}

Attribute& Attribute::operator+= (const Attribute& otherAttrs)
{
	for (int i = 0; i < atCount; ++i)
		values_[i] += floor(otherAttrs.values_[i]);
	extra_power_ += floor(otherAttrs.extra_power_);
	return *this;
}


Attribute& Attribute::operator*= (float rate)
{
	for (int i = 0; i < atCount; ++i)
		values_[i] = floor(values_[i] * rate);
	extra_power_ = floor(extra_power_ * rate);
	return *this;
}

void Attribute::Add(AttributeType type, double value)
{
	if (type < 0 || type > atCount) return;
	values_[type] += floor(value);
}

void Attribute::Set(AttributeType type, double value)
{
	if (type < 0 || type > atCount) return;
	values_[type] = floor(value);
}

double Attribute::Get(AttributeType type)
{
	if (type < 0 || type > atCount) return 0;
	return floor(values_[type]);
}

void Attribute::GetValues(double data[]) const
{
	memcpy(data, values_, sizeof(values_));
}