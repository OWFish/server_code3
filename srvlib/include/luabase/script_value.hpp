#ifndef _SCRIPT_VALUE_HPP_
#define _SCRIPT_VALUE_HPP_

/************************************************************************
*    LUA�к���nil��bool��number��string��lightuserdata��userdata��cfunction
* �����͵�ֵ��CScriptValue������������ʹ洢��Щֵ���������͵�ֵ�������ͨ������ű�
* �����Ĺ�������Ϊ�ű��������õĲ����Լ��洢�ű�����ֵ��ʱ��ʹ�á�
*
************************************************************************/

class ScriptValue
{
public:
	// ����ű�ֵ����������
	enum ScriptValueType
	{
	    vNull = LUA_TNIL,	// nilֵ
	    vBool = LUA_TBOOLEAN,	// boolֵ
	    vLightData = LUA_TLIGHTUSERDATA,//��ָ��ֵ
	    vNumber = LUA_TNUMBER,//numberֵ
	    vString = LUA_TSTRING,//stringֵ
	    vCFunction = LUA_TFUNCTION,//C����ָ��ֵ
	    vUserData = LUA_TUSERDATA,//userdataֵ
	};

	// ����ű�ֵ��ֵ���ݽṹ
	union ScriptValueData
	{
		bool	boVal;		//boolֵ
		const void* lightPtr;	//ָ��ֵ
		double  numVal;		//numberֵ
		struct
		{
			const char*  str; //�ַ���ָ��
			size_t len;//�ַ�������
		}		strVal;		//�ַ���ֵ
		lua_CFunction cfnVal;//C����ֵ
		struct
		{
			const void* ptr;  //�û�����ָ��
			size_t size;//�û����ݳ���
		}		userVal;	//�û�����ֵ
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

	/* ������� */
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

	/* ��ȡ�������� */
	inline ScriptValueType getType()
	{
		return type_;
	}

	/* ��ȡ���ݴ�С
	 * ����vNull���͵�ֵ������ֵΪ0,
	 * ����vBool���͵�ֵ������ֵΪsizeof(bool),
	 * ����vLightData���͵�ֵ������ֵ��sizeof(LPCVOID),
	 * ����vNumber���͵�ֵ������ֵ��sizeof(double),
	 * ����vString���͵�ֵ������ֵ���ַ����ĳ���,
	 * ����vCFunction���͵�ֵ������ֵ��sizeof(lua_CFunction),
	 * ����vUserData���͵�ֵ������ֵ���û����ݵ��ڴ��ֽڳ���,
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
	 * �����м���
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
	 * ���浽����
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
	/* ��boolֵ�ĸ�ֵ���㺯�� */
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

	/* ��LUAC����ָ�루lua_CFunction��ֵ�ĸ�ֵ���㺯�� */
	inline ScriptValue& operator = (const lua_CFunction val)
	{
		clear();
		type_ = vCFunction;
		data_.cfnVal = val;
		return *this;
	}

	/* ��ScriptValueDataֵ�ĸ�ֵ���㺯�� */
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
	/* ����ָ�����ֵ�����������ڴ� */
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
	//ת��Ϊint�����������
	inline operator int ()
	{
		if (type_ == vNumber)
			return (int)data_.numVal;

		return 0;
	}
	//ת��Ϊint64�����������
	inline operator int64_t ()
	{
		if (type_ == vNumber)
			return (int64_t)data_.numVal;

		return 0;
	}
	//ת��Ϊdouble�����������
	inline operator double()
	{
		if (type_ == vNumber)
			return data_.numVal;

		return 0.0;
	}
	//ת��Ϊfloat�����������
	inline operator float()
	{
		if (type_ == vNumber)
			return (float)data_.numVal;

		return 0.0;
	}
	/* ת��Ϊbool����������� */
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
	//ת��Ϊconst char*�����������
	inline operator const char* ()
	{
		if (type_ == vString)
			return (const char*)data_.strVal.str;

		return NULL;
	}
	//ת��Ϊconst lua_CFunction�����������
	inline operator const lua_CFunction()
	{
		if (type_ == vCFunction)
			return data_.cfnVal;

		return NULL;
	}
	//ת��Ϊconst void*�����������
	inline operator const void* ()
	{
		if (type_ == vLightData || type_ == vUserData)
			return (const void*)data_.lightPtr;
		else if (type_ == vString)
			return (const void*)data_.strVal.str;

		return NULL;
	}
protected:
	ScriptValueType	type_;	//ֵ����
	ScriptValueData	data_;	//ֵ
};

#endif


