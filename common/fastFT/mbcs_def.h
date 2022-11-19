#ifndef _MBCSDEF_H_
#define _MBCSDEF_H_

#define MBCSARRAY_SIZE 255

#define NEW_FILTER

#pragma pack(push, 1)
typedef struct tagFT_mbcs_char
{
	char	wordEnd;										//�����ַ��Ƿ񹹳�һ�����������δ�
#ifdef NEW_FILTER
	unsigned char idx[MBCSARRAY_SIZE];
	unsigned char count;
	tagFT_mbcs_char** mem;
#else
	struct tagFT_mbcs_char* next[MBCSARRAY_SIZE];		//��ǰ�ַ��ĺ����ַ�����������Ϊ�ַ�ֵ-1
#endif

#ifdef NEW_FILTER
	tagFT_mbcs_char* getNext(int index)
	{
		if (!mem) return NULL;
		unsigned char ridx = idx[index];
		if (ridx == 0) return NULL;
		return mem[ridx - 1];
	}
	void addNext(int index, tagFT_mbcs_char* next);
#else
	tagFT_mbcs_char* getNext(int index)
	{
		return next[index];
	}
	void addNext(int index, tagFT_mbcs_char* next)
	{
		next[index] = next;
	}
#endif

}FT_MBCS_CHAR, *PFT_MBCS_CHAR;
#pragma pack(pop)

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef STDCALL
#if (defined(WIN32) || defined(WINDOWS))
#define STDCALL __stdcall
#else
#define STDCALL
#endif
#endif

/*
����һ��MBCS���δʱ�
*/
PFT_MBCS_CHAR CreateMBCSFilter(void*);
/*
����һ��MBCS���δʱ��ͷű�ʹ�õ������ڴ�
*/
void STDCALL FreeMBCSFilter(PFT_MBCS_CHAR filter);
int STDCALL LoadMBCSFilterWords(PFT_MBCS_CHAR filter, const char *fn);
char* STDCALL MatchMBCSFilterWord(const PFT_MBCS_CHAR filter, const char *input, int *matchLen);
//��һ���ַ������뵽���δʱ���
int STDCALL AddMBCSFilterStrToTable(PFT_MBCS_CHAR filter,const char* str);

#ifdef __cplusplus
}
#endif

#endif

