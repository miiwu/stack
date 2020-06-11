#include "demo_sde_lib.h"

#if DEMO_SDE_LIB_CFG_LOG_EN

void main_log(void)
{
	printf("\r\n------------------------+ sde.log demo start +------------------------\r\n");

	LOG("\r\nsde.log.LOG() \"%s\" \r\n",
		"start");
	LOG("sde.log.LOG() \"end\" \r\n");

	LOG_DIAGNOSE("sde.log.LOG_DIAGNOSE() \"%s\" \r\n",
		"start");
	LOG_DIAGNOSE("sde.log.LOG_DIAGNOSE() \"end\" \r\n");

	printf("\r\n------------------------+ sde.log demo end +------------------------\r\n");

	return;
}

#endif // DEMO_SDE_LIB_CFG_LOG_EN