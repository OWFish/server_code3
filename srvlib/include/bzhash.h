#ifndef _BZ_HASH_H_
#define _BZ_HASH_H_

/******************************************************************
 *
 *	       $ 基于网上流传的暴雪哈希算法实现的字符串哈希值计算函数 $
 *
 *****************************************************************/

//#ifdef __cplusplus
//extern "C" {
//#endif

/*
* Comments: 计算字符串哈希值
* Param const char * str: 字符串指针，必须是0终止的字符串
* Param unsigned int seed: 哈希计算种子值，不同的种子值计算出的哈希值不同
* @Return unsigned int:
*/
unsigned int bzhashstr(const char *str, unsigned int seed);

//#ifdef __cplusplus
//}
//#endif

#endif
