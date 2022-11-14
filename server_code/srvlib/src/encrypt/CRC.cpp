/************************************************************
*	 crc16的checksum计算
*    如果g_ulTable没有初始化，第一次使用的时候将初始化
***********************************************************/
#include <stddef.h>

#define CRC16_POLYNOMIAL 0x1021 // CRC_16校验方式的多项式.

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
static ulong  g_ulTable[256];

static bool has_inited = false;

// CRC_16方式校验的初始化函数, 计算CRC_16余数表.
void CRC16Init(void)
{
	if (has_inited) return;

	uint   nRemainder;
	int    n, m;
	ulong*   pulTable = g_ulTable;

	for (n = 0; n < 256; n ++)
	{
		nRemainder = (uint)n << 8;

		for (m = 8; m > 0; m --)
		{
			if (nRemainder & 0x8000)
			{
				nRemainder = (nRemainder << 1) ^ CRC16_POLYNOMIAL;
			}
			else
			{
				nRemainder = (nRemainder << 1);
			}
		}

		*(pulTable + n) = nRemainder;
	}

	has_inited = true;
}



// 反转数据的比特位, 反转后MSB为1.
// 反转前: 1110100011101110 0010100111100000
// 反转后: 1111001010001110 1110001011100000
unsigned int CRCBitReflect(ulong ulData, int nBits)
{
	ulong   ulResult = 0x00000000L;
	int    n;

	for (n = 0; n < nBits; n ++)
	{
		if (ulData & 0x00000001L)
		{
			ulResult |= (ulong)(1L << ((nBits - 1) - n));
		}

		ulData = (ulData >> 1);
	}

	return(ulResult);
}

// 以CRC_16方式计算一个数据块的CRC值.
// pucData - 待校验的数据块指针.
// nBytes - 数据块大小, 单位是字节.
// 返回值是无符号的长整型, 其中低16位有效.
unsigned int CRC16Calc(unsigned char* pucData, size_t nBytes)
{
	uint   nRemainder, nRet;

	uchar   index;

	if (has_inited == false)
	{
		CRC16Init(); //如果没有初始化就初始化以下
	}

	ulong*   pulTable = g_ulTable;
	nRemainder = 0x0000;

	for (size_t n = 0; n < nBytes; n ++)
	{
		index = (uchar)((uchar)CRCBitReflect(*(pucData + n), 8) ^ (nRemainder >> 8));
		nRemainder = (uint) * (pulTable + index) ^ (nRemainder << 8);
	}

	nRet = (uint)CRCBitReflect(nRemainder, 16) ^ 0x0000;
	return(nRet);
}

