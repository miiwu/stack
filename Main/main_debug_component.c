#include "main_cfg.h"

#if MAIN_DEBUG_COMPONENT_EN

#define MAIN_DEBUG_COMPONENT_CFG_MICRO_EN						0u
#define MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN						0u
#define MAIN_DEBUG_COMPONENT_CFG_ERROR_EN						1u
#define MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN			0u

void main_debug_micro(void);
void main_debug_assert(void);
void main_debug_error(void);
void main_debug_stack_back_trace(void);

void main_debug_component(void)
{
	#if MAIN_DEBUG_COMPONENT_CFG_MICRO_EN

	main_debug_micro();

	#endif // MAIN_DEBUG_COMPONENT_CFG_MICRO_EN

	#if MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN

	main_debug_assert();

	#endif // MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN

	#if MAIN_DEBUG_COMPONENT_CFG_ERROR_EN

	main_debug_error();

	#endif // MAIN_DEBUG_COMPONENT_CFG_ERROR_EN

	#if MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN

	main_debug_stack_back_trace();

	#endif // MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN

	return;
}

#if MAIN_DEBUG_COMPONENT_CFG_MICRO_EN

void main_debug_micro(void)
{
	printf("debug_component.micro.va_arg.arg%d:\"%s\" \r\n",
		   2, DEBUG_MICRO_CONTROL_VA_ARGS_ARG(2, "1", "2", "3"));

	printf("debug_component.micro.va_arg.arg_num:%d \r\n",
		   DEBUG_MICRO_CONTROL_VA_ARGS_ARG_NUM());
	printf("debug_component.micro.va_arg.arg_num:%d \r\n",
		   DEBUG_MICRO_CONTROL_VA_ARGS_ARG_NUM(1, 2, 3, 4, 5, 6));
	printf("debug_component.micro.va_arg.arg_num:\"%s\" \r\n",
		   DEBUG_MICRO_CONTROL_VA_ARGS_ARG_NUM(1, 2, 3, 4, 5, 6, "*"));

	DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM(2,
										  printf("1"),
										  printf("2"),
										  printf("3\r\n"));

	return;
}

#endif // MAIN_DEBUG_COMPONENT_CFG_MICRO_EN

#if MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN

void debug_assert(char *pointer, size_t variable);

void main_debug_assert(void)
{
	denug_assert_control_error_string_modify("error", __FUNCTION__, __FILE__, __LINE__);
	printf("\"%s\"\r\n", denug_assert_control_error_string_inquire());

	denug_assert_control_error_string_modify("error1", __FUNCTION__, __FILE__, __LINE__);
	printf("\"%s\"\r\n", denug_assert_control_error_string_inquire());

	denug_assert_control_error_string_modify("err", __FUNCTION__, __FILE__, __LINE__);
	printf("\"%s\"\r\n", denug_assert_control_error_string_inquire());

	char string[] = "debug assert";

	debug_assert(string, string[0]);
}

inline void debug_assert(char *pointer, size_t variable)
{
	DEBUG_ASSERT_CONTROL_POINTER(pointer);
	DEBUG_ASSERT_CONTROL_VARIABLE(variable, >= , int, 0);
	DEBUG_ASSERT_CONTROL_EXPRESSION(true == true);

	printf("string:\"%s\" variable:%d\r\n",
		   pointer,
		   variable);
}

#endif // MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN

#if MAIN_DEBUG_COMPONENT_CFG_ERROR_EN

#define DEBUG_ERROR_CONTROL_PRINTF	printf

struct debug_error_structure_s {
	char *string;
};

struct debug_error_structure_s debug_error_structure(void);
errno_t debug_error_log_test(size_t i);
errno_t debug_error_test(void);

void main_debug_error(void)
{
	debug_error_structure();
	printf("debug_error.error: %d .error_string: \"%s\"\r\n",
		   DEBUG_ERROR_CONTROL_ERROR(), 													/* Error, if the error have occurred, it won't be 0 */
		   DEBUG_ERROR_CONTROL_ERROR_STRING());												/* Error string, if the error have occurred, it will be not NULL */

	debug_error_test();

	return;
}

errno_t debug_error_errno(void)
{
	DEBUG_ERROR_CONTROL_ERRNO_INIT(1, 1);
	/* DEBUG_ERROR_CONTROL_INIT(errno_t, 2, 0, 1); */

	if (true) {
		DEBUG_ERROR_CONTROL_JUMP(1, "test:succeed");										/* Appoint error string */
	}

	printf("Must not reach here! \r\n");

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

errno_t *debug_error_pointer(void)
{
	DEBUG_ERROR_CONTROL_POINTER_INIT(1, 1);

	debug_error_errno();
	DEBUG_ERROR_CONTROL_JUDGE(1, "test:succeed");

	DEBUG_ERROR_CONTROL_LOG_EXIT(, NULL);
}

struct debug_error_structure_s debug_error_structure(void)
{
	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct debug_error_structure_s, 1, 3);
	/* DEBUG_ERROR_CONTROL_INIT(struct debug_error_structure_s, 2, 0, 1); */

	DEBUG_ERROR_CONTROL_RETURN_VAL.string = "debug_error_structure";						/* Access the variable will return when function exit() */

	debug_error_pointer();
	DEBUG_ERROR_CONTROL_JUDGE(1);

	printf("Must not reach here! \r\n");

	DEBUG_ERROR_CONTROL_EXIT(printf("debug_error.error occur: "
									"debug_error_structure().test:succeed\r\n"));
}

errno_t debug_error_test(void)
{
	for (size_t i = 0; i < 2; i++) {
		debug_error_log_test(i);
	}

	return 0;
}

errno_t debug_error_log_test(size_t i)
{
	DEBUG_ERROR_CONTROL_ERRNO_INIT(2, 1);

	printf("\r\ndebug_error.test.log.%d\r\n", i);

	switch (i) {
		case 0:
			DEBUG_ERROR_CONTROL_JUMP(1);
			break;
		case 1:
			DEBUG_ERROR_CONTROL_JUMP(1, "succeed");
			break;
		default:
			break;
	}

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

#endif // MAIN_DEBUG_COMPONENT_CFG_ERROR_EN

#if MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN

#define MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN			0u
#define MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_LINK_EN		0u

void stack_back_trace_function_shell(stack_back_trace_stp back_trace);
void stack_back_trace_link_function_shell(stack_back_trace_link_stp link);

void main_debug_stack_back_trace(void)
{
	stack_back_trace_stp capture_stack_back_trace = { NULL };

	stack_back_trace_link_stp link = NULL;

	printf("\r\n ------------------------+ debug component demo start +------------------------\r\n");

	#if (MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN)

	back_trace_hash_t hash = 0;

	printf("\r\ndebug component.stack back trace.init start\r\n");
	debug_capture_stack_back_trace_init(&capture_stack_back_trace, 8);

	printf("\r\ndebug component.stack back trace.trace start\r\n");
	debug_capture_stack_back_trace(capture_stack_back_trace, 0);
	stack_back_trace_function_shell(capture_stack_back_trace);

	printf("\r\ndebug component.stack back trace.get trace start\r\n");
	printf("the first stack trace's top stack address is %p \r\n", debug_capture_stack_back_trace_get_trace(capture_stack_back_trace, 0, 0));

	printf("\r\ndebug component.stack back trace.convert to string start \r\n");
	debug_capture_stack_back_trace_convert_to_string(capture_stack_back_trace);

	printf("\r\ndebug component.stack back trace.get hash start \r\n");
	printf("debug component.stack back trace.get hash:%d", hash = debug_capture_stack_back_trace_get_hash(capture_stack_back_trace, 1));

	printf("\r\ndebug component.stack back trace.reduce count start \r\n");
	debug_capture_stack_back_trace_reduce_count(capture_stack_back_trace, hash);

	printf("\r\ndebug component.stack back trace.destroy start\r\n");
	debug_capture_stack_back_trace_destroy(&capture_stack_back_trace);

	#endif // (MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN)

	#if (MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_LINK_EN)

	printf("\r\ndebug component.stack back trace link.init start\r\n");
	debug_capture_stack_back_trace_link_init(&link, 2);

	printf("\r\ndebug component.stack back trace link.mark start\r\n");
	debug_capture_stack_back_trace_link_mark(link, 0);
	stack_back_trace_link_function_shell(link);

	printf("\r\ndebug component.stack back trace link.link start \r\n");
	debug_capture_stack_back_trace_link_link(link, 0);
	debug_capture_stack_back_trace_link_link(link, 0);

	printf("\r\ndebug component.stack back trace link.get trace ptr start \r\n");
	stack_back_trace_stpp stack_back_trace_tmp = malloc(sizeof(void *));
	if (NULL == stack_back_trace_tmp) {
		return;
	}
	debug_capture_stack_back_trace_link_get_trace_ptr(link, stack_back_trace_tmp);
	debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 0));
	debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 1));

	printf("\r\ndebug component.stack back trace link.destroy start\r\n");
	debug_capture_stack_back_trace_link_destroy(&link);

	#endif // (MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN)

	printf("\r\n ------------------------+ debug component demo end +------------------------\r\n");

	return;
}

void stack_back_trace_function_shell(stack_back_trace_stp back_trace)
{
	for (size_t cnt = 0; cnt < 10; cnt++) {
		debug_capture_stack_back_trace(back_trace, 0);
	}
}

void stack_back_trace_link_function_shell(stack_back_trace_link_stp link)
{
	for (size_t cnt = 0; cnt < 2; cnt++) {
		debug_capture_stack_back_trace_link_mark(link, 0);
	}
}

#endif // MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN

#endif // MAIN_DEBUG_COMPONENT_EN