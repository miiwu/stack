#ifndef __STACK_H
#define __STACK_H

#include "stdio.h"
#include "stdbool.h"
#include "malloc.h"
#include "string.h"
#include "stdarg.h"

#define SEQUENCE_STACK_DATA_TYPE			char
#define CHAIN_STACK_DATA_TYPE				char*

typedef struct Sequence_Stack_Info			SEQUENCE_STACK_INFO_TYPEDEF;
typedef struct Sequence_Stack*				SEQUENCE_STACK_TYPEDEF_PTR;
typedef struct Sequence_Stack**				SEQUENCE_STACK_TYPEDEF_PPTR;

typedef struct Chain_Stack_Info				CHAIN_STACK_INFO_TYPEDEF;
typedef struct Chain_Stack*					CHAIN_STACK_TYPEDEF_PTR;
typedef struct Chain_Stack**				CHAIN_STACK_TYPEDEF_PPTR;

typedef struct Chain_Generic_Stack_Info		CHAIN_GENERIC_STACK_INFO_TYPEDEF;
typedef struct Chain_Generic_Stack*			CHAIN_GENERIC_STACK_TYPEDEF_PTR;
typedef struct Chain_Generic_Stack**		CHAIN_GENERIC_STACK_TYPEDEF_PPTR;

typedef struct Sequence_Stack_Control
{
	bool (*init)(SEQUENCE_STACK_TYPEDEF_PPTR stack, size_t depth);
	bool (*config_expection)(SEQUENCE_STACK_TYPEDEF_PTR stack,
		bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...);
	bool (*free)(SEQUENCE_STACK_TYPEDEF_PPTR stack);

	bool (*push)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE atom);
	bool (*pop)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom);
	bool (*get)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* atom);
	bool (*delete)(SEQUENCE_STACK_TYPEDEF_PTR stack);
	bool (*multi_pop)(SEQUENCE_STACK_TYPEDEF_PTR stack, SEQUENCE_STACK_DATA_TYPE* array, size_t depth);

	struct
	{
		size_t(*current_depth)(SEQUENCE_STACK_TYPEDEF_PTR stack);
		size_t(*max_depth)(SEQUENCE_STACK_TYPEDEF_PTR stack);

		bool(*is_empty)(SEQUENCE_STACK_TYPEDEF_PTR stack);
		bool(*is_topful)(SEQUENCE_STACK_TYPEDEF_PTR stack);
	}get_stack_info;
}SEQUENCE_STACK_CONTROL_TYPEDEF, * SEQUENCE_STACK_CONTROL_TYPEDEF_PTR;

typedef struct Chain_Stack_Control
{
	bool (*init)(CHAIN_STACK_TYPEDEF_PPTR stack, size_t depth);
	bool (*config_expection)(CHAIN_STACK_TYPEDEF_PTR stack,
		bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...);
	bool (*free)(CHAIN_STACK_TYPEDEF_PPTR stack);

	bool (*push)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom, size_t sizeof_atom);
	bool (*pop)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
	bool (*get)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE atom);
	bool (*delete)(CHAIN_STACK_TYPEDEF_PTR stack);
	bool (*multi_pop)(CHAIN_STACK_TYPEDEF_PTR stack, CHAIN_STACK_DATA_TYPE* array, size_t depth);

	struct
	{
		size_t(*current_depth)(CHAIN_STACK_TYPEDEF_PTR stack);
		size_t(*max_depth)(CHAIN_STACK_TYPEDEF_PTR stack);
		size_t(*stack_data_type_size)(CHAIN_STACK_TYPEDEF_PTR stack);

		bool(*is_empty)(CHAIN_STACK_TYPEDEF_PTR stack);
		bool(*is_topful)(CHAIN_STACK_TYPEDEF_PTR stack);
	}get_stack_info;
}CHAIN_STACK_CONTROL_TYPEDEF, * CHAIN_STACK_CONTROL_TYPEDEF_PTR;

typedef struct Chain_Generic_Stack_Control
{
	bool (*init)(CHAIN_GENERIC_STACK_TYPEDEF_PPTR stack, size_t data_type_size, size_t max_depth,
		void (*stack_data_assign)(void*, const void*), void (*stack_data_delete)(void*));
	bool (*config_expection)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack,
		bool is_full_stack_cfg, bool is_null_stack_cfg, bool is_lack_heap_cfg, ...);
	bool (*free)(CHAIN_GENERIC_STACK_TYPEDEF_PPTR stack);

	bool (*push)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void* atom, size_t sizeof_atom);
	bool (*pop)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void* atom);
	bool (*get)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void* atom);
	bool (*delete)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);
	bool (*multi_pop)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack, void** array, size_t depth);

	struct
	{
		size_t(*current_depth)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);
		size_t(*max_depth)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);
		size_t(*stack_data_type_size)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);
		size_t(*stack_top_data_length)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);

		bool(*is_empty)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);
		bool(*is_topful)(CHAIN_GENERIC_STACK_TYPEDEF_PTR stack);
	}get_stack_info;
}CHAIN_GENERIC_STACK_CONTROL_TYPEDEF, * CHAIN_GENERIC_STACK_CONTROL_TYPEDEF_PTR;

typedef struct Stack_Control
{
	SEQUENCE_STACK_CONTROL_TYPEDEF_PTR equence_stack;

	CHAIN_STACK_CONTROL_TYPEDEF_PTR chain_stack;

	CHAIN_GENERIC_STACK_CONTROL_TYPEDEF_PTR chain_generic_stack;
}STACK_CONTROL_TYPEDEF;

extern SEQUENCE_STACK_CONTROL_TYPEDEF sequence_stack_ctrl;
extern CHAIN_STACK_CONTROL_TYPEDEF chain_stack_ctrl;
extern CHAIN_GENERIC_STACK_CONTROL_TYPEDEF chain_generic_stack_ctrl;

extern STACK_CONTROL_TYPEDEF stack_ctrl;

#endif // __STACK_H