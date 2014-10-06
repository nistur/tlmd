#include "tlmd_internal.h"

#include "pt/pt.h"

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct
{
  int         pid;
  struct pt   thread;
  char        path[260];
} threaddat;

static int local_thread( threaddat* dat );
threaddat* dat( threaddat* threads, int size, int pid );
threaddat* empty( threaddat* threads, int size );

#define MAX_THREAD 1

int main( int argc, char** argv )
{
  TLMD_UNUSED( argc );
  TLMD_UNUSED( argv );
  threaddat threads[ MAX_THREAD ];
  int i;
  struct dirent* e;

  for( i = 0; i < MAX_THREAD; ++i )
  {
    threads[ i ].pid = -1;
    threads[ i ].path[0] = 0;
  }

  while( 1 )
  {
    static const char* sockpath = "/tmp/tlmd";
    DIR* dir = opendir( sockpath );
    if( !dir )
      continue;
    while( ( e = readdir( dir ) ) )
    {
      if( strcmp( e->d_name, "." ) != 0 &&
	  strcmp( e->d_name, ".." ) != 0 )
      {
	int pid = atoi( e->d_name );
	
	threaddat* thread = dat( threads, MAX_THREAD, pid );
	
	if( thread )
	{
	}
	else
	{
	  thread = empty( threads, MAX_THREAD );
	  if( thread )
	  {
	    thread->pid = pid;
	    sprintf( thread->path, "%s/%s", sockpath, e->d_name );
            
            PT_INIT( &thread->thread );
	  }
	}
      }
    }
    closedir( dir );

    for( i = 0; i < MAX_THREAD; ++i )
    {
        if( threads[ i ].pid != -1 )
        {
            local_thread( &threads[ i ] );
        }
    }
    
    sleep( 0 );
  }
  
  return 0;
}

threaddat* dat( threaddat* threads, int size, int pid )
{
  int i;
  for( i = 0; i < size; ++i )
  {
    if( threads[ i ].pid == pid )
      return &threads[ i ];
  }
  return NULL;
}

threaddat* empty( threaddat* threads, int size )
{
  int i;
  for( i = 0; i < size; ++i )
  {
    if( threads[ i ].pid == -1 )
      return &threads[ i ];
  }
  return NULL;
}

static int local_thread( threaddat* thread )
{
    PT_BEGIN( &thread->thread );
    
    char outpath[260];
    sprintf( outpath, "%s/out", thread->path );
    
    int f = open( outpath, O_RDONLY | O_NONBLOCK );
    if( f )
    {
        while( 1 )
        {
            if( !opendir( thread->path ) )
            {
                break;
            }
            else
            {
                // check the out file
                tlmdMessage* msg;
                
                //	if( !read(f, &size, sizeof(size)) || size == 0 ) continue;
                tlmdInitMessageInternal(&msg, 0, 0, 1024);
                
                if( read(f, msg->buffer, 1024) )
                {
                    tlmdByte* data = msg->buffer + (sizeof(tlmdMessageID)*2);
                    
                    printf("MSG: %s", data);
                }
                tlmdFree(msg->buffer);
                tlmdFree(msg);
            }
            
            PT_YIELD( &thread->thread);
            sleep( 0 );
            // if we have messages, write them to the in file
        }
    }
    
    thread->pid = -1;
    PT_END( &thread->thread );
}
