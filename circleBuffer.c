#ifdef __cplusplus
extern "C"{
#endif

/******************************************************************************************************
* Copyright (c) 2010,深圳市麦格斯科技有限公司软件部
* All rights reserved.
*
* 文件名称  ：CirclueBuffer.c
* 摘要      ：循环队列的接口
*
* Current Version 1.0--xiefuwei--2011.09.16
* 描述： Create This file
*        循环队列的操作接口，包括写数据，读数据，清空数据等等
*
*******************************************************************************************************
*/

#include "circleBuffer.h"

/******************************************************************************************************
*
* 函数介绍：    CircularBufInit --初始化循环队列
* 输入参数说明：pstBuffer       --要初始化的队列指针
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char CircularBufInit(CIRCLE_BUFF_T* pstBuffer)
{
    if (pstBuffer == NULL)
    {
        return -1;
    }

    /* init the dynamic info */
    pstBuffer->ucReId    = 0;
    pstBuffer->ucWrId    = 0;
    pstBuffer->ucCurrLen = 0;
    memset(pstBuffer->aucBuffer, 0, sizeof(pstBuffer->aucBuffer));

    return 0;
}

/******************************************************************************************************
*
* 函数介绍：    getCircularbufCursize --获取循环队列的已使用空间长度
* 输入参数说明：pCBHandle             --队列指针
* 输出参数说明：无
* 返回值：      成功返回长度,失败返回 0
*******************************************************************************************************
*/
unsigned char GetCircularbufCursize(CIRCLE_BUFF_T *pCBHandle)
{
    if (NULL == pCBHandle)
    {
       return 0;
    }

	return pCBHandle->ucCurrLen;
}

/******************************************************************************************************
*
* 函数介绍：    resetCircularBuf --重置一个循环队列
* 输入参数说明：pCBHandle        --队列指针
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char ResetCircularBuf(CIRCLE_BUFF_T *pCBHandle)
{
    if (NULL == pCBHandle)
    {
        return -1;
    }

    pCBHandle->ucCurrLen = 0;
    pCBHandle->ucReId = 0;
    pCBHandle->ucWrId = 0;

    return 0;
}

/******************************************************************************************************
*
* 函数介绍：    writeCircularBufZero --将队列的某一段数据写0
* 输入参数说明：pCBHandle            --队列指针
*               Length               --要写的长度
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char WriteCircularBufZero(CIRCLE_BUFF_T *pCBHandle, unsigned char ucLength)
{
    unsigned char ucStart = 0;
    unsigned char ucCount = 0;

    if (NULL == pCBHandle)
    {
        return -1;
    }
    
    if (ucLength > MAX_BUFFER_SIZE) 
	{
		return -1;
	}

    if ((pCBHandle->ucCurrLen + ucLength) <= MAX_BUFFER_SIZE)
    {

        ucStart = pCBHandle->ucWrId;        
        ucCount = 0;        
        if ((ucStart + ucLength) <= MAX_BUFFER_SIZE)
        {
        	/*不考虑折返的问题*/
            memset(&pCBHandle->aucBuffer[ucStart],0x00,ucLength);
        }
        else
        {
        	/*考虑折返*/
            ucCount = MAX_BUFFER_SIZE - ucStart;
            memset(&pCBHandle->aucBuffer[ucStart],0x00,ucCount);
            ucStart = 0;

            memset(&pCBHandle->aucBuffer[ucStart],0x00,(ucLength-ucCount));
        }

        /*调整环形缓冲区的写数据指针，缓冲区数据计数器。*/
        pCBHandle->ucWrId= ucStart + (ucLength - ucCount);
        pCBHandle->ucCurrLen += ucLength;

        return 0;
    }

    return -2;

}

/******************************************************************************************************
*
* 函数介绍：    writeCircularBuf --将队列的某一段数据写入队列
* 输入参数说明：pCBHandle        --队列指针
*               pData            --要写的数据
*               Length           --要写的长度
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char WriteCircularBuf(CIRCLE_BUFF_T *pCBHandle, unsigned char *pData, unsigned char ucLength)
{
    unsigned char ucStart = 0;
    unsigned char ucCount = 0;

    if (NULL == pCBHandle || NULL == pData)
    {
        return -1;
    }
    
    if ((pCBHandle->ucCurrLen + ucLength) <= MAX_BUFFER_SIZE)
    {
        ucStart = pCBHandle->ucWrId;        
        ucCount = 0;        
        if ((ucStart + ucLength) <= MAX_BUFFER_SIZE)
        {
        	/*不考虑折返的问题*/
            memcpy(&pCBHandle->aucBuffer[ucStart], pData, ucLength);
        }
        else
        {
        	/*考虑折返*/
            ucCount = MAX_BUFFER_SIZE - ucStart;
            memcpy(&pCBHandle->aucBuffer[ucStart], pData, ucCount);
            ucStart = 0;
            memcpy(&pCBHandle->aucBuffer[ucStart], (pData+ucCount), (ucLength-ucCount)); 
        }

        /*调整环形缓冲区的写数据指针，缓冲区数据计数器。*/
        pCBHandle->ucWrId = ucStart+(ucLength - ucCount);
        pCBHandle->ucCurrLen += ucLength;

        return 0;
    }

    return -2;
}

/******************************************************************************************************
*
* 函数介绍：    readCircularBuf --从队列读出某段数据，并且删除队列的该段数据
* 输入参数说明：pCBHandle       --队列指针
*               pData           --要读出来的数据
*               Length          --要读的长度
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char ReadCircularBuf(CIRCLE_BUFF_T *pCBHandle, unsigned char *pData, unsigned char *pLength)
{
    unsigned char ucStart = 0;
    unsigned char ucCount = 0, ucLen = 0;

    if (NULL == pCBHandle || NULL == pData )
    {
        *pLength = 0;
        return -1;
    } 
    
    if( pCBHandle->ucCurrLen == 0)
    {
        *pLength = 0;
        return -1;
    }
    
    ucLen = *pLength;
    if(ucLen > pCBHandle->ucCurrLen)
    {
        ucLen = pCBHandle->ucCurrLen;
    }

    ucStart = pCBHandle->ucReId;        
    ucCount = 0;

    if ((ucStart + ucLen) <= MAX_BUFFER_SIZE)
    {           
        memcpy(pData, &pCBHandle->aucBuffer[ucStart], ucLen);
    }
    else
    {
        ucCount = MAX_BUFFER_SIZE - ucStart;
        memcpy(pData, &pCBHandle->aucBuffer[ucStart], ucCount);
        ucStart = 0;
        memcpy((pData+ucCount), &pCBHandle->aucBuffer[ucStart], (ucLen-ucCount));            
    }

    /*调整环形缓冲区读数据指针，缓冲区数据计数器*/
    pCBHandle->ucReId = ucStart + (ucLen - ucCount);
    pCBHandle->ucCurrLen -= ucLen;
    *pLength = ucLen;

    return 0;

}

/******************************************************************************************************
*
* 函数介绍：    getCircularBuf  --从队列读出某段数据，但是不删除队列的该段数据
* 输入参数说明：pCBHandle       --队列指针
*               pData           --要读出来的数据
*               Length          --要读的长度
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char GetCircularBuf(CIRCLE_BUFF_T *pCBHandle, unsigned char *pData, unsigned char *pLength)
{
	unsigned char ucStart = 0;
	unsigned char ucCount = 0, ucLen = 0;

	if (NULL == pCBHandle || NULL == pData )
	{
		*pLength = 0;
		return -1;
	}

    if( pCBHandle->ucCurrLen == 0)
    {
        *pLength = 0;
        return -1;
    }
    
	ucLen = *pLength;
    if(ucLen > pCBHandle->ucCurrLen)
    {
        ucLen = pCBHandle->ucCurrLen;
    }
    
	ucStart = pCBHandle->ucReId;		
	ucCount = 0;

	if ((ucStart + ucLen) <= MAX_BUFFER_SIZE)
	{			
		memcpy(pData, &pCBHandle->aucBuffer[ucStart], ucLen);
	}
	else
	{
		ucCount = MAX_BUFFER_SIZE - ucStart;
		memcpy(pData, &pCBHandle->aucBuffer[ucStart], ucCount);
		ucStart = 0;
		memcpy((pData+ucCount), &pCBHandle->aucBuffer[ucStart], (ucLen-ucCount));			 
	}

	*pLength = ucLen;

	return 0;
}

/******************************************************************************************************
*
* 函数介绍：    releaseCircularBuf  --要将队列的某段数据清空掉
* 输入参数说明：pCBHandle           --队列指针
*               Length              --要清空的长度
* 输出参数说明：无
* 返回值：      成功返回0,失败返回-1
*******************************************************************************************************
*/
char ReleaseCircularBuf(CIRCLE_BUFF_T *pCBHandle, unsigned char *pLength)
{
    unsigned char ucStar  = 0;
    unsigned char ucCount = 0;
    unsigned char ucLen   = 0;

    if (NULL == pCBHandle)
    {
       *pLength = 0;
       return -1;
    }

    ucLen = *pLength;

    if(ucLen > pCBHandle->ucCurrLen)
    {
        ucLen = pCBHandle->ucCurrLen;
    }  

    ucStar = pCBHandle->ucReId;
    ucCount = 0;

    if ((ucStar + ucLen) >= MAX_BUFFER_SIZE)
    {  
        ucCount  = MAX_BUFFER_SIZE - ucStar;
        ucStar   = 0;
    }
    
    /*调整环形缓冲区读数据指针，缓冲数据计数器*/
    pCBHandle->ucReId = ucStar + (ucLen - ucCount);
    pCBHandle->ucCurrLen -= ucLen;
    *pLength = ucLen;

    return 0;

}

#ifdef __cplusplus
}
#endif

