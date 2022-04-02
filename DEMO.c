/*******************************************************************************************************
* Copyright (c) 2010,深圳市麦格斯科技有限公司终端部
* All rights reserved.
*
* 文件名称  : main.c
* 摘要      : 主函数
*
* Current Version 1.0--wuwei--2012.08.15
* 描述：创建文件
*******************************************************************************************************
*/


#include "test.h"
#include "memory.h"
#include "aes.h"
#include "circleBuffer.h"
#include <stdlib.h>


void testfun(void)
{
	int a[5] = {1,2,3,4,5};
	int *p = (int*)(&a+1);
	printf("%d,%d\n",*(a+1),*(p-1));
}



int main(int argc, char* argv[])
{
	//char a[5] = {'a','b','c','d','e'};
	//char (*p3)[3]=&a;
	//char (*p4)[3]=&a;
	//char a='a';
	//char b='b';
	//int h = 0;
	//h = GetVal();
	//printf("%d\n",h);
	//PtrMemoryTest();
	//SystemCheck();
	//PaucTest();
	//AucTest();
	//AucTesta();
	//TestMalloc();
	//PtrFun(&a,&b,Fun);/* 比较a和b的值，如果a>b则返回1,否则返回-1 */
	//FunctionTest();
	//PmemoryTest();
	//Pmalloc();
	//ResFun(10);
	//strlen_sizeof();
	//memory();
#if 1
	/************************************************************************/
	/* 测试函数的返回值                                                     */
	/************************************************************************/
	char *p = NULL;
	char c = 0;
	p = GetStr();
	c = GetVal();
	printf("%s\n",p);
	printf("%d\n",c);
#endif
	/************************************************************************/
    /* 测试运算符的优先级                                                   */
    /* 发现“+”的优先级比“*=”高。所以先运行i+j，在执行 *=，最后的结果为40*/
    /************************************************************************/
	//TestOp();
#if 0

	unsigned char cipher_text[16];

//D6 B8 CD 1D 36 F1 86 73 63 E5 BD 65 0B 4D A5 0A
    unsigned char key[16]        = {0xd6, 0xb8, 0xcd, 0x1d, 0x36, 0xf1, 0x86, 0x73, 0x63, 0xe5, 0xbd, 0x65, 0x0b, 0x4d, 0xa5, 0x0a};
//8D CE 26 23 11 3C E2 DB 28 63 12 75 90 37 F6 18
    unsigned char plain_text[16] = {0x8d, 0xce, 0x26, 0x23, 0x11, 0x3c, 0xe2, 0xdb, 0x28, 0x63, 0x12, 0x75, 0x90, 0x37, 0xf6,0x18};


    AES_encrypt(plain_text, key, cipher_text);
    printf("%s\n","ok");

#endif

#if 0
	unsigned char cipher_text[16];

//D6 B8 CD 1D 36 F1 86 73 63 E5 BD 65 0B 4D A5 0A
    unsigned char key[16]        = {0xd6, 0xb8, 0xcd, 0x1d, 0x36, 0xf1, 0x86, 0x73, 0x63, 0xe5, 0xbd, 0x65, 0x0b, 0x4d, 0xa5, 0x0a};
//02 130000 000000 9ff7 00 00 00 00 00 00 00
    unsigned char plain_text[16] = {0x02, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9f, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00};


    AES_encrypt(plain_text, key, cipher_text);
    printf("%s\n","ok");

#endif
	printf("sdasdasdasdsd\r\n");
	system("pause");
	return 0;
}





