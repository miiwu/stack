#include "demo_sde_lib.h"

#if DEMO_SDE_LIB_CFG_DBG_CMPT_STACK_BACK_TRACE_EN

stack_back_trace_stp stack_back_trace = NULL;

void main_stack_back_trace_shell(void);

void main_stack_back_trace(void)
{
	printf("\r\n ------------------------+ stack back trace demo start +------------------------\r\n");

	printf("\r\nsde.debug component.stack back trace.init start\r\n");
	stack_back_trace_control_init(&stack_back_trace, 2);

	printf("\r\nsde.debug component.stack back trace.trace.address start\r\n");
	stack_back_trace_control_trace_address(stack_back_trace,
										   0, 64);

	printf("\r\nsde.debug component.stack back trace.trace.address shell start\r\n");
	main_stack_back_trace_shell();

	printf("\r\nsde.debug component.stack back trace.trace.string start\r\n");
	struct stack_back_trace_string_package_s string_package
		= stack_back_trace_control_trace_string(stack_back_trace,
												FUNC_FILE_LINE, 1);

	printf("string package: \r\n");
	for (size_t i = 0; i < string_package.frames; i++) {
		printf("    +#%d/%d: \r\n    ", i, string_package.frames);
		printf("|-func: %s() \r\n    ", string_package.string_list[i].name_ptr);
		printf("|-file: %s \r\n    ", string_package.string_list[i].file_name_ptr);
		printf("|-line: %d \r\n", string_package.string_list[i].file_line);
	}

	STACK_BACK_TRACE(stack_back_trace_control_trace_address,
					 0, 64);

	string_package = STACK_BACK_TRACE(stack_back_trace_control_trace_string,
									  FUNC_FILE_LINE, 0);

	printf("string package: \r\n");
	for (size_t i = 0; i < string_package.frames; i++) {
		printf("    +#%d/%d: \r\n    ", i, string_package.frames);
		printf("|-func: %s() \r\n    ", string_package.string_list[i].name_ptr);
		printf("|-file: %s \r\n    ", string_package.string_list[i].file_name_ptr);
		printf("|-line: %d \r\n", string_package.string_list[i].file_line);
	}

	printf("\r\nsde.debug component.stack back trace.destroy start\r\n");
	stack_back_trace_control_destroy(&stack_back_trace);

	printf("\r\n ------------------------+ stack back trace demo end +------------------------\r\n");

	return;
}

void main_stack_back_trace_shell(void)
{
	for (size_t i = 0; i < 10; i++) {
		stack_back_trace_control_trace_address(stack_back_trace,
											   0, 64);
	}
}

#endif // DEMO_SDE_LIB_CFG_DBG_CMPT_STACK_BACK_TRACE_EN