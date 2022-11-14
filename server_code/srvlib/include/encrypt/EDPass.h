#ifndef _ED_PASS_H_
#define _ED_PASS_H_
/**
*	加密密码字符串
*	sDest			加密输出缓冲区
*	nDestSize		输出缓冲区长度(如果空间足够，则会在sDest末尾添加终止字符)
*	sPassWord		密码字符串
*	sKey128Bit		16字节的密钥字符串
**/
const char* EncryptPassword(char* sDest, int nDestSize, const unsigned char* sPassWord, const unsigned char* sKey128Bit);

/**
*	解密密码字符串
*	sDest			解密输出缓冲区
*	nDestSize		输出缓冲区长度(如果空间足够，则会在sDest末尾添加终止字符)
*	sPassWord		加密过的密码字符串
*	sKey128Bit		16字节的密钥字符串
**/
const char* DecryptPassword(char* sPassword, int nPasswordLen, const unsigned char* sEncrypted, const unsigned char* sKey128Bit);

#endif

