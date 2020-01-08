#include "queue.h"
/*

bool queue_control_sequence_queue_init(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, size_t depth);
bool queue_control_sequence_queue_exception_config(SEQUENCE_QUEUE_TYPEDEF_PTR chain_queue,
	bool is_full_queue_cfg, bool is_null_queue_cfg, bool is_lack_heap_cfg, ...);
bool queue_control_sequence_queue_free(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue);

bool sequence_queue_enqueue(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE atom);
bool sequence_queue_dequeue(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE* atom);
bool sequence_queue_get(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE* atom);
bool sequence_queue_delete(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue);
bool sequence_queue_multi_dequeue(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE* array, size_t size);

void sequence_queue_default_full_stacl_expection(void);
void sequence_queue_default_null_stacl_expection(void);
void sequence_queue_default_lack_heap_expection(void);

bool queue_control_chain_queue_init(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, size_t depth);
bool queue_control_chain_queue_exception_config(CHAIN_QUEUE_TYPEDEF_PTR chain_queue,
	bool is_full_queue_cfg, bool is_null_queue_cfg, bool is_lack_heap_cfg, ...);
bool queue_control_chain_queue_free(CHAIN_QUEUE_TYPEDEF_PTR queue);

bool chain_queue_enqueue(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE atom, size_t sizeof_atom);
bool chain_queue_dequeue(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE atom);
bool chain_queue_get(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE atom);
bool chain_queue_delete(CHAIN_QUEUE_TYPEDEF_PTR chain_queue);
bool chain_queue_multi_dequeue(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE* array, size_t depth);

void chain_queue_default_full_stacl_expection(void);
void chain_queue_default_null_stacl_expection(void);
void chain_queue_default_lack_heap_expection(void);

SEQUENCE_QUEUE_CONTROL_TYPEDEF sequence_queue_ctrl =
{
	queue_control_sequence_queue_init,
	queue_control_sequence_queue_exception_config,
	queue_control_sequence_queue_free,

	sequence_queue_enqueue,
	sequence_queue_dequeue,
	sequence_queue_get,
	sequence_queue_delete,
	sequence_queue_multi_dequeue
};
CHAIN_QUEUE_CONTROL_TYPEDEF chain_queue_ctrl =
{
	queue_control_chain_queue_init,
	queue_control_chain_queue_exception_config,
	queue_control_chain_queue_free,

	chain_queue_enqueue,
	chain_queue_dequeue,
	chain_queue_get,
	chain_queue_delete,
	chain_queue_multi_dequeue
};

QUEUE_CONTROL_TYPEDEF queue_ctrl =
{
	&sequence_queue_ctrl,
	&chain_queue_ctrl
};

bool queue_control_sequence_queue_init(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, size_t max_depth)
{
	if ((sequence_queue->data = (SEQUENCE_QUEUE_DATA_TYPE*)malloc(sizeof(SEQUENCE_QUEUE_DATA_TYPE) * max_depth)) == NULL)
		return false;

	sequence_queue->info.queue_malloc = true;

	sequence_queue->info.queue_max_depth = max_depth;
	sequence_queue->info.queue_top = 0;
	sequence_queue->info.queue_rear = 0;

	sequence_queue->expection.full_queue = sequence_queue_default_full_stacl_expection;
	sequence_queue->expection.null_queue = sequence_queue_default_null_stacl_expection;
	sequence_queue->expection.lack_heap = sequence_queue_default_lack_heap_expection;

	return true;
}

bool queue_control_sequence_queue_exception_config(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue,
	bool is_full_queue_cfg, bool is_null_queue_cfg, bool is_lack_heap_cfg, ...)
{
	return true;
}

bool queue_control_sequence_queue_free(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue)
{
	if (sequence_queue->info.queue_malloc == true)
	{
		free(sequence_queue->data);

		sequence_queue->info.queue_malloc = false;
		sequence_queue->data = NULL;
	}

	return true;
}

bool sequence_queue_enqueue(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE atom)
{
	if (sequence_queue->info.queue_rear < sequence_queue->info.queue_max_depth)    // 如果没有满栈
	{
		sequence_queue->data[sequence_queue->info.queue_rear++] = atom;

		return true;
	}
	else
	{
		sequence_queue->expection.full_queue();                           // queue_exception

		return false;
	}
}

bool sequence_queue_get(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE* atom)
{
	if (sequence_queue->info.queue_top >= sequence_queue->info.queue_rear)			// 空栈
	{
		sequence_queue->expection.null_queue();

		return false;
	}

	*atom = sequence_queue->data[sequence_queue->info.queue_top];

	return true;
}

bool sequence_queue_delete(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue)
{
	if (sequence_queue->info.queue_top >= sequence_queue->info.queue_rear)			// 空栈
	{
		sequence_queue->expection.null_queue();

		return false;
	}

	sequence_queue->info.queue_top++;

	return true;
}

bool sequence_queue_dequeue(SEQUENCE_QUEUE_TYPEDEF_PTR sequence_queue, SEQUENCE_QUEUE_DATA_TYPE* atom)
{
	if (sequence_queue_get(sequence_queue, atom) == false)
	{
		return false;
	}

	sequence_queue_delete(sequence_queue);

	return true;
}

void sequence_queue_default_full_stacl_expection(void)
{
	printf("queue_full_expectopn. \r\n");
}

void sequence_queue_default_null_stacl_expection(void)
{
	printf("queue_null_expectopn. \r\n");
}

void sequence_queue_default_lack_heap_expection(void)
{
	printf("heap_null_expectopn. \r\n");
}

bool sequence_queue_multi_dequeue(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE* array, size_t size)
{
	if (queue->info.queue_top >= size)                            // 如果没有空栈
	{
		for (size_t cnt = size; cnt > 0; cnt--)
		{
			*(array + cnt - 1) = queue->data[queue->info.queue_top--];
		}

		return true;
	}
	else
	{
		queue->expection.null_queue();                           // queue_exception

		return false;
	}
}

bool queue_control_chain_queue_init(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, size_t max_depth)
{																			// 初始化一个链队
	CHAIN_QUEUE_NODE_TYPEDEF_PTR
		queue_node = (CHAIN_QUEUE_NODE_TYPEDEF_PTR)calloc(1, sizeof(CHAIN_QUEUE_NODE_TYPEDEF));

	if (queue_node == NULL)
	{
		chain_queue->expection.lack_heap();

		return false;
	}

	if (max_depth <= 0)
	{
		return false;
	}

	chain_queue->top = queue_node;
	chain_queue->rear = queue_node;

	chain_queue->info.queue_crt_depth = 0;									// 填充最大深度和清零当前深度
	chain_queue->info.queue_max_depth = max_depth;

	chain_queue->expection.full_queue = chain_queue_default_full_stacl_expection;	// 赋值异常函数
	chain_queue->expection.null_queue = chain_queue_default_null_stacl_expection;
	chain_queue->expection.lack_heap = chain_queue_default_lack_heap_expection;

	return true;
}

bool queue_control_chain_queue_exception_config(CHAIN_QUEUE_TYPEDEF_PTR chain_queue,
	bool is_full_queue_cfg, bool is_null_queue_cfg, bool is_lack_heap_cfg, ...)
{
	va_list va_ptr;

	short
		cfg_queue[CHAIN_QUEUE_EXCEPTION_TYPE_AMOUNT] =
	{ is_full_queue_cfg + 10 ,is_null_queue_cfg + 20 ,is_lack_heap_cfg + 30 };

	va_start(va_ptr, is_lack_heap_cfg);

	for (size_t cnt = 0; cnt < CHAIN_QUEUE_EXCEPTION_TYPE_AMOUNT; cnt++)
	{
		switch (cfg_queue[cnt])
		{
			case 11:
				chain_queue->expection.full_queue = (void*)va_arg(va_ptr, void *);
				break;
			case 21:
				chain_queue->expection.null_queue = (void*)va_arg(va_ptr, void *);
				break;
			case 31:
				chain_queue->expection.lack_heap = (void*)va_arg(va_ptr, void *);
				break;
			default:
				break;
		}
	}

	va_end(va_ptr);

	return true;
}

bool queue_control_chain_queue_free(CHAIN_QUEUE_TYPEDEF_PTR chain_queue)
{
	if (chain_queue->info.queue_malloc == true ||
		chain_queue->info.queue_crt_depth >= 0)								// 如果被 malloc 过,或者没空栈
	{
		CHAIN_QUEUE_NODE_TYPEDEF* queue_node_prev = NULL;

		char atom[10] = { 0 };

		for (size_t cnt = chain_queue->info.queue_crt_depth; cnt > 0; cnt--)
			chain_queue_delete(chain_queue);

		free(chain_queue->top);

		chain_queue->info.queue_malloc = false;
		chain_queue->top = NULL;											// 变成空指针
		chain_queue->rear = NULL;											// 变成空指针
	}

	return true;
}

bool chain_queue_enqueue(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE atom, size_t sizeof_atom)
{																			// push top 节点，入栈一个数据，并创建一个节点用于存储
	CHAIN_QUEUE_NODE_TYPEDEF_PTR
		queue_node_now = (CHAIN_QUEUE_NODE_TYPEDEF_PTR)calloc(1, sizeof(CHAIN_QUEUE_NODE_TYPEDEF));

	CHAIN_QUEUE_DATA_TYPE queue_node_data_ptr = (CHAIN_QUEUE_DATA_TYPE)calloc(sizeof_atom + 1, sizeof(char));

	if (queue_node_now == NULL || queue_node_data_ptr == NULL)				// 堆空间不足异常
	{
		chain_queue->expection.lack_heap();

		return false;
	}
	if (chain_queue->info.queue_max_depth <=
		chain_queue->info.queue_crt_depth)									// 满栈异常
	{
		chain_queue->expection.full_queue();

		return false;
	}

	queue_node_now->data = queue_node_data_ptr;								// 分配数据空间
	queue_node_now->data_length = sizeof_atom;								// 记录数据长度

	for (size_t i = 0; i < sizeof_atom; i++)
		queue_node_now->data[i] = atom[i];									// 填充数据空间

	// rear	进队		最新的 now
	// top 出队		最老的

	queue_node_now->next = NULL;

	chain_queue->rear->next = queue_node_now;

	chain_queue->rear = queue_node_now;

	chain_queue->info.queue_crt_depth++;

	return true;
}

bool chain_queue_get(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE atom)
{																			// get rear 节点数据,并且不出队
	if (chain_queue->info.queue_crt_depth == 0)								// 空栈异常
	{
		chain_queue->expection.null_queue();

		return false;
	}

	for (size_t i = 0; i < chain_queue->top->next->data_length; i++)
		atom[i] = chain_queue->top->next->data[i];

	return true;
}

bool chain_queue_delete(CHAIN_QUEUE_TYPEDEF_PTR chain_queue)
{																			// delete rear 节点，使其出队
	CHAIN_QUEUE_NODE_TYPEDEF_PTR
		queue_node_prev = chain_queue->rear;									// 记录当前 rear 节点

	if (chain_queue->info.queue_crt_depth == 0)								// 空队异常
	{
		chain_queue->expection.null_queue();

		return false;
	}

	//free(chain_queue->top->data);											// 释放 rear.data 存储空间
	//chain_queue->top->data_length = 0;										// 清理数据
	//chain_queue->top->data = NULL;											// 变成空指针

	free(chain_queue->top->next->data);											// 释放 rear.data 存储空间
	chain_queue->top->next->data_length = 0;										// 清理数据
	chain_queue->top->next->data = NULL;											// 变成空指针

	queue_node_prev = chain_queue->top;										// 记录 rear 数据空间

	chain_queue->top = chain_queue->top->next;								// 把当前的 rear.next 节点变成 rear 节点

	free(queue_node_prev);													// 释放 prev rear 存储空间

	chain_queue->info.queue_crt_depth--;									// 减少 chain_queue 当前深度

	if (chain_queue->info.queue_crt_depth == 0)								// 已经空栈
		chain_queue->info.queue_malloc = false;

	queue_node_prev = NULL;

	return true;
}

bool chain_queue_dequeue(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE atom)
{																			// pop top 节点 : 1. get 节点 top 数据; 2. delete top 节点,使其出栈;
	if (chain_queue_get(chain_queue, atom) == false)						// 读取节点数据
		return false;														// 空栈异常

	return chain_queue_delete(chain_queue);
}

bool chain_queue_multi_dequeue(CHAIN_QUEUE_TYPEDEF_PTR chain_queue, CHAIN_QUEUE_DATA_TYPE* array, size_t depth)
{
	if (array == NULL)
		return false;

	for (size_t i = 0; i < depth; i++)
		chain_queue_dequeue(chain_queue, array[i]);

	return true;
}

void chain_queue_default_full_stacl_expection(void)
{
	printf("queue_full_expectopn. \r\n");
}

void chain_queue_default_null_stacl_expection(void)
{
	printf("queue_null_expectopn. \r\n");
}

void chain_queue_default_lack_heap_expection(void)
{
	printf("heap_null_expectopn. \r\n");
}
//
//void main()
//{
//
//#define CHAIN_QUEUE_STRING   1
//
//#if defined( SEQUEENCE_QUEUE_TEST_CHAR)
//
//	SEQUENCE_QUEUE_DATA_TYPE atom = 0;
//	SEQUENCE_QUEUE_DATA_TYPE array[100] = { 0 };
//	SEQUENCE_QUEUE_TYPEDEF queue;
//
//	queue_ctrl.seqence_queue.init(&queue,10);
//
//	for (size_t i = 0; i < 11; i++)
//	{
//		sequence_queue_ctrl.enqueue(&queue, i);
//	}
//
//	//	  sequence_queue_ctrl.multi_dequeue(&queue, array,10);
//
//	for (size_t i = 0; i < 11; i++)
//	{
//		sequence_queue_ctrl.dequeue(&queue, array);
//		printf("pop: %d ", array[0]);
//	}
//
//	queue_ctrl.seqence_queue.free(&queue);
//
//	printf("\r\n");
//
//#elif defined(CHAIN_QUEUE_CHAR)
//
//	//char atom = 0;
//	//char array[100] = { 0 };
//	//CHAIN_SEQUENCE_QUEUE_TYPEDEF chain_queue;
//
//	//queue_ctrl.chain_queue.init(&chain_queue, 10);
//
//	//for (size_t i = 0; i < 10; i++)
//	//{
//	//    chain_queue.push(&chain_queue, i + '0');
//	//}
//
//	//for (size_t i = 0; i < 10; i++)
//	//{
//	//    chain_queue.pop(&chain_queue, &array[i]);
//
//	//    printf("pop: %c ", array[i]);
//	//}
//
//	//chain_queue.pop(&chain_queue, &array[11]);
//
//	//queue_ctrl.free(&chain_queue);
//
//	//printf("\r\n");
//
//#elif defined(CHAIN_QUEUE_STRING)
//
//	char atom = 0;
//	char array[10][100] = { 0 };
//	CHAIN_QUEUE_TYPEDEF chain_queue;
//
//	CHAIN_QUEUE_DATA_TYPE* array_ptr = NULL;
//	CHAIN_QUEUE_DATA_TYPE array_p[10] = { NULL };
//
//	for (size_t i = 0; i < 10; i++)
//	{
//		array_p[i] = (CHAIN_QUEUE_DATA_TYPE)calloc(10, sizeof(char));
//	}
//
//	chain_queue_ctrl.init(&chain_queue, 10);
//
//	chain_queue_ctrl.config_expection(&chain_queue, true, true, true,
//		chain_queue.expection.full_queue, chain_queue.expection.null_queue, chain_queue.expection.lack_heap);
//
//	for (char i = 0; i < 10; i++)
//	{
//		char temp[20] = { 0 };
//
//		temp[0] = i + '0';
//
//		chain_queue_ctrl.enqueue(&chain_queue, temp, strlen(temp));
//	}
//
//	chain_queue_ctrl.get(&chain_queue, array[0]);
//
//	printf("get: %s \r\n", array[0]);
//
//	chain_queue_ctrl.multi_dequeue(&chain_queue, array_p, 10);
//
//	for (size_t i = 0; i < 10; i++)
//	{
//		printf("pop: %s ", array_p[i]);
//	}
//
//	chain_queue_ctrl.free(&chain_queue);
//
//	chain_queue_ctrl.delete(&chain_queue);
//
//#endif
//
//	printf(" \r\n Test End\r\n");
//
//	return;
//}
*/