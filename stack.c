/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


#include "stack.h"

#include "mem_test.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define SEQUENCE_STACK_EXCEPTION_TYPE_AMOUNT	4
#define CHAIN_STACK_EXCEPTION_TYPE_AMOUNT		4


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


typedef struct Stack_Info
{
	size_t stack_crt_depth;
	size_t stack_max_depth;
	bool stack_malloc;
}STACK_INFO_TYPEDEF;

typedef struct Sequence_Stack_Expection
{
	void (*full_stack)(void);
	void (*null_stack)(void);
	void (*lack_heap)(void);
}SEQUENCE_STACK_EXPECTION_TYPEDEF;

typedef struct Sequence_Stack
{
	STACK_INFO_TYPEDEF info;
	SEQUENCE_STACK_DATA_TYPE* data;

	SEQUENCE_STACK_EXPECTION_TYPEDEF expection;
}SEQUENCE_STACK_TYPEDEF;

typedef struct Chain_Stack_Node
{
	struct Chain_Stack_Node* next;
	CHAIN_STACK_DATA_TYPE data;
	size_t data_length;
}CHAIN_STACK_NODE_TYPEDEF, * CHAIN_STACK_NODE_TYPEDEF_PTR;

typedef struct Chain_Stack_Expection
{
	void (*full_stack)(void);
	void (*null_stack)(void);
	void (*lack_heap)(void);
}CHAIN_STACK_EXPECTION_TYPEDEF;

typedef struct Chain_Stack
{
	STACK_INFO_TYPEDEF info;
	CHAIN_STACK_NODE_TYPEDEF_PTR top;

	CHAIN_STACK_EXPECTION_TYPEDEF expection;
}CHAIN_STACK_TYPEDEF;

struct Chain_Generic_Stack_Info
{
	size_t stack_crt_depth;
	size_t stack_max_depth;
	size_t stack_data_type_size;
	bool stack_malloc;
};

typedef struct Chain_Generic_Stack_Data_Handle
{
	void (*stack_data_copy)(void* buffer, const void* data);
	void (*stack_data_free)(void* buffer);
}CHAIN_GENERIC_STACK_DATA_HANDLE_TYPEDEF;

typedef struct Chain_Generic_Stack_Node
{
	void* data;
	size_t data_length;
	struct Chain_Generic_Stack_Node* next;
}CHAIN_GENERIC_STACK_NODE_TYPEDEF, * CHAIN_GENERIC_STACK_NODE_TYPEDEF_PTR;

typedef struct Chain_Generic_Stack
{
	CHAIN_GENERIC_STACK_INFO_TYPEDEF info;
	CHAIN_GENERIC_STACK_DATA_HANDLE_TYPEDEF data_handle;

	CHAIN_GENERIC_STACK_NODE_TYPEDEF_PTR top;

	CHAIN_STACK_EXPECTION_TYPEDEF expection;
}CHAIN_GENERIC_STACK_TYPEDEF;


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

SEQUENCE_STACK_CONTROL_TYPEDEF sequence_stack_ctrl =
{
	stack_control_sequence_stack_init,
	stack_control_sequence_stack_exception_config,
	stack_control_sequence_stack_free,

	sequence_stack_push,
	sequence_stack_pop,
	sequence_stack_get,
	sequence_stack_delete,
	sequence_stack_multi_pop
};
CHAIN_STACK_CONTROL_TYPEDEF chain_stack_ctrl =
{
	stack_control_chain_stack_init,
	stack_control_chain_stack_exception_config,
	stack_control_chain_stack_free,

	chain_stack_push,
	chain_stack_pop,
	chain_stack_get,
	chain_stack_delete,
	chain_stack_multi_pop,

	{
		stack_control_chain_stack_get_info_get_current_depth,
		stack_control_chain_stack_get_info_get_max_depth,
		stack_control_chain_stack_get_info_get_stack_top_data_length,

		stack_control_chain_stack_get_info_get_is_empty,
		stack_control_chain_stack_get_info_get_is_full
	}
};

CHAIN_GENERIC_STACK_CONTROL_TYPEDEF chain_generic_stack_ctrl =
{
	stack_control_chain_generic_stack_init,
	stack_control_chain_generic_stack_exception_config,
	stack_control_chain_generic_stack_free,

	chain_generic_stack_push,
	chain_generic_stack_pop,
	chain_generic_stack_get,
	chain_generic_stack_delete,
	chain_generic_stack_multi_pop,

	{
		stack_control_chain_generic_stack_get_info_get_current_depth,
		stack_control_chain_generic_stack_get_info_get_max_depth,
		stack_control_chain_generic_stack_get_info_get_stack_data_type_size,
		stack_control_chain_generic_stack_get_info_get_stack_top_data_length,

		stack_control_chain_generic_stack_get_info_get_is_empty,
		stack_control_chain_generic_stack_get_info_get_is_full
	}
};


STACK_CONTROL_TYPEDEF stack_ctrl =
{
	&sequence_stack_ctrl,
	&chain_stack_ctrl,
	&chain_generic_stack_ctrl
};


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void stack_init_error_expection(void);

void stack_default_full_stack_expection(void);
void stack_default_null_stack_expection(void);
void stack_default_lack_heap_expection(void);


/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

bool stack_control_sequence_stack_init(SEQUENCE_STACK_TYPEDEF_PTR* stack, size_t max_depth)
{
	if (NULL == stack ||
		0 >= max_depth)
	{
		stack_init_error_expection();

		return false;
	}

	SEQUENCE_STACK_TYPEDEF_PTR
		stack_new = (SEQUENCE_STACK_TYPEDEF_PTR)mem_calloc(1, sizeof(SEQUENCE_STACK_TYPEDEF));

	if (NULL == stack_new ||
		NULL == (stack_new->data = (char*)malloc(sizeof(char) * max_depth)))
	{
		stack_default_lack_heap_expection();

		return false;
	}

	stack_new->info.stack_malloc = true;
	stack_new->info.stack_max_depth = max_depth;
	stack_new->info.stack_crt_depth = 0;

	//stack->push = stack_push;
	//stack->pop = stack_pop;
	//stack->multi_pop = stack_multi_pop;

	stack_new->expection.full_stack = stack_default_full_stack_expection;
	stack_new->expection.null_stack = stack_default_null_stack_expection;
	stack_new->expection.lack_heap = stack_default_lack_heap_expection;

	*stack = stack_new;

	return true;
}

bool stack_control_sequence_stack_exception_config(SEQUENCE_STACK_TYPEDEF_PTR stack,
	bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...)
{
	va_list va_ptr;

	short
		cfg_queue[SEQUENCE_STACK_EXCEPTION_TYPE_AMOUNT] =
	{ is_full_stack_cfg + 10 ,is_null_stack_cfg + 20 ,is_lack_heap_cfg + 30 };

	va_start(va_ptr, is_lack_heap_cfg);

	for (size_t cnt = 0; cnt < CHAIN_STACK_EXCEPTION_TYPE_AMOUNT; cnt++)
	{
		switch (cfg_queue[cnt])
		{
			case 11:
				stack->expection.full_stack = (void(*)(void))va_arg(va_ptr, int);
				break;
			case 21:
				stack->expection.null_stack = (void(*)(void))va_arg(va_ptr, int);
				break;
			case 31:
				stack->expection.lack_heap = (void(*)(void))va_arg(va_ptr, int);
				break;
			default:
				break;
		}
	}

	va_end(va_ptr);

	return true;
}

bool stack_control_sequence_stack_free(SEQUENCE_STACK_TYPEDEF_PPTR stack)
{
	if ((*stack)->info.stack_malloc == true)
	{
		mem_free((*stack)->data);

		(*stack)->info.stack_malloc = false;
		(*stack)->data = NULL;
	}

	mem_free(*stack);

	*stack = NULL;														// 变成空指针

	return true;
}

bool sequence_stack_push(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE atom)
{
	if (stack->info.stack_crt_depth >= stack->info.stack_max_depth)
	{
		stack->expection.full_stack();                           // stack_exception

		return false;
	}

	stack->data[++stack->info.stack_crt_depth] = atom;

	return true;
}

bool sequence_stack_get(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom)
{
	if (stack->info.stack_crt_depth <= 0)
	{
		stack->expection.null_stack();

		return false;
	}

	*atom = stack->data[stack->info.stack_crt_depth];

	return true;
}

bool sequence_stack_delete(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth <= 0)
	{
		stack->expection.null_stack();

		return false;
	}

	stack->info.stack_crt_depth--;

	return true;
}

bool sequence_stack_pop(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom)
{
	if (sequence_stack_get(stack, atom) == false)			// 这里不用写异常，因为 sequence_stack_get 会先捕捉到
		return false;

	return sequence_stack_delete(stack);
}

bool sequence_stack_multi_pop(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* array, size_t size)
{
	if (stack->info.stack_crt_depth >= size)                            // 如果没有空栈
	{
		for (size_t cnt = size; cnt > 0; cnt--)
		{
			*(array + cnt - 1) = stack->data[stack->info.stack_crt_depth--];
		}

		return true;
	}
	else
	{
		stack->expection.null_stack();                           // stack_exception

		return false;
	}
}

size_t stack_control_sequence_stack_get_info_get_current_depth(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_crt_depth;
}

size_t stack_control_sequence_stack_get_info_get_max_depth(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_max_depth;
}

bool stack_control_sequence_stack_get_info_get_is_empty(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth <= 0)
		return true;
	else
		return false;
}

bool stack_control_sequence_stack_get_info_get_is_full(SEQUENCE_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth >= stack->info.stack_max_depth)
		return true;
	else
		return false;
}

bool stack_control_chain_stack_init(CHAIN_STACK_TYPEDEF_PPTR stack, size_t max_depth)
{																			// 初始化一个链栈
	if (NULL == stack ||
		0 >= max_depth)
	{
		stack_init_error_expection();

		return false;
	}

	CHAIN_STACK_TYPEDEF_PTR
		stack_new = (CHAIN_STACK_TYPEDEF_PTR)mem_calloc(1, sizeof(CHAIN_STACK_TYPEDEF));

	if (NULL == stack_new)
	{
		stack_default_lack_heap_expection();

		return false;
	}

	stack_new->info.stack_crt_depth = 0;									// 填充最大深度和清零当前深度
	stack_new->info.stack_max_depth = max_depth;

	stack_new->expection.full_stack = stack_default_full_stack_expection;	// 赋值异常函数
	stack_new->expection.null_stack = stack_default_null_stack_expection;
	stack_new->expection.lack_heap = stack_default_null_stack_expection;

	*stack = stack_new;

	return true;
}

bool stack_control_chain_stack_exception_config(CHAIN_STACK_TYPEDEF_PTR stack,
	bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...)
{
	va_list va_ptr;

	short
		cfg_queue[CHAIN_STACK_EXCEPTION_TYPE_AMOUNT] =
	{ is_full_stack_cfg + 10 ,is_null_stack_cfg + 20 ,is_lack_heap_cfg + 30 };

	va_start(va_ptr, is_lack_heap_cfg);

	for (size_t cnt = 0; cnt < CHAIN_STACK_EXCEPTION_TYPE_AMOUNT; cnt++)
	{
		switch (cfg_queue[cnt])
		{
			case 11:
				stack->expection.full_stack = (void(*)(void))va_arg(va_ptr, int);
				break;
			case 21:
				stack->expection.null_stack = (void(*)(void))va_arg(va_ptr, int);
				break;
			case 31:
				stack->expection.lack_heap = (void(*)(void))va_arg(va_ptr, int);
				break;
			default:
				break;
		}
	}

	va_end(va_ptr);

	return true;
}

bool stack_control_chain_stack_free(CHAIN_STACK_TYPEDEF_PPTR stack)
{
	if ((*stack)->info.stack_malloc == true ||
		(*stack)->info.stack_crt_depth > 0)								// 如果被 malloc 过,或者没空栈
	{
		for (size_t cnt = (*stack)->info.stack_crt_depth; cnt > 0; cnt--)
			chain_stack_delete((*stack));

		(*stack)->info.stack_malloc = false;
		(*stack)->top = NULL;											// 变成空指针
	}

	mem_free(*stack);

	*stack = NULL;														// 变成空指针

	return true;
}

bool chain_stack_push(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom, size_t sizeof_atom)
{																			// push top 节点，入栈一个数据，并创建一个节点用于存储
	CHAIN_STACK_NODE_TYPEDEF_PTR
		stack_node_now = (CHAIN_STACK_NODE_TYPEDEF_PTR)mem_calloc(1, sizeof(CHAIN_STACK_NODE_TYPEDEF));

	CHAIN_STACK_DATA_TYPE stack_node_data_ptr = (CHAIN_STACK_DATA_TYPE)mem_calloc(sizeof_atom + 1, sizeof(char));

	if (stack_node_now == NULL || stack_node_data_ptr == NULL)				// 堆空间不足异常
	{
		stack->expection.lack_heap();

		return false;
	}
	if (stack->info.stack_max_depth <=
		stack->info.stack_crt_depth)									// 空栈异常
	{
		stack->expection.full_stack();

		return false;
	}

	stack_node_now->data = stack_node_data_ptr;								// 分配数据空间
	stack_node_now->data_length = sizeof_atom;								// 记录数据长度

	for (size_t i = 0; i < sizeof_atom; i++)
		stack_node_now->data[i] = atom[i];									// 填充数据空间

	stack_node_now->next = stack->top;								// 把 top 节点压入栈底，即赋值给 now.next

	stack->top = stack_node_now;										// 上浮 top 节点为 now
	stack->info.stack_crt_depth++;

	return true;
}

bool chain_stack_get(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom)
{																			// get top 节点数据,并且不出栈
	if (stack->info.stack_crt_depth == 0)								// 空栈异常
	{
		stack->expection.null_stack();

		return false;
	}

	for (size_t i = 0; i < stack->top->data_length; i++)
		atom[i] = stack->top->data[i];

	return true;
}

bool chain_stack_delete(CHAIN_STACK_TYPEDEF_PTR stack)
{																			// delete top 节点，使其出栈
	CHAIN_STACK_NODE_TYPEDEF_PTR
		stack_node_prev = stack->top;									// 记录当前 top 节点

	if (stack->info.stack_crt_depth == 0)								// 空栈异常
	{
		stack->expection.null_stack();

		return false;
	}

	mem_free(stack->top->data);											// 释放 top.data 存储空间

	stack->top->data_length = 0;										// 清理数据
	stack->top->data = NULL;											// 变成空指针

	stack_node_prev = stack->top;										// 记录 top 数据空间

	stack->top = stack->top->next;								// 把当前的 top.next 节点变成 top 节点

	mem_free(stack_node_prev);													// 释放 prev top 存储空间

	stack->info.stack_crt_depth--;									// 减少 chain_stack 当前深度

	if (stack->info.stack_crt_depth == 0)								// 已经空栈
		stack->info.stack_malloc = false;

	stack_node_prev = NULL;

	return true;
}

bool chain_stack_pop(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom)
{																			// pop top 节点 : 1. get 节点 top 数据; 2. delete top 节点,使其出栈;
	if (chain_stack_get(stack, atom) == false)						// 读取节点数据
		return false;														// 空栈异常

	return chain_stack_delete(stack);
}

bool chain_stack_multi_pop(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE* array, size_t depth)
{
	if (NULL == stack ||
		NULL == array ||
		0 >= depth)
		return false;

	for (size_t i = 0; i < depth; i++)
	{
		chain_stack_pop(stack, array[i]);
	}

	return true;
}

size_t stack_control_chain_stack_get_info_get_current_depth(CHAIN_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_crt_depth;
}

size_t stack_control_chain_stack_get_info_get_max_depth(CHAIN_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_max_depth;
}

size_t stack_control_chain_stack_get_info_get_stack_top_data_length(CHAIN_STACK_TYPEDEF_PTR stack)
{
	return stack->top->data_length;
}

bool stack_control_chain_stack_get_info_get_is_empty(CHAIN_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth <= 0)
		return true;
	else
		return false;
}

bool stack_control_chain_stack_get_info_get_is_full(CHAIN_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth >= stack->info.stack_max_depth)
		return true;
	else
		return false;
}

bool stack_control_chain_generic_stack_init(CHAIN_GENERIC_STACK_TYPEDEF_PPTR stack, size_t data_type_size, size_t max_depth,
	void (*stack_data_copy)(void*, const void*), void (*stack_data_free)(void*))
{																			// 初始化一个链栈
	if (NULL == stack ||
		0 >= max_depth)
	{
		stack_init_error_expection();

		return false;
	}

	CHAIN_GENERIC_STACK_TYPEDEF_PTR
		stack_new = (CHAIN_GENERIC_STACK_TYPEDEF_PTR)mem_calloc(1, sizeof(CHAIN_GENERIC_STACK_TYPEDEF));

	if (NULL == stack_new)
	{
		stack_default_lack_heap_expection();

		return false;
	}

	stack_new->info.stack_data_type_size = data_type_size / sizeof(char);		// 确定数据内存空间
	stack_new->info.stack_crt_depth = 0;										// 填充最大深度和清零当前深度
	stack_new->info.stack_max_depth = max_depth;

	stack_new->data_handle.stack_data_copy = stack_data_copy;							// 深复制操作函数
	stack_new->data_handle.stack_data_free = stack_data_free;							// 释放深复制操作函数中复制的指针

	stack_new->top = NULL;														//

	stack_new->expection.full_stack = stack_default_full_stack_expection;	// 赋值异常函数
	stack_new->expection.null_stack = stack_default_null_stack_expection;
	stack_new->expection.lack_heap = stack_default_lack_heap_expection;

	*stack = stack_new;

	return true;
}

bool stack_control_chain_generic_stack_exception_config(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack,
	bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...)
{
	va_list va_ptr;

	short
		cfg_queue[CHAIN_STACK_EXCEPTION_TYPE_AMOUNT] =
	{ is_full_stack_cfg + 10 ,is_null_stack_cfg + 20 ,is_lack_heap_cfg + 30 };

	va_start(va_ptr, is_lack_heap_cfg);

	for (size_t cnt = 0; cnt < CHAIN_STACK_EXCEPTION_TYPE_AMOUNT; cnt++)
	{
		switch (cfg_queue[cnt])
		{
			case 11:
				stack->expection.full_stack = (void(*)(void))va_arg(va_ptr, int);
				break;
			case 21:
				stack->expection.null_stack = (void(*)(void))va_arg(va_ptr, int);
				break;
			case 31:
				stack->expection.lack_heap = (void(*)(void))va_arg(va_ptr, int);
				break;
			default:
				break;
		}
	}

	va_end(va_ptr);

	return true;
}

bool stack_control_chain_generic_stack_free(CHAIN_GENERIC_STACK_TYPEDEF_PPTR stack)
{
	if ((*stack)->info.stack_malloc == true ||
		(*stack)->info.stack_crt_depth > 0)								// 如果被 malloc 过,或者没空栈
	{
		for (size_t cnt = (*stack)->info.stack_crt_depth; cnt > 0; cnt--)
			chain_generic_stack_delete(*stack);

		(*stack)->info.stack_malloc = false;
		(*stack)->top = NULL;											// 变成空指针
	}

	mem_free(*stack);

	*stack = NULL;														// 变成空指针

	return true;
}

bool chain_generic_stack_push(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void* atom, size_t sizeof_string_atom)
{																			// push top 节点，入栈一个数据，并创建一个节点用于存储,sizeof_atom 仅在 string 类型时使用
	CHAIN_GENERIC_STACK_NODE_TYPEDEF_PTR
		stack_node_now = (CHAIN_GENERIC_STACK_NODE_TYPEDEF_PTR)mem_calloc(1, sizeof(CHAIN_GENERIC_STACK_NODE_TYPEDEF));

	size_t
		stack_node_data_size = (sizeof_string_atom != 0) ?
								(stack->info.stack_data_type_size + 1) :
								(stack->info.stack_data_type_size);

	void* 
		stack_node_data_ptr =
		(void*)mem_calloc(stack_node_data_size, sizeof(char));

	if (stack_node_now == NULL || stack_node_data_ptr == NULL)				// 堆空间不足异常
	{
		stack->expection.lack_heap();

		return false;
	}
	if (stack->info.stack_max_depth <=
		stack->info.stack_crt_depth)									// 空栈异常
	{
		stack->expection.full_stack();

		return false;
	}

	stack_node_now->data = stack_node_data_ptr;									// 分配数据空间

	if (sizeof_string_atom != 0)
	{
		stack_node_now->data_length = sizeof_string_atom;						// 记录 string 长度

		*((char*)stack_node_data_ptr + sizeof_string_atom) = '\0';				// 添加尾字符
	}
	else
	{
		stack_node_now->data_length = stack->info.stack_data_type_size;			// 记录非 string 数据长度
	}

	if (stack->data_handle.stack_data_copy != NULL)								// 如果指定了深复制函数
	{	// 深复制(data 涉及指针)
		stack->data_handle.stack_data_copy(stack_node_now->data, atom);
	}
	else
	{	// 浅复制(data 不涉及指针)
		memcpy(stack_node_now->data, atom, stack_node_now->data_length);
	}

	stack_node_now->next = stack->top;									// 把 top 节点压入栈底，即赋值给 now.next

	stack->top = stack_node_now;										// 上浮 top 节点为 now
	stack->info.stack_crt_depth++;

	return true;
}

bool chain_generic_stack_get(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void* atom)
{																			// get top 节点数据,并且不出栈
	if (stack->info.stack_crt_depth == 0)								// 空栈异常
	{
		stack->expection.null_stack();

		return false;
	}

	if (stack->data_handle.stack_data_copy != NULL)								// 如果指定了赋值函数
	{
		stack->data_handle.stack_data_copy(atom, stack->top->data);
	}
	else
	{
		memcpy(atom, stack->top->data, stack->top->data_length/*stack->info.stack_data_type_size*/);
	}

	return true;
}

bool chain_generic_stack_delete(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{																			// delete top 节点，使其出栈
	CHAIN_GENERIC_STACK_NODE_TYPEDEF_PTR
		stack_node_prev = stack->top;									// 记录当前 top 节点

	if (stack->info.stack_crt_depth == 0)								// 空栈异常
	{
		stack->expection.null_stack();

		return false;
	}

	if (stack->data_handle.stack_data_free != NULL)						// 释放 top.data 中深复制时产生的的指针存储空间
		stack->data_handle.stack_data_free(stack->top->data);			
	
	mem_free(stack->top->data);												// 释放 top.data 存储空间

	stack->top->data_length = 0;										// 清理数据
	stack->top->data = NULL;											// 变成空指针

	stack_node_prev = stack->top;										// 记录 top 数据空间

	stack->top = stack->top->next;										// 把当前的 top.next 节点变成 top 节点

	mem_free(stack_node_prev);												// 释放 prev top 存储空间

	stack->info.stack_crt_depth--;										// 减少 stack 当前深度

	if (stack->info.stack_crt_depth == 0)								// 已经空栈
		stack->info.stack_malloc = false;

	stack_node_prev = NULL;

	return true;
}

bool chain_generic_stack_pop(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void* atom)
{																			// pop top 节点 : 1. get 节点 top 数据; 2. delete top 节点,使其出栈;
	if (chain_generic_stack_get(stack, atom) == false)						// 读取节点数据
		return false;														// 空栈异常

	return chain_generic_stack_delete(stack);
}

bool chain_generic_stack_multi_pop(CHAIN_GENERIC_STACK_TYPEDEF_PTR chain_stack, void** array, size_t depth)
{
	if (array == NULL)
		return false;

	for (size_t i = 0; i < depth; i++)
	{
		chain_generic_stack_pop(chain_stack, array[i]);
	}

	return true;
}

size_t stack_control_chain_generic_stack_get_info_get_current_depth(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_crt_depth;
}

size_t stack_control_chain_generic_stack_get_info_get_max_depth(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_max_depth;
}

size_t stack_control_chain_generic_stack_get_info_get_stack_data_type_size(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{
	return stack->info.stack_data_type_size;
}

size_t stack_control_chain_generic_stack_get_info_get_stack_top_data_length(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{
	return stack->top->data_length;
}

bool stack_control_chain_generic_stack_get_info_get_is_empty(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth <= 0)
		return true;
	else
		return false;
}

bool stack_control_chain_generic_stack_get_info_get_is_full(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack)
{
	if (stack->info.stack_crt_depth >= stack->info.stack_max_depth)
		return true;
	else
		return false;
}

void stack_init_error_expection(void)
{
	while (1);
}

void stack_default_full_stack_expection(void)
{
	printf("stack_full_expectopn. \r\n");
}

void stack_default_null_stack_expection(void)
{
	printf("stack_null_expectopn. \r\n");
}

void stack_default_lack_heap_expection(void)
{
	printf("heap_null_expectopn. \r\n");
}