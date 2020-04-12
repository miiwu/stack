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

#include <errno.h>

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			debug error control error pointer.										            */
#define DEBUG_ERROR_CONTROL_ERRNO_PTR                                                                   \
    debug_error_control_errno_ptr

/* Define			debug error control error.										                    */
#define DEBUG_ERROR_CONTROL_ERRNO                                                                       \
    *debug_error_control_errno_ptr

/* Define			debug error control error pointer.										            */
#define DEBUG_ERROR_CONTROL_RETURN_PTR                                                                  \
    debug_error_control_errno_exit_ptr

/* Define			debug error control error.										                    */
#define DEBUG_ERROR_CONTROL_RETURN                                                                      \
    *debug_error_control_errno_exit_ptr

/* Define			debug error control init.										                    */
#define DEBUG_ERROR_CONTROL_INIT(return_type, count, code, ...)                                         \
    static errno_t debug_error_control_errno_table[count] = { code, __VA_ARGS__ };                      \
    static return_type *debug_error_control_errno_exit_ptr

/* Define			debug error control set.										                    */
#define DEBUG_ERROR_CONTROL_SET(count, ...)                                                             \
	DEBUG_ERROR_CONTROL_ERRNO_PTR                                                                       \
        = (errno_t*)debug_error_control_errno_exit_ptr                                                  \
            = &debug_error_control_errno_table[count];                                                  \
    *(errno_t*)&debug_error_control_errno_table[count] __VA_ARGS__

/* Define			debug error control exit.										                    */
#define DEBUG_ERROR_CONTROL_EXIT(...)                                                                   \
	__VA_ARGS__;                                                                                        \
    return *debug_error_control_errno_exit_ptr

/* Define			debug error control init.										                    */
#define DEBUG_ERROR_CONTROL_ERRNO_INIT(count, code, ...)                                                \
    DEBUG_ERROR_CONTROL_INIT(errno_t, count, code, __VA_ARGS__)

/* Define			debug error control set.										                    */
#define DEBUG_ERROR_CONTROL_ERRNO_SET(count)                                                            \
	DEBUG_ERROR_CONTROL_SET(count)

/* Define			debug error control exit.										                    */
#define DEBUG_ERROR_CONTROL_EXIT_ERRNO(...)                                                             \
	DEBUG_ERROR_CONTROL_EXIT(__VA_ARGS__)

/* Define			debug error control init.										                    */
#define DEBUG_ERROR_CONTROL_STRUCTURE_INIT(return_type)                                                 \
    DEBUG_ERROR_CONTROL_INIT(return_type, 1, 0)

/* Define			debug error control set.										                    */
#define DEBUG_ERROR_CONTROL_STRUCTURE_SET(expression)                                                   \
	DEBUG_ERROR_CONTROL_SET(0, expression)

/* Define			debug error control exit.										                    */
#define DEBUG_ERROR_CONTROL_STRUCTURE_EXIT(...)                                                         \
	DEBUG_ERROR_CONTROL_EXIT(__VA_ARGS__)

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

/**
 * @brief This variable is the debug error control error pointer.
 */

extern errno_t *DEBUG_ERROR_CONTROL_ERRNO_PTR;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__DEBUG_ERROR_H