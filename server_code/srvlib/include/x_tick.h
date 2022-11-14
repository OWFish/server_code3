#ifndef _MTICK_H_
#define _MTICK_H_


/******************************************************************
 *
 *	$ ��ǿGetTickCount������ $
 *  
 *  - ��Ҫ���� - 
 *
 *	��ʹ��64λ��TickCount���ڲ������TickCount�ڳ���49������¿�ʼ�����⡣
 *  ͬʱ���ṩ��һ��������������ʹ��ͬ����TickCount�Ļ��ƣ���ͨ��SetTickCountEx
 *  ����������ͬ����ʱ��ֵ���Ӷ������ڶദ�����в�ͬ������֮���Ƶ�ʲ������������
 *
 *****************************************************************/
#include "os_def.h"

#define _getTickCount		tick64::GetTickCountEx
//#define _timeGetTime		tick64::GetTickCountEx

namespace tick64
{
	//ȡ��������ʱ��ĺ������������ص��Ǻ���ֵ��
	//���Ӳ��֧�ֲ�ѯPerformanceCounter��ɱ���49����������������
	/***
	  ʵ�ʲ��Ժ�˺������ܽϲ��Ϊ��ѯCPU�жϻᵼ�½����ں˲����ܹ���
	  r3�����̡߳������ڶദ�������������������֮��Ƶ�����������
	  �����ɲ�ͬ�̵߳����������ε��ã�����ȡ�õ�ʱ��ֵ��ǰ��Ҫ������⡣
	***/

	#ifdef _MTICK64
	typedef int64_t TICKCOUNT64;
	typedef TICKCOUNT64	TICKCOUNT;
	#	define GetTickCountEx		GetTickCount64
	TICKCOUNT64 GetTickCount64();
	#else
	typedef int64_t	TICKCOUNT;
	//typedef TICKCOUNT32	TICKCOUNT;	
	#	define GetTickCountEx		GetTickCount32
	TICKCOUNT GetTickCount32();
	#endif

};

#endif
