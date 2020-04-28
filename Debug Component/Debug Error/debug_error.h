/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_ERROR_H
#define __DEBUG_ERROR_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_component_def.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			debug error control return.										                    */
#define DEBUG_ERROR_CONTROL_RETURN_VAL                                                                  \
    (debug_error_control_return)

/* Define			debug error control init.										                    */
#define DEBUG_ERROR_CONTROL_INIT(return_type, count, code, ...)                                         \
    static errno_t debug_error_control_error_table[count] = { code, __VA_ARGS__ };                      \
    static return_type DEBUG_ERROR_CONTROL_RETURN_VAL;                                                  \
    _DEBUG_ERROR_CONTROL_SET_(0)

/* Define			debug error control jump.										                    */
#define DEBUG_ERROR_CONTROL_JUMP(count, ...)                                                            \
    do {                                                                                                \
        DEBUG_MICRO_CONTROL_NOT_ZERO(count);                                                            \
	    _DEBUG_ERROR_CONTROL_SET_(count, __VA_ARGS__);                                                  \
        goto DEBUG_ERROR_CONTROL_EXIT_LABLE;                                                            \
    } while (0)

/* Define			debug error control exit.										                    */
#define DEBUG_ERROR_CONTROL_EXIT(...)                                                                   \
    do {                                                                                                \
        DEBUG_ERROR_CONTROL_EXIT_LABLE:                                                                 \
	        __VA_ARGS__;                                                                                \
            return DEBUG_ERROR_CONTROL_RETURN_VAL;                                                      \
    } while (0)

/* Define			debug error control error.										                    */
#define DEBUG_ERROR_CONTROL_ERROR()                                                                     \
    (debug_error_control_error_inquire())

/* Define			debug error control log.										                    */
#define DEBUG_ERROR_CONTROL_LOG(logger)                                                                 \
    do {                                                                                                \
        if (debug_error_control_error_inquire()) {                                                      \
			logger("debug_component.error.error occur:");                                               \
			logger(debug_error_control_error_string_inquire());                                         \
			logger("\r\n");                                                                             \
		}                                                                                               \
    } while (0)

/* Define			debug error control errno init.										                */
#define DEBUG_ERROR_CONTROL_ERRNO_INIT(count, ...)                                                      \
    DEBUG_ERROR_CONTROL_INIT(errno_t, count + 1, 0, __VA_ARGS__)

/* Define			debug error control structure init.										            */
#define DEBUG_ERROR_CONTROL_STRUCTURE_INIT(return_type, count, ...)                                     \
    DEBUG_ERROR_CONTROL_INIT(return_type, count + 1, 0, __VA_ARGS__)

/* Define			debug error control printf and exit.										        */
#define DEBUG_ERROR_CONTROL_PRINTF_EXIT(...)                                                            \
    do {                                                                                                \
        DEBUG_ERROR_CONTROL_EXIT(DEBUG_ERROR_CONTROL_LOG(printf);##__VA_ARGS__);                        \
    } while (0)

/* Define			debug error control set.										                    */
#define _DEBUG_ERROR_CONTROL_SET_(count, ...)                                                           \
    do {                                                                                                \
        debug_error_control_error_pointer_modify(&DEBUG_ERROR_CONTROL_RETURN_VAL);                      \
        debug_error_control_error_modify(debug_error_control_error_table[count]);                       \
        debug_error_control_error_string_modify(DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                        \
                2, NULL, __VA_ARGS__, NULL));                                                           \
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

errno_t debug_error_control_error_inquire(void);

void debug_error_control_error_modify(errno_t error);

void debug_error_control_error_pointer_modify(void *pointer);

char *debug_error_control_error_string_inquire(void);

void debug_error_control_error_string_modify(char *string);

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

#endif // !__DEBUG_ERROR_H