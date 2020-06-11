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

#include "stack_back_trace_platform.h"

/*
 *********************************************************************************************************
 *									      CONFIG DEFINES
 *********************************************************************************************************
 */

/* Configure        the max frames of the stack back trace can capture.									*/
#define STACK_BACK_TRACE_CFG_FRAMES_CAPTURE_MAX															\
	64u

/* Configure        if enable the capture stack back trace debug mode.                                  */
#define STACK_BACK_TRACE_CFG_DEBUG_EN																	\
	0u

/* Define			built-in stack back trace.															*/
#define STACK_BACK_TRACE(method, ...)																	\
	BUILT_IN(&_built_in_stack_back_trace_, method, __VA_ARGS__)

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

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

errno_t stack_back_trace_control_init(stack_back_trace_stpp stack_back_trace,
									  stack_back_trace_size_t count);

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void stack_back_trace_control_destroy(stack_back_trace_stpp stack_back_trace);

/**
 * @brief This function will back trace the stack.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

errno_t stack_back_trace_control_trace_address(stack_back_trace_stp stack_back_trace,
											   stack_back_trace_frame_t skip,
											   stack_back_trace_frame_t capture);

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
	stack_back_trace_control_trace_string(stack_back_trace_stp stack_back_trace,
										  enum stack_back_trace_string_option_e option,
										  size_t index);

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

stack_back_trace_hash_t stack_back_trace_control_get_hash(stack_back_trace_stp strcuture,
														  stack_back_trace_size_t index);

/**
 * @brief This function will return the count package.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

struct stack_back_trace_count_package_s
	stack_back_trace_control_get_count_package(stack_back_trace_stp stack_back_trace);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

extern struct stack_back_trace_s _built_in_stack_back_trace_;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__DEBUG_STACK_BACK_TRACE_H