/*******************************************************************************************************
* Copyright (c) 2010,深圳市麦格斯科技有限公司终端部
* All rights reserved.
*
* 文件名称  : test.c
* 摘要      : 测试函数
*
* Current Version 1.0--wuwei--2012.08.15
* 描述：创建文件
*******************************************************************************************************
*/

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char (*PFUN)(char*,char*);

void pfun(void);

char PtrTest(void);

/*测试系统大端和小端模式 */
unsigned char SystemCheck(void);

/*测试数组和指针的关系*/
int PaucTest(void);

/*多维数组的应用测试*/
int AucTest(void);

/*多维数组测试函数*/
/*&p[4][2] - &a[4][2]的值为多少？*/
int AucTesta(void);
void PtrMemoryTest(void);

/* a.使用return的方法 */
char* GetMemory_ptr(char*p,unsigned char num);

/* b.使用2级指针的方法 */
char* GetMemory(char**p,unsigned char num);

/*测试内存分配*/
char TestMalloc(void);

/*函数指针实验函数*/
char Fun(char* Ptr1,char* Ptr2);

char PtrFun(char* ptr1,char* ptr2,PFUN cpFun);
#if 0
char PtrFun(void);
#endif

void Function(void);

void FunctionTest(void);

/************************************************************************************************************
*测试sizeof和strlen的区别
************************************************************************************************************/
void strlen_sizeof(void);

/************************************************************************************************************
*测试运算符的优先级
************************************************************************************************************/

void TestOp(void);

#endif






























