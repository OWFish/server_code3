#ifndef	_CRC_H_
#define	_CRC_H_

// 以CRC_16方式计算一个数据块的CRC值.
// pData - 待校验的数据块指针.
// nBytes - 数据块大小, 单位是字节.
// 返回值是无符号的长整型, 其中低16位有效.
#include <stddef.h>

unsigned int CRC16Calc(unsigned char *pData, size_t nBytes);

#endif

