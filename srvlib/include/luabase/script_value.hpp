#ifndef _SCRIPT_VALUE_HPP_
#define _SCRIPT_VALUE_HPP_

/************************************************************************
*    LUA中含有nil、bool、number、string、lightuserdata、userdata、cfunction
* 等类型的值。CScriptValue类可用于描述和存储这些值中任意类型的值。这个类通常在与脚本
* 交互的过程中作为脚本函数调用的参数以及存储脚本返回值的时候使用。
*
************************************************************************/

class ScriptValue
{
public:
	// 定义脚本值的数据类型
	enum ScriptValueType
	{
	    vNull = LUA_TNIL,	// nil值
	    vBool = LUA_TBOOLEAN,	// bool值
	    vLightData = LUA_TLIGHTUSERDATA,//纯指针值
	    vNumber = LUA_TNUMBER,//number值
	    vString = LUA_TSTRING,//string值
	    vCFunction = LUA_TFUNCTION,//C函数指针值
	    vUserData = LUA_TUSERDATA,//userdata值
	};

	// 定义脚本值的值数据结构
	union ScriptValueData
	{
		bool	boVal;		//bool值
		const void* lightPtr;	//指针值
		double  numVal;		//number值
		struct
		{
			const char*  str; //字符串指针
			size_t len;//字符串长度
		}		strVal;		//字符串值
		lua_CFunction cfnVal;//C函数值
		struct
		{
			const void* ptr;  //用户数据指针
			size_t size;//用户数据长度
		}		userVal;	//用户数据值
	};

public:
	ScriptValue()
	{
		type_ = vNull;
		data_.userVal.ptr = 0;
		data_.userVal.size = 0;
	}
	~ScriptValue()
	{
		clear();
	}

	/* 清除数据 */
	inline void clear()
	{
		if (type_ != vNull)
		{
			if (type_ == vString)
				free((void*)data_.strVal.str);
			else if (type_ == vUserData)
				free((void*)data_.userVal.ptr);

			type_ = vNull;
			data_.userVal.ptr = 0;
			data_.userVal.size = 0;
		}
	}

	/* 获取数据类型 */
	inline ScriptValueType getType()
	{
		return type_;
	}

	/* 获取数据大小
	 * 对于vNull类型的值，返回值为0,
	 * 对于vBool类型的值，返回值为sizeof(bool),
	 * 对于vLightData类型的值，返回值是sizeof(LPCVOID),
	 * 对于vNumber类型的值，返回值是sizeof(double),
	 * 对于vString类型的值，返回值是字符串的长度,
	 * 对于vCFunction类型的值，返回值是sizeof(lua_CFunction),
	 * 对于vUserData类型的值，返回值是用户数据的内存字节长度,
	*/
	inline size_t getSize()
	{
		switch (type_)
		{
		case vBool:
			return sizeof(data_.boVal);

		case vLightData:
			return sizeof(data_.lightPtr);

		case vNumber:
			return sizeof(data_.numVal);

		case vString:
			return data_.strVal.len;

		case vCFunction:
			return sizeof(data_.cfnVal);

		case vUserData:
			return data_.userVal.size;

		default:
			return 0;
		}
	}

	/*
	 * 从流中加载
	 */
	inline void loadFromStream(stream::BaseStream& stm)
	{
		clear();

		stm.read(&type_, sizeof(uint8_t));

		switch (type_)
		{
		case vBool:
			stm.read(&data_.boVal, sizeof(data_.boVal));
			break;

		case vLightData:
			stm.read(&data_.lightPtr, sizeof(data_.lightPtr));
			break;

		case vNumber:
			stm.read(&data_.numVal, sizeof(data_.numVal));
			break;

		case vString:
			stm.read(&data_.strVal.len, sizeof(data_.strVal.len));
			data_.strVal.str = (const char*)malloc(data_.strVal.len + sizeof(int));
			stm.read((void*)data_.strVal.str, (const int)(data_.strVal.len * sizeof(data_.strVal.str[0])));
			((char*)(data_.strVal.str))[data_.strVal.len] = 0;
			break;

		case vCFunction:
			stm.read(&data_.cfnVal, sizeof(data_.cfnVal));
			break;

		case vUserData:
			stm.read(&data_.userVal.size, sizeof(data_.userVal.size));
			data_.userVal.ptr = malloc(data_.userVal.size);
			stm.read((void*)data_.userVal.ptr, (const int)(data_.userVal.size));
			break;

		default:
			break;
		}

	}

	/*
	 * 保存到流中
	 */
	inline int64_t saveToStream(stream::BaseStream& stm) const
	{
		int64_t dwPos = stm.getPosition();

		stm.write(&type_, sizeof(uint8_t));

		switch (type_)
		{
		case vBool:
			stm.write(&data_.boVal, sizeof(data_.boVal));
			break;

		case vLightData:
			stm.write(&data_.lightPtr, sizeof(data_.lightPtr));
			break;

		case vNumber:
			stm.write(&data_.numVal, sizeof(data_.numVal));
			break;

		case vString:
			stm.write(&data_.strVal.len, sizeof(data_.strVal.len));
			stm.write(data_.strVal.str, data_.strVal.len * sizeof(data_.strVal.str[0]));
			break;

		case vCFunction:
			stm.write(&data_.cfnVal, sizeof(data_.cfnVal));
			break;

		case vUserData:
			stm.write(&data_.userVal.size, sizeof(data_.userVal.size));
			stm.write(data_.userVal.ptr, data_.userVal.size);
			break;

		default:
			break;
		}

		return stm.getPosition() - dwPos;
	}
public:
#define SETLUANUMBER(val) clear();	type_ = vNumber; data_.numVal = (double)val;
	inline ScriptValue& operator = (const int val)
	{
		SETLUANUMBER(val);
		return *this;
	}
	inline ScriptValue& operator = (const unsigned int val)
	{
		SETLUANUMBER(val);
		return *this;
	}
	inline ScriptValue& operator = (const int64_t val)
	{
		SETLUANUMBER(val);
		return *this;
	}

	inline ScriptValue& operator = (const uint64_t val)
	{
		SETLUANUMBER(val);
		return *this;
	}

	inline ScriptValue& operator = (const double val)
	{
		SETLUANUMBER(val);
		return *this;
	}
	inline ScriptValue& operator = (const float val)
	{
		SETLUANUMBER(val);
		return *this;
	}
	/* 从bool值的赋值运算函数 */
	inline ScriptValue& operator = (const bool val)
	{
		clear();
		type_ = vBool;
		data_.boVal = val;
		return *this;
	}
	inline ScriptValue& operator = (const char* val)
	{
		clear();
		type_ = vString;

		if (val)
		{
			data_.strVal.len = strlen(val);
			data_.strVal.str = (const char*)malloc(data_.strVal.len + sizeof(int));
			memcpy((char*)data_.strVal.str, val, data_.strVal.len);
			((char*)(data_.strVal.str))[data_.strVal.len] = 0;
		}
		else
		{
			data_.strVal.len = 0;
			data_.strVal.str = NULL;
		}

		return *this;
	}

	inline ScriptValue& operator = (const void* val)
	{
		clear();
		type_ = vLightData;
		data_.lightPtr = val;
		return *this;
	}

	/* 从LUAC函数指针（lua_CFunction）值的赋值运算函数 */
	inline ScriptValue& operator = (const lua_CFunction val)
	{
		clear();
		type_ = vCFunction;
		data_.cfnVal = val;
		return *this;
	}

	/* 从ScriptValueData值的赋值运算函数 */
	inline ScriptValue& operator = (const ScriptValue& val)
	{
		switch (val.type_)
		{
		case vBool:
			return operator = (val.data_.boVal);

		case vLightData:
			return operator = (val.data_.lightPtr);

		case vNumber:
			return operator = (val.data_.numVal);

		case vString:
			return operator = (val.data_.strVal.str);

		case vCFunction:
			return operator = (val.data_.cfnVal);

		case vUserData:
			return SetUserData(val.data_.userVal.ptr, val.data_.userVal.size);

		default:
			clear();
			return *this;
		}
	}
	/* 赋予指针对象值并拷贝对象内存 */
	inline ScriptValue&  SetUserData(const void* data, size_t dwSize)
	{
		clear();
		type_ = vUserData;
		data_.userVal.size = dwSize;
		data_.userVal.ptr = malloc(dwSize);
		memcpy((void*)data_.userVal.ptr, data, dwSize);
		return *this;
	}

public:
	//转换为int的运算符重载
	inline operator int ()
	{
		if (type_ == vNumber)
			return (int)data_.numVal;

		return 0;
	}
	//转换为int64的运算符重载
	inline operator int64_t ()
	{
		if (type_ == vNumber)
			return (int64_t)data_.numVal;

		return 0;
	}
	//转换为double的运算符重载
	inline operator double()
	{
		if (type_ == vNumber)
			return data_.numVal;

		return 0.0;
	}
	//转换为float的运算符重载
	inline operator float()
	{
		if (type_ == vNumber)
			return (float)data_.numVal;

		return 0.0;
	}
	/* 转换为bool的运算符重载 */
	inline operator bool ()
	{
		switch (type_)
		{
		case vBool:
			return data_.boVal;

		case vLightData:
			return data_.lightPtr != NULL;

		case vNumber:
			return data_.numVal != 0;

		case vString:
			return data_.strVal.str && strcmp("true", data_.strVal.str) == 0;

		case vCFunction:
			return data_.cfnVal != NULL;

		case vUserData:
			return data_.userVal.ptr != NULL;

		default:
			return false;
		}
	}
	//转换为const char*的运算符重载
	inline operator const char* ()
	{
		if (type_ == vString)
			return (const char*)data_.strVal.str;

		return NULL;
	}
	//转换为const lua_CFunction的运算符重载
	inline operator const lua_CFunction()
	{
		if (type_ == vCFunction)
			return data_.cfnVal;

		return NULL;
	}
	//转换为const void*的运算符重载
	inline operator const void* ()
	{
		if (type_ == vLightData || type_ == vUserData)
			return (const void*)data_.lightPtr;
		else if (type_ == vString)
			return (const void*)data_.strVal.str;

		return NULL;
	}
protected:
	ScriptValueType	type_;	//值类型
	ScriptValueData	data_;	//值
};

#endif


