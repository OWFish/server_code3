#ifndef _WELL_RNG_H_
#define _WELL_RNG_H_

/******************************************************************
 *
 *	$ 基于WELL算法实现的快速随机函数库 $
 *  
 *  - 主要功能 - 
 *
 *	实现快速的波动更无规律的随机数算法
 *
 *****************************************************************/

/*
* Comments: 使用WELL算法产生一个随机数，产生的随机数在0到max以内。
* Param unsigned long max: 随机数上限
* @Return unsigned long:
*/
//#ifdef __cplusplus
//extern "C" {
//#endif

//范围一个[0,max)之间的随机数
unsigned long wrand(unsigned long max);
/*
* Comments: 初始化随机种子表
* Param unsigned int seed: 种子值，如果值为0则自动使用time()值作为种子
* 该函数在整个程序中调用一次即可。也可以不调用，只是每次运行第N次随机产生的值都一样。
*/
void winitseed(unsigned int seed);

//返回一个随机数
unsigned long wrandvalue();

//#ifdef __cplusplus
//}
//#endif

#endif
