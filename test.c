/*******************************************************************************************************
* Copyright (c) 2010,深圳市麦格斯科技有限公司终端部
* All rights reserved.
*
* 文件名称  : test.c
* 摘要      : 指针和数组的测试函数
*
* Current Version 1.0--wuwei--2012.08.15
* 描述：创建文件
*******************************************************************************************************
*/

#include "test.h"


void pfun(void)
{
	int res = 100;
	printf("res = %d\n", res);
	printf("res = %d\n",res);
}

/*数组指针的测试函数*/
char PtrTest(void)
{
	char a[5] = {'A','B','C','D'};
	char (*p3)[5] = &a;
	//char (*p4)[5] = a;
	return 0;
}

/*测试系统的大小端模式函数,如果返回值为0x36的时候就为小端模式，为0x35时就为大端模式*/
unsigned char SystemCheck(void)
{
	// printf("测试系统大小端模式\n");
	// union DataCheck
	// {
	// 	int iData;
	// 	unsigned char ucRet;
	// }*p,unData;

	// union DataTemp
	// {
	// 	int iData;
	// 	unsigned char ucData;
	// };

	// DataTemp data;
	// data.iData = 0x00003344;
	// DataTemp *p1;
	// p1=&data;
	// printf("p->ucData的值%x\n",p1->ucData);
	// printf("data.ucData的值%x\n",data.ucData);
	
	// unData.iData = 0x00003536;
	// p = &unData;
	// printf("%x\n",unData.ucRet);
	return 0;
}

/*测试指针*/
void PtrMemoryTest(void)
{
	int i = 10;
	int j = 100;
	i = 1000;
	int *p=(int *)0x0018fee0;
	*p = NULL;
	p = NULL;
}
/*测试数组和指针的关系*/
int PaucTest(void)
{
	printf("测试数组指针关系\n");
	int a[4] = {1,2,3,4};
	int *ptr1 = (int*)(&a+1);/*数组a的首地址加上4*sizeof(a)*/
	int *ptr2 = (int*)((int)(a+1));/*数组a首元素地址加上sizeof(int)=数组a的第二个元素的首地址*/
	printf("%x,%x\n",ptr1[-1],*ptr2);/*ptr[-1]数组a的第四个元素的首地址,*ptr2=数组a的第二个元素首地址*/
	return 0;
}

/*多维数组的应用测试*/
/********************************************************************************************
逗号表达式，又称为“顺序求值运算符”。逗号表达式的一般形式为

　　　　　　　　 表达式1,表达式2

逗号表达式的求解过程是：先求解表达式1，再求解表达式2。整个逗号表达式的值是表达式2的值

********************************************************************************************/
int AucTest(void)
{
	int a[3][2] = {(0,1),(2,3),(4,5)};/*花括号里面是逗号表达式(逗号表达式又叫顺序求值运算符)*/
	int *p;
	p = a[0];
	printf("%d\n",p[0]);/*打印出来的是1不是0.此处要特别注意*/
	return 0;
}

/*多维数组测试函数*/
/*&p[4][2] - &a[4][2]的值为多少？*/
int AucTesta(void)
{
	int a[5][5];
	int (*p)[5];
	p=a;
	printf("a_ptr=%#p,p_ptr=%#p\n",&a[4][2],&p[4][2]);
	printf("%p,%d\n",&p[4][2]-&a[4][2],&p[4][2]-&a[4][2]);
	return 0;
}

/* 无法把指针变量本身传给函数解决办法 */

/* a.使用return的方法 */
#if 1
char* GetMemory_ptr(char*p,unsigned char num)
{
	p = (char*)malloc(num*sizeof(char));
	return p;
}
#else

/* b.使用2级指针的方法 */
char* GetMemory(char**p,unsigned char num)
{
	*p = (char*)malloc(num*sizeof(char));
	return *p;
}
#endif

/*测试内存分配*/
char TestMalloc(void)
{
	char *Str = NULL;
	#if 1
	Str = GetMemory_ptr(Str,10);
	#else
	Str = GetMemory(&Str,10);
	#endif
	strcpy(Str,"hello!");/*字符串拷贝函数把hello!拷贝给Str*/
	printf("%s\n",Str);
	free(Str);
	return 0;
}


/******************************************************************************************************
函数指针的定义:
a)char*(*fun1)(char* p1,char* p2);fun1为一个指针变量，它指向一个函数，这个函数有2个指针类型的参数其返回
值也是一个指针。可以把表达式写成char*(*)(char* p1,char* p2) fun1.

b)char** fun2(char* p1,char* p2);函数返回值为char**

c)char* fun3(char* p1,char* p2); 函数返回值为一个char类型的指针


*****************************************************************************************************/


/*函数指针实验函数*/
char Fun(char* Ptr1,char* Ptr2)
{
	int i = 0;
	i = strcmp(Ptr1,Ptr2);
	return i;
}

char PtrFun(char* ptr1,char* ptr2,PFUN cpFun)
{
	char RetPtr = 0;
	//char(*pf)(char* Ptr1,char* Ptr2);/* pf指向一个函数，此函数有2个指针参数和char类型的返回值 */
	//pf = &Fun;/* 此处还可以写成pf = Fun; */
	//RetPtr = (*pf)("Bb","aa");
	RetPtr = cpFun(ptr1,ptr2);
	printf("%d\n",RetPtr);
	return 0;
}

#if 0
char PtrFun(void)
{
	char RetPtr = 0;
	char(*pf)(char* Ptr1,char* Ptr2);/* pf指向一个函数，此函数有2个指针参数和char类型的返回值 */
	pf = &Fun;/* 此处还可以写成pf = Fun; */
	RetPtr = (*pf)("Bb","aa");	
	printf("%d\n",RetPtr);
	return 0;
}
#endif


/* *(int*)&p ----这是什么？ */
void Function(void)
{
	printf("call function!\n");
}

void FunctionTest(void)
{
	void (*p)();/* 定义指针变量p指向一个没有返回值没有参数的函数 */
	/* &p-求指针p的地址，为一个32位二进制的常数.(int*)&p-把p的地址强制转换为一个int型的指针 */
	/*(int)Function 表示将函数的入口地址强制转换成 int类型的数据。*/
	/* *(int*)&p=(int)Function;表示将函数的入口地址赋值给指指针变量P*/
	*(int*)&p = (int)Function;
	(*p)();/*调用函数Function*/
}
/***********************************************************************************************************
有以上2个函数可以看出使用函数指针的好处：可以将实现同一功能的多个模块统一起来标识。也可以说
便于分层设计、利于系统抽象、降低耦合度以及使接口与实现分开
***********************************************************************************************************/


/**********************************************************************************************************
*函数指针数组的指针学习
*char*(*pf[3])(char* p1,char* p2);定义一个函数指针数组，它是一个数组，数组名为pf，数组内存有3个元素，每一个元素
*都指向一个函数指针
***********************************************************************************************************/







/************************************************************************************************************
*测试sizeof和strlen的区别
************************************************************************************************************/
void strlen_sizeof()
{
	char auc[]="abcde";
	char *p = NULL;
	p = auc;
	//size_lens = sizeof(auc);
	//strlens = strlen(auc);
	
	printf("*p sizeof value is:%d\n", sizeof(*p));
	printf("p sizeof value is:%d\n", sizeof(p));
	printf("size_lens value is:%d\n", sizeof(auc));//打印的值包括'/'
	printf("strlens value is:%d\n",strlen(auc));//打印的不包括 '/'

}

/************************************************************************/
/* 测试运算符的优先级                                                   */
/* 发现“+”的优先级比“*=”高。所以先运行i+j，在执行 *=，最后的结果为40*/
/************************************************************************/

void TestOp(void)
{
	int i = 10;
	int j = 10;
	int k = 2;

	k *= i + j;

	printf("k=%d\n",k);
}



