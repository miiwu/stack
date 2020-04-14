/*
 ************************************************************************************************************************
 *                                  DEBUG COMPONENT OF CAPATURE STACK BACK TRACE FUNCTIONS
 *
 * File    : DEBUG_CAPATURE_STACK_BACK_TRACE.H
 * By      : Miao Mico
 * Version : V0.01.00
 *
 * FIRST ENLIGHTENMENT : https://gist.github.com/t-mat/7979300
 * SECONDARY REFERANCE : https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb204633(v=vs.85)?redirectedfrom=MSDN
 *
 ************************************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_STACK_BACK_TRACE_H
#define __DEBUG_STACK_BACK_TRACE_H

/*
 *********************************************************************************************************
 *                                          INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_component_def.h"

/*
 *********************************************************************************************************
 *									      CONFIG DEFINES
 *********************************************************************************************************
 */

/* Configure        the max depth of the capture stack back trace.                                      */
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH	    64u

/* Configure        the main() depth of the capture stack back trace.                                   */
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_MAIN_DEPTH	        7u

/* Configure        if enable the capture stack back trace debug mode.                                  */
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN	    0u

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the stack back trace frame typedef.
 */

typedef WORD
stack_back_trace_frame_t,
*stack_back_trace_frame_tp;

/**
 * @brief This type is the stack back trace hash typedef.
 */

typedef ULONG
stack_back_trace_hash_t,
*stack_back_trace_hash_tp;

/**
 * @brief This type is the stack back trace size typedef.
 */

typedef DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE
stack_back_trace_size_t;

/**
 * @brief This type is the stack back trace structure typedef.
 */

typedef struct stack_back_trace_t
*stack_back_trace_stp,
**stack_back_trace_stpp;

/**
 * @brief This type is the stack back trace string structure.
 */

struct stack_back_trace_string_t {
	/* @brief This variables will record the max types.													*/
	size_t name_len;

	/* @brief This variables will record how many types is recorded.					                */
	char *name_ptr;

	/* @brief This variables will record the trace value of the both stack.					            */
	size_t file_line;

	/* @brief This variables will record the trace value of the both stack.					            */
	size_t file_line_len;

	/* @brief This variables will record the hash value of the both stack.					            */
	char *file_name_ptr;
};

/**
 * @brief This type is the stack back trace string package typedef.
 */

struct stack_back_trace_string_package_s {
	stack_back_trace_frame_t frames;

	struct stack_back_trace_string_t *string;
};

/**
 * @brief This type is the stack back trace count package typedef.
 */

struct stack_back_trace_count_package_s {
	/* @brief This variables will record how many types is recorded.					                */
	stack_back_trace_size_t type_count;

	/* @brief This variables will record the amount of back trace.					                    */
	stack_back_trace_size_t *back_trace_count_ptr;
};

/*
 *********************************************************************************************************
 *											FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will initialize the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param count the amount of type stack situation
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_init(stack_back_trace_stpp stack_back_trace,
											stack_back_trace_size_t count);

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_destroy(stack_back_trace_stpp stack_back_trace);

/**
 * @brief This function will back trace the stack.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace(stack_back_trace_stp stack_back_trace,
									   stack_back_trace_size_t frames_to_skip);

/**
 * @brief This function will back trace the stack.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

struct stack_back_trace_string_package_s
	debug_capture_stack_back_trace_convert_to_string(stack_back_trace_stp stack_back_trace,
													 size_t count);

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

stack_back_trace_hash_t debug_capture_stack_back_trace_get_hash(stack_back_trace_stp strcuture,
																stack_back_trace_size_t index);

/**
 * @brief This function will return the count package.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

struct stack_back_trace_count_package_s
	debug_capture_stack_back_trace_get_count_package(stack_back_trace_stp stack_back_trace);

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

   /*
	*********************************************************************************************************
	*                                             MODULE END
	*********************************************************************************************************
	*/
#endif // !__DEBUG_STACK_BACK_TRACE_H