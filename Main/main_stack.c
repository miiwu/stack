#include "main_cfg.h"

#define MAIN_STACK_CFG_ADAPT_ARRAY_EN				MAIN_ARRAY_EN

#define MAIN_STACK_CFG_ADAPT_VECTOR_EN				MAIN_VECTOR_EN

#define MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN		MAIN_FORWARD_LIST_EN

#define MAIN_STACK_CFG_ADAPT_LIST_EN				MAIN_LIST_EN

void *stack_container = NULL;

#if (MAIN_STACK_CFG_ADAPT_ARRAY_EN)

#define MAIN_STACK_CONTAINER	ARRAY

#define MAIN_STACK_CONTAINER_CONTROL	array_ctrl

#define MAIN_STACK_CONTAINER_TYPE		(struct array_s *)stack_container

#endif // (MAIN_STACK_CFG_ADAPT_ARRAY_EN)

#if (MAIN_STACK_CFG_ADAPT_VECTOR_EN)

#define MAIN_STACK_CONTAINER	VECTOR

#define MAIN_STACK_CONTAINER_CONTROL	vector_ctrl

#define MAIN_STACK_CONTAINER_TYPE		(struct vector_s *)stack_container

#endif // (MAIN_STACK_CFG_ADAPT_VECTOR_EN)

#if (MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN)

#define MAIN_STACK_CONTAINER	FORWARD_LIST

#define MAIN_STACK_CONTAINER_CONTROL	forward_list_ctrl

#define MAIN_STACK_CONTAINER_TYPE		(struct list_family_s *)stack_container

#endif // (MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN)

#if (MAIN_STACK_CFG_ADAPT_LIST_EN)

#define MAIN_STACK_CONTAINER	LIST

#define MAIN_STACK_CONTAINER_CONTROL	list_ctrl

#define MAIN_STACK_CONTAINER_TYPE		(struct list_family_s *)stack_container

#endif // (MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN)

#ifndef MAIN_STACK_CONTAINER

#define MAIN_STACK_CONTAINER	ARRAY

#define MAIN_STACK_CONTAINER_CONTROL	array_ctrl

#define MAIN_STACK_CONTAINER_TYPE		(struct array_s *)stack_container

#endif // !MAIN_STACK_CONTAINER

void main_stack(void)
{
	stack_tp
		stack = NULL,
		stack_attach = NULL,
		stack_copy = NULL;

	char
		**string = calloc(1, sizeof(char **)),
		*string_start = "####",
		string_modle[] = "stack";

	printf("\r\n ------------------------+ stack demo start +------------------------ \r\n");

	printf("stack.init start\r\n");
	stack_ctrl.configuration.init(&stack, 											/* Initialize stack,char[sizeof(string_moudle)] type */
								  MAIN_STACK_CONTAINER, sizeof(string_modle),
								  NULL, NULL);
	MAIN_STACK_CONTAINER_CONTROL.configuration.init(&MAIN_STACK_CONTAINER_TYPE, 	/* Initialize stack_container,char[sizeof(string_moudle)] type */
													sizeof(string_modle),
													NULL, NULL);
	stack_ctrl.configuration.attach(&stack_attach, 									/* Attach stack adapt to the container */
									MAIN_STACK_CONTAINER, MAIN_STACK_CONTAINER_TYPE);

	printf("\r\nstack.max_size start\r\n");
	printf("max size : %d \r\n    ", stack_ctrl.capacity.max_size(stack));

	printf("\r\nstack_attach.max_size start\r\n");
	printf("max size : %d \r\n    ", stack_ctrl.capacity.max_size(stack_attach));

	printf("\r\nstack.push start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("push no.%d : \"%s\" \r\n", cnt, string_modle);

		stack_ctrl.modifiers.push(stack, string_modle);

		string_modle[0] += 1;
	}

	printf("\r\nstack .top start\r\n");
	printf("top : \"%s\" \r\n", (char *)stack_ctrl.element_access.top(stack));

	printf("\r\nstack & stack_attach.copy stack start\r\n");
	stack_ctrl.modifiers.copy(&stack_attach, stack);

	printf("\r\nstack_attach.pop start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("top no.%d : \"%s\" \r\n", cnt, (char *)stack_ctrl.element_access.top(stack_attach));
		stack_ctrl.modifiers.pop(stack_attach);
	}

	printf("\r\nstack.destroy start\r\n");
	stack_ctrl.configuration.destroy(&stack);

	printf("\r\nstack_attach.destroy start\r\n");
	stack_ctrl.configuration.destroy(&stack_attach);

	printf("\r\n ------------------------+ stack demo end +------------------------\r\n");

	return;
}