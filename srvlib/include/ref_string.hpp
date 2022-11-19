#ifndef _REF_STRING_HPP_
#define _REF_STRING_HPP_

#include "string_ex.h"
#include "ref_class.hpp"

namespace string
{
template <class TS, typename TC>
class CTRefString
	: public misc::RefObject<TS>
{
	typedef misc::RefObject<TS> Inherited;
	typedef misc::RefObjectImpl<TS> CRefTS;
public:
	/* 构造函数列表 */
	CTRefString()
		: Inherited()
	{
	}
	CTRefString(const size_t len)
	{
		this->m_ptr = new CRefTS(len);
	}
	CTRefString(const TC* str)
	{
		operator = (str);
	}
	CTRefString(const TS& str)
	{
		this->m_ptr = new CRefTS(str);
	}
	CTRefString(const CTRefString<TS, TC>& rStr)
	{
		operator = (rStr);
	}
public:
	/*  类型转换函数，转换为(const TC*)。
		注意： 如果当前字符串为NULL，则会返回""而不是NULL。
	*/
	inline operator const TC* () const
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*  类型转换函数，转换为(const TC*)。
		注意： 如果当前字符串为NULL，则会返回""而不是NULL。
	*/
	inline operator TC* ()
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*	赋值函数，赋予(const TC*)类型的值	*/
	inline void operator = (const TC* data)
	{
		CRefTS* newPtr = new CRefTS();
		*((TS*)newPtr) = data;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*	赋值函数，赋予TS类型的值	*/
	inline void operator = (const TS& str)
	{
		CRefTS* newPtr = new CRefTS();
		*((TS*)newPtr) = str;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*	与(const TC*)类型的字符串连接  */
	inline void operator += (const TC* data)
	{
		CRefTS* newPtr = new CRefTS();

		if (this->m_ptr) *((TS*)newPtr) = *this->m_ptr;

		*newPtr += data;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*	与自己或其他字符串连接	*/
	inline void operator += (const TS& str)
	{
		CRefTS* newPtr = new CRefTS();

		if (this->m_ptr) *((TS*)newPtr) = *this->m_ptr;

		*newPtr += str;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*  判断与(const TC*)类型的字符串指针中的字符串数据是否相同（区分大小小写）  */
	inline bool operator == (const TC* data) const
	{
		return compare(data) == 0;
	}
	/*  判断与另一个字符串的数据是否相同（区分大小小写）  */
	inline bool operator == (const TS& str) const
	{
		return compare(str) == 0;
	}
	/*  判断与另一个引用字符串的数据是否相同（区分大小小写）  */
	inline bool operator == (const CTRefString<TS, TC>& str) const
	{
		return compare(str) == 0;
	}
	/*  判断与(const TC*)类型的字符串指针中的字符串数据是否不相同（区分大小小写）  */
	inline bool operator != (const TC* data) const
	{
		return compare(data) != 0;
	}
	/*  判断与另一个字符串的数据是否不相同（区分大小小写）  */
	inline bool operator != (const TS& str) const
	{
		return compare(str.m_sStr) != 0;
	}
	/*  判断与另一个引用字符串的数据是否不相同（区分大小小写）  */
	inline bool operator != (const CTRefString<TS, TC>& str) const
	{
		return compare(str) != 0;
	}

public:
	/*	取得字符串指针	*/
	inline const TC* rawStr() const
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*	取得字符串指针	*/
	inline TC* rawStr()
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*	取得字符串长度	*/
	inline size_t length() const
	{
		return this->m_ptr ? this->m_ptr->length() : 0;
	}
	/*	设置字符串长度(保留空间)	*/
	inline void setLength(const size_t len)
	{
		misc::RefObjectImpl<TS>* newPtr = new misc::RefObjectImpl<TS>(len);

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/* 与另一个字符串指针对比  */
	inline int compare(const TC* data) const
	{
		if (!this->m_ptr)
			return !data ? 0 : -1;

		if (data == this->m_ptr->rawStr())
			return 0;

		return this->m_ptr->compare(data);
	}
	/* 与另一个字符串类进行对比  */
	inline int compare(const TS& str) const
	{
		if (!this->m_ptr)
			return str.isEmpty() ? 0 : -1;

		if (this->m_ptr == &str)
			return 0;

		return this->m_ptr->compare(str);
	}
	/* 与另一个引用字符串类进行对比  */
	inline int compare(const CTRefString<TS, TC>& str) const
	{
		if (this->m_ptr == str.m_ptr)
			return 0;

		if (!this->m_ptr) return -1;

		return this->m_ptr->compare(str->raw_ptr());
	}
	/* 格式化字符串  */
	inline size_t format(const TC* fmt, ...)
	{
		va_list	args;
		size_t Result = 0;

		va_start(args, fmt);
		Result = format_args(fmt, args);
		va_end(args);

		return Result;
	}
	inline size_t format_args(const TC* fmt, va_list _Args)
	{
		size_t Result = 0;

		misc::RefObjectImpl<TS>* newPtr = new misc::RefObjectImpl<TS>();
		Result = newPtr->format_args(fmt, _Args);

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;

		return Result;
	}
};

typedef CTRefString<AnsiString, char>		CRefAnsiString;
};

typedef string::CRefAnsiString	RefString;

#endif
