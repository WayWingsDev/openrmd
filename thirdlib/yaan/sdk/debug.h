/*******************************************************************
 * Copyright(C), 2001-2060, 天津市亚安科技股份有限公司 版权所有
 * *****************************************************************
 * 文件名称：  debug.h
 * 作者：     zhangmingliang
 * 创建日期：  20130117
 * 描述：     本文件主要定义调试过程中用到的接口函数
 * *****************************************************************
 */

#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/*调试信息的最大长度*/
#define MAX_LOG_MSG_SIZE  4096

#define LOGERR(x, ...)

#define LOGDBG(x, ...)

#define LOGWRN(x, ...)

/*do NOT use LogOutput*/
//void LogOutput(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
