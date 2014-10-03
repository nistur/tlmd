#include "tlmd_internal.h"
#include <string.h>

tlmdReturn tlmdInitMessageInternal(tlmdMessage** message, tlmdMessageID sysid, tlmdMessageID id, tlmdSize size)
{
  if(message == 0)
    tlmdReturn(NO_MESSAGE);
  
  *message = tlmdMalloc(tlmdMessage);
  (*message)->size = size + sizeof(sysid) + sizeof(id);

  (*message)->offs = 0;
  
  (*message)->buffer = tlmdMallocArray(tlmdByte, size);
  tlmdMessageWrite(*message, &sysid, sizeof(sysid));
  tlmdMessageWrite(*message, &id, sizeof(id));

  tlmdReturn(SUCCESS);
}

tlmdReturn tlmdInitMessage(tlmdMessage** message, tlmdMessageID id, tlmdSize size)
{
  return tlmdInitMessageInternal(message, 0, id, size);
}

tlmdReturn tlmdMessageRead(tlmdMessage* message, tlmd_void* data, tlmdSize size)
{
  if(message == 0)
    tlmdReturn(NO_MESSAGE);
  
  memcpy(data, &message->buffer[message->offs], size);
  message->offs += size;

  tlmdReturn(SUCCESS);
}

tlmdReturn tlmdMessageWrite(tlmdMessage* message, const tlmd_void* data, tlmdSize size)
{
  if(message == 0)
    tlmdReturn(NO_MESSAGE);

  memcpy(&message->buffer[message->offs], data, size);
  message->offs += size;

  tlmdReturn(SUCCESS);
}
