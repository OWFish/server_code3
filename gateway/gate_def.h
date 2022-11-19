#pragma once

#define MSG_LOG(format, ...) OutputMsg(rmNormal, "[%s:%d %s] "#format, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);
#define MSG_WAR(format, ...) OutputMsg(rmWarning, "[%s:%d %s] "#format, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);
#define MSG_TIP(format, ...) OutputMsg(rmTip, "[%s:%d %s] "#format, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);
#define MSG_ERR(format, ...) OutputMsg(rmError, "[%s:%d %s] "#format, __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__);

#define OrderSwap16(A) (((uint16_t)(A) >> 8) | ((uint16_t)(A & 0xFF) << 8))
#define OrderSwap32(A) (OrderSwap16((uint32_t)(A) >> 16) | ((uint32_t)(OrderSwap16(A)) << 16))
#define OrderSwap64(A) (OrderSwap32((uint64_t)(A) >> 32) | ((uint64_t)(OrderSwap32(A)) << 32));
