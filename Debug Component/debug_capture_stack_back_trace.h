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
#include <stdbool.h>

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
#define DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN	    1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    the back trace type.                                                                    */
typedef void
*single_back_trace_t,
*back_trace_t[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH],
*(*back_trace_pt)[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH];

/* Configure    the back trace frame type.                                                              */
typedef WORD back_trace_frame_t, *back_trace_frame_pt;

/* Configure    the back trace hash type.                                                               */
typedef ULONG back_trace_hash_t, *back_trace_hash_pt;

/* Configure    the back trace symbol type.                                                             */
typedef struct stack_back_trace_string_t
STACK_BACK_TRACE_STRING_TYPEDEF[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH],
(*STACK_BACK_TRACE_STRING_TYPEDEF_PTR)[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH];

/* Configure    the back trace line type.                                                               */
typedef IMAGEHLP_LINE64 *back_trace_line_t;

/* Configure    the stack back trace type.                                                              */
typedef struct stack_back_trace_t *STACK_BACK_TRACE_TYPEDEF_PTR,**STACK_BACK_TRACE_TYPEDEF_PPTR;

/* Configure    the stack back trace link type.                                                         */
typedef struct stack_back_trace_link_t *STACK_BACK_TRACE_LINK_TYPEDEF_PTR;

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

void debug_capture_stack_back_trace_init(STACK_BACK_TRACE_TYPEDEF_PTR *stack_back_trace,
										 DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE count);

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param structure the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_destroy(STACK_BACK_TRACE_TYPEDEF_PTR *stack_back_trace);

/**
 * @brief This function will back trace the stack.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

void debug_capture_stack_back_trace(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace,
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip);

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_reduce_count(STACK_BACK_TRACE_TYPEDEF_PTR strcuture,
												 back_trace_hash_t hash);

/**
 * @brief This function will back trace the stack.
 *
 * @param structure the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_convert_to_string(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace);

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

back_trace_hash_t debug_capture_stack_back_trace_get_hash(STACK_BACK_TRACE_TYPEDEF_PTR strcuture,
														  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index);

single_back_trace_t *debug_capture_stack_back_trace_get_trace(STACK_BACK_TRACE_TYPEDEF_PTR strcuture,
															  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index,
															  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE sub_index);

/**
 * @brief This function will initialize a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_link_init(STACK_BACK_TRACE_LINK_TYPEDEF_PTR *link,
											  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE count);

/**
 * @brief This function will destroy a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_link_destroy(STACK_BACK_TRACE_LINK_TYPEDEF_PTR *link);

/**
 * @brief This function will make a sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return index
 */

DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE debug_capture_stack_back_trace_link_mark(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
																					  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip);

/**
 * @brief This function will set a link via the sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

back_trace_hash_t *debug_capture_stack_back_trace_link_link(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
															DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index,
															DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip);

/**
 * @brief This function will get the trace in the link.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NULL
 */

void debug_capture_stack_back_trace_link_get_trace_ptr(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
                                                   STACK_BACK_TRACE_TYPEDEF_PPTR trace);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__DEBUG_CAPTURE_STACK_BACK_TRACE_H