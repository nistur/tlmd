#include "tlmd_internal.h"
#include <stdio.h>
#include <unistd.h>
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
    if(context == 0)
        tlmdReturn(NO_CONTEXT);
    context->out = -1;
    context->in  = -1;
    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdInitContext(tlmdContext** context)
{
    if(context == 0)
        tlmdReturn(NO_CONTEXT);
    *context = tlmdMalloc(tlmdContext);
    if(tlmdClearContext(*context) != TLMD_SUCCESS)
	   tlmdTerminateContext(context);

    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdTerminateContext(tlmdContext** context)
{
    if(*context == 0)
	   tlmdReturn(NO_CONTEXT);

    close((*context)->out);

    char path[260];
    sprintf(path, "/tmp/tlmd/%d/out", getpid());
    remove( path );


    // TODO: Check if this directory is empty first, only clean up if it is
    sprintf(path, "/tmp/tlmd/%d", getpid());
    remove(path);
    
    tlmdFree(*context);
    *context = 0;
    tlmdReturn(SUCCESS);
}

tlmdReturn tlmdAuthenticate(tlmdContext* context, tlmdConnectionType connection, tlmdConnectionProperties* properties)
{
   if(context == 0)
	   tlmdReturn(NO_CONTEXT);

   if( connection == TLMD_CONNECTION_LOCAL )
   {
     char path[260];
     sprintf(path, "/tmp/tlmd/%d/out", getpid());
     
     tlmdOpen(path, &context->out);

     sprintf( context->path, "%s", path );

     tlmdMessage* authMsg;
     tlmdAuthMessageData data;
     static const char* auth = "Hello, World\n";
     tlmdInitMessageInternal(&authMsg, TLMD_AUTH, 0, strlen(auth)+1);

     tlmdMessageWrite( authMsg, "Hello, World\n", strlen(auth)+1 );

     tlmdSend(context, authMsg);
   }
   else
   {
     tlmdReturn(NOT_IMPLEMENTED);
   }
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

   //   context->out = open( context->path, O_WRONLY | O_NONBLOCK );
   //write(context->out, &message->size, sizeof(message->size));
   write(context->out, message->buffer, message->size);
   //   close(context->out);

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

tlmdReturn tlmdOpen(char* path, int* fd)
{
  mkdir_p(path);
  mkfifo(path, 0666);
  *fd = open(path, O_WRONLY | O_NONBLOCK);
  if(*fd)
    tlmdReturn(SUCCESS);
  tlmdReturn(IO_ERROR);
}
