#include "main_cfg.h"

bool main_forward_list_remove_if_rule(void *data)
{
	if (*((char *)data) >= 'w') {
		return true;
	}
	
	return false;
}

void main_forward_list(void)
{
	FORWARD_LIST_TYPEDEF_PTR
		forward_list = NULL,
		forward_list_list_operations = NULL;

	char
		*string = (char *)calloc(25, sizeof("forward list")),
		**string_ptr = calloc(1, sizeof(char *)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "forward list";

	printf("\r\n ------------------------+ forward list demo start +------------------------\r\n");

	printf("forward_list.init start\r\n");
	forward_list_ctrl.configuration.init(&forward_list, sizeof(string_moudle), NULL, NULL);		/* Initialize vector,char[sizeof(string_moudle)] type */

	printf("\r\nforward_list.insert after start\r\n");
	if (NULL != string &&
		NULL != string_ptr) {

		void
			*string_addr = NULL;

		for (size_t i = 0; i < 25; i++) {
			memcpy(((char *)string + i * sizeof("forward list")), string_moudle, sizeof(string_moudle));

			string_moudle[0] ++;
		}

		string_addr = (void *)((size_t)string + 10 * sizeof("forward list"));
		forward_list_ctrl.modifiers.insert_after(forward_list, 5, 10, &string_addr);	/* F: 5 - 15 S/FF:10(p) - 20(y)*/

		string_addr = (void *)((size_t)string + 5 * sizeof("forward list"));
		forward_list_ctrl.modifiers.insert_after(forward_list, 0, 5, &string_addr);		/* F: 0 - 5 S/FF:5(k) - 10(o) */

		forward_list_ctrl.modifiers.insert_after(forward_list, 0, 5, &string);			/* F: 0 - 5 S/FF:0(f) - 5(j) */

		string_addr = (void *)((size_t)string + 20 * sizeof("forward list"));
		forward_list_ctrl.modifiers.insert_after(forward_list, 20, 5, &string_addr);	/* F: 20 - 25 S/FF:20(z) - 25(~) */
	}

	printf("\r\nforward_list & forward_list_list_operation.copy start\r\n");
	forward_list_ctrl.modifiers.copy(&forward_list_list_operations, forward_list);				/* Copy vector,char[sizeof(string_moudle)] type */

	printf("\r\nforward_list_list_operation.pop front start\r\n");
	forward_list_ctrl.modifiers.pop_front(forward_list);

	printf("\r\nforward_list_list_operation.push front start\r\n");
	forward_list_ctrl.modifiers.push_front(forward_list, "############");

	printf("\r\nforward_list.erase start\r\n");
	for (size_t i = 20; i < 25; i++) {     
		forward_list_ctrl.modifiers.erase_after(forward_list, 20);
	}

	printf("\r\nforward_list & forward_list_list_operation.splice_after start\r\n");
	forward_list_ctrl.list_operations.splice_after(forward_list_list_operations, forward_list_ctrl.capacity.size(forward_list_list_operations), forward_list, 0, 1);

	printf("\r\nforward_list & forward_list_list_operation.merge start\r\n");
	forward_list_ctrl.list_operations.merge(forward_list, forward_list_list_operations);

	printf("\r\nforward_list & forward_list_list_operation.splice_after start\r\n");
	forward_list_ctrl.list_operations.splice_after(forward_list_list_operations, forward_list_ctrl.capacity.size(forward_list_list_operations), forward_list, 20, 25);

	printf("\r\nforward_list.front start\r\n");
	printf("front.: \"%s\" \r\n", (char *)forward_list_ctrl.element_access.front(forward_list));

	printf("\r\nforward_list & forward_list_list_operation.swap start\r\n");
	forward_list_ctrl.modifiers.swap(&forward_list, &forward_list_list_operations);

	printf("\r\nforward_list_list_operation.remove start\r\n");
	forward_list_ctrl.list_operations.remove(forward_list_list_operations, "yorward list");

	printf("\r\nforward_list_list_operation.reverse start\r\n");
	forward_list_ctrl.list_operations.reverse(forward_list_list_operations);

	printf("\r\nforward_list_list_operation.sort start\r\n");
	forward_list_ctrl.list_operations.sort(forward_list_list_operations, NULL);

	printf("\r\nforward_list_list_operation.unique start\r\n");
	forward_list_ctrl.list_operations.unique(forward_list_list_operations);

	printf("\r\nforward_list_list_operation.remove if start\r\n");
	forward_list_ctrl.list_operations.remove_if(forward_list_list_operations, main_forward_list_remove_if_rule);

	printf("\r\nforward_list.clear start\r\n");
	forward_list_ctrl.modifiers.clear(forward_list);

	printf("\r\nforward_list_list_operation.clear start\r\n");
	forward_list_ctrl.modifiers.clear(forward_list_list_operations);

	printf("\r\nforward_list.destroy start\r\n");
	forward_list_ctrl.configuration.destroy(&forward_list);

	printf("\r\nnforward_list_list_operation.destroy start\r\n");
	forward_list_ctrl.configuration.destroy(&forward_list_list_operations);

	printf("\r\n ------------------------+ forward list end +------------------------ \r\n");

	return;
}