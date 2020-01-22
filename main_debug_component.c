#include "main_cfg.h"

STACK_BACK_TRACE_TYPEDEF_PTR capture_stack_back_trace = { NULL };

STACK_BACK_TRACE_LINK_TYPEDEF_PTR link = NULL;

DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index[2] = {0};

void stack_back_trace_function_shell(STACK_BACK_TRACE_TYPEDEF_PTR back_trace)
{
	index[1] = debug_capture_stack_back_trace_link_mark(link, capture_stack_back_trace, 0);
}

void main_debug_component(void)
{
	printf("\r\n ------------------------+ debug component demo start +------------------------\r\n");

	printf("\r\ndebug component.init start\r\n");
	debug_capture_stack_back_trace_init(&capture_stack_back_trace, 8);
	debug_capture_stack_back_trace_link_init(&link, 2);

	printf("\r\ndebug component.link:mark start \r\n");
	for (size_t i = 0; i < 10; i++) {
		index[0] = debug_capture_stack_back_trace_link_mark(link, capture_stack_back_trace, 0);
	}

	printf("\r\ndebug component.allocate start\r\n");
	for (size_t i = 0; i < 10; i++) {
		stack_back_trace_function_shell(capture_stack_back_trace);
	}

	printf("\r\ndebug component.link:link start \r\n");
	debug_capture_stack_back_trace_reduce_count(capture_stack_back_trace, debug_capture_stack_back_trace_link_link(link, index[0], 0));
	debug_capture_stack_back_trace_reduce_count(capture_stack_back_trace, debug_capture_stack_back_trace_link_link(link, index[1], 0));

	printf("\r\ndebug component.convert to symbol start \r\n");
	debug_capture_stack_back_trace_convert_to_symbol(capture_stack_back_trace);

	printf("\r\ndebug component.destroy start\r\n");
	debug_capture_stack_back_trace_destroy(&capture_stack_back_trace);
	debug_capture_stack_back_trace_link_destroy(&link);

	printf("\r\n ------------------------+ debug component demo end +------------------------\r\n");

	typedef int test_element_t, *test_t[2], *(*ptest_t)[2];
	typedef test_t *ptest_t1;
//	pptest_t test = calloc(1, sizeof(pptest_t));
	ptest_t1 ptest1 = calloc(1, sizeof(ptest_t1));
	ptest_t ptest = calloc(2, sizeof(test_t));
	test_t test = { 0 };

	if (NULL != ptest) {
		*(ptest + 0)[0] = 0x10;
		*(ptest + 0)[1] = 0x11;
		*(ptest + 1)[0] = 0x20;
		*(ptest + 1)[1] = 0x21;

		*(*(ptest + 0) + 0) = 0x30;
		*(*(ptest + 0) + 1) = 0x31;
		*(*(ptest + 1) + 0) = 0x40;
		*(*(ptest + 1) + 1) = 0x41;

		void *ptest_block = calloc(2, sizeof(test_t));

		if (NULL == ptest_block) {
			return;
		}

		for (size_t cnt = 0; cnt < 2; cnt++) {
			size_t amt = 0;
			for (size_t ct = 0; ct < 2; ct++) {
				*(*(ptest + cnt) + ct) = (void *)((size_t)&ptest_block + (cnt * 2 + ct) * sizeof(test_element_t));

				printf("%p \r\n", (void *)((size_t)&ptest_block + (cnt * 2 + ct) * sizeof(test_element_t)));

				amt++;
			}
		}
	}

	return;
}