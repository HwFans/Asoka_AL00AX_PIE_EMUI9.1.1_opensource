/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2018. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef __PSCOMMONDEF_H__
#define __PSCOMMONDEF_H__



/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "v_timer.h"    /*lint !e537*/


#ifdef _lint
/* PCLINT������뿪�أ�ֻ��PCLINTʱ�� */
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#endif

#ifdef __RECUR_TEST__                                                           /* _H2ASN_Skip */
#include "RecurTest.h"                                                          /* _H2ASN_Skip */
#endif                                                                          /* _H2ASN_Skip */



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define PS_SUBMOD_NULL 0

#ifndef L2_LIBFUZZ_TEST
#define PS_PRINTF                                           (VOS_VOID)vos_printf
#else
#define PS_PRINTF
#endif

/* �ڴ������װ */
#ifdef _lint

#define PS_MEM_CMP(pDestBuffer,pSrcBuffer,Count)            memcmp(pDestBuffer,pSrcBuffer, Count )


/*������Ϣ��,����ĳ��Ȱ�����Ϣ��ͷ����*/
/*lint -emacro({586}, PS_ALLOC_MSG_WITH_HEADER_LEN)*/
#define PS_ALLOC_MSG_WITH_HEADER_LEN(ulPid , ulLen)         malloc(ulLen)

/*������Ϣ��,����ĳ��Ȳ�������Ϣ��ͷ����*/
/*lint -emacro({586}, PS_ALLOC_MSG)*/
#define PS_ALLOC_MSG(ulPid , ulLen)                         malloc((ulLen) + VOS_MSG_HEAD_LENGTH)

/*��Ϣ����*/
#ifdef LINUX_PC_LINT
#define PS_SEND_MSG(ulPid, pMsg)                            (free((VOS_VOID*)pMsg), ulPid)
#define PS_CHR_RPT_SEND_MSG(ulPid, pMsg)                    (free((VOS_VOID*)pMsg), ulPid)


#else
/*lint -emacro({58}, PS_SEND_MSG)*/
/*lint -emacro({64}, PS_SEND_MSG)*/
/*lint -emacro({144}, PS_SEND_MSG)*/
/*lint -emacro({586}, PS_SEND_MSG)*/
/*lint -emacro({516}, PS_SEND_MSG)*/
#define PS_SEND_MSG(ulPid, pMsg)                            free(pMsg)

/*lint -emacro({64}, PS_CHR_RPT_SEND_MSG)*/
/*lint -emacro({144}, PS_CHR_RPT_SEND_MSG)*/
#define PS_CHR_RPT_SEND_MSG(ulPid, pMsg)                    free(pMsg)
#endif

/*��Ϣ����,����PS_POST_MSG֮��,��Ҫʹ������ʾ���ͷ���Ϣ��,������ﲻ����ת����Ϊfree*/
#define PS_POST_MSG(ulPid, pMsg)                            VOS_PostMsg( ulPid, pMsg )

/*��Ϣ����*/
#ifdef LINUX_PC_LINT
#define PS_SEND_URGENT_MSG(ulPid, pMsg)                     (free(pMsg), ulPid)

#else
/*lint -emacro({58}, PS_SEND_URGENT_MSG)*/
/*lint -emacro({64}, PS_SEND_URGENT_MSG)*/
/*lint -emacro({144}, PS_SEND_URGENT_MSG)*/
/*lint -emacro({586}, PS_SEND_URGENT_MSG)*/
#define PS_SEND_URGENT_MSG(ulPid, pMsg)                     free(pMsg)

#endif

/*��Ϣ�ͷź궨��*/
#ifdef LINUX_PC_LINT
#define PS_FREE_MSG(ulPid, pMsg)                            (free(pMsg), ulPid)

#else
/*lint -emacro({58}, PS_FREE_MSG)*/
/*lint -emacro({64}, PS_FREE_MSG)*/
/*lint -emacro({144}, PS_FREE_MSG)*/
/*lint -emacro({586}, PS_FREE_MSG)*/
#define PS_FREE_MSG(ulPid, pMsg)                            free(pMsg)

#endif

/*�ڴ�����궨��*/
/*lint -emacro({586}, PS_MEM_ALLOC)*/
#define PS_MEM_ALLOC(ulPid , ulSize)                         malloc(ulSize)

/*�ڴ��ͷź궨��*/
#ifdef LINUX_PC_LINT
#define PS_MEM_FREE(ulPid, pAddr )                          (free(pAddr), ulPid)

#else
/*lint -emacro({58}, PS_MEM_FREE)*/
/*lint -emacro({64}, PS_MEM_FREE)*/
/*lint -emacro({144}, PS_MEM_FREE)*/
/*lint -emacro({586}, PS_MEM_FREE)*/
#define PS_MEM_FREE(ulPid, pAddr )                          free(pAddr)

#endif

/*���뾲̬�ڴ�궨��*/
/*lint -emacro({586}, PS_ALLOC_STATIC_MEM)*/
#define PS_ALLOC_STATIC_MEM(ulPid , ulSize)                 malloc(ulSize)

/*�ͷž�̬�ڴ�궨��*/
#ifdef LINUX_PC_LINT
#define PS_FREE_STATIC_MEM(ulPid, pAddr )                   (free(pAddr), ulPid)

#else
/*lint -emacro({58}, PS_FREE_STATIC_MEM)*/
/*lint -emacro({64}, PS_FREE_STATIC_MEM)*/
/*lint -emacro({144}, PS_FREE_STATIC_MEM)*/
/*lint -emacro({586}, PS_FREE_STATIC_MEM)*/
#define PS_FREE_STATIC_MEM(ulPid, pAddr )                   free(pAddr)

#endif


/*�ڴ�����*/
#define PS_ALLOC_MSG_ALL_CHECK(ulPid , ulLen)  \
            VOS_AllocMsg( ulPid, (ulLen)-(VOS_MSG_HEAD_LENGTH) )


#elif defined(PS_UT_SWITCH)|| defined(_GAS_UT_SWITCH_)
#include "stdlib.h"


/*lint -emacro({586}, PS_ALLOC_MSG)*/
#define PS_ALLOC_MSG(ulPid , ulLen)                         malloc((ulLen) + VOS_MSG_HEAD_LENGTH)

/*lint -emacro({586}, PS_ALLOC_MSG_WITH_HEADER_LEN)*/
#define PS_ALLOC_MSG_WITH_HEADER_LEN(ulPid , ulLen)         malloc(ulLen)
#define PS_POST_MSG(ulPid, pMsg)                            VOS_PostMsg(ulPid,pMsg)

/*lint -emacro({586}, PS_SEND_MSG)*/
/*lint -emacro({516}, PS_SEND_MSG)*/
#define PS_SEND_MSG(ulPid, pMsg)                            free(pMsg)
#define PS_CHR_RPT_SEND_MSG(ulPid, pMsg)                    free(pMsg)
/*lint -emacro({586}, PS_MEM_FREE)*/
#define PS_MEM_FREE(ulPid, pAddr )                          free(pAddr)
/*lint -emacro({586}, PS_MEM_ALLOC)*/
#define PS_MEM_ALLOC(ulPid , ulSize)                        malloc(ulSize)
/*lint -emacro({586}, PS_FREE_MSG)*/
#define PS_FREE_MSG(ulPid, pMsg)                            free(pMsg)
/*lint -emacro({586}, PS_FREE_STATIC_MEM)*/
#define PS_FREE_STATIC_MEM(ulPid, pAddr )                   free(pAddr)
#define PS_MEM_CMP(pDestBuffer,pSrcBuffer,Count)            memcmp(pDestBuffer, pSrcBuffer, Count )
#define PS_MEM_MOVE(pDestBuffer,pSrcBuffer,ulBuffLen)       memmove_s(pDestBuffer, ulBuffLen, pSrcBuffer, ulBuffLen)

#else

#define PS_MEM_CMP( pucDestBuffer, pucSrcBuffer, ulBufferLen ) \
            VOS_MemCmp( pucDestBuffer, pucSrcBuffer, ulBufferLen )


/*������Ϣ��,����ĳ��Ȱ�����Ϣ��ͷ����*/
/*lint -emacro({586}, PS_ALLOC_MSG_WITH_HEADER_LEN)*/
#define PS_ALLOC_MSG_WITH_HEADER_LEN(ulPid , ulLen)  \
            VOS_AllocMsg( ulPid, (ulLen)-(VOS_MSG_HEAD_LENGTH) )

/*������Ϣ��,����ĳ��Ȳ�������Ϣ��ͷ����*/
/*lint -emacro({586}, PS_ALLOC_MSG)*/
#define PS_ALLOC_MSG(ulPid , ulLen)  \
            VOS_AllocMsg( ulPid, ulLen)

/*lint -emacro({586}, PS_ALLOC_MSG_ALL_CHECK)*/
#define PS_ALLOC_MSG_ALL_CHECK(ulPid , ulLen)  \
            VOS_AllocMsg( ulPid, (ulLen)-(VOS_MSG_HEAD_LENGTH) )

/*Ŀǰ,Э��ջOSA����֧��WIN32����ϵͳ,��PC�����ϲ���ʱ����Ҫʹ��miniDOPRA,���
  ���������ｫPS_SEND_MSG�ֱ���,����WIN32��VXWORKS�汾,����WIN32�汾,��ʹ��ԭ
  Ps_SendMsg����,�Ա�����PC STUB׮ת����Ϣ.����OSA֧��WIN32�汾��,�����ͳһ����*/
    #if(VOS_OS_VER == VOS_WIN32 )

/*�ڴ濽���궨��*/
#define PS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
                (VOS_VOID)memcpy(pucDestBuffer, pucSrcBuffer, ulBufferLen)    // unsafe_function_ignore: memcpy

/*�ڴ��������궨��*/
#define PS_MEM_SET(pucBuffer, ucData, ulBufferLen) \
                (VOS_VOID)memset(pucBuffer, ucData, ulBufferLen)     // unsafe_function_ignore: memset

/*�ڴ��ƶ��궨��*/
#define PS_MEM_MOVE(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
                memmove(pucDestBuffer, pucSrcBuffer, ulBufferLen)   // unsafe_function_ignore: memmove

        /*��Ϣ����*/
        #ifdef __RECUR_TEST__

        #define PS_SEND_MSG(ulPid, pMsg) \
            RECRUTEST_PsSendMsg(ulPid, pMsg)

        #elif defined(PS_ITT_PC_TEST)

        #define PS_SEND_MSG(ulPid, pMsg) \
            Ps_Itt_Stub_SendMsg(ulPid, pMsg)

        #elif defined(PS_ITT_PC_TEST_L2)
        #define PS_SEND_MSG(ulPid, pMsg) \
            VOS_SendMsg(ulPid, pMsg)
        #else

        VOS_UINT32 Ps_SendMsg(VOS_INT8 *cFileName, VOS_UINT32 ulLine, VOS_PID ulPid, VOS_VOID * pMsg);

        #define PS_SEND_MSG(ulPid, pMsg) \
            Ps_SendMsg((VOS_INT8 *)__FILE__, __LINE__, ulPid, pMsg)

        #define PS_CHR_RPT_SEND_MSG(ulPid, pMsg)  Ps_SendMsg((VOS_INT8 *)__FILE__, __LINE__, ulPid, pMsg)

        #endif
    #else
    /*��Ϣ����*/
    /*lint --e(683)*/
    #define PS_SEND_MSG(ulPid, pMsg) \
            VOS_SendMsg( ulPid, pMsg)

    #define PS_CHR_RPT_SEND_MSG(ulPid, pMsg)  Chr_MsgReport(pMsg)
    #endif

/*��Ϣ����*/
#define PS_POST_MSG(ulPid, pMsg) \
            VOS_PostMsg( ulPid, pMsg)

/*��Ϣ����*/
#define PS_SEND_URGENT_MSG(ulPid, pMsg) \
            VOS_SendUrgentMsg( ulPid, pMsg)


/*��Ϣ�ͷź궨��*/
#define PS_FREE_MSG(ulPid, pMsg) \
            VOS_FreeMsg( ulPid, pMsg)

/*�ڴ�����궨��*/
#if (VOS_OS_VER != VOS_WIN32)

/*lint -emacro({586}, PS_MEM_ALLOC)*/
#define PS_MEM_ALLOC(ulPid , ulSize) \
            VOS_MemAlloc( ulPid, (DYNAMIC_MEM_PT), ulSize)

#else   /*WIN32 DOPRA 1.6.1�汾DYNAMIC_MEM_PT�ڴ�����㷨����BUG����˻���BLOCK_MEM_PT */
/*lint -emacro({586}, PS_MEM_ALLOC)*/
#define PS_MEM_ALLOC(ulPid , ulSize) \
            VOS_MemAlloc( ulPid, (BLOCK_MEM_PT), ulSize)
#endif


/*�ڴ��ͷź궨��*/
/*lint -emacro({586}, PS_MEM_FREE)*/
#define PS_MEM_FREE(ulPid, pAddr ) \
            VOS_MemFree( ulPid, pAddr)

/*���뾲̬�ڴ�궨��*/
/*lint -emacro({586}, PS_ALLOC_STATIC_MEM)*/
#define PS_ALLOC_STATIC_MEM(ulPid , ulSize)\
            VOS_MemAlloc(ulPid, (STATIC_MEM_PT), ulSize)


/*�ͷž�̬�ڴ�궨��*/
/*lint -emacro({586}, PS_FREE_STATIC_MEM)*/
#define PS_FREE_STATIC_MEM(ulPid, pAddr )\
            VOS_MemFree(ulPid, (pAddr))
#endif



/* ��ʱ����װ */

/* ������ʱ��
Input Parameters
Pid: The function module ID of application.

ulLength:The duration of relative timer, in milliseconds.

ulName:Timer name. When the timer times out, this parameter will be passed to the application.

ulParam:Additional parameter. When the timer times out,
this parameter will be passed to the application.

ucMode: Work mode of relative timer:
VOS_RELTIMER_LOOP (loop);
VOS_RELTIMER_NOLOOP (no loop).

Output Parameters

phTm: The relative timer provided to the application by the system.
When phTm is VOS_NULL_PTR, ucMode is not allowed to be VOS_RELTIMER_LOOP.
*/

#if (VOS_OS_VER != VOS_WIN32)

    #define PS_START_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
                            VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode, VOS_TIMER_PRECISION_0 )

    #define PS_START_NO_PRECISION_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
                            VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode, VOS_TIMER_NO_PRECISION )

#else
#ifndef DMT
#ifdef __PS_WIN32_RECUR__
    #define PS_START_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
        VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode ,VOS_TIMER_PRECISION_0)
    #define PS_START_NO_PRECISION_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
        VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode ,VOS_TIMER_NO_PRECISION)
#else
    #define PS_START_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
                            VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode )
    #define PS_START_NO_PRECISION_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
                            VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode )
#endif
#else
	#define PS_START_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
                            VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode ,VOS_TIMER_PRECISION_0)
    #define PS_START_NO_PRECISION_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode)\
                            VOS_StartRelTimer( phTm, ulPid, ulLength, ulName, ulParam, ucMode ,VOS_TIMER_NO_PRECISION)
#endif
#endif

#define PS_START_CALLBACK_REL_TIMER(phTm, ulPid, ulLength, ulName, ulParam, ucMode, TimeOutRoutine, ulPrecision)\
                            VOS_StartCallBackRelTimer(phTm, ulPid, ulLength, ulName, ulParam, ucMode, TimeOutRoutine, ulPrecision)


#define PS_STOP_REL_TIMER(phTm)               VOS_StopRelTimer( phTm )

#define PS_GET_REL_TIMER_NAME(pMsg)          (((REL_TIMER_MSG *)pMsg)->ulName)

#define PS_GET_REL_TIMER_PARA(pMsg)          (((REL_TIMER_MSG *)pMsg)->ulPara)

#define PS_RESTART_REL_TIMER(phTm) \
        VOS_RestartRelTimer(phTm)

/*��װ���Ӻ���ע�ắ��*/
#define PS_REGISTER_MSG_GET_HOOK(pfnMsgHook) \
        VOS_RegisterMsgGetHook(pfnMsgHook)
#if (VOS_WIN32 != VOS_OS_VER)
#ifdef _lint
#define PS_SND_MSG_ALL_CHECK(ulPid , pMsg)              PS_SEND_MSG(ulPid, pMsg)
#else

#define PS_SND_MSG_ALL_CHECK(ulPid , pMsg)              PS_OM_SendMsg(ulPid, pMsg)//PS_SEND_MSG(ulPid, pMsg)
#endif
#else
#define PS_SND_MSG_ALL_CHECK(ulPid , pMsg)              PS_SEND_MSG(ulPid, pMsg)
#endif

/* ���ͽ�����Ϣ */
#define PS_SND_URGENT_MSG(ulPid , pMsg)                 VOS_SendUrgentMsg(ulPid, pMsg)

#define PS_MEM_ALLOC_All_CHECK(ulPid , ulSize) \
            PS_MEM_ALLOC(ulPid , ulSize)

/*�ڴ��ͷź궨��*/
#define PS_MEM_FREE_ALL_CHECK(ulPid, pAddr )            PS_MEM_FREE(ulPid, pAddr)

#define PS_FREE_MSG_ALL_CHECK(Pid, pMsg)                PS_FREE_MSG(Pid, pMsg)

/*v8r1��ֲ���µ�RTOS��C���õ�arm A7�� flush��clear�ײ�ʵ��һ��*/
#if (VOS_WIN32 != VOS_OS_VER)
#if (VOS_VXWORKS == VOS_OS_VER)
#define    LPS_CacheClear(pDataAddr, ulDataLen)         (VOS_VOID)cacheClear(DATA_CACHE, (VOS_VOID *)(pDataAddr), (ulDataLen))
#define    LPS_CacheFlush(pDataAddr, ulDataLen)         (VOS_VOID)cacheFlush(DATA_CACHE,(VOS_VOID *)(pDataAddr), (ulDataLen))
#define    LPS_CacheInvalidate(pDataAddr, ulDataLen)    (VOS_VOID)cacheInvalidate(DATA_CACHE,(VOS_VOID *)(pDataAddr), (ulDataLen))
#else
#define    LPS_CacheClear(pDataAddr, ulDataLen)         (VOS_VOID)OSAL_CacheFlush(OSAL_DATA_CACHE, (VOS_VOID *)(pDataAddr), (ulDataLen))
#define    LPS_CacheFlush(pDataAddr, ulDataLen)         (VOS_VOID)OSAL_CacheFlush(OSAL_DATA_CACHE, (VOS_VOID *)(pDataAddr), (ulDataLen))
#define    LPS_CacheInvalidate(pDataAddr, ulDataLen)    (VOS_VOID)OSAL_CacheInvalid(OSAL_DATA_CACHE, (VOS_VOID *)(pDataAddr), (ulDataLen))
#endif
/* #else: VOS_UnCacheMemAlloc --> VOS_UnCacheMemAllocDebug */
/* #if: OSAL_CacheDmaMalloc --> VOS_UnCacheMemAllocDebug */
/* #if: OSAL_CacheDmaFree --> VOS_UnCacheMemFree */
#if (VOS_OS_VER == VOS_RTOSCK)
#define    LPS_CacheDmaMalloc(ulSize,pDataAddr,uwCookie)        VOS_UnCacheMemAllocDebug(ulSize,pDataAddr,uwCookie)
#define    LPS_CacheDmaFree(pBuf,ulSize)                        VOS_UnCacheMemFree(pBuf,pBuf,ulSize)
#else
#define    LPS_CacheDmaMalloc(ulSize,pDataAddr,uwCookie)        VOS_UnCacheMemAllocDebug(ulSize,pDataAddr,uwCookie)
#define    LPS_CacheDmaFree(pBuf,ulSize)                        VOS_UnCacheMemFree(pBuf,pBuf,ulSize)
#endif
#endif


#ifndef CONST
  #define CONST const
#endif

#ifndef STATIC
  #if (VOS_OS_VER == VOS_WIN32)
    #define STATIC
  #else
    #define STATIC static
  #endif
#endif



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
typedef enum   /*CACHE TYPE, copy from BSP*/
{
    OSAL_INSTRUCTION_CACHE,
    OSAL_DATA_CACHE
}OSAL_CACHE_TYPE;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/*v8r1֧���µ�RTOS����cache��ز������ӿ����Ե���*/
extern int OSAL_CacheInvalid(OSAL_CACHE_TYPE type, void * address, unsigned int bytes);
extern int OSAL_CacheFlush(OSAL_CACHE_TYPE type, void * address, unsigned int bytes);
extern VOS_VOID* OSAL_CacheDmaMalloc(unsigned int  bytes);
extern int OSAL_CacheDmaFree(VOS_VOID*  pBuf);



/*****************************************************************************
  9 OTHERS
*****************************************************************************/




#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* PsOsAdapter.h */

