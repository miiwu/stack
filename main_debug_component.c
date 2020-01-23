#include "main_cfg.h"

#define MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN			0u
#define MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_LINK_EN		1u

STACK_BACK_TRACE_TYPEDEF_PTR capture_stack_back_trace = { NULL };

STACK_BACK_TRACE_LINK_TYPEDEF_PTR link = NULL;

void stack_back_trace_function_shell(STACK_BACK_TRACE_TYPEDEF_PTR back_trace)
{
	for (size_t cnt = 0; cnt < 10; cnt++) {
		debug_capture_stack_back_trace(back_trace, 0);
	}
}

void stack_back_trace_link_function_shell(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link)
{
	for (size_t cnt = 0; cnt < 2; cnt++) {
		debug_capture_stack_back_trace_link_mark(link, 0);
	}
}

void main_debug_component(void)
{
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
	STACK_BACK_TRACE_TYPEDEF_PPTR stack_back_trace_tmp = malloc(sizeof(void*));
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