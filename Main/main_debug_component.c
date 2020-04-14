#include "main_cfg.h"

#if MAIN_DEBUG_COMPONENT_EN

#define MAIN_DEBUG_COMPONENT_CFG_ASSERT_EN						1u
#define MAIN_DEBUG_COMPONENT_CFG_ERROR_EN						0u
#define MAIN_DEBUG_COMPONENT_CFG_STACK_BACK_TRACE_EN			0u

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