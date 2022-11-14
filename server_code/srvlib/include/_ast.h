#ifndef	_MDBG_H_
#define	_MDBG_H_

/*	����Win32Ӧ�ó����Assert��	*/
#ifndef Assert

#ifdef	_DEBUG
#include <assert.h>
#define	Assert	assert
#define DbgAssert assert
#else
#define	Assert(exp)	(exp)
#define DbgAssert(exp)	//ʲô������
#endif

#endif	// --> #ifndef Assert

#ifndef	TRACE

#ifdef _DEBUG
#define	TRACE	_mdbgOutputDbgStr

static void _mdbgOutputDbgStr(const char* szFormat, ...)
{
	static char szStaticBuf[4096];

	va_list	args;
	va_start(args, szFormat);
	vsprintf(szStaticBuf, szFormat, args);
	va_end(args);
#ifdef _MSC_VER
	OutputDebugString(szStaticBuf);
#else
	perror(szStaticBuf);
#endif
}
#else
#define	TRACE
#endif
#endif	// --> #ifndef	TRACE


/*	���嵱ǰ�ļ��Լ��е��ַ�����ȡ�ĺ�(��ȡ���ַ������磺abc.cpp(2000))	*/
#ifndef __FILE_LINE__


#define	_TLN(LN)		#LN
#define	__TLINE__(LN)	_TLN(LN)
#define	__FILE_LINE__	__FILE__"("__TLINE__(__LINE__)")"

#endif  // --> #ifndef	__FILE_LINE__

/*	�����ڱ������������������ݵĺ꣬�������л��Զ������ļ��Լ��кŲ���˫��������ں����ֱ�Ӷ�λ����Ϣ������ */
#ifndef __CPMSG__

#define	__CPMSG__(MSG)	message( __FILE_LINE__ " : " #MSG )

#endif	// --> ifndef __CPMSG__


/* ����SafeDelete��SafeDeleteArray��SafeFree�Լ�SafeRelease�� */
#ifndef	SafeDelete
#define	SafeDelete(p)	if (p) { delete p; p = NULL; }
#endif

#ifndef	SafeDeleteArray
#define	SafeDeleteArray(p)	if (p) { delete [] p; p = NULL; }
#endif

#ifndef	SafeFree
#define	SafeFree(p)	if (p) { free(p); p = NULL; }
#endif

#ifndef SafeRelease
#define	SafeRelease(p)	if (p){ p->Release(); p = NULL; }
#endif

#define ArrayCount(a)	(sizeof(a) / sizeof((a)[0]))

#endif
