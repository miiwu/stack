#include "demo_sde_lib.h"

#if DEMO_SDE_LIB_CFG_MICRO_EN

void main_micro_built_in_method(void *structure, char *string, size_t num);

void main_micro(void)
{
	printf("\r\n------------------------+ sde.micro demo start +------------------------\r\n");

	printf("\r\nsde.micro.va_arg.arg%d:\"%s\" \r\n",
		   2, VA_ARGS_ARG(2, "1", "2", "3"));

	printf("\r\nsde.micro.va_arg.arg_num:%d \r\n",
		   VA_ARGS_ARG_NUM());
	printf("\r\nsde.micro.va_arg.arg_num:%d \r\n",
		   VA_ARGS_ARG_NUM(1, 2, 3, 4, 5, 6));
	printf("\r\nsde.micro.va_arg.arg_num:\"%s\" \r\n",
		   VA_ARGS_ARG_NUM(1, 2, 3, 4, 5, 6, "*"));

	printf("\r\nsde.micro.va_arg.from: ");
	VA_ARGS_FROM(2,
				 printf("1"),
				 printf("2"),
				 printf("3\r\n"));

	BUILT_IN(NULL, main_micro_built_in_method, "\r\nbuilt-in method(): %d\r\n", 1);

	printf("\r\n------------------------+ sde.micro demo end +------------------------\r\n");

	return;
}

void main_micro_built_in_method(void *structure, char *string, size_t num)
{
	printf(string, num);
}

#endif // DEMO_SDE_LIB_CFG_CFG_MICRO_EN