#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

//#include <Windows.h>
#include "wrand.h"
class  Encrypt
{
public:
	Encrypt()
	{
		m_nSelfSalt = 0;
		m_nTargetSalt = 0;
		m_nKey = 0;
		m_nSelfSalt = 0;

	}
	void SetSelfSalt(int salt); //设置自己的随机数
	void SetTargetSalt(int salt);  //设置通信方的随机数,同时会生成key

	int GetSelfSalt()
	{
		return m_nSelfSalt;   //获取自身的随机数
	}

	bool Encode(char* pInBuff, size_t len, char* pOutBuff); //加密数据

	bool Decode(char* pInBuff, size_t len, char* pOutBuff); //解密数据

	inline bool IsKeyCrcCorrect(unsigned short nKeyCRC)  //
	{
		return (GetKeyCRC() == nKeyCRC);
	}

	inline static unsigned short CRC16(const char* lpBuffer, size_t len)  //计算CRC-16的Checksum
	{
		return (unsigned short)CRC16Calc((unsigned char*)lpBuffer, len);
	}
	inline int GetKey()
	{
		return m_nKey;
	}
	unsigned int GetKeyCRC() //获取key的crc值
	{
		return (CRC16((const char*)m_sKeybuff, 4));
	}
private:
	void  GenKey();      //产生密钥

	int   GenSalt(); // 产生salt
private:
	int m_nSelfSalt;    //自己产生的随机数
	int m_nTargetSalt;  //通信方的随机数
	int m_nKey;         //密钥
	unsigned char m_sKeybuff[4] ;  //密钥的buff，添加这个为了方便计算
};


#endif
