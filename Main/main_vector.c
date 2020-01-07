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
		string_moudle[] = "vector";

	printf("\r\n------------------------+ vector demo start +------------------------\n");


	printf("vector.init start\r\n");
	vector_ctrl.configuration.init(&vector, sizeof(char) * 10, true, NULL, NULL);		/* Initialize vector,char[10] type */


	printf("\r\nvector.data start\r\n");
	printf("data : %p \r\n", vector_ctrl.element_access.data(vector));


	printf("\r\nvector.max_size start\r\n");
	printf("max_size : %d \r\n", vector_ctrl.capacity.max_size(vector));


	printf("\r\nvector.push back start\r\n");
	vector_ctrl.modifiers.push_back(vector, string_start);
	printf("at no.%d : \"%s\" \r\n", 0, (char *)vector_ctrl.element_access.at(vector, 0));


	printf("\r\nvector.insert start\r\n");
	if (NULL != string)
	{
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


	printf("\r\nvector.pop back start\r\n");
	vector_ctrl.modifiers.pop_back(vector, string_moudle);
	printf("vector.pop back : %s \r\n", string_moudle);


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
		memset(buffer, '\0', sizeof(buffer));

		vector_ctrl.modifiers.erase(vector_copy, cnt, buffer);

		printf("erase no.%d : \"%s\" \r\n", cnt, buffer);
	}


	printf("\r\nvector.destroy start\r\n");
	vector_ctrl.configuration.destroy(&vector);
	vector_ctrl.configuration.destroy(&vector_copy);


	printf("\r\n------------------------+ vector demo end +------------------------\n");

	return;
}
