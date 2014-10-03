#include "tlmd-tests.h"
#include "tlmd.h"

#include <unistd.h>

/*
TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
	 m_data.context = 0;
     },
     // cleanup
     {
	 tlmdTerminateContext(&m_data.context);
     },
     // test
     {
	 ASSERT(tlmdInitContext(&m_data.context) == TLMD_SUCCESS);
	 ASSERT(m_data.context != 0);
	 ASSERT(tlmdTerminateContext(&m_data.context) == TLMD_SUCCESS);
	 ASSERT(m_data.context == 0)
     },
     // data
     {
	 tlmdContext* context;
     }
    );
*/
TEST(Authenticate, Basic, 0.0f,
     {
	 m_data.context = 0;
	 tlmdInitContext(&m_data.context);
     },
     {
	 tlmdTerminateContext(&m_data.context);
     },
     {
       ASSERT(tlmdAuthenticate(0, TLMD_CONNECTION_LOCAL, 0) != TLMD_SUCCESS);
       ASSERT(tlmdAuthenticate(m_data.context, TLMD_CONNECTION_LOCAL, 0) == TLMD_SUCCESS);
     },
     {
	 tlmdContext* context;
     }
    );
