#ifndef __QUEUE_H
#define __QUEUE_H

#include "stdio.h"
#include "stdbool.h"
#include "malloc.h"
#include "string.h"
#include "stdarg.h"

#define SEQUENCE_QUEUE_DATA_TYPE			int
#define CHAIN_QUEUE_DATA_TYPE				char*

#define CHAIN_QUEUE_EXCEPTION_TYPE_AMOUNT	3

typedef struct Sequence_Queue_Info
{
	size_t queue_top;
	size_t queue_rear;
	size_t queue_max_depth;
	bool queue_malloc;
}SEQUENCE_QUEUE_INFO_TYPEDEF;

typedef struct Sequence_Queue_Expection
{
	void (*full_queue)(void);
	void (*null_queue)(void);
	void (*lack_heap)(void);
}SEQUENCE_QUEUE_EXPECTION_TYPEDEF;

typedef struct Sequence_Queue
{
	SEQUENCE_QUEUE_INFO_TYPEDEF info;
	SEQUENCE_QUEUE_DATA_TYPE* data;

	SEQUENCE_QUEUE_EXPECTION_TYPEDEF expection;
}SEQUENCE_QUEUE_TYPEDEF, * SEQUENCE_QUEUE_TYPEDEF_PTR;

typedef struct Chain_Queue_Info
{
	size_t queue_crt_depth;
	size_t queue_max_depth;
	bool queue_malloc;
}CHAIN_QUEUE_INFO_TYPEDEF;

typedef struct Chain_Queue_Node
{
	struct Chain_Queue_Node* next;
	CHAIN_QUEUE_DATA_TYPE data;
	size_t data_length;
}CHAIN_QUEUE_NODE_TYPEDEF, * CHAIN_QUEUE_NODE_TYPEDEF_PTR;

typedef struct Chain_Queue_Expection
{
	void (*full_queue)(void);
	void (*null_queue)(void);
	void (*lack_heap)(void);
}CHAIN_QUEUE_EXPECTION_TYPEDEF;

typedef struct Chain_Queue
{
	CHAIN_QUEUE_INFO_TYPEDEF info;

	CHAIN_QUEUE_NODE_TYPEDEF_PTR top;				// 队列顶
	CHAIN_QUEUE_NODE_TYPEDEF_PTR rear;				// 队列底

	CHAIN_QUEUE_EXPECTION_TYPEDEF expection;
}CHAIN_QUEUE_TYPEDEF, * CHAIN_QUEUE_TYPEDEF_PTR;

typedef struct Sequence_Queue_Control
{
	bool (*enqueue)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE atom);
	bool (*dequeue)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE* atom);
	bool (*get)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE atom);
	bool (*delete)(SEQUENCE_QUEUE_TYPEDEF_PTR queue);
	bool (*multi_dequeue)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE* array, size_t depth);
}SEQUENCE_QUEUE_CONTROL_TYPEDEF, * SEQUENCE_QUEUE_CONTROL_TYPEDEF_PTR;

typedef struct Chain_Queue_Control
{
	bool (*enqueue)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE atom, size_t sizeof_atom);
	bool (*dequeue)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE atom);
	bool (*get)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE atom);
	bool (*delete)(CHAIN_QUEUE_TYPEDEF_PTR queue);
	bool (*multi_dequeue)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE* array, size_t depth);
}CHAIN_QUEUE_CONTROL_TYPEDEF, * CHAIN_QUEUE_CONTROL_TYPEDEF_PTR;

typedef struct Queue_Control
{
	struct
	{
		bool (*init)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, size_t depth);
		bool (*config_expection)(SEQUENCE_QUEUE_TYPEDEF_PTR chain_queue,
			bool is_full_queue_cfg, bool is_null_queue_cfg, bool is_lack_heap_cfg, ...);
		bool (*free)(SEQUENCE_QUEUE_TYPEDEF_PTR queue);

		bool (*enqueue)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE atom);
		bool (*dequeue)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE atom);
		bool (*get)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE* atom);
		bool (*delete)(SEQUENCE_QUEUE_TYPEDEF_PTR queue);
		bool (*multi_dequeue)(SEQUENCE_QUEUE_TYPEDEF_PTR queue, SEQUENCE_QUEUE_DATA_TYPE* array, size_t depth);
	}seqence_queue;
	struct
	{
		bool (*init)(CHAIN_QUEUE_TYPEDEF_PTR queue, size_t depth);
		bool (*config_expection)(CHAIN_QUEUE_TYPEDEF_PTR chain_queue,
			bool is_full_queue_cfg, bool is_null_queue_cfg, bool is_lack_heap_cfg, ...);
		bool (*free)(CHAIN_QUEUE_TYPEDEF_PTR queue);

		bool (*enqueue)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE atom, size_t sizeof_atom);
		bool (*dequeue)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE atom);
		bool (*get)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE atom);
		bool (*delete)(CHAIN_QUEUE_TYPEDEF_PTR queue);
		bool (*multi_dequeue)(CHAIN_QUEUE_TYPEDEF_PTR queue, CHAIN_QUEUE_DATA_TYPE* array, size_t depth);
	}chain_queue;
}QUEUE_CONTROL_TYPEDEF, * QUEUE_CONTROL_TYPEDEF_PTR;

extern CHAIN_QUEUE_CONTROL_TYPEDEF chain_queue_ctrl;
extern SEQUENCE_QUEUE_CONTROL_TYPEDEF sequence_queue_ctrl;

extern QUEUE_CONTROL_TYPEDEF queue_ctrl;

#endif // __QUEUE_H