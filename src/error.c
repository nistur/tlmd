#include "tlmd.h"

tlmdReturn g_tlmdError;
const char* g_tlmdErrors[] = 
{
    "Success",
    "Null context",
};


const char* tlmdError()
{
    return g_tlmdErrors[g_tlmdError];
}
