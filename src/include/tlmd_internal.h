#pragma once
#ifndef __TLMD_INTERNAL_H__
#define __TLMD_INTERNAL_H__

#include "tlmd.h"

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlmdContext
{
  int                out;
  int                in;
  char               path[260];
  tlmdConnectionType type;
};
struct _tlmdMessage
{
  tlmdByte*     buffer;
  tlmdSize      size;
  tlmdSize      offs;
};

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tlmdMalloc(x) (x*)malloc(sizeof(x))
#define tlmdMallocArray(x,n) (x*)malloc(sizeof(x)*n)
#define tlmdFree(x)   free(x)

/***************************************
 * Error handling
 ***************************************/
extern tlmdReturn  g_tlmdError;
extern const char* g_tlmdErrors[];
#define tlmdReturn(x)				\
    {						\
	g_tlmdError = TLMD_##x;			\
	return TLMD_##x;			\
    }

tlmdReturn tlmdInitMessageInternal(tlmdMessage** message, tlmdMessageID sysid, tlmdMessageID id, tlmdSize sise);

tlmdReturn tlmdOpen(char* path, int* fd);

#define TLMD_AUTH 1

#include "tlmd_message_defs.h"

#endif/*__TLMD_INTERNAL_H__*/
