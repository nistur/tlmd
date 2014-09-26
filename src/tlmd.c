#include "tlmd_internal.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

void mkdir_p(char* path)
{
  char* p = path;
  while(*p)
  {
    if(*p == '/')
    {
      *p = 0;
      mkdir(path, S_IRWXU);
      *p = '/';
    }

    ++p;
  }
}

tlmdReturn tlmdClearContext(tlmdContext* context)
{
    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdInitContext(tlmdContext** context)
{
    if(context == 0)
        tlmdReturn(NO_CONTEXT);
    *context = tlmdMalloc(tlmdContext);
    if(tlmdClearContext(*context) != TLMD_SUCCESS)
	   tlmdTerminateContext(context);

    char path[260];
    sprintf(path, "/tmp/tlmd/%d/out", getpid());

    mkdir_p(path);
    mkfifo(path, 0666);
    (*context)->fifo = open(path, O_WRONLY | O_NONBLOCK);

    printf( "%d\n", (*context)->fifo);

    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdTerminateContext(tlmdContext** context)
{
    if(*context == 0)
	   tlmdReturn(NO_CONTEXT);

    close((*context)->fifo);

    char path[260];
    sprintf(path, "/tmp/tlmd/%d/out", getpid());
    remove( path );
    
    tlmdFree(*context);
    *context = 0;
    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdAuthenticate(tlmdContext* context, tlmdConnectionType connection, tlmdConnectionProperties* properties)
{
   if(context == 0)
	   tlmdReturn(NO_CONTEXT);

   tlmdMessage* authMsg;
   tlmdAuthMessageData data;
   tlmdInitMessageInternal(&authMsg, TLMD_AUTH, 0, sizeof(data));

   tlmdSend(context, authMsg);

    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdRegister(tlmdContext* context, tlmdMessageID message)
{
   if(context == 0)
     tlmdReturn(NO_CONTEXT);

    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdSend(tlmdContext* context, tlmdMessage* message)
{
   if(context == 0)
	   tlmdReturn(NO_CONTEXT);

   write(context->fifo, message->buffer, message->size);
   

   // we own the message, so we can clean it up now
   tlmdFree(message->buffer);
   tlmdFree(message);

    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdSetCallback(tlmdContext* context, tlmdCallback callback)
{
   if(context == 0)
	   tlmdReturn(NO_CONTEXT);

    tlmdReturn(SUCCESS);
}
