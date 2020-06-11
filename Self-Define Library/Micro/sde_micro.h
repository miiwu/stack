/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __SELF_DEFINE_MICRO_H
#define __SELF_DEFINE_MICRO_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <malloc.h>

#include <windows.h>

#pragma warning( disable : 4996)
#pragma warning( disable : 26812)

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			left bracket.								                                        */
#define LEFTBRACKET                                                                                     \
    (

/* Define			expand.								                                                */
#define EXPAND(...)                                                                                     \
    __VA_ARGS__

/* Define			string.								                                                */
#define STRING(...)                                                                                     \
    #__VA_ARGS__

/* Define			swap.										                                        */
#define SWAP(lhs, rhs)                                                                                  \
    (lhs) = (lhs) ^ (rhs),                                                                              \
    (rhs) = (lhs) ^ (rhs),                                                                              \
    (lhs) = (lhs) ^ (rhs)

/* Define			shortcuts.										                                    */
#define SHORTCUTS(body, shortcut, ...)                                                                  \
    body ## shortcut LEFTBRACKET __VA_ARGS__)

/* Define			shortcuts.										                                    */
#define DBG_MIC(shortcut, ...)                                                                          \
    SHORTCUTS(DEBUG_MICRO, shortcut, __VA_ARGS__)

/* Define			field offset.								                                        */
#define FIELD(variable_address, field_type, field_offset)                                               \
    *(field_type*)((char *)variable_address + (field_offset))

/* Define			field offset.								                                        */
#ifdef FIELD_OFFSET
#else

#define FIELD_OFFSET(type, field)                                                                       \
    ((size_t)(size_t *) & (((type *)0)->field))

#endif

/* Define			probe, if zero, the compiler will throw warnings.		                            */
#define PROBE(zero)                                                                                     \
    (1u ? sizeof(char[zero]) : 0u)

/* Define			probe value what x.		                                                            */
#define PROBE_WHAT_X(value, symbol, x)                                                                  \
    PROBE(value symbol x)

/* Define			probe not zero.		                                                                */
#define PROBE_NOT_ZERO(value)                                                                           \
    PROBE_WHAT_X(value, !=, 0)

/* Define			probe arg max.		                                                                */
#define PROBE_ARG_MAX(max, ...)	                                                                        \
    PROBE_WHAT_X(VA_ARGS_ARG_NUM(__VA_ARGS__), <=, max)

/* Define			probe arg min.		                                                                */
#define PROBE_ARG_MIN(min, ...)	                                                                        \
    PROBE_WHAT_X(VA_ARGS_ARG_NUM(__VA_ARGS__), >=, min)

/* Define			function-like.										                                */
#define FUNCTION_LIKE(...)                                                                              \
    do {                                                                                                \
        __VA_ARGS__;                                                                                    \
    } while (0)

/* Define			get the index-th arg of the va_arg.				                                    */
#define VA_ARGS_ARG(index, ...)                                                                         \
    VA_ARGS_ARG ## index LEFTBRACKET __VA_ARGS__)

/* Define			get the number of the va_arg, the range between 0 and 6.		                    */
#define VA_ARGS_ARG_NUM(...)                                                                            \
	VA_ARGS_ARG LEFTBRACKET                                                                             \
        7, __VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)

/* Define			get the args of the va_arg from first to last.				                        */
#define VA_ARGS_ARGS_FROM(first, ...)                                                                   \
    VA_ARGS_ARGS_FROM ## first LEFTBRACKET __VA_ARGS__)

/* Define			get the arg1 of the va_arg.							                                */
#define VA_ARGS_ARG1(arg1, ...)                                                                         \
    arg1

/* Define			get the arg2 of the va_arg.							                                */
#define VA_ARGS_ARG2(arg1, arg2, ...)                                                                   \
    arg2

/* Define			get the arg3 of the va_arg.							                                */
#define VA_ARGS_ARG3(arg1, arg2, arg3, ...)                                                             \
    arg3

/* Define			get the arg4 of the va_arg.							                                */
#define VA_ARGS_ARG4(arg1, arg2, arg3, arg4, ...)                                                       \
    arg4

/* Define			get the arg5 of the va_arg.							                                */
#define VA_ARGS_ARG5(arg1, arg2, arg3, arg4, arg5, ...)                                                 \
    arg5

/* Define			get the arg6 of the va_arg.							                                */
#define VA_ARGS_ARG6(arg1, arg2, arg3, arg4, arg5, arg6, ...)                                           \
    arg6

/* Define			get the arg7 of the va_arg.							                                */
#define VA_ARGS_ARG7(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...)                                     \
    arg7

/* Define			get the args of the va_arg from 1 to last.				                            */
#define VA_ARGS_ARGS_FROM1(...)                                                                         \
    __VA_ARGS__

/* Define			get the args of the va_arg from 2 to last.				                            */
#define VA_ARGS_ARGS_FROM2(arg1, ...)                                                                   \
    __VA_ARGS__

/* Define			get the args of the va_arg from 3 to last.				                            */
#define VA_ARGS_ARGS_FROM3(arg1, arg2, ...)                                                             \
    __VA_ARGS__

/* Define			get the args of the va_arg from 4 to last.				                            */
#define VA_ARGS_ARGS_FROM4(arg1, arg2, arg3, ...)                                                       \
    __VA_ARGS__

/* Define			get the args of the va_arg from 5 to last.				                            */
#define VA_ARGS_ARGS_FROM5(arg1, arg2, arg3, arg4, ...)                                                 \
    __VA_ARGS__

/* Define			get the args of the va_arg from 6 to last.				                            */
#define VA_ARGS_ARGS_FROM6(arg1, arg2, arg3, arg4, arg5, ...)                                           \
    __VA_ARGS__

/* Define			get the args of the va_arg from 7 to last.				                            */
#define VA_ARGS_ARGS_FROM7(arg1, arg2, arg3, arg4, arg5, arg6, ...)                                     \
    __VA_ARGS__

/* Define			get the args of the va_arg from 8 to last.				                            */
#define VA_ARGS_ARGS_FROM8(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...)                               \
    __VA_ARGS__

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

#endif // !__SELF_DEFINE_MICRO_H