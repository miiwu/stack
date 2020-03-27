#include "main_cfg.h"

#if MAIN_LIST_EN

bool main_list_remove_if_rule(void *data)
{
	if (*((char *)data) > 'z') {
		return true;
	}

	return false;
}

void main_list(void)
{
	list_stp
		list = NULL,
		list_list_operations = NULL;

	char
		*string = (char *)calloc(25, sizeof("list")),
		**string_ptr = calloc(1, sizeof(char *)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "list";

	printf("\r\n ------------------------+ list demo start +------------------------\r\n");

	printf("list.init start\r\n");
	list_ctrl.configuration.init(&list, sizeof(string_moudle), NULL, NULL);		/* Initialize vector,char[sizeof(string_moudle)] type */

	printf("\r\nlist.insert after start\r\n");
	if (NULL != string &&
		NULL != string_ptr) {
		void
			*string_addr = NULL;

		for (size_t i = 0; i < 25; i++) {
			memcpy(((char *)string + i * sizeof("list")), string_moudle, sizeof(string_moudle));

			string_moudle[0] ++;
		}

		string_addr = (void *)((size_t)string + 10 * sizeof("list"));
		list_ctrl.modifiers.insert_after(list, 5, 10, &string_addr);	/* F: 5 - 15 S/FF:10(p) - 20(y)*/

		string_addr = (void *)((size_t)string + 5 * sizeof("list"));
		list_ctrl.modifiers.insert_after(list, 0, 5, &string_addr);		/* F: 0 - 5 S/FF:5(k) - 10(o) */

		list_ctrl.modifiers.insert_after(list, 0, 5, &string);			/* F: 0 - 5 S/FF:0(f) - 5(j) */

		string_addr = (void *)((size_t)string + 20 * sizeof("list"));
		list_ctrl.modifiers.insert_after(list, 20, 5, &string_addr);	/* F: 20 - 25 S/FF:20(z) - 25(~) */
	}

	printf("\r\nlist & list_list_operation.copy start\r\n");
	list_ctrl.modifiers.copy(&list_list_operations, list);

	printf("\r\nlist_list_operation.pop front start\r\n");
	list_ctrl.modifiers.pop_front(list);

	printf("\r\nlist_list_operation.push front start\r\n");
	list_ctrl.modifiers.push_front(list, "####");

	printf("\r\nlist.erase start\r\n");
	for (size_t i = 20; i < 25; i++) {
		list_ctrl.modifiers.erase_after(list, 20);
	}

	printf("\r\nlist & list_list_operation.splice_after start\r\n");
	list_ctrl.list_operations.splice_after(list_list_operations, list_ctrl.capacity.size(list_list_operations), list, 0, 1);

	printf("\r\nlist & list_list_operation.merge start\r\n");
	list_ctrl.list_operations.merge(list, list_list_operations);

	printf("\r\nlist & list_list_operation.splice_after start\r\n");
	list_ctrl.list_operations.splice_after(list_list_operations, list_ctrl.capacity.size(list_list_operations), list, 20, 25);

	printf("\r\nlist.front start\r\n");
	printf("front.: \"%s\" \r\n", (char *)list_ctrl.element_access.front(list));

	printf("\r\nlist & list_list_operation.swap start\r\n");
	list_ctrl.modifiers.swap(&list, &list_list_operations);

	printf("\r\nlist_list_operation.remove start\r\n");
	list_ctrl.list_operations.remove(list_list_operations, "|ist");

	printf("\r\nlist_list_operation.reverse start\r\n");
	list_ctrl.list_operations.reverse(list_list_operations);

	printf("\r\nlist_list_operation.sort start\r\n");
	list_ctrl.list_operations.sort(list_list_operations, NULL);

	printf("\r\nlist_list_operation.unique start\r\n");
	list_ctrl.list_operations.unique(list_list_operations);

	printf("\r\nlist_list_operation.remove if start\r\n");
	list_ctrl.list_operations.remove_if(list_list_operations, main_list_remove_if_rule);

	printf("\r\nlist.clear start\r\n");
	list_ctrl.modifiers.clear(list);

	printf("\r\nlist_list_operation.clear start\r\n");
	list_ctrl.modifiers.clear(list_list_operations);

	printf("\r\nlist.destroy start\r\n");
	list_ctrl.configuration.destroy(&list);

	printf("\r\nnlist_list_operation.destroy start\r\n");
	list_ctrl.configuration.destroy(&list_list_operations);

	printf("\r\n ------------------------+ list end +------------------------ \r\n");

	return;
}

#endif // MAIN_LIST_EN