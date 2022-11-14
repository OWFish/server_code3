#ifndef _LIB_ANSISTRING_H_
#define _LIB_ANSISTRING_H_

/******************************************************************
 *
 *
 *	$ UCS2�ַ����� $
 *  
 *  - ��Ҫ���� - 
 *
 *	ʵ��UCS�ַ����Ļ���������������UCS2�ַ�ָ����໥����
 *
 *****************************************************************/
#include <stdlib.h>
#include <string.h>

namespace string
{
	class AnsiString
	{
	public:
		typedef char			CharType;
		typedef char*			RawStrType;

	private:
		char*	m_sStr;

	private:
		static const char* EMPTY_STR;

	protected:
		/*
			realloc �ڴ����롢�ͷź����������Ҫ�����ڴ��������ͷţ�������Լ̳д˺���
				ptr: ���롢�ͷŵ�ָ��
				newsize: �����ڴ��ֽ�������Ϊ0���ʾ�ͷ�ptrָ��
				��ptr��newsize����Ϊ0���ʾ��ptr�ڴ�����������С
		*/
		virtual void* alloc(void* ptr, size_t newsize)
		{
			if ( newsize == 0 )
			{
				if ( ptr ) free( ptr );
				return NULL;
			}
			return realloc( ptr, newsize );
		}
		/*
			setData	�趨�ַ�������
				data: ָ��ԭʼ�ַ�����ָ��
		*/
		inline void setData(const char* data)
		{
			if ( data )
			{
				size_t size = strlen(data) + 1;
				size *= sizeof(*data);
				m_sStr = (char*)alloc( m_sStr, size );
				memcpy( m_sStr, data, size );
			}
			else m_sStr = (char*)alloc( m_sStr, 0 );
		}
		/*
			catData �������ַ�����������
				data: ָ��ԭʼ�ַ�����ָ�룬�ַ������ݻᱻ���ӵ���ǰ�ַ���֮��
		*/
		inline void catData(const char* data)
		{
			if ( data )
			{
				size_t cat_size = strlen(data);
				size_t cur_size = length();
				m_sStr = (char*)alloc( m_sStr, (cat_size + cur_size + 1) * sizeof(*data) );
				memcpy( &m_sStr[cur_size], data, (cat_size + 1) * sizeof(*data) );
			}
		}
	public:
		/*
			?�������������
		*/
		AnsiString()
		{
			m_sStr = NULL;
		}
		AnsiString(const char* data)
		{
			m_sStr = NULL;
			setData( data );
		}
		AnsiString(const AnsiString &str)
		{
			m_sStr = NULL;
			setData( str.m_sStr );
		}
		virtual ~AnsiString()
		{
			setData( NULL );
		}

	public:
		/*  ����ת��������ת��Ϊ(const char*)��
			ע�⣺ �����ǰ�ַ���ΪNULL����᷵��""������NULL��
		*/
		inline operator const char*() const
		{
			return m_sStr ? m_sStr : EMPTY_STR;
		}
		/*  ����ת��������ת��Ϊ(const char*)��
			ע�⣺ �����ǰ�ַ���ΪNULL����᷵��""������NULL��
		*/
		inline operator char*()
		{
			return m_sStr ? m_sStr : NULL;
		}
		/*	��ֵ����������(const char*)���͵�ֵ	*/
		inline void operator = (const char* data)
		{
			if ( data != m_sStr )
			{
				setData( data );
			}
		}
		/*	��ֵ������������ͬ���͵�ֵ	*/
		inline void operator = (const AnsiString& str)
		{
			if ( &str != this )
			{
				setData( str.m_sStr );
			}
		}
		/*	��(const char*)���͵��ַ�������  */
		inline void operator += (const char* data)
		{
			if ( data != m_sStr )
			{
				catData( data );
			}
			else
			{
				AnsiString wstr(m_sStr);
				catData(wstr.m_sStr);
			}
		}
		/*	���Լ��������ַ�������	*/
		inline void operator += (const AnsiString& str)
		{
			if ( &str != this )
			{
				catData( str.m_sStr );
			}
			else
			{
				AnsiString wstr(m_sStr);
				catData(wstr.m_sStr);
			}
		}
		/*	��(const char*)���ͽ��мӷ����㲢�������Ӻ��CAnsiString��	*/
		inline const AnsiString operator + (const char* data)
		{
			AnsiString str( m_sStr );
			str.catData( data );
			return str;
		}
		/*	����һ���ַ������мӷ����㲢�������Ӻ��CAnsiString��	*/
		inline const AnsiString operator + (const AnsiString& str)
		{
			AnsiString _str( m_sStr );
			_str.catData( str.m_sStr );
			return _str;
		}
		/*  �ж���(const char*)���͵��ַ���ָ���е��ַ��������Ƿ���ͬ�����ִ�ССд��  */
		inline bool operator == (const char* data) const
		{
			return compare( data ) == 0;
		}
		/*  �ж�����һ���ַ����������Ƿ���ͬ�����ִ�ССд��  */
		inline bool operator == (const AnsiString& str) const
		{
			return compare( str.m_sStr ) == 0;
		}
		/*  �ж���(const char*)���͵��ַ���ָ���е��ַ��������Ƿ���ͬ�����ִ�ССд��  */
		inline bool operator != (const char* data) const
		{
			return compare( data ) != 0;
		}
		/*  �ж�����һ���ַ����������Ƿ���ͬ�����ִ�ССд��  */
		inline bool operator != (const AnsiString& str) const
		{
			return compare( str.m_sStr ) != 0;
		}
		/*	�ж��Ƿ�ǿ�	*/
		inline bool operator ! () const
		{
			return !m_sStr || !m_sStr[0];
		}


	public:
		/*	ȡ���ַ���ָ��	*/
		inline const char* rawStr() const
		{
			return m_sStr;
		}
		/*	ȡ���ַ���ָ��	*/
		inline char* rawStr()
		{
			return m_sStr;
		}
		/*	ȡ���ַ�������	*/
		inline size_t length() const
		{
			return m_sStr ? strlen(m_sStr) : 0;
		}
		/*	�����ַ�������(�����ռ�)	*/
		inline void setLength(const size_t len)
		{
			if ( len > 0 )
			{
				m_sStr = (char*)alloc( m_sStr, sizeof(m_sStr[0]) * (len + 1) );
				if ( m_sStr ) m_sStr[len] = 0;
			}
			else m_sStr = (char*)alloc( m_sStr, 0 );
		}
		/* ����һ���ַ���ָ��Ա�  */
		inline int compare(const char* data) const
		{
			if ( !m_sStr || !m_sStr[0] )
			{
				if ( !data || !data[0] )
					return 0;
				else return 1;
			}
			return strcmp( m_sStr, data );
		}
		/* ����һ���ַ�������жԱ�  */
		inline int compare(const AnsiString& str) const
		{
			if ( !m_sStr || !m_sStr[0] )
			{
				if ( !str.m_sStr || !str.m_sStr[0] )
					return 0;
				else return 1;
			}
			return strcmp( m_sStr, str.m_sStr );
		}
		/* �ж��Ƿ�Ϊ���ַ��� */
		inline bool isEmpty() const
		{
			return !m_sStr || !m_sStr[0];
		}
		/*	ת���ַ�������ΪUCS-2LE��ʽ��
			���sOutput������Ϊ�ұ���ת���ɹ�������ת�������ֵ��sOutput����������sOutput��
			��ת��ʧ���򷵻�null��sOutput�����ݿ�����Ȼ��ı䣻
			���sOutput����Ϊ���Һ���ת������ɹ��򷵻��µ�CWideString���󣬴�ʱ��������Ҫ�ٺ��ʵ�ʱ��delete����ֵ��
			ת��ʧ����������NULL
		*/
		//WideString* toWStr(WideString* sOutput = NULL) const;
		/* ��ʽ���ַ��� */
		size_t format(const char* fmt, ...);
		size_t format_args(const char* fmt, va_list _Args);
	};

};

#endif

