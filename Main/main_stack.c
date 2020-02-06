#include "main_cfg.h"

#define MAIN_STACK_CFG_ADAPT_ARRAY_EN				MAIN_ARRAY_EN

#define MAIN_STACK_CFG_ADAPT_VECTOR_EN				MAIN_VECTOR_EN

#define MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN		MAIN_FORWARD_LIST_EN

#define MAIN_STACK_CFG_ADAPT_LIST_EN				MAIN_LIST_EN

#define MAIN_STACK_CONTAINER	ARRAY

#define MAIN_STACK_CONTAINER_CONTROL	array_ctrl

VECTOR_TYPEDEF_PTR stack_container = NULL;

#if (MAIN_STACK_CFG_ADAPT_ARRAY_EN)

#define MAIN_STACK_CONTAINER	ARRAY

#define MAIN_STACK_CONTAINER_CONTROL	array_ctrl

ARRAY_TYPEDEF_PTR stack_container = NULL;

#endif // (MAIN_STACK_CFG_ADAPT_ARRAY_EN)

#if (MAIN_STACK_CFG_ADAPT_VECTOR_EN)

#define MAIN_STACK_CONTAINER	VECTOR

#define MAIN_STACK_CONTAINER_CONTROL	vector_ctrl

VECTOR_TYPEDEF_PTR stack_container = NULL;

#endif // (MAIN_STACK_CFG_ADAPT_VECTOR_EN)

#if (MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN)

#define MAIN_STACK_CONTAINER	FORWARD_LIST

#define MAIN_STACK_CONTAINER_CONTROL	forward_list_ctrl

FORWARD_LIST_TYPEDEF_PTR stack_container = NULL;

#endif // (MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN)

#if (MAIN_STACK_CFG_ADAPT_LIST_EN)

#define MAIN_STACK_CONTAINER	LIST

#define MAIN_STACK_CONTAINER_CONTROL	list_ctrl

LIST_TYPEDEF_PTR stack_container = NULL;

#endif // (MAIN_STACK_CFG_ADAPT_FORWARD_LIST_EN)

void main_stack_generic_type_operator_assign(void *gnc, void *src);
void main_stack_generic_type_operator_free(void *gnc);

struct generic_type_t {
	char symbol;

	char *string;

	int number;
};

void main_stack(void)
{
	STACK_TYPEDEF_PTR
		stack = NULL,
		stack_attach = NULL,
		stack_copy = NULL;

	char
		**string = calloc(1, sizeof(char **)),
		*string_start = "####",
		string_modle[] = "stack";

	struct generic_type_t demo = {
		'1',
		string_modle,
		3
	};

	printf("\r\n ------------------------+ stack demo start +------------------------ \r\n");

	printf("stack.init start\r\n");
	stack_ctrl.configuration.init(&stack, MAIN_STACK_CONTAINER, sizeof(struct generic_type_t),
								  main_stack_generic_type_operator_assign, main_stack_generic_type_operator_free);						/* Initialize stack,char[sizeof(string_moudle)] type */
	MAIN_STACK_CONTAINER_CONTROL.configuration.init(&stack_container, sizeof(struct generic_type_t),
													main_stack_generic_type_operator_assign, main_stack_generic_type_operator_free);	/* Initialize stack_container,char[sizeof(string_moudle)] type */
	stack_ctrl.configuration.attach(&stack_attach, MAIN_STACK_CONTAINER, stack_container);

	printf("\r\nstack.max_size start\r\n");
	printf("max size : %d \r\n    ", stack_ctrl.capacity.max_size(stack));

	printf("\r\nstack_attach.max_size start\r\n");
	printf("max size : %d \r\n    ", stack_ctrl.capacity.max_size(stack_attach));

	printf("\r\nstack.push start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("push no.%d : \"%s\" \r\n", cnt, demo.string);

		stack_ctrl.modifiers.push(stack, &demo);

		string_modle[0] += 1;
	}

	printf("\r\nstack .top start\r\n");
	printf("top : \"%s\" \r\n", ((struct generic_type_t *)stack_ctrl.element_access.top(stack))->string);

	printf("\r\nstack & stack_attach.copy stack start\r\n");
	stack_ctrl.modifiers.copy(&stack_attach, stack);

	printf("\r\nstack_attach.pop start\r\n");
	for (size_t cnt = 0; cnt < 10; cnt++) {
		printf("top no.%d : \"%s\" \r\n", cnt, ((struct generic_type_t *)stack_ctrl.element_access.top(stack_attach))->string);
		stack_ctrl.modifiers.pop(stack_attach);
	}

	printf("\r\nstack.destroy start\r\n");
	stack_ctrl.configuration.destroy(&stack);

	printf("\r\nstack_attach.destroy start\r\n");
	stack_ctrl.configuration.destroy(&stack_attach);

	printf("\r\n ------------------------+ stack demo end +------------------------\r\n");

	return;
}

void main_stack_generic_type_operator_assign(void *gnc, void *src)					/* function may preform like copy the pointer src to the pointer gnc */
{
	assert(gnc);
	assert(src);

	struct generic_type_t
		*generic_type_gnc = gnc,
		*generic_type_src = src;

	generic_type_gnc->string = calloc(1, sizeof("stack"));							/* those are pointer,so malloc it as count*sizeof("stack"),
																						the sizeof("stack") will be the memory size of the type the pointer point to */

	if (NULL == generic_type_gnc->string) {
		return;
	}

	generic_type_gnc->symbol = generic_type_src->symbol;							/* both below are the not-pointer type handle method */
	memcpy(&generic_type_gnc->number, &generic_type_src->number, sizeof(int));

	memcpy(generic_type_gnc->string, generic_type_src->string, sizeof("stack"));	/* memcpy the content of the pointer point to */
}

void main_stack_generic_type_operator_free(void *gnc)
{
	struct generic_type_t
		*generic_type_gnc = gnc;

	memset(generic_type_gnc->string, '0', sizeof("stack"));

	free(generic_type_gnc->string);													/* free the memory space the calloc on the assign function */
}