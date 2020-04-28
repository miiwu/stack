/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_MICRO_H
#define __DEBUG_MICRO_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			debug micro control left bracket.								                    */
#define DEBUG_MICRO_CONTROL_LEFTBRACKET                                                                 \
    (

/* Define			debug micro control expand.								                            */
#define DEBUG_MICRO_CONTROL_EXPAND(...)                                                                 \
    (__VA_ARGS__)

/* Define			debug micro control string.								                            */
#define DEBUG_MICRO_CONTROL_STRING(...)                                                                 \
    (#__VA_ARGS__)

/* Define			debug micro control function-like.										            */
#define DEBUG_MICRO_CONTROL_FUNCTION_LIKE(...)                                                          \
    do {                                                                                                \
        __VA_ARGS__;                                                                                    \
    } while (0)

/* Define			debug micro control get the arg1 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG1(arg1, ...)                                                     \
    (arg1)

/* Define			debug micro control get the arg2 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG2(arg1, arg2, ...)                                               \
    (arg2)

/* Define			debug micro control get the arg3 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG3(arg1, arg2, arg3, ...)                                         \
    (arg3)

/* Define			debug micro control get the arg4 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG4(arg1, arg2, arg3, arg4, ...)                                   \
    (arg4)

/* Define			debug micro control get the arg5 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG5(arg1, arg2, arg3, arg4, arg5, ...)                             \
    (arg5)

/* Define			debug micro control get the arg6 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG6(arg1, arg2, arg3, arg4, arg5, arg6, ...)                       \
    (arg6)

/* Define			debug micro control get the arg7 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG7(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...)                 \
    (arg7)

/* Define			debug micro control get the arg8 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG8(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, ...)           \                                                                                             \
    (arg8)

/* Define			debug micro control get the cnt-th arg of the va_arg.				                */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG(cnt, ...)                                                       \
    (DEBUG_MICRO_CONTROL_VA_ARGS_ARG ## cnt DEBUG_MICRO_CONTROL_LEFTBRACKET __VA_ARGS__))

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

#endif // !__DEBUG_MICRO_H