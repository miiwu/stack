#include "stack.h"

#include "main_cfg.h"

void main_stack(void)
{
	STACK_TYPEDEF_PTR
		stack = NULL,
		vector_copy = NULL;

	char
		**string = calloc(1, sizeof(char **)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "stack";

	printf("\r\n------------------------+ stack demo start +------------------------\n");

	printf("stack.init start\r\n");
	stack_ctrl.configuration.init(&stack, VECTOR, sizeof(char) * 10, true, NULL, NULL);		/* Initialize stack,char[10] type */

	printf("\r\nstack.max_size start\r\n");
	printf("max size : %d \r\n", stack_ctrl.capacity.max_size(stack));

	printf("\r\nstack.push start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("push no.%d : \"%s\" \r\n", cnt, string_moudle);

		stack_ctrl.modifiers.push(stack, string_moudle);

		string_moudle[0] += 1;
	}

	printf("\r\nstack.top start\r\n");
	printf("top : \"%s\" \r\n", (char *)stack_ctrl.element_access.top(stack));

	printf("\r\nstack.pop start\r\n");
	for (size_t cnt = 0; cnt < 15; cnt++) {
		printf("pop no.%d : \"%s\" \r\n", cnt, (char *)stack_ctrl.modifiers.pop(stack));
	}

	printf("\r\nstack.destroy start");
	stack_ctrl.configuration.destroy(&stack);

	printf("\r\n------------------------+ stack demo end +------------------------\n");

	return;
}