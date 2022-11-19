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
	/* ���캯���б� */
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
	/*  ����ת��������ת��Ϊ(const TC*)��
		ע�⣺ �����ǰ�ַ���ΪNULL����᷵��""������NULL��
	*/
	inline operator const TC* () const
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*  ����ת��������ת��Ϊ(const TC*)��
		ע�⣺ �����ǰ�ַ���ΪNULL����᷵��""������NULL��
	*/
	inline operator TC* ()
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*	��ֵ����������(const TC*)���͵�ֵ	*/
	inline void operator = (const TC* data)
	{
		CRefTS* newPtr = new CRefTS();
		*((TS*)newPtr) = data;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*	��ֵ����������TS���͵�ֵ	*/
	inline void operator = (const TS& str)
	{
		CRefTS* newPtr = new CRefTS();
		*((TS*)newPtr) = str;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*	��(const TC*)���͵��ַ�������  */
	inline void operator += (const TC* data)
	{
		CRefTS* newPtr = new CRefTS();

		if (this->m_ptr) *((TS*)newPtr) = *this->m_ptr;

		*newPtr += data;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*	���Լ��������ַ�������	*/
	inline void operator += (const TS& str)
	{
		CRefTS* newPtr = new CRefTS();

		if (this->m_ptr) *((TS*)newPtr) = *this->m_ptr;

		*newPtr += str;

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/*  �ж���(const TC*)���͵��ַ���ָ���е��ַ��������Ƿ���ͬ�����ִ�ССд��  */
	inline bool operator == (const TC* data) const
	{
		return compare(data) == 0;
	}
	/*  �ж�����һ���ַ����������Ƿ���ͬ�����ִ�ССд��  */
	inline bool operator == (const TS& str) const
	{
		return compare(str) == 0;
	}
	/*  �ж�����һ�������ַ����������Ƿ���ͬ�����ִ�ССд��  */
	inline bool operator == (const CTRefString<TS, TC>& str) const
	{
		return compare(str) == 0;
	}
	/*  �ж���(const TC*)���͵��ַ���ָ���е��ַ��������Ƿ���ͬ�����ִ�ССд��  */
	inline bool operator != (const TC* data) const
	{
		return compare(data) != 0;
	}
	/*  �ж�����һ���ַ����������Ƿ���ͬ�����ִ�ССд��  */
	inline bool operator != (const TS& str) const
	{
		return compare(str.m_sStr) != 0;
	}
	/*  �ж�����һ�������ַ����������Ƿ���ͬ�����ִ�ССд��  */
	inline bool operator != (const CTRefString<TS, TC>& str) const
	{
		return compare(str) != 0;
	}

public:
	/*	ȡ���ַ���ָ��	*/
	inline const TC* rawStr() const
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*	ȡ���ַ���ָ��	*/
	inline TC* rawStr()
	{
		return this->m_ptr ? this->m_ptr->rawStr() : NULL;
	}
	/*	ȡ���ַ�������	*/
	inline size_t length() const
	{
		return this->m_ptr ? this->m_ptr->length() : 0;
	}
	/*	�����ַ�������(�����ռ�)	*/
	inline void setLength(const size_t len)
	{
		misc::RefObjectImpl<TS>* newPtr = new misc::RefObjectImpl<TS>(len);

		if (this->m_ptr) this->m_ptr->release();

		this->m_ptr = newPtr;
	}
	/* ����һ���ַ���ָ��Ա�  */
	inline int compare(const TC* data) const
	{
		if (!this->m_ptr)
			return !data ? 0 : -1;

		if (data == this->m_ptr->rawStr())
			return 0;

		return this->m_ptr->compare(data);
	}
	/* ����һ���ַ�������жԱ�  */
	inline int compare(const TS& str) const
	{
		if (!this->m_ptr)
			return str.isEmpty() ? 0 : -1;

		if (this->m_ptr == &str)
			return 0;

		return this->m_ptr->compare(str);
	}
	/* ����һ�������ַ�������жԱ�  */
	inline int compare(const CTRefString<TS, TC>& str) const
	{
		if (this->m_ptr == str.m_ptr)
			return 0;

		if (!this->m_ptr) return -1;

		return this->m_ptr->compare(str->raw_ptr());
	}
	/* ��ʽ���ַ���  */
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
