/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEMO_SELF_DEFINE_LIBRARY_H
#define __DEMO_SELF_DEFINE_LIBRARY_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "sde_lib.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

#define DEMO_SDE_LIB_CFG_MICRO_EN													\
	0

#define DEMO_SDE_LIB_CFG_LOG_EN														\
	0

#define DEMO_SDE_LIB_CFG_ASSERT_EN													\
	0

#define DEMO_SDE_LIB_CFG_ERROR_EN													\
	0

#define DEMO_SDE_LIB_CFG_DBG_CMPT_STACK_BACK_TRACE_EN								\
	1

#if DEMO_SDE_LIB_CFG_MICRO_EN

void main_micro(void);

#endif // DEMO_SDE_LIB_CFG_MICRO_EN

#if DEMO_SDE_LIB_CFG_LOG_EN

void main_log(void);

#endif // DEMO_SDE_LIB_CFG_LOG_EN

#if DEMO_SDE_LIB_CFG_ASSERT_EN

void main_assert(void);

#endif // DEMO_SDE_LIB_CFG_ASSERT_EN

#if DEMO_SDE_LIB_CFG_ERROR_EN

void main_error(void);

#endif // DEMO_SDE_LIB_CFG_ERROR_EN

#if DEMO_SDE_LIB_CFG_DBG_CMPT_STACK_BACK_TRACE_EN

void main_stack_back_trace(void);

#endif // DEMO_SDE_LIB_CFG_DBG_CMPT_STACK_BACK_TRACE_EN

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

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

#endif // !__DEMO_SELF_DEFINE_LIBRARY_H