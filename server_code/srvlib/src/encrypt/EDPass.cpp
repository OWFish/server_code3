#include <stdlib.h>
#include <string.h>
#include "aes.h"
#include "base64.h"
#include "share_util.h"

static int boInited = 0;
static const int Bits128 = 16;

const char* EncryptPassword(char* sDest, int nDestSize, const unsigned char* sPassWord, const unsigned char* sKey128Bit)
{
	struct aes_ctx ctx;
	int nInSize;
	char* sBuffer;
	char* sBase64Buffer;
	int nSize;

	if (!boInited)
	{
		boInited = 1;
		gen_tabs();
	}

	aes_set_key(&ctx, (const u8*)sKey128Bit, Bits128);

	nInSize = (int)strlen((const char*)sPassWord) * sizeof(sPassWord[0]);
	sBuffer = (char*)malloc(nInSize * 8 + 4);
	sBase64Buffer = sBuffer + nInSize * 2;

	nSize = (int)_AESEncrypt(&ctx, (unsigned char*)sBuffer, sPassWord, nInSize);
	nSize = base64_encode(sBase64Buffer, sBuffer, nSize);
	sBase64Buffer[nSize] = 0;

	_STRNCPY_S(sDest, sBase64Buffer, nDestSize);

	free(sBuffer);
	return sDest;
}


const char* DecryptPassword(char* sPassword, int nPasswordLen, const unsigned char* sEncrypted, const unsigned char* sKey128Bit)
{
	struct aes_ctx ctx;
	int nInSize;
	char* sAESBuffer;
	char* sBuffer;
	int nSize;

	if (!boInited)
	{
		boInited = 1;
		gen_tabs();
	}

	aes_set_key(&ctx, (const u8*)sKey128Bit, Bits128);


	nInSize = (int)strlen((const char*)sEncrypted) * sizeof(sEncrypted[0]);
	sAESBuffer = (char*)malloc(nInSize * 8 + 4);
	sBuffer = sAESBuffer + nInSize * 2;

	nSize = base64_decode(sAESBuffer, (const char*)sEncrypted, nInSize);
	_AESDecrypt(&ctx, (unsigned char*)sBuffer, (const unsigned char*)sAESBuffer, nSize);
	sBuffer[nSize] = 0;

	_STRNCPY_S(sPassword, sBuffer, nPasswordLen);

	free(sAESBuffer);
	return sPassword;
}


