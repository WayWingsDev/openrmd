/*******************************************************************
 * Copyright(C), 2001-2060, 天津市亚安科技股份有限公司 版权所有
 * *****************************************************************
 * 文件名称：  type.h
 * 作者：     zhangmingliang
 * 创建日期：  20130219
 * 描述：     本文件主要定义调试过程中用到的接口函数
 * *****************************************************************
 */

#ifndef _TYPE_H_
#define _TYPE_H_

/**************************************************************
 * The common data type, will be used in the whole project
 **************************************************************/

typedef unsigned char           U8;
typedef unsigned short          U16;
typedef unsigned int            U32;

typedef signed char             S8;
typedef short                   S16;
typedef int                     S32;

#ifndef _M_IX86
    typedef unsigned long long  U64;
    typedef long long           S64;
#else
    typedef __int64             U64;
    typedef __int64             S64;
#endif

typedef char                    CHAR;
#define VOID                    void

/************************************************
 * const defination
 ************************************************/
typedef enum
{
    FALSE = 0,
    TRUE  = 1,
} BOOL;

#ifndef NULL
#define NULL    0L
#endif

#endif
