#ifndef _BASE64_H_
#define _BASE64_H_

//#ifdef __cplusplus
//extern "C"
//{
//#endif

int base64_encode(char *out, const char *data, int insize);
int base64_decode(char *out, const char *bdata, int insize);

//#ifdef __cplusplus
//}
//#endif

#endif
