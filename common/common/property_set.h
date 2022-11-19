#ifndef _PROPERTY_SET_H_
#define _PROPERTY_SET_H_

#include "common.h"
#include "property_id_def.h"

#pragma  pack(4)

// ��ʱ֧��32*8�����ԣ����ֻ��255�����ԣ� ��Ϊ����ط���uint8_t��ʾ���Ե�����
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
	*���õ�nPos��int�Ƿ��޸Ĺ�
	* nPos �ڼ���4�ֽ�
	* flag flag=true��ʾ�޸Ĺ�,����ȥ������޸ı��
	*/
	inline void SetMask(int pos/*, bool flag = true*/)
	{
		if (IsForbid(pos)) return;   // ��ֹ����

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
		// ���ԭ������masked��mask_countҪ��һ
		//	if (mask_[byte_pos] & value){ assert(mask_count_ > 0);--mask_count_;}
		//	value = ~value;
		//	mask_[byte_pos] &= value;
		//}
		if (used_count_ <= byte_pos)
			used_count_ = byte_pos + 1;
	}

	//��nPos��int�Ƿ��޸Ĺ�
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

		if (flag) //�������
		{
			arr[byte_pos] |= value;
		}
		else
		{
			value = ~value; //ȡ��
			arr[byte_pos] &= value; //��λ��
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

	//���ý�ֹ���µ����Ե�λ
	static void SetForbid(int pos, bool flag)
	{
		SetArrayBit(s_forbit_mask, pos, flag);
	}

	//ĳ��λ���Ƿ��ֹ����
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

	unsigned char mask_[MAX_BYTE];  //�����mask�Ĵ洢�ط�

	unsigned int used_count_; //�Ѿ�ʹ�õ��ֽ���

	unsigned int mask_count_;
	
	char lock_[MAX_BYTE]; // ��������ֵ��������������ֵ 
};

//ʵ�����Լ���,�����Ǹ�������,����һ��mask��¼�ڼ���int��ֵ�޸Ĺ�
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

		if (*pos == value) return false; //û�ı�
		int offset = (int)((char*)pos - (char*)this - sizeof(UpdateMask));  //ƫ���˶����ֽ�

		if (offset < 0) return false;

		*pos = value; //����ֵ

		if (offset > 0) offset = offset >> 2;

		int size = sizeof(T);
		size = __max(size >> 2, 1); //���ٸ�4�ֽ�

		for (int i = 0; i < size; ++i)
		{
			SetMask(offset + i);
		}
		return true;
	}

	//��ȡ���Լ���nPos��int��ָ��
	inline const char* ptr(int pos) const
	{
		const char* ptr = (const char*)this + sizeof(UpdateMask) + (pos << 2);
		return ptr;
	}

	// ��ȡ���ݵ��׵�ַ
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

	// d��true��ʾ��ȡ8�ֽڣ�����Ĭ�϶���4�ֽڣ�int��float���͵ĳ��ȣ�
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

//��ҵ����Լ�,���� ��ҵ�db����,1����������
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

// ����޸Ĺ�ActorProperty�ṹ�������ֵ��Ӧ���޸ĳ��µ�PROP_MAX_ACTOR��ֵ��ͬʱ֪��ͻ��˳���
STATIC_ASSERT((sizeof(ActorProperty) - sizeof(UpdateMask)) / sizeof(int) == P_MAX_ACTOR);

//��������Լ���
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

