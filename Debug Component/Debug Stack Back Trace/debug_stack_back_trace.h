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
 * @brief This type is the stack back trace link structure typedef.
 */

typedef struct stack_back_trace_link_t
*stack_back_trace_link_stp,
**stack_back_trace_link_stpp;

/**
 * @brief This type is the stack back trace convert_to_string_return typedef.
 */

struct stack_back_trace_convert_to_string_return_s {
	stack_back_trace_frame_t frames;

	struct stack_back_trace_string_t *string;
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
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_reduce_count(stack_back_trace_stp strcuture,
													stack_back_trace_hash_t hash);

/**
 * @brief This function will back trace the stack.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

struct stack_back_trace_convert_to_string_return_s
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
 * @brief This function will initialize a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_link_init(stack_back_trace_link_stpp link,
												 stack_back_trace_size_t count);

/**
 * @brief This function will destroy a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_link_destroy(stack_back_trace_link_stp *link);

/**
 * @brief This function will make a sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return index
 */

errno_t debug_capture_stack_back_trace_link_mark(stack_back_trace_link_stp link,
												 stack_back_trace_size_t frames_to_skip);

/**
 * @brief This function will set a link via the sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_link_link(stack_back_trace_link_stp link,
												 stack_back_trace_size_t frames_to_skip);

/**
 * @brief This function will log the mark and the link information.
 *
 * @param link the pointer to the stack back trace link struct
 * @param option the option of the log
 *
 * @return the error code
 */

errno_t debug_capture_stack_back_trace_link_log(stack_back_trace_link_stp link,
												size_t option);

/**
 * @brief This function will get the trace in the link.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NULL
 */

errno_t debug_capture_stack_back_trace_link_get_trace_ptr(stack_back_trace_link_stp link,
														  stack_back_trace_stpp trace);

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__DEBUG_STACK_BACK_TRACE_H