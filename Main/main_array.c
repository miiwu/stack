#include "main_cfg.h"

#if MAIN_ARRAY_EN

void main_array(void)
{
	array_stp
		array = NULL,
		array_copy = NULL;

	char
		*string = (char *)calloc(sizeof("array") * 20, sizeof(char)),
		**string_ptr = calloc(1, sizeof(char *)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "array";

	LONG start = 0, end = 0;

	printf("\r\n ------------------------+ array demo start +------------------------\r\n");

	printf("array.init start\r\n");
	array_ctrl.configuration.init(&array, sizeof(string_moudle), NULL, NULL);		/* Initialize array,char[sizeof(string_moudle)] type */

	printf("\r\narray.data start\r\n");
	printf("data : %p \r\n", array_ctrl.element_access.data(array));

	printf("\r\narray.max_size start\r\n");
	printf("max_size : %d \r\n", array_ctrl.capacity.max_size(array));

	printf("\r\narray.push back start\r\n");
	array_ctrl.modifiers.push_back(array, string_start);
	printf("at no.%d : \"%s\" \r\n", 0, (char *)array_ctrl.element_access.at(array, 0));

	printf("\r\narray.insert start\r\n");
	if (NULL != string &&
		NULL != string_ptr) {
		for (size_t i = 0; i < 10; i++) {
			memcpy(((char *)string + i * sizeof("array")), string_moudle, sizeof(string_moudle));

			string_moudle[0] ++;
		}

		array_ctrl.modifiers.insert(array, 0, 10, &string);
	}

	printf("\r\narray copy.copy stack start\r\n");
	array_ctrl.modifiers.copy(&array_copy, array);

	printf("\r\narray.pop back start\r\n");
	array_ctrl.modifiers.pop_back(array);
	printf("array.pop back : %s \r\n", (char *)array_ctrl.element_access.at(array, array_ctrl.capacity.size(array)));

	printf("\r\narray.at start\r\n");
	for (size_t cnt = 0; cnt < 15; cnt++) {
		printf("at no.%d : \"%s\" \r\n", cnt, (char *)array_ctrl.element_access.at(array, cnt));
	}

	printf("\r\narray.front start\r\n");
	printf("front : \"%s\" \r\n", (char *)array_ctrl.element_access.front(array));

	printf("\r\narray.back start\r\n");
	printf("back : \"%s\" \r\n", (char *)array_ctrl.element_access.back(array));

	printf("\r\narray.clear start\r\n");
	array_ctrl.modifiers.clear(array);

	printf("\r\narray copy.erase start\r\n");

	for (size_t cnt = 0; cnt < 15; cnt++) {
		array_ctrl.modifiers.erase(array_copy, cnt);
	}

	printf("\r\narray & array copy.destroy start\r\n");
	array_ctrl.configuration.destroy(&array);
	array_ctrl.configuration.destroy(&array_copy);

	printf("\r\n ------------------------+ array demo end +------------------------ \r\n");

	return;
}

#endif // MAIN_ARRAY_EN