/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_ASSERT_H
#define __DEBUG_ASSERT_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_component_def.h"

#include "debug_micro.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configuration    debug assert configuration logger.										            */
#define DEBUG_ASSERT_CFG_LOGGER                                                                         \
    printf

/* Define			debug assert control expression.								                    */
#define DEBUG_ASSERT_CONTROL_EXPRESSION(expression, ...)                                                \
    do {                                                                                                \
        _DEBUG_ASSERT_CONTROL_ASSERT_(                                                                  \
            expression, _DEBUG_ASSERT_CONTROL_LOG_(                                                     \
                expression, __VA_ARGS__));                                                              \
    } while (0)

/* Define			debug assert control variable.								                        */
#define DEBUG_ASSERT_CONTROL_VARIABLE(variable, comp, value_type, value, ...)                           \
    do {                                                                                                \
        _DEBUG_ASSERT_CONTROL_ASSERT_(                                                                  \
            ((value_type)(variable)) comp ((value_type)(value)), _DEBUG_ASSERT_CONTROL_LOG_(            \
                variable comp value, __VA_ARGS__));                                                     \
    } while (0)

/* Define			debug assert control pointer.								                        */
#define DEBUG_ASSERT_CONTROL_POINTER(pointer, ...)							                            \
    do {                                                                                                \
        _DEBUG_ASSERT_CONTROL_ASSERT_(                                                                  \
            pointer != NULL, _DEBUG_ASSERT_CONTROL_LOG_(                                                \
                pointer != NULL, __VA_ARGS__));                                                         \
    } while (0)

/* Define			debug assert control assert.										                */
#define _DEBUG_ASSERT_CONTROL_ASSERT_(expression, ...)                                                  \
	do {																								\
		assert(expression);	                                                                            \
        if (!(expression)) {                                                                            \
            __VA_ARGS__;                                                                                \
            while (1) {                                                                                 \
            }                                                                                           \
        }                                                                                               \
	} while (0)

/* Define			debug assert control log.								                            */
#define _DEBUG_ASSERT_CONTROL_LOG_(expression, ...)                                                     \
    do {                                                                                                \
        debug_assert_control_error_string_modify(                                                       \
            #expression,                                                                                \
            __FUNCTION__,                                                                               \
            __FILE__,                                                                                   \
            __LINE__);                                                                                  \
        DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                                \
            2, printf, __VA_ARGS__, DEBUG_ASSERT_CFG_LOGGER)(                                           \
                debug_assert_control_error_string_inquire());                                           \
        DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM(                                                          \
            2, __VA_ARGS__, NULL, NULL);                                                                \
    } while (0)

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

void debug_assert_control_error_string_modify(char *expression,
											  char *function,
											  char *file,
											  size_t line);

char *debug_assert_control_error_string_inquire(void);

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

#endif // !__DEBUG_ASSERT_H