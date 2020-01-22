#include "main_cfg.h"

#define MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN			1u
#define MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_LINK_EN		0u

STACK_BACK_TRACE_TYPEDEF_PTR capture_stack_back_trace = { NULL };

STACK_BACK_TRACE_LINK_TYPEDEF_PTR link = NULL;

DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index[2] = { 0 };

void stack_back_trace_function_shell(STACK_BACK_TRACE_TYPEDEF_PTR back_trace)
{
	for (size_t cnt = 0; cnt < 10; cnt++) {
		debug_capture_stack_back_trace(back_trace, 0);
	}
}

void stack_back_trace_link_function_shell(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link)
{

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
	index[0] = debug_capture_stack_back_trace_link_mark(link, capture_stack_back_trace, 0);

	printf("\r\ndebug component.allocate start\r\n");
	for (size_t i = 0; i < 10; i++) {
		stack_back_trace_function_shell(capture_stack_back_trace);
	}

	printf("\r\ndebug component.link:link start \r\n");
	debug_capture_stack_back_trace_reduce_count(capture_stack_back_trace, debug_capture_stack_back_trace_link_link(link, index[0], 0));
	debug_capture_stack_back_trace_reduce_count(capture_stack_back_trace, debug_capture_stack_back_trace_link_link(link, index[1], 0));

	printf("\r\ndebug component.stack back trace link.destroy start\r\n");
	debug_capture_stack_back_trace_link_destroy(&link);

	#endif // (MAIN_DEBUG_COMPONENT_CFG_BACK_TRACE_EN)

	printf("\r\n ------------------------+ debug component demo end +------------------------\r\n");

	return;
}