#ifndef __STACK_H
#define __STACK_H

#include "stdio.h"
#include "stdbool.h"
#include "malloc.h"
#include "string.h"
#include "stdarg.h"

#define SEQUENCE_STACK_DATA_TYPE			char
#define CHAIN_STACK_DATA_TYPE				char*

#define CHAIN_STACK_EXCEPTION_TYPE_AMOUNT	3

typedef struct Sequence_Stack_Info
{
	size_t stack_top;
	size_t stack_depth;
	bool stack_malloc;
}SEQUENCE_STACK_INFO_TYPEDEF;

typedef struct Sequence_Stack_Expection
{
	void (*full_stack)(void);
	void (*null_stack)(void);
	void (*lack_heap)(void);
}SEQUENCE_STACK_EXPECTION_TYPEDEF;

typedef struct Sequence_Stack
{
	SEQUENCE_STACK_INFO_TYPEDEF info;
	SEQUENCE_STACK_DATA_TYPE* data;

	//bool (*push)(struct Stack* stack, char atom);
	//bool (*pop)(struct Stack* stack, char* atom);
	//bool (*multi_pop)(struct Stack* stack, char* array, size_t depth);

	SEQUENCE_STACK_EXPECTION_TYPEDEF expection;
}SEQUENCE_STACK_TYPEDEF, * SEQUENCE_STACK_TYPEDEF_PTR;

typedef struct Chain_Stack_Info
{
	size_t stack_crt_depth;
	size_t stack_max_depth;
	bool stack_malloc;
}CHAIN_STACK_INFO_TYPEDEF;

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
	CHAIN_STACK_INFO_TYPEDEF info;
	CHAIN_STACK_NODE_TYPEDEF_PTR top;                           

	//bool (*push)(struct Chain_Stack* stack, CHAIN_SEQUENCE_STACK_DATA_TYPE atom, size_t sizeof_atom);
	//bool (*pop)(struct Chain_Stack* stack, CHAIN_SEQUENCE_STACK_DATA_TYPE atom);
	//bool (*multi_pop)(struct Chain_Stack* stack, CHAIN_SEQUENCE_STACK_DATA_TYPE* array, size_t depth);

	CHAIN_STACK_EXPECTION_TYPEDEF expection;
}CHAIN_STACK_TYPEDEF, * CHAIN_STACK_TYPEDEF_PTR;

typedef struct Sequence_Stack_Control
{
	bool (*push)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE atom);
	bool (*pop)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom);
	bool (*multi_pop)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* array, size_t depth);
}SEQUENCE_STACK_CONTROL_TYPEDEF, * SEQUENCE_STACK_CONTROL_TYPEDEF_PTR;

typedef struct Chain_Stack_Control
{
	bool (*push)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom, size_t sizeof_atom);
	bool (*pop)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
	bool (*get)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
	bool (*delete)(CHAIN_STACK_TYPEDEF_PTR stack);
	bool (*multi_pop)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE* array, size_t depth);
}CHAIN_STACK_CONTROL_TYPEDEF, * CHAIN_STACK_CONTROL_TYPEDEF_PTR;

typedef struct Stack_Control
{
	struct
	{
		bool (*init)(SEQUENCE_STACK_TYPEDEF_PTR stack, size_t depth);
		bool (*free)(SEQUENCE_STACK_TYPEDEF_PTR stack);

		bool (*push)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE atom);
		bool (*pop)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom);
		bool (*multi_pop)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* array, size_t depth);
	}sequence_stack;

	struct
	{
		bool (*init)(CHAIN_STACK_TYPEDEF_PTR stack, size_t depth);
		bool (*config_expection)(CHAIN_STACK_TYPEDEF_PTR chain_stack,
			bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...);
		bool (*free)(CHAIN_STACK_TYPEDEF_PTR stack);

		bool (*push)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom, size_t sizeof_atom);
		bool (*pop)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
		bool (*get)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
		bool (*delete)(CHAIN_STACK_TYPEDEF_PTR stack);
		bool (*multi_pop)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE* array, size_t depth);
	}chain_stack;
}STACK_CONTROL_TYPEDEF;

extern SEQUENCE_STACK_CONTROL_TYPEDEF sequence_stack_ctrl;
extern CHAIN_STACK_CONTROL_TYPEDEF chain_stack_ctrl;

extern STACK_CONTROL_TYPEDEF stack_ctrl;

#endif // __STACK_H