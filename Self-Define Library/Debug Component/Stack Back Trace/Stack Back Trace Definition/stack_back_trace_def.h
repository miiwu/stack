/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __STACK_BACK_TRACE_DEFINITION_H
#define __STACK_BACK_TRACE_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "sde_log.h"

#include <assert.h>
#include <stdbool.h>

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

typedef size_t
stack_back_trace_size_t,
*stack_back_trace_size_tp;

typedef size_t *
stack_back_trace_address_t,
**stack_back_trace_address_tp;

typedef unsigned short
stack_back_trace_frame_t,
*stack_back_trace_frame_tp;

typedef unsigned long
stack_back_trace_hash_t,
*stack_back_trace_hash_tp;

/**
 * @brief This type is the stack back trace string structure.
 */

struct stack_back_trace_string_s {
	stack_back_trace_size_t name_len;

	char *name_ptr;

	stack_back_trace_size_t file_line;

	stack_back_trace_size_t file_line_len;

	char *file_name_ptr;
};

/**
 * @brief This type is the stack back trace string package typedef.
 */

struct stack_back_trace_string_package_s {
	stack_back_trace_frame_t frames;

	struct stack_back_trace_string_s *string_list;
};

/**
 * @brief This type is the stack back trace count package typedef.
 */

struct stack_back_trace_count_package_s {
	stack_back_trace_size_t types;

	stack_back_trace_size_t *back_trace_count_ptr;
};

typedef struct stack_back_trace_s
*stack_back_trace_stp,
**stack_back_trace_stpp;

enum stack_back_trace_string_option_e {
	FUNC_ONLY,
	FUNC_FILE_LINE,
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

#endif // !__STACK_BACK_TRACE_DEFINITION_H