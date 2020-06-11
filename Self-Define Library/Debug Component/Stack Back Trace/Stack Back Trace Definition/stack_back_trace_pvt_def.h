/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __STACK_BACK_TRACE_PRIVITE_DEFINITION_H
#define __STACK_BACK_TRACE_PRIVITE_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "stack_back_trace_def.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the stack back trace structure.
 */

struct stack_back_trace_types_s {
	stack_back_trace_size_t max;

	stack_back_trace_size_t current;
};

struct stack_back_trace_information_s {
	struct stack_back_trace_types_s types;

	stack_back_trace_size_tp count_ptr;
};

struct stack_back_trace_frames_s {
	stack_back_trace_frame_t skip;

	stack_back_trace_frame_t capture;
};

struct stack_back_trace_trace_unit_s {
	stack_back_trace_address_tp address_list;

	struct stack_back_trace_frames_s frames;

	stack_back_trace_hash_t hash;
};

struct stack_back_trace_exception_s {
	bool (*full_types_callback)(struct stack_back_trace_s *stack_back_trace);
};

/**
 * @brief This type is the stack back trace structure.
 */

struct stack_back_trace_s {
	struct stack_back_trace_information_s info;

	struct stack_back_trace_trace_unit_s *trace_unit_ptr;

	struct stack_back_trace_exception_s exception;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__STACK_BACK_TRACE_PRIVITE_DEFINITION_H