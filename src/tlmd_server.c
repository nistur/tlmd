#include "tlmd_internal.h"

#include <stdio.h>

int main( int argc, char** argv )
{
  tlmdContext* context;
  tlmdInitContext( &context );

  while( true )
  {
  }

  tlmdTermianteContext( &context );
  return 0;
}

