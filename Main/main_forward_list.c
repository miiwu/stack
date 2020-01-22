#include "main_cfg.h"

void main_forward_list(void)
{
	FORWARD_LIST_TYPEDEF_PTR
		forward_list = NULL;

	char
		*string = (char *)calloc(sizeof("vector") * 20, sizeof(char)),
		**string_ptr = calloc(1, sizeof(char *)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "forward list";

	printf("\r\n ------------------------+ forward list demo start +------------------------\r\n");


	printf("forward list.init start\r\n");
	forward_list_ctrl.configuration.init(&forward_list, sizeof(string_moudle), NULL, NULL);		/* Initialize vector,char[sizeof(string_moudle)] type */


	printf("\r\nforward list.insert after start\r\n");
	if (NULL != string &&
		NULL != string_ptr) {
		for (size_t i = 0; i < 10; i++) {
			memcpy(((char *)string + i * sizeof("forward list")), string_moudle, sizeof(string_moudle));

			string_moudle[0] ++;
		}

		forward_list_ctrl.modifiers.insert_after(forward_list, 0, 10, &string);
	}


	printf("\r\nforward list.front start\r\n");
	printf("front.: \"%s\" \r\n", (char*)forward_list_ctrl.element_access.front(forward_list));


	//printf("\r\nforward list.erase start\r\n");
	//for (size_t i = 0; i < 10; i++) {
	//	forward_list_ctrl.modifiers.erase_after(forward_list, 0, buffer);				/* MUST NOT :  */
	//	printf("erase no.%d : \"%s\" \r\n", i,buffer);
	//}


	printf("\r\nforward list.clear start\r\n");
	forward_list_ctrl.modifiers.clear(forward_list);


	printf("\r\nforward list.destroy start\r\n");
	forward_list_ctrl.configuration.destroy(&forward_list);


	printf("\r\n ------------------------+ forward list end +------------------------ \r\n");


	return;
}