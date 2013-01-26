/*
 * Loger.h
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#ifndef LOGER_H_
#define LOGER_H_

#include <android/log.h>

#define  LOGV(tag, ...)  __android_log_print(ANDROID_LOG_VERBOSE,tag,__VA_ARGS__)
#define  LOGD(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG,tag,__VA_ARGS__)
#define  LOGI(tag, ...)  __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)
#define  LOGW(tag, ...)  __android_log_print(ANDROID_LOG_WARN,tag,__VA_ARGS__)
#define  LOGE(tag, ...)  __android_log_print(ANDROID_LOG_ERROR,tag,__VA_ARGS__)



#endif /* LOGER_H_ */
