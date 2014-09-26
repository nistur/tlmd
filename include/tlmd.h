#pragma once
#ifndef __TLMD_H__
#define __TLMD_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TLMD_DYNAMIC
# ifdef WIN32
#  ifdef TLMD_BUILD
#   define TLMD_EXPORT __declspec( dllexport )
#  else
#   define TLMD_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TLMD_EXPORT
# define TLMD_EXPORT
#endif

typedef unsigned int     tlmdReturn;
typedef unsigned int     tlmdMessageID;
typedef unsigned int     tlmdSize;
typedef unsigned char    tlmdConnectionType;
typedef unsigned char    tlmdByte;

typedef struct _tlmdContext              tlmdContext;
typedef struct _tlmdMessage              tlmdMessage;
typedef struct _tlmdConnectionProperties tlmdConnectionProperties;

typedef void(*tlmdCallback)(tlmdMessage*);


#define TLMD_SUCCESS    0
#define TLMD_NO_CONTEXT 1
#define TLMD_NO_MESSAGE 2

#define TLMD_CONNECTION_LOCAL  0
#define TLMD_CONNECTION_REMOTE 1

TLMD_EXPORT tlmdReturn   tlmdInitContext     (tlmdContext** context);
TLMD_EXPORT tlmdReturn   tlmdTerminateContext(tlmdContext** context);

TLMD_EXPORT tlmdReturn   tlmdAuthenticate    (tlmdContext* context, tlmdConnectionType connection, tlmdConnectionProperties* properties);

TLMD_EXPORT tlmdReturn   tlmdRegister        (tlmdContext* context, tlmdMessageID message);
TLMD_EXPORT tlmdReturn   tlmdSend            (tlmdContext* context, tlmdMessage* message);
TLMD_EXPORT tlmdReturn   tlmdSetCallback     (tlmdContext* context, tlmdCallback callback);

#include "tlmd_types.h"
#include "tlmd_message.h"

TLMD_EXPORT const char*  tlmdError();

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TLMD_H__*/
