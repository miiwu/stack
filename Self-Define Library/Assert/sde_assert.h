/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __SELF_DEFINE_ASSERT_H
#define __SELF_DEFINE_ASSERT_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "sde_micro.h"

#include "sde_log.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configuration    config enable log or not when assert fail.									        */
#define ASSERT_CFG_LOG_EN                                                                               \
    1

/* Define			assert expression.								                                    */
#define ASSERT(expression, ...)                                                                         \
    do {                                                                                                \
        _ASSERT_(                                                                                       \
            expression,                                                                                 \
            expression,                                                                                 \
            __VA_ARGS__);                                                                               \
    } while (0)

/* Define			assert variable.								                                    */
#define ASSERT_VARIABLE(variable, comp, value_type, value, ...)                                         \
    do {                                                                                                \
        _ASSERT_(                                                                                       \
            ((value_type)(variable)) comp ((value_type)(value)),                                        \
            variable comp value,                                                                        \
            __VA_ARGS__);                                                                               \
    } while (0)

/* Define			assert pointer.								                                        */
#define ASSERT_POINTER(pointer, ...)							                                        \
    do {                                                                                                \
        _ASSERT_(                                                                                       \
            pointer != NULL,                                                                            \
            pointer != NULL,                                                                            \
            __VA_ARGS__);                                                                               \
    } while (0)

/* Define			assert.										                                        */
#define _ASSERT_(expression, message, ...)                                                              \
	do {																								\
		assert(expression);	                                                                            \
        if (!(expression)) {                                                                            \
            _ASSERT_LOG_(message);                                                                      \
            __VA_ARGS__;                                                                                \
            while (1) {                                                                                 \
            }                                                                                           \
        }                                                                                               \
	} while (0)

/* Define			assert log.								                                            */
#if ASSERT_CFG_LOG_EN

#define _ASSERT_LOG_(message)                                                                           \
    assert_control_string_modify(                                                                       \
        #message,                                                                                       \
        __FUNCTION__,                                                                                   \
        __FILE__,                                                                                       \
        __LINE__);                                                                                      \
    LOG(assert_control_string_inquire());                                                               \
    NULL

#else

#define _ASSERT_LOG_(message)

#endif // ASSERT_CFG_LOG_EN

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

void assert_control_string_modify(char *expression,
                                  char *function,
                                  char *file,
                                  size_t line);

char *assert_control_string_inquire(void);

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

#endif // !__SELF_DEFINE_ASSERT_H