#include "stack.h"

bool stack_control_sequence_stack_init(SEQUENCE_STACK_TYPEDEF_PTR stack, size_t depth);
bool stack_control_sequence_stack_free(SEQUENCE_STACK_TYPEDEF_PTR stack);

bool sequence_stack_push(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE atom);
bool sequence_stack_pop(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom);
bool sequence_stack_multi_pop(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* array, size_t size);

void sequence_stack_default_full_stacl_expection(void);
void sequence_stack_default_null_stacl_expection(void);
void sequence_stack_default_lack_heap_expection(void);

bool stack_control_chain_stack_init(CHAIN_STACK_TYPEDEF_PTR stack, size_t depth);
bool stack_control_chain_stack_exception_config(CHAIN_STACK_TYPEDEF_PTR chain_stack,
	bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...);
bool stack_control_chain_stack_free(CHAIN_STACK_TYPEDEF_PTR stack);

bool chain_stack_push(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom, size_t sizeof_atom);
bool chain_stack_pop(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom);
bool chain_stack_get(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom);
bool chain_stack_delete(CHAIN_STACK_TYPEDEF_PTR chain_stack);
bool chain_stack_multi_pop(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE* array, size_t depth);

void chain_stack_default_full_stacl_expection(void);
void chain_stack_default_null_stacl_expection(void);
void chain_stack_default_lack_heap_expection(void);

SEQUENCE_STACK_CONTROL_TYPEDEF sequence_stack_ctrl =
{
	sequence_stack_push,
	sequence_stack_pop,
	sequence_stack_multi_pop
};
CHAIN_STACK_CONTROL_TYPEDEF chain_stack_ctrl =
{
	chain_stack_push,
	chain_stack_pop,
	chain_stack_get,
	chain_stack_delete,
	chain_stack_multi_pop
};

STACK_CONTROL_TYPEDEF stack_ctrl =
{
	{
		stack_control_sequence_stack_init,
		stack_control_sequence_stack_free,

		sequence_stack_push,
		sequence_stack_pop,
		sequence_stack_multi_pop
	},
	{
		stack_control_chain_stack_init,
		stack_control_chain_stack_exception_config,
		stack_control_chain_stack_free,

		chain_stack_push,
		chain_stack_pop,
		chain_stack_get,
		chain_stack_delete,
		chain_stack_multi_pop
	}
};

bool stack_control_sequence_stack_init(SEQUENCE_STACK_TYPEDEF_PTR stack, size_t depth)
{
	if ((stack->data = (char*)malloc(sizeof(char) * depth)) == NULL)
		return false;

	stack->info.stack_malloc = true;
	stack->info.stack_depth = depth;
	stack->info.stack_top = 0;

	//stack->push = stack_push;
	//stack->pop = stack_pop;
	//stack->multi_pop = stack_multi_pop;

	stack->expection.full_stack = sequence_stack_default_full_stacl_expection;
	stack->expection.null_stack = sequence_stack_default_null_stacl_expection;
	stack->expection.lack_heap = sequence_stack_default_lack_heap_expection;

	return true;
}

bool stack_control_sequence_stack_free(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_malloc == true)
	{
		free(stack->data);

		stack->info.stack_malloc = false;
		stack->data = NULL;
	}

	return true;
}

bool sequence_stack_push(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE atom)
{
	if (stack->info.stack_top < stack->info.stack_depth)    // 如果没有满栈
	{
		stack->data[++stack->info.stack_top] = atom;

		return true;
	}
	else
	{
		stack->expection.full_stack();                           // stack_exception

		return false;
	}
}

bool sequence_stack_pop(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom)
{
	if (stack->info.stack_top > 0)                            // 如果没有空栈
	{
		*atom = stack->data[stack->info.stack_top];
		stack->info.stack_top--;

		return true;
	}
	else
	{
		stack->expection.null_stack();                           // stack_exception

		return false;
	}
}

void sequence_stack_default_full_stacl_expection(void)
{
	printf("stack_full_expectopn. \r\n");
}

void sequence_stack_default_null_stacl_expection(void)
{
	printf("stack_null_expectopn. \r\n");
}

void sequence_stack_default_lack_heap_expection(void)
{
	printf("heap_null_expectopn. \r\n");
}

bool sequence_stack_multi_pop(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* array, size_t size)
{
	if (stack->info.stack_top >= size)                            // 如果没有空栈
	{
		for (size_t cnt = size; cnt > 0; cnt--)
		{
			*(array + cnt - 1) = stack->data[stack->info.stack_top--];
		}

		return true;
	}
	else
	{
		stack->expection.null_stack();                           // stack_exception

		return false;
	}
}

int sequence_stack_get_top(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	int temp = 0;

	//if(stack_pop(stack,&temp) == false)
	//    return false;

	return temp;
}

bool stack_control_chain_stack_init(CHAIN_STACK_TYPEDEF_PTR chain_stack, size_t max_depth)
{																			// 初始化一个链栈
	if (max_depth <= 0)
	{
		return false;
	}

	chain_stack->info.stack_crt_depth = 0;									// 填充最大深度和清零当前深度
	chain_stack->info.stack_max_depth = max_depth;

	//chain_stack->push = chain_stack_push;
	//chain_stack->pop = chain_stack_pop;
	//chain_stack->multi_pop = chain_stack_multi_pop;

	chain_stack->expection.full_stack = chain_stack_default_full_stacl_expection;	// 赋值异常函数
	chain_stack->expection.null_stack = chain_stack_default_null_stacl_expection;
	chain_stack->expection.lack_heap = chain_stack_default_lack_heap_expection;

	return true;
}

bool stack_control_chain_stack_exception_config(CHAIN_STACK_TYPEDEF_PTR chain_stack, 
	bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg,...)
{
	va_list va_ptr;

	short 
		cfg_queue[CHAIN_STACK_EXCEPTION_TYPE_AMOUNT] = 
			{ is_full_stack_cfg + 10 ,is_null_stack_cfg + 20 ,is_lack_heap_cfg + 30};

	va_start(va_ptr, is_lack_heap_cfg);

	for (size_t cnt = 0; cnt < CHAIN_STACK_EXCEPTION_TYPE_AMOUNT; cnt++)
	{	
		switch (cfg_queue[cnt])
		{
			case 11:
				chain_stack->expection.full_stack = (void*)va_arg(va_ptr, int);
				break;
			case 21:
				chain_stack->expection.null_stack = (void*)va_arg(va_ptr, int);
				break;
			case 31:
				chain_stack->expection.lack_heap = (void*)va_arg(va_ptr, int);
				break;
			default:
				break;
		}
	}

	va_end(va_ptr);

	return true;
}

bool stack_control_chain_stack_free(CHAIN_STACK_TYPEDEF_PTR chain_stack)
{
	if (chain_stack->info.stack_malloc == true ||
		chain_stack->info.stack_crt_depth > 0)								// 如果被 malloc 过,或者没空栈
	{
		CHAIN_STACK_NODE_TYPEDEF* stack_node_prev = NULL;

		char atom[10] = { 0 };

		for (size_t cnt = chain_stack->info.stack_crt_depth; cnt > 0; cnt--)
			chain_stack_delete(chain_stack);

		chain_stack->info.stack_malloc = false;
		chain_stack->top = NULL;											// 变成空指针
	}

	return true;
}

bool chain_stack_push(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom, size_t sizeof_atom)
{																			// push top 节点，入栈一个数据，并创建一个节点用于存储
	CHAIN_STACK_NODE_TYPEDEF_PTR
		stack_node_now = (CHAIN_STACK_NODE_TYPEDEF_PTR)calloc(1, sizeof(CHAIN_STACK_NODE_TYPEDEF));

	CHAIN_STACK_DATA_TYPE stack_node_data_ptr = (CHAIN_STACK_DATA_TYPE)calloc(sizeof_atom + 1, sizeof(char));

	if (stack_node_now == NULL || stack_node_data_ptr == NULL)				// 堆空间不足异常
	{
		chain_stack->expection.lack_heap();

		return false;
	}
	if (chain_stack->info.stack_max_depth <=
		chain_stack->info.stack_crt_depth)									// 空栈异常
	{
		chain_stack->expection.full_stack();

		return false;
	}

	stack_node_now->data = stack_node_data_ptr;								// 分配数据空间
	stack_node_now->data_length = sizeof_atom;								// 记录数据长度

	for (size_t i = 0; i < sizeof_atom; i++)
		stack_node_now->data[i] = atom[i];									// 填充数据空间

	stack_node_now->next = chain_stack->top;								// 把 top 节点压入栈底，即赋值给 now.next

	chain_stack->top = stack_node_now;										// 上浮 top 节点为 now
	chain_stack->info.stack_crt_depth++;

	return true;
}

bool chain_stack_get(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom)
{																			// get top 节点数据,并且不出栈
	if (chain_stack->info.stack_crt_depth == 0)								// 空栈异常
	{
		chain_stack->expection.null_stack();

		return false;
	}

	for (size_t i = 0; i < chain_stack->top->data_length; i++)
		atom[i] = chain_stack->top->data[i];

	return true;
}

bool chain_stack_delete(CHAIN_STACK_TYPEDEF_PTR chain_stack)
{																			// delete top 节点，使其出栈
	CHAIN_STACK_NODE_TYPEDEF_PTR
		stack_node_prev = chain_stack->top;									// 记录当前 top 节点

	if (chain_stack->info.stack_crt_depth == 0)								// 空栈异常
	{
		chain_stack->expection.null_stack();

		return false;
	}

	free(chain_stack->top->data);											// 释放 top.data 存储空间

	chain_stack->top->data_length = 0;										// 清理数据
	chain_stack->top->data = NULL;											// 变成空指针

	stack_node_prev = chain_stack->top;										// 记录 top 数据空间

	chain_stack->top = chain_stack->top->next;								// 把当前的 top.next 节点变成 top 节点

	free(stack_node_prev);													// 释放 prev top 存储空间

	chain_stack->info.stack_crt_depth--;									// 减少 chain_stack 当前深度

	if (chain_stack->info.stack_crt_depth == 0)								// 已经空栈
		chain_stack->info.stack_malloc = false;

	stack_node_prev = NULL;

	return true;
}

bool chain_stack_pop(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE atom)
{																			// pop top 节点 : 1. get 节点 top 数据; 2. delete top 节点,使其出栈;
	if (chain_stack_get(chain_stack, atom) == false)						// 读取节点数据
		return false;														// 空栈异常

	return chain_stack_delete(chain_stack);
}

bool chain_stack_multi_pop(CHAIN_STACK_TYPEDEF_PTR chain_stack, CHAIN_STACK_DATA_TYPE* array, size_t depth)
{
	if (array == NULL)
		return false;

	for (size_t i = 0; i < depth; i++)
	{
		chain_stack_pop(chain_stack, array[i]);
	}

	return true;
}

void chain_stack_default_full_stacl_expection(void)
{
	printf("stack_full_expectopn. \r\n");
}

void chain_stack_default_null_stacl_expection(void)
{
	printf("stack_null_expectopn. \r\n");
}

void chain_stack_default_lack_heap_expection(void)
{
	printf("heap_null_expectopn. \r\n");
}
//
//float _data_verify_percent(int* input, int* rule, size_t sizeof_rule)     // 数据正确率
//{
//	float perc = 0;
//	int
//		correct_num = 0,
//		order_correct_num = 0;
//
//	for (size_t cnt = 0; cnt < sizeof_rule; cnt++)
//	{
//		if (input[cnt] == rule[cnt])
//		{
//			correct_num++;
//		}
//	}
//
//	perc = correct_num / (float)sizeof_rule;
//
//	return perc;
//}
//
//float data_verify_percent(int* input, int* rule, size_t sizeof_rule)     // 数据正确率
//{
//	float perc = 0;
//
//	int record_num[11] = { 0 };
//	size_t
//		record_part_num = 0;
//	int
//		record_part[10] = { 0 },
//		record_part_param[10][10] = { 0 };
//
//	int correct_num = 0;
//
//	for (size_t cnt = 0; cnt < sizeof_rule; cnt++)
//	{
//		for (size_t i = record_num[cnt]; i < sizeof_rule; i++)
//		{
//			if (input[cnt] == rule[i])
//			{
//				record_num[cnt + 1] = i + 1;
//
//				record_part_param[record_part_num][record_part[record_part_num]] = rule[i];
//				record_part[record_part_num]++;
//
//				break;
//			}
//			else if (record_num[cnt] != 0 && cnt != 0)
//			{
//				record_num[cnt + 1] = cnt + 1;
//
//				record_part_num++;
//
//				break;
//			}
//		}
//	}
//
//	for (size_t cnt = 0; cnt <= record_part_num; cnt++)
//	{
//		correct_num += record_part[cnt];
//	}
//
//	perc = correct_num / (float)sizeof_rule;
//
//	return perc;
//}
//
//void main()
//{
//#define CHAIN_STACK_STRING   1
//
//#if defined( STACK_TEST_CHAR)
//	//  char atom = 0;
//	//  char array[100] = { 0 };
//	//  SEQUENCE_STACK_TYPEDEF stack;
//
//	//  stack_ctrl.init(&stack,100);
//
//	//  for (size_t i = 0; i < 10; i++)
//	//  {
//	//      stack.push(&stack, i + '0');
//	//  }
//	//  stack.multi_pop(&stack, array,10);
//
//	//stack_pop(&stack, &atom);
//
//	//printf("pop: %d ", atom);
//
//	//  for (size_t i = 0; i < 10; i++)
//	//  {
//	//      printf("pop: %c ", array[i]);
//	//  }
//
//	//  stack_ctrl.free(&stack);
//
//	//  printf("\r\n");
//#elif defined(CHAIN_STACK_CHAR)
//	//char atom = 0;
//	//char array[100] = { 0 };
//	//CHAIN_SEQUENCE_STACK_TYPEDEF chain_stack;
//
//	//stack_ctrl.chain_stack.init(&chain_stack, 10);
//
//	//for (size_t i = 0; i < 10; i++)
//	//{
//	//    chain_stack.push(&chain_stack, i + '0');
//	//}
//
//	//for (size_t i = 0; i < 10; i++)
//	//{
//	//    chain_stack.pop(&chain_stack, &array[i]);
//
//	//    printf("pop: %c ", array[i]);
//	//}
//
//	//chain_stack.pop(&chain_stack, &array[11]);
//
//	//stack_ctrl.free(&chain_stack);
//
//	//printf("\r\n");
//#elif defined(CHAIN_STACK_STRING)
//
//	char atom = 0;
//	char array[10][100] = { 0 };
//	CHAIN_STACK_TYPEDEF chain_stack;
//
//	CHAIN_STACK_DATA_TYPE* array_ptr = NULL;
//	CHAIN_STACK_DATA_TYPE array_p[10] = { NULL };
//
//	for (size_t i = 0; i < 10; i++)
//	{
//		array_p[i] = (CHAIN_STACK_DATA_TYPE)calloc(10, sizeof(char));
//	}
//
//	stack_ctrl.chain_stack.init(&chain_stack, 10);
//
//	stack_ctrl.chain_stack.config_expection(&chain_stack, true, true, true,
//		chain_stack.expection.full_stack, chain_stack.expection.null_stack, chain_stack.expection.lack_heap);
//
//	for (char i = 0; i < 11; i++)
//	{
//		char temp[20] = { 0 };
//
//		temp[0] = i + '0';
//
//		chain_stack_ctrl.push(&chain_stack, temp, strlen(temp));
//	}
//
//	chain_stack_ctrl.get(&chain_stack, array[0]);
//
//	printf("get: %s \r\n", array[0]);
//
//	//	chain_stack_ctrl.multi_pop(&chain_stack, array_p, 10);
//
//		//for (size_t i = 0; i < 10; i++)
//		//{
//		//	printf("pop: %s ", array_p[i]);
//		//}
//
//	stack_ctrl.chain_stack.free(&chain_stack);
//
//	chain_stack_ctrl.delete(&chain_stack);
//
//	printf(" \r\n end\r\n");
//
//#elif  defined(DATA_VERIFY)
//	//int
//	//    array[10] = { 0,1,3,0,5,6,7,0,9,1 },
//	//    rule[10] = { 1,2,3,4,5,6,7,8,9,1 };
//
//	//int size = 10;
//
//	//data_verify_percent(array,rule,size);
//
//	//printf("*:%f \r\n", data_verify_percent(array, rule, size));
//	//printf("_:%f \r\n", _data_verify_percent(array, rule, size));
//#endif
//
//	return;
//}