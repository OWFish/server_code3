#ifndef _BZ_HASH_H_
#define _BZ_HASH_H_

/******************************************************************
 *
 *	       $ �������������ı�ѩ��ϣ�㷨ʵ�ֵ��ַ�����ϣֵ���㺯�� $
 *
 *****************************************************************/

//#ifdef __cplusplus
//extern "C" {
//#endif

/*
* Comments: �����ַ�����ϣֵ
* Param const char * str: �ַ���ָ�룬������0��ֹ���ַ���
* Param unsigned int seed: ��ϣ��������ֵ����ͬ������ֵ������Ĺ�ϣֵ��ͬ
* @Return unsigned int:
*/
unsigned int bzhashstr(const char *str, unsigned int seed);

//#ifdef __cplusplus
//}
//#endif

#endif
