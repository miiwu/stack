#include "vector.h"

#include "main_cfg.h"

void main_vector(void)
{
	VECTOR_TYPEDEF_PTR
		vector = NULL,
		vector_copy = NULL;

	char
		**string = calloc(1,sizeof(char**)),
		buffer[100] = { 0 },
		*string_start = "####",
		string_moudle[] = "0####";

	printf("\r\n------------------------+ vector demo start +------------------------\n");


	printf("vector.init start\r\n");
	vector_ctrl.configuration.init(&vector, sizeof(char) * 10, true, NULL, NULL);		// 初始化存储 10 长度的 char 类型的 vector_t


	printf("\r\nvector.max_size start\r\n");
	printf("max_size : %d \r\n", vector_ctrl.capacity.max_size(vector));


	printf("\r\nvector.insert start\r\n");
	vector_ctrl.modifiers.insert(vector, 0, 1, &string_start);

	if (NULL != string)
	{
		string_moudle[0] = '0';

		for (size_t i = 0; i < 10; i++) {
			*(string + i) = calloc(100, sizeof(char));

			if (NULL != *(string + i)) {
				memcpy(*(string + i), string_moudle, strlen(string_moudle));
			}

			string_moudle[0] ++;
		}

		vector_ctrl.modifiers.insert(vector, 0, 10, string);
	}


	printf("\r\nvector.copy start\r\n");
	vector_ctrl.modifiers.copy(&vector_copy, vector);


	printf("\r\nvector.at start\r\n");
	for (size_t cnt = 0; cnt < 15; cnt++) {
		printf("at no.%d : \"%s\" \r\n", cnt, (char*)vector_ctrl.element_access.at(vector, cnt));
	}


	printf("\r\nvector.front start\r\n");
	printf("front : \"%s\" \r\n", (char *)vector_ctrl.element_access.front(vector));


	printf("\r\nvector.back start\r\n");
	printf("back : \"%s\" \r\n", (char *)vector_ctrl.element_access.back(vector));


	printf("\r\nvector.clear start\r\n");
	vector_ctrl.modifiers.clear(vector);


	printf("\r\nvector.erase start\r\n");
	for (size_t cnt = 0; cnt < 15; cnt++) {
		vector_ctrl.modifiers.erase(vector_copy, cnt, buffer);

		printf("erase no.%d : \"%s\" \r\n", cnt, buffer);
	}


	printf("\r\nvector.destroy start");
	vector_ctrl.configuration.destroy(&vector);


	printf("\r\n------------------------+ vector demo end +------------------------\n");
	return;
}
