#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mbcs_def.h"
#include "memory/base_allocator.hpp"

#define toupper(c) (((c) >= 'a' && (c) <= 'z') ? (c) ^ 0x20 : (c))

BaseAllocator mbcsFilter("mbcsFilter");

#ifdef NEW_FILTER
void tagFT_mbcs_char::addNext(int index, tagFT_mbcs_char* next)
{
	unsigned char ridx = idx[index];
	assert(ridx == 0);
	mem = (tagFT_mbcs_char**)mbcsFilter.ReAllocBuffer(mem, (count + 1) * sizeof(tagFT_mbcs_char*));
	mem[count] = next;
	count++;
	idx[index] = count;
}
#endif

//��һ���ַ������뵽���δʱ���
int STDCALL AddMBCSFilterStrToTable(PFT_MBCS_CHAR filter, const char* str)
{
	int len = (int)strlen(str);
	PFT_MBCS_CHAR prev = filter;

	if (!filter)
		return 0;

	for (int i = 0; i < len; i++)
	{
		unsigned char index = str[i];
		index = toupper(index) - 1;

		PFT_MBCS_CHAR next = prev->getNext(index);

		if (!next)
		{
			next = CreateMBCSFilter(0);
			prev->addNext(index, next);
		}

		if (i == (len - 1))
			next->wordEnd = 1;

		prev = next;
	}

	return 1;
}

//-----------------------------------------------------------------------
PFT_MBCS_CHAR CreateMBCSFilter(void*)
{
	PFT_MBCS_CHAR pMBCSChar = 
		(PFT_MBCS_CHAR)mbcsFilter.AllocBuffer(sizeof(FT_MBCS_CHAR));
	memset(pMBCSChar, 0, sizeof(FT_MBCS_CHAR));
	return pMBCSChar;
}

void STDCALL FreeMBCSFilter(PFT_MBCS_CHAR filter)
{
	if (!filter) return;

#ifdef NEW_FILTER
	if (filter->count > 0)
	{
		for (int i = 0; i < filter->count; i++)
		{
			PFT_MBCS_CHAR next = filter->mem[i];

			if (next) FreeMBCSFilter(next);
		}
	}
	mbcsFilter.FreeBuffer(filter->mem);
#else
	for (int i = 0; i < MBCSARRAY_SIZE; i++)
	{
		PFT_MBCS_CHAR next = filter->next[i];

		if (next) FreeMBCSFilter(next);
	}
#endif

	mbcsFilter.FreeBuffer(filter);

	filter = NULL;
}

int STDCALL LoadMBCSFilterWords(PFT_MBCS_CHAR filter, const char* fn)
{
	int nStrCount = 0;
	char szText[256] = {0};
	char* pStr = 0;
	FILE* fl = fopen(fn, "r");
	//��鲢����UTF-8�ļ�BOM
	fread(szText, 3, 1, fl);

	if ((*(int*)szText & 0x00FFFFFF) != 0xBFBBEF)
		fseek(fl, 0, 0);

	while ((pStr = fgets(szText, 256, fl)))
	{
		size_t nLen = strlen(szText);

		while (nLen > 0 && ((unsigned int)szText[nLen - 1] <= 0x20))
		{
			szText[nLen - 1] = 0;
			nLen--;
		}

		if (nLen > 0 && AddMBCSFilterStrToTable(filter, szText))
			++nStrCount;
	}

	fclose(fl);

	return nStrCount;
}

char* STDCALL MatchMBCSFilterWord(const PFT_MBCS_CHAR filter, const char* input, int* matchLen)
{
	char* matchStart = NULL;	//��ƥ��������ַ�������ʼ�ַ�ָ��
	char* matchEnd = NULL;	//��ƥ����ַ����Ľ����ַ�֮���һ���ַ���ָ��,��ֵ��ȥlpMatchStart��Ϊ��ƥ���ַ����ĳ���
	unsigned char ch;

	while ((ch = *input))
	{
		ch = toupper(ch);
		PFT_MBCS_CHAR curFTChar = filter->getNext(ch - 1);

		if (curFTChar)
		{
			char* test = matchStart = (char*)input;

			do
			{
				test++;

				//�����ַ��Ƿ񴦹�����������ƥ���
				if (curFTChar->wordEnd)
					matchEnd = test;

				//�������ƥ��
				ch = *test;
				if (!ch) break;

				ch = toupper(ch);
				curFTChar = curFTChar->getNext(ch - 1);
			}
			while (curFTChar && *test);

			//������������ƥ�������ֹ
			if (matchEnd)
				break;
		}

		//����MBCS��������һ���ַ�Ӧ������2���ַ�
		//if ( (unsigned char)(*pInput) >= 0x80 )
		//	pInput += 2;
		//else pInput += 1;
		input++;
	}

	char* result = (matchEnd  ? matchStart : NULL);

	if (matchLen)
		*matchLen = (int)(size_t)(result ? (matchEnd - matchStart) : 0);

	return result;
}

