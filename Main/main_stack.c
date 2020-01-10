#include "main_cfg.h"

void main_stack(void)
{
	STACK_TYPEDEF_PTR
		stack = NULL,
		stack_attach = 0,
		stack_copy = NULL;

	VECTOR_TYPEDEF_PTR
		vector = NULL;

	char
		**string = calloc(1, sizeof(char **)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "stack";

	printf("\r\n ------------------------+ stack demo start +------------------------ \r\n");

	printf("stack.init start\r\n    ");
	stack_ctrl.configuration.init(&stack, VECTOR, sizeof(string_moudle), NULL, NULL);		/* Initialize stack,char[sizeof(string_moudle)] type */
	vector_ctrl.configuration.init(&vector, sizeof(string_moudle), NULL, NULL);			/* Initialize vector,char[sizeof(string_moudle)] type */
	stack_ctrl.configuration.attach(&stack_attach, vector, vector_function_address_tables);


	printf("\r\nstack.max_size start\r\n    ");
	printf("max size : %d \r\n    ", stack_ctrl.capacity.max_size(stack));

	printf("\r\nstack.push start\r\n    ");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("push no.%d : \"%s\" \r\n    ", cnt, string_moudle);

		stack_ctrl.modifiers.push(stack, string_moudle);

		string_moudle[0] += 1;
	}

	printf("\r\nstack .top start\r\n    ");
	printf("top : \"%s\" \r\n    ", (char *)stack_ctrl.element_access.top(stack));

	printf("\r\nstack attach.copy stack start\r\n    ");
	stack_ctrl.modifiers.copy(&stack_attach, stack);

	printf("\r\nstack attach.pop start\r\n    ");
	for (size_t cnt = 0; cnt < 15; cnt++) {
		printf("pop no.%d : \"%s\" \r\n    ", cnt, (char *)stack_ctrl.modifiers.pop(stack_attach));
	}

	printf("\r\nstack.destroy start\r\n    ");
	stack_ctrl.configuration.destroy(&stack);
	stack_ctrl.configuration.destroy(&stack_attach);

	printf("\r\n ------------------------+ stack demo end +------------------------\r\n");

	return;
}