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

#include <setjmp.h>

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configuration    error configuration the logger of _LOG().									        */
#define ERROR_CFG_LOGGER                                                                                \
    printf

/* Define			error control shortcut.										                        */
#define ERR(shortcut, ...)                                                                              \
    SHORTCUTS(ERROR_CONTROL_, shortcut, __VA_ARGS__)

/* Define			error control return.										                        */
#define ERROR_CONTROL_RETURN                                                                            \
    (error_control_return)

/* Define			error control init.										                            */
#define ERROR_CONTROL_INIT(return_type, count, code, ...)                                               \
    static const errno_t error_control_code_table[count] = { code, __VA_ARGS__ };                       \
    struct error_nest_unit_s error_control_nest_unit = {                                                \
        .code_table_ptr = (void *)&error_control_code_table,                                            \
    };                                                                                                  \
    return_type ERROR_CONTROL_RETURN = { 0 };                                                           \
    _ERROR_CONTROL_SET_(0, NULL)

/* Define			error control trap.										                            */
#define ERROR_CONTROL_TRAP(trap, index, ...)                                                            \
    do {                                                                                                \
	    if ((trap)                                                                                      \
            /* The 1st priority, if it's result is 1, enter                                         */  \
            || error_control_code_table[0] != error_control_code_inquire()                              \
            /* The 2st priority                                                                     */  \
            || error_control_label_longjmp_modify(                                                      \
                setjmp(*error_control_label_inquire(index)))) {                                         \
            /* The 3st priority, this won't be called when error occurs                             */  \
            if(!error_control_label_longjmp_inquire()) {                                                \
            /* If reach not because longjmp()                                                       */  \
                _ERROR_CONTROL_SET_ LEFTBRACKET                                                         \
                    index, VA_ARGS_ARG(                                                                 \
                        2, NULL, __VA_ARGS__, NULL));                                                   \
            }                                                                                           \
	        VA_ARGS_ARGS_FROM(                                                                          \
		        2, __VA_ARGS__, NULL, NULL);                                                            \
            _ERROR_CONTROL_JUMP_(index);                                                                \
            /* The args from the 2st to the last will execute                                       */  \
	    }                                                                                               \
    } while (0)

/* Define			error control judge.										                        */
#define ERROR_CONTROL_JUDGE(index, ...)                                                                 \
    do {                                                                                                \
        ERROR_CONTROL_TRAP LEFTBRACKET                                                                  \
            0, index, __VA_ARGS__);                                                                     \
    } while (0)

/* Define			error control exit.										                            */
#define ERROR_CONTROL_EXIT(...)                                                                         \
    do {                                                                                                \
        ERROR_CONTROL_LABEL_EXIT:                                                                       \
	        __VA_ARGS__;                                                                                \
            return ERROR_CONTROL_RETURN;                                                                \
    } while (0)

/* Define			error control code.										                            */
#define ERROR_CONTROL_CODE()                                                                            \
    (error_control_code_inquire())

/* Define			error control string.										                        */
#define ERROR_CONTROL_STRING()                                                                          \
    (error_control_string_inquire())

/* Define			error control log.										                            */
#define ERROR_CONTROL_LOG(...)                                                                          \
    do {                                                                                                \
        PROBE_ARG_MAX(1, __VA_ARGS__);                                                                  \
        if (0u != error_control_code_table_index_inquire()) {                                           \
            VA_ARGS_ARG(                                                                                \
                2, printf, __VA_ARGS__, ERROR_CFG_LOGGER)(                                              \
                    error_control_string_inquire());                                                    \
		}                                                                                               \
    } while (0)

/* Define			error control errno init.										                    */
#define ERROR_CONTROL_ERRNO_INIT(count, ...)                                                            \
    ERROR_CONTROL_INIT(errno_t, count + 1, 0, __VA_ARGS__)

/* Define			error control structure init.										                */
#define ERROR_CONTROL_STRUCTURE_INIT(return_type, count, ...)                                           \
    ERROR_CONTROL_INIT(return_type, count + 1, 0, __VA_ARGS__)

/* Define			error control pointer init.										                    */
#define ERROR_CONTROL_POINTER_INIT(count, ...)                                                          \
    ERROR_CONTROL_INIT(void *, count + 1, 0, __VA_ARGS__)

/* Define			error control log and exit.										                    */
#define ERROR_CONTROL_LOG_EXIT(...)                                                                     \
    do {                                                                                                \
        ERROR_CONTROL_EXIT LEFTBRACKET                                                                  \
			ERROR_CONTROL_LOG LEFTBRACKET									                            \
				VA_ARGS_ARG(                                                                            \
                    2, printf, __VA_ARGS__, ERROR_CFG_LOGGER));	                                        \
            VA_ARGS_ARGS_FROM(                                                                          \
                2, __VA_ARGS__, NULL, NULL));                                                           \
    } while (0)

/* Define			error control single error.										                    */
#define ERROR_CONTROL_SINGLE_ERROR(return_type, error_code, expression, ...)                            \
    ERROR_CONTROL_INIT(return_type, 2, 0, error_code);                                                  \
    expression;                                                                                         \
    ERROR_CONTROL_JUDGE(1, __VA_ARGS__)

/* Define			error control set.										                            */
#define _ERROR_CONTROL_SET_(index, ...)                                                                 \
    do {                                                                                                \
        error_control_code_table_index_modify(index);                                                   \
        error_control_nest(error_control_nest_unit);                                                    \
        error_control_string_modify(                                                                    \
            VA_ARGS_ARG LEFTBRACKET                                                                     \
                2, NULL, __VA_ARGS__, NULL),                                                            \
            error_control_code_inquire(),                                                               \
            __FILE__, __LINE__);                                                                        \
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

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the error nest unit structure.
 */

struct error_nest_unit_s {
    errno_t *code_table_ptr;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

void error_control_code_table_index_modify(char index);

size_t error_control_code_table_index_inquire(void);

errno_t error_control_code_inquire(void);

void error_control_string_modify(char *message,
                                 size_t code,
                                 char *file,
                                 size_t line);

char *error_control_string_inquire(void);

jmp_buf *error_control_label_inquire(size_t index);

int error_control_label_longjmp_modify(int value);

bool error_control_label_longjmp_inquire(void);

void error_control_nest(struct error_nest_unit_s nest_unit);

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