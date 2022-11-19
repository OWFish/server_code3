#ifndef __AES_H__
#define __AES_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define AES_MIN_KEY_SIZE    16
#define AES_MAX_KEY_SIZE    32

#define AES_BLOCK_SIZE        16

typedef unsigned char    u8;
typedef signed char    s8;
typedef signed short    s16;
typedef unsigned short    u16;
typedef signed int    s32;
typedef unsigned int    u32;
typedef signed long long    s64;
typedef unsigned long long    u64;
typedef u16        __le16;
typedef u32        __le32;

#define E_KEY    (&ctx->buf[0])
#define D_KEY    (&ctx->buf[60])
#define le32_to_cpu
#define cpu_to_le32

struct aes_ctx
{
	int key_length;
	u32 buf[120];
};


void gen_tabs (void);
int aes_set_key(struct aes_ctx * ctx, const u8 *in_key, unsigned int key_len);
void aes_encrypt(struct aes_ctx * ctx, u8 *out, const u8 *in);
void aes_decrypt(struct aes_ctx * ctx, u8 *out, const u8 *in);
int AesEncrypt(struct aes_ctx * ctx,unsigned char* in, unsigned char* result, int len);
int AesDecrypt(struct aes_ctx * ctx,unsigned char* in,unsigned char* result);
/*	如果out为null则返回加密缓冲区需要的字节长度，否则返回加密后实际使用out的字节长度	*/
s64 _AESEncrypt(struct aes_ctx *ctx, unsigned char* out, const unsigned char* in, s64 inlen);
/*	成功返回0，否则返回非0值	*/
int _AESDecrypt(struct aes_ctx *ctx, unsigned char* out, const unsigned char* in, s64 inlen);

#ifdef __cplusplus
}
#endif

#endif

