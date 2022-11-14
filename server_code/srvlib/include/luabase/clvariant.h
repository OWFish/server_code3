#ifndef _CL_VARIANT_H_
#define _CL_VARIANT_H_


/************************************************************************
*                 C/C++程序中为脚本提供的变量类
*  变量支持double、char*、以及带有名称的成员值
************************************************************************/
#include "bzhash.h"

class CLVariant
{
public:
	/** 定义变量类型 **/
	typedef enum tagVarType
	{
	    vNil = 0, //无值
	    vNumber = 1,//数字值
	    vStr = 2,//字符串值
	    vStruct = 3,//结构值
	} VARTYPE;
public:
	/** 类型转换运算符函数集 **/
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
	/** 比较判断运算符函数集 **/
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
			else if (var.type_ == vStr)//此时不要进行将数字转换为字符而进行strcmp比较，因为进行>运算的时候，lua会将第二个参数传递为第一个参数
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
			else if (var.type_ == vStr)//此时不要进行将数字转换为字符而进行strcmp比较，因为进行>=运算的时候，lua会将第二个参数传递为第一个参数
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
				return (data_.s.len </*这里不能用<=*/ var.data_.s.len) ||
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
	/** 复制运算符函数集 **/
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
	/** 取成员值以及设置成员值的函数集 **/
	//通过名称获取成员值
	inline CLVariant* get(const char* name)
	{
		if (type_ != vStruct || !name)
			return NULL;

		unsigned int h1 = bzhashstr(name, 1);
		unsigned int h2 = bzhashstr(name, 2);
		int64_t namecode = MAKEINT64(h1, h2);

		return get(namecode);
	}

	//通过数字名称或索引获取成员值
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

	//创建成员值，如果成员已经存在则什么也不做，否则创建按一个值为vNil的成员
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

	//设置一个成员的double值，如果成员值不存在则会自动创建，如果成员值存在则会改变成员值的类型
	inline const CLVariant& set(const char* name, double val)
	{
		CLVariant& Var = set(name);
		Var.operator = (val);
		return Var;
	}

	//设置一个成员的字符串值，如果成员值不存在则会自动创建，如果成员值存在则会改变成员值的类型
	inline const CLVariant& set(const char* name, const char* val)
	{
		CLVariant& Var = set(name);
		Var.operator = (val);
		return Var;
	}

	//设置为空数据结构体
	inline const void setToEmptyStruct()
	{
		clear();
		type_ = vStruct;
	}
public:
	//获取变量的类型
	inline int type()
	{
		return type_;
	}

	/* 获取变量的长度
	*  当变量的值类型为数字的时候，返回值为1；
	*  当变量的值类型为字符串的时候，返回值为字符串长度；
	*  当变量的值类型为结构化数据的时候，返回一级子成员的数量；
	*  返回0表示变量没有值
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

	//清空变量的值
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

	//获取在vStr类型中排除vNil值的成员数量
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
	* Comments: 从数据流中加载变量数据
	* Param const char * ptr: 数据流指针
	* Param size_t size: 数据流长度
	* Param size_t *pCount: 用于保存加载了多少个变量对象
	* @Return size_t: 函数返回加载了变量后的内存的新位置
	*/
	const char* loadFromMemory(const char* ptr, size_t& size, size_t* pCount = NULL);

	/*
	* Comments: 将变量保存到内存中
	* Param char * ptr: 内存流指针
	* Param size_t size: 内存缓存长度，如果值为0，则函数不会写入变量数据，且返回写入变量所需的内存字节长度
	memory:会作为返回值，表示内存是否足够
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
	unsigned int type_; //数据类型
	int64_t name_id_; //哈希名称
	union
	{
		//整数值
		double n;
		//字符串值
		struct
		{
			char* str;
			unsigned int len;
		} s;
		//数组值
		struct
		{
			CLVariant** list;
			unsigned int len;
		} a;
	} data_;
};


#endif

