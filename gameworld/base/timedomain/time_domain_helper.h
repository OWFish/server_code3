#ifndef _TIME_DOMAIN_HELPER_H_
#define _TIME_DOMAIN_HELPER_H_

/*
 为lua注册函数提供中间函数
*/

namespace TimeDomainHelper{
bool regStartScript(const char* rule);
bool regEndScript(const char* rule);
}

#endif