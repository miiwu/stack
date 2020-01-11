#include "main_cfg.h"

void stack_back_trace_function_shell(struct capture_stack_back_trace_t *back_trace)
{
	debug_capture_stack_back_trace_to_symbol(back_trace, 0, 64);
}

void main_debug_component(void)
{
	struct capture_stack_back_trace_t
		*capture_stack_back_trace = { NULL };

	printf("\r\n ------------------------+ debug component demo start +------------------------\r\n");

	printf("\r\ndebug component.init start\r\n");
	debug_capture_stack_back_trace_init(&capture_stack_back_trace, 2);

	printf("\r\ndebug component.allocate start\r\n");
	for (size_t i = 0; i < 10; i++) {
		debug_capture_stack_back_trace_to_symbol(capture_stack_back_trace, 0, 64);
		stack_back_trace_function_shell(capture_stack_back_trace);
	}

	printf("\r\ndebug component.destroy start\r\n");
	debug_capture_stack_back_trace_destroy(&capture_stack_back_trace);

	printf("\r\n ------------------------+ debug component demo end +------------------------\r\n");

	return;
}