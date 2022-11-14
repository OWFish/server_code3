#ifndef _CL_VARIANT_H_
#define _CL_VARIANT_H_


/************************************************************************
*                 C/C++������Ϊ�ű��ṩ�ı�����
*  ����֧��double��char*���Լ��������Ƶĳ�Աֵ
************************************************************************/
#include "bzhash.h"

class CLVariant
{
public:
	/** ����������� **/
	typedef enum tagVarType
	{
	    vNil = 0, //��ֵ
	    vNumber = 1,//����ֵ
	    vStr = 2,//�ַ���ֵ
	    vStruct = 3,//�ṹֵ
	} VARTYPE;
public:
	/** ����ת������������� **/
	inline  operator int64_t() const
	{
		if (type_ == vNumber)
			return (int64_t)data_.n;

		if (type_ == vStr)
		{
			char* e;
			double d = strtod(data_.s.str, &e);

			if (!e || !*e)
				return (int64_t)d;
		}

		return 0;
	}

	inline operator double() const
	{
		if (type_ == vNumber)
			return data_.n;

		if (type_ == vStr)
		{
			char* e;
			double d = strtod(data_.s.str, &e);

			if (!e || !*e)
				return d;
		}

		return 0;
	}

	inline operator const char* () const
	{
		if (type_ == vStr)
		{
			return data_.s.str;
		}

		return NULL;
	}

	inline operator const CLVariant** () const
	{
		if (type_ == vStruct)
			return (const CLVariant**)data_.a.list;

		return NULL;
	}
public:
	/** �Ƚ��ж������������ **/
	inline bool operator == (const CLVariant& var)
	{
		switch (type_)
		{
		case vNumber:
			if (var.type_ == vNumber)
			{
				return data_.n == var.data_.n;
			}
			else if (var.type_ == vStr)
			{
				char* e = NULL;
				double d = strtod(var.data_.s.str, &e);

				if (!e || !*e)
					return data_.n == d;
			}

			break;

		case vStr:
			if (var.type_ == vNumber)
			{
				char* e = NULL;

				double d = strtod(data_.s.str, &e);

				if (!e || !*e)
					return d == var.data_.n;
			}
			else if (var.type_ == vStr)
			{
				return (data_.s.len == var.data_.s.len) && !strcmp(data_.s.str, var.data_.s.str);
			}

			break;
		}

		return false;
	}

	inline bool operator < (const CLVariant& var)
	{
		switch (type_)
		{
		case vNumber:
			if (var.type_ == vNumber)
			{
				return data_.n < var.data_.n;
			}
			else if (var.type_ == vStr)//��ʱ��Ҫ���н�����ת��Ϊ�ַ�������strcmp�Ƚϣ���Ϊ����>�����ʱ��lua�Ὣ�ڶ�����������Ϊ��һ������
			{
				char* e = NULL;
				double d = strtod(var.data_.s.str, &e);

				if (!e || !*e)
					return data_.n < d;
			}

			break;

		case vStr:
			if (var.type_ == vNumber)
			{
				char* e = NULL;
				double d = strtod(data_.s.str, &e);

				if (!e || !*e)
					return d < var.data_.n;
			}
			else if (var.type_ == vStr)
				return (data_.s.len < var.data_.s.len) || strcmp(data_.s.str, var.data_.s.str) < 0;

			break;
		}

		return false;
	}

	inline bool operator > (const CLVariant& var)
	{
		return !operator <= (var);
	}

	inline bool operator <= (const CLVariant& var)
	{
		switch (type_)
		{
		case vNumber:
			if (var.type_ == vNumber)
			{
				return data_.n <= var.data_.n;
			}
			else if (var.type_ == vStr)//��ʱ��Ҫ���н�����ת��Ϊ�ַ�������strcmp�Ƚϣ���Ϊ����>=�����ʱ��lua�Ὣ�ڶ�����������Ϊ��һ������
			{
				char* e = NULL;
				double d = strtod(var.data_.s.str, &e);

				if (!e || !*e)
					return data_.n <= d;
			}

			break;

		case vStr:
			if (var.type_ == vNumber)
			{
				char* e = NULL;
				double d = strtod(data_.s.str, &e);

				if (!e || !*e)
					return d <= var.data_.n;
			}
			else if (var.type_ == vStr)
				return (data_.s.len </*���ﲻ����<=*/ var.data_.s.len) ||
				       (data_.s.len == var.data_.s.len && strcmp(data_.s.str, var.data_.s.str) <= 0);

			break;
		}

		return false;
	}

	inline bool operator >= (const CLVariant& var)
	{
		return !operator < (var);
	}
public:
	/** ��������������� **/
	inline CLVariant& operator = (double val)
	{
		if (type_ != vNumber && type_ != vNil)
			clear();

		type_ = vNumber;
		data_.n = val;
		return *this;
	}
	inline CLVariant& operator = (const char* val)
	{
		if (type_ == vStr && data_.s.str && !strcmp(data_.s.str, val))
			return *this;

		clear();
		type_ = vStr;
		data_.s.len = (unsigned int)strlen(val);
		data_.s.str = (char*)malloc(data_.s.len + 1);
		memcpy(data_.s.str, val, data_.s.len + 1);
		return *this;
	}
	inline CLVariant& operator = (const CLVariant& val)
	{
		if (&val == this)
			return *this;

		if (val.type_ == vNumber)
		{
			operator = (val.data_.n);
		}
		else if (val.type_ == vStr)
		{
			if (type_ == vStr && data_.s.len == val.data_.s.len && data_.s.str
			        && val.data_.s.str && !strcmp(data_.s.str, val.data_.s.str))
			{
				return *this;
			}

			clear();
			type_ = vStr;
			data_.s.str = (char*)malloc(val.data_.s.len + 1);
			memcpy(data_.s.str, val.data_.s.str, val.data_.s.len + 1);
		}
		else if (val.type_ == vStruct)
		{
			clear();
			type_ = vStruct;
			data_.a.list = (CLVariant**)calloc(val.data_.a.len, sizeof(*data_.a.list));
			data_.a.len = val.data_.a.len;

			for (int i = 0; i < (int)val.data_.a.len; ++i)
			{
				data_.a.list[i] = new CLVariant(*val.data_.a.list[i]);
			}
		}

		return *this;
	}

public:
	/** ȡ��Աֵ�Լ����ó�Աֵ�ĺ����� **/
	//ͨ�����ƻ�ȡ��Աֵ
	inline CLVariant* get(const char* name)
	{
		if (type_ != vStruct || !name)
			return NULL;

		unsigned int h1 = bzhashstr(name, 1);
		unsigned int h2 = bzhashstr(name, 2);
		int64_t namecode = MAKEINT64(h1, h2);

		return get(namecode);
	}

	//ͨ���������ƻ�������ȡ��Աֵ
	inline CLVariant* get(int64_t namecode)
	{
		if (type_ != vStruct)
			return NULL;

		CLVariant* pVar = NULL;

		if (data_.a.len && data_.a.list)
		{
			int low = 0;
			int high = data_.a.len - 1;

			while (low <= high)
			{
				int mid = ((unsigned int)(low + high)) >> 1;
				const CLVariant* mid_item = data_.a.list[mid];

				if (mid_item->name_id_ < namecode)
					low = mid + 1;
				else if (mid_item->name_id_ > namecode)
					high = mid - 1;
				else
					return data_.a.list[mid]; // key found
			}
		}

		return pVar;
	}

	//������Աֵ�������Ա�Ѿ�������ʲôҲ���������򴴽���һ��ֵΪvNil�ĳ�Ա
	inline CLVariant& set(const char* name)
	{
		if (type_ != vStruct)
			clear();

		type_ = vStruct;

		unsigned int h1 = bzhashstr(name, 1);
		unsigned int h2 = bzhashstr(name, 2);
		int64_t namecode = MAKEINT64(h1, h2);

		CLVariant* var = get(namecode);

		if (!var)
		{
			var = new CLVariant();
			var->name_id_ = namecode;

			int low = 0;
			int high = data_.a.len - 1;

			while (low <= high)
			{
				int mid = ((unsigned)(low + high)) >> 1;
				const CLVariant* mid_item  = data_.a.list[mid];

				if (mid_item->name_id_ < var->name_id_)
					low = mid + 1;
				else
					high = mid - 1;
			}

			int index = low;
			data_.a.list = (CLVariant**)realloc(data_.a.list, sizeof(*data_.a.list) * (data_.a.len + 1));

			if (index < (int)data_.a.len)
			{
				memmove(data_.a.list + index + 1, data_.a.list + index, sizeof(CLVariant*) * (data_.a.len - index));
			}

			data_.a.list[index] = var;
			data_.a.len++;
		}

		return *var;
	}

	//����һ����Ա��doubleֵ�������Աֵ����������Զ������������Աֵ�������ı��Աֵ������
	inline const CLVariant& set(const char* name, double val)
	{
		CLVariant& Var = set(name);
		Var.operator = (val);
		return Var;
	}

	//����һ����Ա���ַ���ֵ�������Աֵ����������Զ������������Աֵ�������ı��Աֵ������
	inline const CLVariant& set(const char* name, const char* val)
	{
		CLVariant& Var = set(name);
		Var.operator = (val);
		return Var;
	}

	//����Ϊ�����ݽṹ��
	inline const void setToEmptyStruct()
	{
		clear();
		type_ = vStruct;
	}
public:
	//��ȡ����������
	inline int type()
	{
		return type_;
	}

	/* ��ȡ�����ĳ���
	*  ��������ֵ����Ϊ���ֵ�ʱ�򣬷���ֵΪ1��
	*  ��������ֵ����Ϊ�ַ�����ʱ�򣬷���ֵΪ�ַ������ȣ�
	*  ��������ֵ����Ϊ�ṹ�����ݵ�ʱ�򣬷���һ���ӳ�Ա��������
	*  ����0��ʾ����û��ֵ
	*/
	inline size_t len()
	{
		if (type_ == vStr)
			return data_.s.len;

		if (type_ == vStruct)
			return data_.a.len;

		if (type_ == vNumber)
			return 1;

		return 0;
	}

	//��ձ�����ֵ
	inline void clear()
	{
		if (type_ == vStr)
		{
			free(data_.s.str);
			data_.s.str = NULL;
			data_.s.len = 0;
		}
		else if (type_ == vStruct)
		{
			if (data_.a.len)
			{
				for (int i = data_.a.len - 1; i > -1; --i)
				{
					delete data_.a.list[i];
				}
			}

			free(data_.a.list);
			data_.a.list = NULL;
			data_.a.len = 0;
		}
		else if (type_ == vNumber)
		{
			data_.n = 0;
		}

		type_ = vNil;
	}

	//��ȡ��vStr�������ų�vNilֵ�ĳ�Ա����
	inline size_t packedlen()
	{
		if (vStruct != type_ || data_.a.len == 0)
		{
			return 0;
		}

		size_t result = 0;

		for (int i = data_.a.len - 1; i > -1; --i)
		{
			if (data_.a.list[i]->type_ != vNil)
				result++;
		}

		return result;
	}

	/*
	* Comments: ���������м��ر�������
	* Param const char * ptr: ������ָ��
	* Param size_t size: ����������
	* Param size_t *pCount: ���ڱ�������˶��ٸ���������
	* @Return size_t: �������ؼ����˱�������ڴ����λ��
	*/
	const char* loadFromMemory(const char* ptr, size_t& size, size_t* pCount = NULL);

	/*
	* Comments: ���������浽�ڴ���
	* Param char * ptr: �ڴ���ָ��
	* Param size_t size: �ڴ滺�泤�ȣ����ֵΪ0����������д��������ݣ��ҷ���д�����������ڴ��ֽڳ���
	memory:����Ϊ����ֵ����ʾ�ڴ��Ƿ��㹻
	*/
	size_t saveToMemory(char* ptr, size_t size, bool& memory);

	inline int compareName(CLVariant* v2)
	{
		if (name_id_ < v2->name_id_)
		{
			return -1;
		}
		else if (name_id_ > v2->name_id_)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
private:
	inline void zd()
	{
		type_ = vNil;
		name_id_ = 0;
		data_.s.len = 0;
		data_.n = 0;
	}

public:
	CLVariant()
	{
		zd();
	}

	CLVariant(double val)
	{
		zd();
		type_ = vNumber;
		data_.n = val;
	}

	CLVariant(const char* val)
	{
		zd();
		this->operator = (val);
	}

	CLVariant(const CLVariant& val)
	{
		zd();
		this->operator = (val);
	}

	~CLVariant()
	{
		clear();
	}

private:
	unsigned int type_; //��������
	int64_t name_id_; //��ϣ����
	union
	{
		//����ֵ
		double n;
		//�ַ���ֵ
		struct
		{
			char* str;
			unsigned int len;
		} s;
		//����ֵ
		struct
		{
			CLVariant** list;
			unsigned int len;
		} a;
	} data_;
};


#endif

