/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ERROR_H
#define __ERROR_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "sde_assert.h"

#include "sde_log.h"

#include <errno.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configuration    config the code of no error.									                    */
#define ERROR_CFG_NOERROR                                                                                \
    0u

/* Configuration    config enable log or not when _EXIT().									            */
#define ERROR_CFG_LOG_EN                                                                                \
    1u

/* Define			error control init.										                            */
#define ERROR_CONTROL_INIT(return_type, count, ...)                                                     \
    _ERROR_CONTROL_NEST_(ERROR_CONTROL_INIT);                                                           \
    error_control_code_table_modify(count + 1, ERROR_CFG_NOERROR, __VA_ARGS__);                          \
    _ERROR_CONTROL_VARIABLE_RETURN_(return_type);                                                       \
    _ERROR_CONTROL_SET_(0, NULL)

/* Define			error control trap.										                            */
#define ERROR_CONTROL_TRAP(trap, index, ...)                                                            \
    do {                                                                                                \
	    if ((trap)                                                                                      \
            /* The 1st priority, if it's result is 1, enter                                         */  \
            || ERROR_CFG_NOERROR != error_control_code_inquire()                                         \
            /* The 2st priority                                                                     */  \
            || error_control_label_longjmp_modify(                                                      \
                setjmp(*error_control_label_inquire(index)))) {                                         \
            /* The 3st priority, this won't be called when error occurs                             */  \
            if(!error_control_label_longjmp_inquire()) {                                                \
            /* If enter not because longjmp()                                                       */  \
                _ERROR_CONTROL_NEST_(ERROR_CONTROL_TRAP);                                               \
                _ERROR_CONTROL_SET_ LEFTBRACKET                                                         \
                    index, VA_ARGS_ARG(                                                                 \
                        2, NULL, __VA_ARGS__, NULL));                                                   \
            }                                                                                           \
	        VA_ARGS_FROM(                                                                               \
		        2, __VA_ARGS__, NULL, NULL);                                                            \
            _ERROR_CONTROL_JUMP_(index);                                                                \
            /* The args from the 2st to the last will execute                                       */  \
	    }                                                                                               \
    } while (0)

/* Define			error control judge.										                        */
#define ERROR_CONTROL_JUDGE(index, ...)                                                                 \
    do {                                                                                                \
        ERROR_CONTROL_TRAP(0, index, __VA_ARGS__);                                                      \
    } while (0)

/* Define			error control exit.										                            */
#define ERROR_CONTROL_EXIT(...)                                                                         \
    _ERROR_CONTROL_EXIT_(ERROR_CONTROL_RETURN, __VA_ARGS__)

/* Define			error control at fault.										                        */
#define ERROR_CONTROL_AT_FAULT(before_loop)                                                             \
    do {                                                                                                \
        error_control_fault_before_loop(before_loop);                                                   \
    } while (0)

/* Define			error control return.										                        */
#define ERROR_CONTROL_RETURN                                                                            \
    (error_control_return)

/* Define			error control code.										                            */
#define ERROR_CONTROL_CODE()                                                                            \
    (error_control_code_inquire())

/* Define			error control string.										                        */
#define ERROR_CONTROL_STRING()                                                                          \
    (error_control_string_inquire())

/* Define			error control shortcut.										                        */
#define ERR(shortcut, ...)                                                                              \
    SHORTCUTS(ERROR_CONTROL_, shortcut, __VA_ARGS__)

/* Define			error control void init.										                    */
#define ERROR_CONTROL_VOID_INIT(count, ...)                                                             \
    ERROR_CONTROL_INIT(, count, __VA_ARGS__)

/* Define			error control errno init.										                    */
#define ERROR_CONTROL_ERRNO_INIT(count, ...)                                                            \
    ERROR_CONTROL_INIT(errno_t, count, __VA_ARGS__)

/* Define			error control structure init.										                */
#define ERROR_CONTROL_STRUCTURE_INIT(return_type, count, ...)                                           \
    ERROR_CONTROL_INIT(return_type, count, __VA_ARGS__)

/* Define			error control pointer init.										                    */
#define ERROR_CONTROL_POINTER_INIT(count, ...)                                                          \
    ERROR_CONTROL_INIT(void *, count, __VA_ARGS__)

/* Define			error control void exit.										                    */
#define ERROR_CONTROL_VOID_EXIT(...)                                                                    \
    _ERROR_CONTROL_EXIT_(, __VA_ARGS__)

/* Define			error control single error.										                    */
#define ERROR_CONTROL_SINGLE_ERROR(return_type, error_code, expression, ...)                            \
    ERROR_CONTROL_INIT(return_type, 2, 0, error_code);                                                  \
    expression;                                                                                         \
    ERROR_CONTROL_JUDGE(1, __VA_ARGS__)

/* Define			error control variable.										                        */
#define _ERROR_CONTROL_VARIABLE_(...)	                                                                \
	VA_ARGS_ARG LEFTBRACKET                                                                             \
		1, __VA_ARGS__, NULL)

/* Define			error control variable return.										                */
#define _ERROR_CONTROL_VARIABLE_RETURN_(...)	                                                        \
	VA_ARGS_ARG LEFTBRACKET		                                                                        \
		2, __VA_ARGS__,                                                                                 \
        _ERROR_CONTROL_VARIABLE_(__VA_ARGS__ ERROR_CONTROL_RETURN = { 0 }),                             \
        _ERROR_CONTROL_VARIABLE_())

/* Define			error control set.										                            */
#define _ERROR_CONTROL_SET_(index, ...)                                                                 \
    do {                                                                                                \
        error_control_code_table_index_modify(index);                                                   \
        error_control_string_modify(                                                                    \
            VA_ARGS_ARG LEFTBRACKET                                                                     \
                2, NULL, __VA_ARGS__, NULL),                                                            \
            error_control_code_inquire(),                                                               \
            __FUNCTION__, __FILE__, __LINE__);                                                          \
    } while (0)

/* Define			error control jump.										                            */
#define _ERROR_CONTROL_JUMP_(index)                                                                     \
    do {                                                                                                \
        if (index - 1) {                                                                                \
            longjmp(*error_control_label_inquire(index - 1), 0);                                        \
        } else {                                                                                        \
            goto ERROR_CONTROL_LABEL_EXIT;                                                              \
        }                                                                                               \
    } while (0)

/* Define			error control log.										                            */
#if ERROR_CFG_LOG_EN

#define _ERROR_CONTROL_LOG_()                                                                           \
    do {                                                                                                \
        if (0u != error_control_code_table_index_inquire()) {                                           \
            LOG(error_control_string_inquire());                                                        \
		}                                                                                               \
    } while (0)

#else

#define _ERROR_CONTROL_LOG_()

#endif // ERROR_CFG_LOG_EN

/* Define			error control exit.										                            */
#define _ERROR_CONTROL_EXIT_(variable, ...)                                                             \
    do {                                                                                                \
        ERROR_CONTROL_LABEL_EXIT:                                                                       \
	        __VA_ARGS__;                                                                                \
            _ERROR_CONTROL_LOG_();	                                                                    \
            _ERROR_CONTROL_NEST_(ERROR_CONTROL_EXIT);                                                   \
            return variable;                                                                            \
    } while (0)

#define _ERROR_CONTROL_NEST_(type)                                                                      \
    do {                                                                                                \
        error_control_nest(type);                                                                       \
    } while (0)

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the error control type enum.
 */

enum error_control_type_e {
	ERROR_CONTROL_INIT,
	ERROR_CONTROL_TRAP,
	ERROR_CONTROL_EXIT,
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

void error_control_code_table_index_modify(size_t index);

size_t error_control_code_table_index_inquire(void);

void error_control_code_table_modify(size_t count, ...);

errno_t error_control_code_inquire(void);

void error_control_string_modify(char *message,
								 size_t code,
								 char *function,
								 char *file,
								 size_t line);

char *error_control_string_inquire(void);

jmp_buf *error_control_label_inquire(size_t index);

int error_control_label_longjmp_modify(int value);

bool error_control_label_longjmp_inquire(void);

void error_control_nest(enum error_control_type_e control_type);

void error_control_fault_before_loop(void (*before_loop)(void));

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

#endif // !__ERROR_H