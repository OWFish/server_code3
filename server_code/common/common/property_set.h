#ifndef _PROPERTY_SET_H_
#define _PROPERTY_SET_H_

#include "common.h"
#include "property_id_def.h"

#pragma  pack(4)

// 暂时支持32*8个属性，最大只能255个属性， 因为个别地方用uint8_t表示属性的数量
static const unsigned int MAX_BYTE = 32;
static char s_forbit_mask[MAX_BYTE] = {};

class UpdateMask
{
public:
	UpdateMask(): used_count_(0), mask_count_(0)
	{
		memset(lock_, 0, sizeof(lock_));
		clear();
	}

	inline void clear()
	{
		memset(mask_, 0, sizeof(mask_));
		used_count_ = 0;
		mask_count_ = 0;
	}

	inline UpdateMask& operator &= (UpdateMask& mask)
	{
		int count = __max(used_count_, mask.count());

		if (count == 0) return  *this;

		int max_count = 0;
		unsigned char* s = mask;

		for (int i = 0; i < count; ++i)
		{
			mask_[i] &= s[i];

			if (mask_[i]) max_count = i + 1;
		}

		used_count_ = max_count;
		mask_count_ = 0;
		int total = used_count_ << 3;

		for (int i = 0; i < total; ++i)
		{
			if (IsMask(i)) ++mask_count_;
		}

		return *this;
	}

	/*
	*设置第nPos个int是否修改过
	* nPos 第几个4字节
	* flag flag=true表示修改过,否则去掉这个修改标记
	*/
	inline void SetMask(int pos/*, bool flag = true*/)
	{
		if (IsForbid(pos)) return;   // 禁止更新

		unsigned int bit_pos = pos & 7;
		unsigned int byte_pos = pos >> 3;

		if (byte_pos >= MAX_BYTE) return;

		unsigned char value = 1 << bit_pos;
		//if (flag)
		{
			if (!(mask_[byte_pos] & value)) ++mask_count_;

			mask_[byte_pos] |= value;
		}

		//else
		//{
		// 如果原来就是masked，mask_count要减一
		//	if (mask_[byte_pos] & value){ assert(mask_count_ > 0);--mask_count_;}
		//	value = ~value;
		//	mask_[byte_pos] &= value;
		//}
		if (used_count_ <= byte_pos)
			used_count_ = byte_pos + 1;
	}

	//第nPos个int是否修改过
	inline bool IsMask(int pos)
	{
		unsigned int bit_pos = pos & 7;
		unsigned int byte_pos = pos >> 3;

		if (byte_pos >= MAX_BYTE) return false;

		unsigned char value = 1 << bit_pos;
		return mask_[byte_pos] & value ? true : false;
	}

	inline unsigned int count()
	{
		return used_count_;
	}
	inline unsigned int MaskCount()
	{
		return mask_count_;
	}

	inline operator unsigned char* ()
	{
		return mask_;
	}

	static void SetArrayBit(char* arr, int pos, bool flag)
	{
		unsigned int bit_pos = pos & 7;
		unsigned int byte_pos = pos >> 3;

		if (byte_pos >= MAX_BYTE) return;

		unsigned char value = 1 << bit_pos;

		if (flag) //让其成立
		{
			arr[byte_pos] |= value;
		}
		else
		{
			value = ~value; //取反
			arr[byte_pos] &= value; //按位与
		}
	}

	static bool IsArrayBit(char* arr, int pos)
	{
		unsigned int bit_pos = pos & 7;
		unsigned int byte_pos = pos >> 3;

		if (byte_pos >= MAX_BYTE) return false;

		unsigned char value = 1 << bit_pos;
		return arr[byte_pos] & value ? true : false;
	}

	//设置禁止更新的属性的位
	static void SetForbid(int pos, bool flag)
	{
		SetArrayBit(s_forbit_mask, pos, flag);
	}

	//某个位置是否禁止更新
	inline bool IsForbid(int pos)
	{
		return IsArrayBit(s_forbit_mask, pos);
	}

	inline bool IsLock(int pos)
	{
		return IsArrayBit(lock_, pos);
	}

	void Lock(int pos)
	{
		SetArrayBit(lock_, pos, true);
	}
	void UnLock(int pos)
	{
		SetArrayBit(lock_, pos, false);
	}

	static void Init()
	{
		memset(s_forbit_mask, 0 , sizeof(s_forbit_mask));
	}

private:

	unsigned char mask_[MAX_BYTE];  //这个是mask的存储地方

	unsigned int used_count_; //已经使用的字节数

	unsigned int mask_count_;
	
	char lock_[MAX_BYTE]; // 锁定属性值，不允许设置新值 
};

//实体属性集合,可以是各种数据,带有一个mask纪录第几个int的值修改过
class PropertySet:
	public UpdateMask
{
public:
	PropertySet() {}

	template<typename T>
	inline bool set(int pid, const T& value)
	{
		if (IsLock(pid)) return false;
		
		T* pos = (T*)ptr(pid);

		if (*pos == value) return false; //没改变
		int offset = (int)((char*)pos - (char*)this - sizeof(UpdateMask));  //偏移了多少字节

		if (offset < 0) return false;

		*pos = value; //设置值

		if (offset > 0) offset = offset >> 2;

		int size = sizeof(T);
		size = __max(size >> 2, 1); //多少个4字节

		for (int i = 0; i < size; ++i)
		{
			SetMask(offset + i);
		}
		return true;
	}

	//获取属性集第nPos个int的指针
	inline const char* ptr(int pos) const
	{
		const char* ptr = (const char*)this + sizeof(UpdateMask) + (pos << 2);
		return ptr;
	}

	// 获取数据的首地址
	inline const char* ptr() const
	{
		return (const char*)this + sizeof(UpdateMask);
	}

	template < class T>
	inline T GetProperty(int pos) const
	{
		return *(T*)this->ptr(pos);
	}

	template < class T>
	inline void SetProperty(int pos, const T& value)
	{
		if (IsLock(pos)) return;

		T oldValue = GetProperty<T>(pos);

		if (oldValue == value) return;

		this->set(pos, value);
	}

	// d：true表示读取8字节，否则默认都是4字节（int，float类型的长度）
	inline void set(int pos, PropertySet* set, bool d)
	{
		memcpy((char*)(this->ptr(pos)), set->ptr(pos), d ? 8 : 4);
	}
};

class EntityProperty:
	public PropertySet
{
public:
	int data_[P_MAX_ENTITY];
	EntityProperty()
	{
		memset(this, 0, sizeof(EntityProperty));
	}
};

STATIC_ASSERT((P_MAX_ENTITY - P_ID) == (sizeof(EntityProperty) - sizeof(PropertySet)) / sizeof(int));

//玩家的属性集,包括 玩家的db数据,1级属性数据
class ActorProperty:
	public PropertySet
{
public:
	int data_[P_MAX_ACTOR];
	ActorProperty()
	{
		memset(this, 0, sizeof(ActorProperty));
	}
};

// 如果修改过ActorProperty结构，把这个值相应的修改成新的PROP_MAX_ACTOR的值，同时知会客户端程序
STATIC_ASSERT((sizeof(ActorProperty) - sizeof(UpdateMask)) / sizeof(int) == P_MAX_ACTOR);

//怪物的属性集合
class MonsterProperty:
	public PropertySet
{
public:
	int data_[P_MAX_MONSTER];
	MonsterProperty()
	{
		memset(this, 0, sizeof(MonsterProperty));
	}
};

STATIC_ASSERT((sizeof(MonsterProperty) - sizeof(UpdateMask)) / sizeof(int) == P_MAX_MONSTER);


#pragma  pack()

#endif

