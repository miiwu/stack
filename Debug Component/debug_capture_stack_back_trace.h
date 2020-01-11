/*
************************************************************************************************************************
*                                  DEBUG COMPONENT OF CAPATURE STACK BACK TRACE FUNCTIONS
*
* File    : DEBUG_CAPATURE_STACK_BACK_TRACE.H
* By      : lqq
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

#ifndef __DEBUG_CAPTURE_STACK_BACK_TRACE_H
#define __DEBUG_CAPTURE_STACK_BACK_TRACE_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include <windows.h>
#include <DbgHelp.h>

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#pragma comment(lib, "Dbghelp.lib")

/*
*********************************************************************************************************
*									     CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure the type of the capture stack back trace size.                                             */
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE	        size_t

/* Configure the max depth of the capture stack back trace.                                             */
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH	    64u

/* Configure if enable the capture stack back trace debug mode.                                         */
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN	    0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    the back trace type.                                                              */
typedef void *back_trace_t[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH];

/* Configure    the back trace hash type.                                                              */
typedef ULONG back_trace_hash_t;

/* Configure    the back trace symbol type.                                                              */
typedef SYMBOL_INFO *back_trace_symbol_t;

/* Configure    the back trace line type.                                                              */
typedef IMAGEHLP_LINE64 *back_trace_line_t;

/**
 * @brief This struct is the capture stack back trace structure module
 */

struct capture_stack_back_trace_t {
	/* @brief This variables will record the max types.					                */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE max_type_count;

	/* @brief This variables will record how many types is recorded.					                */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE type_count;

	/* @brief This variables will record the amount of back trace.					                    */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE *back_trace_count;

	/* @brief This variables will record the back trace.					                            */
    back_trace_t *back_trace;

	/* @brief This variables will record the hash value of back trace.					                */
    back_trace_hash_t *back_trace_hash;

    /* @brief This variables will record the symbol description of the back trace.					    */
    back_trace_symbol_t *back_trace_symbol;

    /* @brief This variables will record the line description of the back trace.					    */
    back_trace_line_t *back_trace_line;
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

void debug_capture_stack_back_trace_init(struct capture_stack_back_trace_t **strcuture,
										 DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE count);

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_destroy(struct capture_stack_back_trace_t **strcuture);

/**
 * @brief This function will back trace the stack.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

void debug_capture_stack_back_trace(struct capture_stack_back_trace_t *stack_back_trace,
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip,
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_capture);

void debug_capture_stack_back_trace_to_symbol(struct capture_stack_back_trace_t *stack_back_trace,
											  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip,
											  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_capture);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__DEBUG_CAPTURE_STACK_BACK_TRACE_H