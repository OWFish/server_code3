//#include <Windows.h>
#include "encrypt/CRC.h"
#include "encrypt/Encrypt.h"
#include <time.h>

void Encrypt::SetSelfSalt(int salt)
{
	if (salt)
	{
		m_nSelfSalt = salt;
	}
}
int Encrypt::GenSalt()
{
	int salt = 0;
	do
	{
		salt = (unsigned int) wrand((int) time(NULL));
	}
	while (! salt);

	return salt;
}
void Encrypt::SetTargetSalt(int salt)
{
	m_nTargetSalt = salt;

	if (m_nSelfSalt == 0)
	{
		m_nSelfSalt = GenSalt();
	}

	GenKey();
}

void Encrypt::GenKey()
{
	if (m_nSelfSalt &&  m_nTargetSalt)
	{
		m_nKey = (m_nSelfSalt ^  m_nTargetSalt) + 8254;
		*((int*)m_sKeybuff) = m_nKey;
	}
}

bool Encrypt::Encode(char* pInBuff, size_t len, char* pOutBuff)
{
	if (m_nSelfSalt && m_nTargetSalt)
	{
		for (size_t i = 0; i < len; i++)
		{
			pOutBuff[i] =  pInBuff[i] ^ m_sKeybuff[i & 3];
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool Encrypt::Decode(char* pInBuff, size_t len, char* pOutBuff)
{
	//当前的加密算法和解密算法是一样的,反向操作
	return Encode(pInBuff, len, pOutBuff);
}

