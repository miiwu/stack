#include "demo_sde_lib.h"

#if DEMO_SDE_LIB_CFG_CFG_ASSERT_EN

#define ASSERT_FAULT_EN																					\
	1

void main_assert(void)
{
	printf("\r\n------------------------+ sde.assert demo start +------------------------\r\n");

	char string[] = "sde.assert: succeed";

	ASSERT(true == true);
	ASSERT_POINTER(string);

#if ASSERT_FAULT_EN

	ASSERT_VARIABLE(-1, >= , int, 0, printf("this assert is failed!\r\n"));

#endif // ASSERT_FAULT_EN

	printf("\r\n------------------------+ sde.assert demo start +------------------------\r\n");

	return;
}

#endif // DEMO_SDE_LIB_CFG_CFG_ASSERT_EN