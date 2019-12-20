#include "stack.h"
#include "queue.h"

typedef struct
{
	char ch;
	short* so;
	int it;
}TEST_TYPEDEF, * TEST_TYPEDEF_PTR;

void assign(void* buffer, const void* data)
{
	TEST_TYPEDEF_PTR temp_data_ptr = (TEST_TYPEDEF_PTR)data;
	TEST_TYPEDEF_PTR temp_buffer_ptr = (TEST_TYPEDEF_PTR)buffer;

	short* temp = temp_buffer_ptr->so = (short*)calloc(1, sizeof(short));

	*temp = *(short*)(temp_data_ptr->so);

	*temp_buffer_ptr = *temp_data_ptr;

	temp_buffer_ptr->so = temp;
}

void delete(void* buffer)
{
	TEST_TYPEDEF_PTR temp_data_ptr = (TEST_TYPEDEF_PTR)buffer;

	free(temp_data_ptr->so);
}

void assign_charp(void* buffer, const void* data)
{
	char* temp_date_ptr = (char*)data;
	char* temp_buffer_ptr = (char*)buffer;

	size_t length = strlen(temp_date_ptr);

	for (size_t i = 0; i < length; i++)
	{
		temp_buffer_ptr[i] = temp_date_ptr[i];
	}

	temp_buffer_ptr[length] = '\0';
}

void main()
{
#define CHAIN_GENERIC_STACK				1
#define STACK_TEST_CHAR					0
#define CHAIN_STACK_TEST_CHAR			0
#define CHAIN_STACK_TEST_STRING			1

#if CHAIN_GENERIC_STACK

	short
		buffer_so = 0,
		data_so = 2;

	TEST_TYPEDEF
		data_buffer_typedef =
	{
		0,
		&buffer_so ,
		0
	},
		data_typedef =
	{
		1,
		&data_so,
		3
	};

	char
		buffer[100] = { 0 },
		data[] = "12345";

	CHAIN_GENERIC_STACK_TYPEDEF_PTR
		chain_generic_stack_normal = { 0 },
		chain_generic_stack = { 0 };

	chain_generic_stack_ctrl.init(&chain_generic_stack, sizeof(TEST_TYPEDEF), 10, assign, delete);

	chain_generic_stack_ctrl.push(chain_generic_stack, &data_typedef, 0);

	printf("stack current depth:%d \r\n",chain_generic_stack_ctrl.get_stack_info.current_depth(chain_generic_stack));

	chain_generic_stack_ctrl.pop(chain_generic_stack, &data_buffer_typedef);

	printf("stack current depth:%d \r\n", chain_generic_stack_ctrl.get_stack_info.current_depth(chain_generic_stack));

	chain_generic_stack_ctrl.free(&chain_generic_stack);

	/* 
	|->Problem Part Start [ RESERVED SOLVE ]

	//printf("%s \r\n", data);

	//chain_generic_stack_ct.init(&chain_generic_stack_normal, sizeof(char*), 10, assign_charp, NULL);

	//chain_generic_stack_ct.push(&chain_generic_stack_normal, &data, 0);

	//chain_generic_stack_ct.pop(&chain_generic_stack_normal, &buffer);

	//printf("%s \r\n", buff);

	Problem Part End <-| 
	*/

#endif

#if STACK_TEST_CHAR

	char atom = 0;
	char array[100] = { 0 };
	SEQUENCE_STACK_TYPEDEF stack;

	stack_ctrl.init(&stack, 100);

	for (size_t i = 0; i < 10; i++)
	{
		stack.push(&stack, i + '0');
	}
	stack.multi_pop(&stack, array, 10);

	stack_pop(&stack, &atom);

	printf("pop: %d ", atom);

	for (size_t i = 0; i < 10; i++)
	{
		printf("pop: %c ", array[i]);
	}

	stack_ctrl.free(&stack);

	printf("\r\n");

#endif
#if CHAIN_STACK_TEST_CHAR

	char atom = 0;
	char array[100] = { 0 };
	CHAIN_SEQUENCE_STACK_TYPEDEF chain_stack;

	stack_ctrl.chain_stack.init(&chain_stack, 10);

	for (size_t i = 0; i < 10; i++)
	{
	    chain_stack.push(&chain_stack, i + '0');
	}

	for (size_t i = 0; i < 10; i++)
	{
	    chain_stack.pop(&chain_stack, &array[i]);

	    printf("pop: %c ", array[i]);
	}

	chain_stack.pop(&chain_stack, &array[11]);

	stack_ctrl.free(&chain_stack);

	printf("\r\n");

#endif
#if CHAIN_STACK_TEST_STRING

	char atom = 0;
	char array[10][100] = { 0 };
	CHAIN_STACK_TYPEDEF_PTR 
		chain_stack = NULL;

	CHAIN_STACK_DATA_TYPE* array_ptr = NULL;
	CHAIN_STACK_DATA_TYPE array_p[10] = { NULL };

	for (size_t i = 0; i < 10; i++)
	{
		array_p[i] = (CHAIN_STACK_DATA_TYPE)calloc(10, sizeof(char));
	}

	chain_stack_ctrl.init(&chain_stack, 10);

	for (char i = 0; i < 11; i++)
	{
		char temp[20] = { 0 };

		temp[0] = i + '0';

		chain_stack_ctrl.push(chain_stack, temp, strlen(temp));
	}

	chain_stack_ctrl.get(chain_stack, array[0]);

	printf("get: %s \r\n", array[0]);

	chain_stack_ctrl.multi_pop(chain_stack, array_p, 10);

	for (size_t i = 0; i < 10; i++)
	{
		printf("pop: %s ", array_p[i]);
	}

	chain_stack_ctrl.delete(chain_stack);

	chain_stack_ctrl.free(&chain_stack);

#endif
#if 0
	//int
	//    array[10] = { 0,1,3,0,5,6,7,0,9,1 },
	//    rule[10] = { 1,2,3,4,5,6,7,8,9,1 };

	//int size = 10;

	//data_verify_percent(array,rule,size);

	//printf("*:%f \r\n", data_verify_percent(array, rule, size));
	//printf("_:%f \r\n", _data_verify_percent(array, rule, size));
#endif

	printf("\r\n Program End . \r\n");

	return;
}