/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __STACK_BACK_TRACE_WINDOWS_H
#define __STACK_BACK_TRACE_WINDOWS_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "stack_back_trace_def.h"

#include <DbgHelp.h>
#pragma comment (lib, "Dbghelp.lib")

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configure        the main() depth of the capture stack back trace.                                   */
#define STACK_BACK_TRACE_WINDOWS_CFG_FRAMES_BEFORE_MAIN													\
	7u

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

stack_back_trace_frame_t
stack_back_trace_control_platform_trace_address(struct stack_back_trace_trace_unit_s *trace_unit);

stack_back_trace_frame_t
stack_back_trace_control_platform_trace_string(struct stack_back_trace_string_s *string_list,
											   struct stack_back_trace_trace_unit_s trace_unit,
											   enum stack_back_trace_string_option_e option);

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

#endif // !__STACK_BACK_TRACE_WINDOWS_H