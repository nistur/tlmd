#ifndef __TLMD_H__
#error Do not #include tlmd_message.h manually. You should use tlmd.h
#else
#ifndef __TLMD_MESSAGE_H__
#define __TLMD_MESSAGE_H__

TLMD_EXPORT tlmdReturn tlmdInitMessage(tlmdMessage** message, tlmdMessageID id, tlmdSize size);

TLMD_EXPORT tlmdReturn tlmdMessageReadU32 (tlmdMessage* message, tlmd_u32 value);
TLMD_EXPORT tlmdReturn tlmdMessageWriteU32(tlmdMessage* message, tlmd_u32 value);

#endif/*__TLMD_MESSAGE_H__*/
#endif/*__TLMD_H__*/
