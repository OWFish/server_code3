#ifndef	_SHAREUTIL_H_
#define	_SHAREUTIL_H_

#include <time.h>
#include <stdarg.h>
#include "os_def.h"

#ifndef	STDCALL
#ifdef _MSC_VER
#define	STDCALL __stdcall
#else
#define STDCALL
#endif
#endif

#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)))
#  define GCC_UNUSED __attribute__((unused))
#else
#  define GCC_UNUSED
#endif

#define STATIC_ASSERT(Expr) typedef char UnName##__LINE__[(Expr) ? 1 : -1] GCC_UNUSED;  // ��̬����
#define COMPILE_ASSERT STATIC_ASSERT

//�ȴ����ر��߳�
#ifdef _MSC_VER
#define	CloseThread(ht)		if ( ht ) { WaitForSingleObject( ht, INFINITE ); CloseHandle( ht ); (ht) = NULL; }
#define itoa _itoa
#define I64FMT "%I64d"
#define os_assert assert
#else
#define itoa(n, s, x) sprintf(s, "%d", n)
#define I64FMT "%lld"
#define os_assert
#endif

#ifndef SafeDelete
#define	SafeDelete(p)		if ( p ){ delete p; p = NULL; }
#endif

//��ȡ���鳤��
#ifndef ArrayCount
#define	ArrayCount(a)		(sizeof(a)/sizeof((a)[0]))
#endif

#ifdef _MSC_VER
//�����ַ������ַ����飨֧��MBCS��UCS��
#ifndef _asncpy
#define	_asncpy(dest, src)	_tcsncpy(dest, src, sizeof(dest)/sizeof(TCHAR)-1)
//#define strlcpy strncpy
#endif
//�����ַ������ַ����鲢�����ֹ�ַ���֧��MBCS��UCS��
#ifndef _asncpyt
#define	_asncpyt(dest, src)	{ _tcsncpy(dest, src, sizeof(dest)/sizeof(TCHAR)-1); dest[sizeof(dest)/sizeof(TCHAR)-1] = 0;}
#endif
#endif

//����MBCS�ַ�����MBCS�ַ����鲢�����ֹ�ַ�
#define _STRNCPY_S strlcpy
#define _STRNCAT_S strlcat
#define _STRNCPY_A(dest, src) {strlcpy((dest), (src), sizeof(dest));}	// ���Զ���NULL
#define _STRNCAT_A(dest, src) {strlcat((dest), (src), sizeof(dest));}

//���ַ�����ֹ��ָ������
#ifndef STRNTERM
#define STRNTERM(s, l)	s[l] = 0;
#endif

//ȡ64λ�����ĵ�32λ����
#ifndef LO_INT64
#define LO_INT64(S)           ((unsigned int)((uint64_t)(S) & 0xffffffff))
#endif
//ȡ64λ�����ĸ�32λ����
#ifndef HI_INT64
#define HI_INT64(S)           ((unsigned int)((uint64_t)(S) >> 32))
#endif

//ò��vc��û��snprintf�������,�ṩ��_snprintf����,��gcc��snprintf��_snprintf����ֵ���в���ģ����Ҫע��
//�����ʽ���ĳ��ȴ����ṩ���ֽڳ��ȣ�_snprintf����-1����snprintf�Ƿ���ʵ�ʵĳ���
#ifndef _MSC_VER
#define SNPRINTF snprintf
#define STRNCASECMP strncasecmp
#else
#define SNPRINTF _snprintf	
#define STRNCASECMP _strnicmp
#endif

//����ָ�����ȣ�len,������ֵ��[0-len]����Ҫ��snprintf���س������жϵ�ͳһ���������
int SNPRINTFA(char *dst, int len, const char *format, ...);

int VSNPRINTFA(char *dst, int len, const char *format, va_list args);

size_t strlcpy(char *dst, const char *src, size_t siz);
size_t strlcat(char *dst, const char *src, size_t siz);

//�ַ���hash����
unsigned int hashstr(const char* str);
//�ַ���hash��������Ҫ�ṩ����
unsigned int hashlstr(const char* str, size_t len);

struct SystemTime
{
	int sec_;     /* seconds after the minute - [0,59] */
	int min_;     /* minutes after the hour - [0,59] */
	int hour_;    /* hours since midnight - [0,23] */
	int mday_;    /* day of the month - [1,31] */
	int mon_;     /* months since January - [1,12] */
	int year_;    /* years */
	int wday_;    /* days since Sunday[0--6], Sunday:0, Monday:1 ...*/
};

void GetSystemTime(SystemTime& sysTime);

//�����Ϣ����
typedef enum tagShareOutputMsgType
{
	rmNormal = 0,
	rmWarning,
	rmTip,
	rmError,
}SHAREOUTPUTMSGTYPE;

//��Ϣ�����������
typedef	int (STDCALL *SHAREOUTPUTMSGFN)	(SHAREOUTPUTMSGTYPE MsgType, const char * msg, int len);


//ȫ����Ϣ�������
int	 STDCALL OutputMsg(SHAREOUTPUTMSGTYPE MsgType, const char * format, ...);
//ȫ�ִ����������
//ɾ���Ĵ����ʽΪ��sprintf(sFormat, ...) + ������ + ��������
int  STDCALL OutputError(const int errcode, const char * format, ...);
//��ʼ��ȫ����Ϣ���
void STDCALL InitDefMsgOut();
//����ʼ��ȫ����Ϣ���
void STDCALL UninitDefMsgOut();

//����ȫ����Ϣ�������,���ص�ǰ����Ϣ�������
SHAREOUTPUTMSGFN STDCALL SetOutputMsgFn(SHAREOUTPUTMSGFN fn);

#ifdef _MSC_VER

//Ĭ�ϵ��쳣������
long WINAPI DefaultUnHandleExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo);
//��ȡϵͳ�ṩ�Ĵ�����������
const char * GetSysErrorMessage(const int ErrorCode, char* sBuffer, size_t dwBufferSize, size_t *dwBufferNeeded);
void SetMiniDumpFlag(int nFlag, const char* dump_file);
#endif


//�ַ���ת64λ����
long long int StrToInt64(const char * sText);
//�ַ���ת32λ����
int StrToInt(const char * sText);

#define NOW_T	time(NULL)
#define TIME_CHECK(X,Y) (X) > (Y)
#define TIME_CHECK_NOW(Y) TIME_CHECK((NOW_T),(Y))

bool CheckIdentity(const char *id, bool *enough18);

#define MAKEFOUR(ch0, ch1, ch2, ch3)                              \
	((unsigned int)(unsigned char)(ch0) | ((unsigned int)(unsigned char)(ch1) << 8) |   \
	((unsigned int)(unsigned char)(ch2) << 16) | ((unsigned int)(unsigned char)(ch3) << 24 ))

#ifndef _MSC_VER
void Fork();

#else

//#define _M_DBGFUNC_BEGIN { __try {
//#define _M_DBGFUNC_END }__except (DefaultUnHandleExceptionFilter(GetExceptionInformation()),EXCEPTION_EXECUTE_HANDLER){OutputMsg( rmTip, ("abnormal output!!!") );}}

#endif
#define _M_DBGFUNC_BEGIN
#define _M_DBGFUNC_END

void OutputWatchFile(const char* str, const char* fn = NULL);

void CheckDate();
#endif
