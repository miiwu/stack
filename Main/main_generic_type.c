#include "main_cfg.h"

errno_t main_generic_type_demo_assign(void *gnc, void *src);
errno_t main_generic_type_demo_free(void *gnc);

struct generic_type_s {
	char symbol;

	char *string;

	int number;
};

void main_generic_type(void)
{
	stack_tp
		stack = NULL;

	char
		**string = calloc(1, sizeof(char **)),
		*string_start = "####",
		string_modle[] = "stack";

	struct generic_type_s demo = {
		'1',
		string_modle,
		3
	};

	printf("\r\n ------------------------+ generic type element demo start +------------------------ \r\n");

	printf("stack.init start\r\n");
	stack_ctrl.configuration.init(&stack, ARRAY, sizeof(struct generic_type_s),				/* Initialize stack,char[sizeof(string_moudle)] type */
								  main_generic_type_demo_assign,
								  main_generic_type_demo_free);

	printf("\r\nstack.push start\r\n");
	for (size_t cnt = 0; cnt < 2; cnt++) {
		printf("push no.%d : \"%s\" \r\n", cnt, demo.string);

		stack_ctrl.modifiers.push(stack, &demo);

		string_modle[0] += 1;
	}

	printf("\r\nstack .top start\r\n");
	printf("top : \"%s\" \r\n",
		((struct generic_type_s *)stack_ctrl.element_access.top(stack))->string);

	printf("\r\nstack_attach.pop start\r\n");
	stack_ctrl.modifiers.pop(stack);

	printf("\r\nstack .top start\r\n");
	printf("top : \"%s\" \r\n",
		((struct generic_type_s *)stack_ctrl.element_access.top(stack))->string);

	printf("\r\nstack_attach.destroy start\r\n");
	stack_ctrl.configuration.destroy(&stack);

	printf("\r\n ------------------------+ generic type element demo start +------------------------\r\n");

	return;
}

errno_t main_generic_type_demo_assign(void *gnc, void *src)
	/* Function may preform like copy the pointer src to the pointer gnc.	*/
{
	assert(gnc);
	assert(src);

	/* The length of these data type below must be absolutely CERTAIN,
		because it may use the memcpy(), for safety,
		Or you need to allocate the memory for the type in advance,
		then Store the address of the memory to the container,
		when this element is useless, deallocate it yourself.				*/

	struct generic_type_s
		*generic_type_gnc = gnc,
		*generic_type_src = src;

	/* This are pointer,i want to store many "*tack",
		so malloc it as count * sizeof("stack").							*/
	if (NULL == (generic_type_gnc->string = calloc(1, sizeof("stack")))) {
		return -1;
	}

	/* Memcpy the content of the pointer point to							*/
	if (NULL == memcpy(generic_type_gnc->string, generic_type_src->string,
					   sizeof("stack"))) {
		return 1;
	}

	/* Copy the value of src to the gnc.									*/
	generic_type_gnc->symbol = generic_type_src->symbol;
	generic_type_gnc->number = generic_type_src->number;

	return 0;
}

errno_t main_generic_type_demo_free(void *gnc)
{
	assert(gnc);

	/* Free the memory space allocated at the assign().						*/
	free(((struct generic_type_s *)gnc)->string);

	return 0;
}