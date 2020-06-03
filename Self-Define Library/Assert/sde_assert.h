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

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configuration    assert configuration logger.										                */
#define ASSERT_CFG_LOGGER                                                                               \
    printf

/* Define			assert expression.								                                    */
#define ASSERT(expression, ...)                                                                         \
    do {                                                                                                \
        _ASSERT_(                                                                                       \
            expression, _ASSERT_LOG_(                                                                   \
                expression, __VA_ARGS__));                                                              \
    } while (0)

/* Define			assert variable.								                                    */
#define ASSERT_VARIABLE(variable, comp, value_type, value, ...)                                         \
    do {                                                                                                \
        _ASSERT_(                                                                                       \
            ((value_type)(variable)) comp ((value_type)(value)),                                        \
             _ASSERT_LOG_(                                                                              \
                variable comp value, __VA_ARGS__));                                                     \
    } while (0)

/* Define			assert pointer.								                                        */
#define ASSERT_POINTER(pointer, ...)							                                        \
    do {                                                                                                \
        _ASSERT_(                                                                                       \
            pointer != NULL,                                                                            \
            _ASSERT_LOG_(                                                                               \
                pointer != NULL, __VA_ARGS__));                                                         \
    } while (0)

/* Define			assert.										                                        */
#define _ASSERT_(expression, ...)                                                                       \
	do {																								\
		assert(expression);	                                                                            \
        if (!(expression)) {                                                                            \
            __VA_ARGS__;                                                                                \
            while (1) {                                                                                 \
            }                                                                                           \
        }                                                                                               \
	} while (0)

/* Define			assert log.								                                            */
#define _ASSERT_LOG_(expression, ...)                                                                   \
    do {                                                                                                \
        assert_control_string_modify(                                                                   \
            #expression,                                                                                \
            __FUNCTION__,                                                                               \
            __FILE__,                                                                                   \
            __LINE__);                                                                                  \
        VA_ARGS_ARG(                                                                                    \
            2, printf, __VA_ARGS__, ASSERT_CFG_LOGGER)(                                                 \
                assert_control_string_inquire());                                                       \
        VA_ARGS_FROM(                                                                                   \
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