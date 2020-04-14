#include "main_cfg.h"

#if MAIN_DEBUG_COMPONENT_EN

#define MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN						0u
#define MAIN_DEBUG_COMPONENT_CFG_ERROR_EN						0u
#define MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN			1u

void main_debug_assert(void);
void main_debug_error(void);
void main_debug_stack_back_trace(void);

void main_debug_component(void)
{
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

#if MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN

void debug_assert(char *pointer, size_t variable);

void main_debug_assert(void)
{
	char string[] = "debug assert";

	debug_assert(string, string[0]);
}

void debug_assert(char *pointer, size_t variable)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(pointer);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(variable, >= , int, 0);
	DEBUG_ASSERT_CONTROL_EXPRESSION_PRINTF(true == true);

	printf("string:\"%s\" variable:%d\r\n",
		   pointer,
		   variable);
}

#endif // MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN

#if MAIN_DEBUG_COMPONENT_CFG_ERROR_EN

struct debug_error_structure_s {
	errno_t err;    /* This is the must */

	char *string;
};

errno_t debug_error_errno(void);
struct debug_error_structure_s debug_error_structure(void);

void main_debug_error(void)
{
	printf("debug_component.error.errno.error:%d\r\n", debug_error_errno());

	struct debug_error_structure_s structure = debug_error_structure();
	printf("debug_error.structure.error:%d string:\"%s\"\r\n",
		   structure.err,
		   structure.string);

	return;
}

errno_t debug_error_errno(void)
{
	DEBUG_ERROR_CONTROL_ERRNO_INIT(1, 1);
	/* DEBUG_ERROR_CONTROL_INIT(errno_t, 2, 0, 1); */

	if (true) {
		DEBUG_ERROR_CONTROL_JUMP(1);
	}

	DEBUG_ERROR_CONTROL_EXIT();
}

struct debug_error_structure_s debug_error_structure(void)
{
	DEBUG_ERROR_CONTROL_STRUCTURE_INIT(struct debug_error_structure_s, 1, 1);
	/* DEBUG_ERROR_CONTROL_INIT(struct debug_error_structure_s, 2, 0, 1); */

	DEBUG_ERROR_CONTROL_RETURN_VAL.string = "debug_error_structure";

	if (true) {
		DEBUG_ERROR_CONTROL_JUMP(1);
	}

	DEBUG_ERROR_CONTROL_EXIT();
}

#endif // MAIN_DEBUG_COMPONENT_CFG_ERROR_EN

#if MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN

void stack_back_trace_function_shell(stack_back_trace_stp back_trace);

void main_debug_stack_back_trace(void)
{
	stack_back_trace_stp capture_stack_back_trace = { NULL };

	printf("\r\ndebug component.stack back trace.init start\r\n");
	debug_capture_stack_back_trace_init(&capture_stack_back_trace, 8);

	printf("\r\ndebug component.stack back trace.trace start\r\n");
	debug_capture_stack_back_trace(capture_stack_back_trace, 0);
	stack_back_trace_function_shell(capture_stack_back_trace);

	printf("\r\ndebug component.stack back trace.convert to string start \r\n");
	struct stack_back_trace_convert_to_string_return_s
		string_return = debug_capture_stack_back_trace_convert_to_string(capture_stack_back_trace, 1);
	for (size_t cnt = 0; cnt < string_return.frames; cnt++) {
		printf("%s\r\n", (string_return.string + cnt)->name_ptr);
	}

	printf("\r\ndebug component.stack back trace.get hash start \r\n");
	stack_back_trace_hash_t
		hash = debug_capture_stack_back_trace_get_hash(capture_stack_back_trace, 1);
	printf("debug component.stack back trace.get hash:%d", hash);

	printf("\r\ndebug component.stack back trace.destroy start\r\n");
	debug_capture_stack_back_trace_destroy(&capture_stack_back_trace);

	return;
}

void stack_back_trace_function_shell(stack_back_trace_stp back_trace)
{
	for (size_t cnt = 0; cnt < 10; cnt++) {
		debug_capture_stack_back_trace(back_trace, 0);
	}
}

#endif // MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN

#endif // MAIN_DEBUG_COMPONENT_EN