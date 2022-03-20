/*******************************************************************************************************
* Copyright (c) 2010,深圳市麦格斯科技有限公司终端部
* All rights reserved.
*
* 文件名称  : aes.h
* 摘要      : aes加密算法
*
* Current Version 1.0--wuwei--2012.08.17
* 描述：创建文件
*******************************************************************************************************
*/



#ifndef AES_H
#define AES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void AES_encrypt(unsigned char plain_text[16], unsigned char key[16], unsigned char out[16]);
void AES_decrypt(unsigned char cipher_text[16], unsigned char key[16], unsigned char out[16]);





















#endif