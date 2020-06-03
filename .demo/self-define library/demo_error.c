#include "demo_sde_lib.h"

#if DEMO_SDE_LIB_CFG_CFG_ERROR_EN

#define ERROR_CONTROL_PRINTF	printf

struct error_structure_s {
	char *string;
};

struct error_structure_s error_structure(void);

size_t return_t(void)
{
	return 1;
}

void return_void(void)
{
	return;
}

void main_error(void)
{
	printf("\r\n------------------------+ sde.error demo start +------------------------\r\n");

	error_structure();
	printf("sde.error.code: %d .string: \"%s\"\r\n",
		   ERROR_CONTROL_CODE(), 													/* _CODE(), if the error have occurred, it won't be 0 */
		   ERROR_CONTROL_STRING());													/* _STRING(), if the error have occurred, it will be not NULL */

	printf("\r\n------------------------+ sde.error demo end +------------------------\r\n");

	return;
}

void error_void(void)
{
	ERROR_CONTROL_VOID_INIT(1, 1);
	/* ERROR_CONTROL_INIT(errno_t, 2, 0, 1); */

	bool fail = true;
	ERROR_CONTROL_TRAP(fail,
					   1, "test:succeed",
					   printf("i will handle this void error! #%d\r\n",
							  ERROR_CONTROL_CODE()));

	printf("Must not reach here! \r\n");

	ERROR_CONTROL_VOID_EXIT();
}

errno_t *error_pointer(void)
{
	ERROR_CONTROL_POINTER_INIT(1, 2);

	printf("last string:%s \r\n", ERROR_CONTROL_STRING());

	error_void();
	ERROR_CONTROL_JUDGE(1, "test:succeed",
						printf("i will handle this pointer error! #%d\r\n",
							   ERROR_CONTROL_CODE()));

	ERROR_CONTROL_EXIT();
}

struct error_structure_s error_structure(void)
{
	ERROR_CONTROL_STRUCTURE_INIT(struct error_structure_s, 2, 3, 4);

	ERROR_CONTROL_RETURN.string = "error_structure";						/* Access the variable will return when function exit() */
	ERROR_CONTROL_TRAP(true != true,
					   1, ,
					   printf("i will handle the first structure error! #%d\r\n",
							  ERROR_CONTROL_CODE()));

	error_pointer();
	ERROR_CONTROL_JUDGE(2, ,
						printf("i will handle the second structure error! #%d\r\n",
							   ERROR_CONTROL_CODE()));

	printf("Must not reach here! \r\n");

	ERROR_CONTROL_EXIT(printf("is it exit?\r\n"));
}

#endif // DEMO_SDE_LIB_CFG_CFG_ERROR_EN