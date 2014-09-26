#include "tlmd_internal.h"

tlmdReturn tlmdInitMessageInternal(tlmdMessage** message, tlmdMessageID sysid, tlmdMessageID id, tlmdSize size)
{
  if(message == 0)
    tlmdReturn(NO_MESSAGE);
  
  *message = tlmdMalloc(tlmdMessage);
  (*message)->size = size;
  
  (*message)->buffer = tlmdMallocArray(tlmdByte, size + sizeof(sysid) + sizeof(id));
  tlmdMessageWriteU32(*message, sysid);
  tlmdMessageWriteU32(*message, id);

  tlmdReturn(SUCCESS);
}

tlmdReturn tlmdInitMessage(tlmdMessage** message, tlmdMessageID id, tlmdSize size)
{
  return tlmdInitMessageInternal(message, 0, id, size);
}

tlmdReturn tlmdMessageReadU32 (tlmdMessage* message, tlmd_u32 value)
{
  if(message == 0)
    tlmdReturn(NO_MESSAGE);
  
  tlmdReturn(SUCCESS);
}

tlmdReturn tlmdMessageWriteU32(tlmdMessage* message, tlmd_u32 value)
{
  if(message == 0)
    tlmdReturn(NO_MESSAGE);
  
  tlmdReturn(SUCCESS);
}
