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

#include "debug_micro.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Configuration    debug error configuration the logger of _LOG().									    */
#define DEBUG_ERROR_CFG_LOGGER                                                                          \
    printf

/* Configuration    debug error configuration the second arg of _LOG_EXIT().						    */
#define DEBUG_ERROR_CFG_LOG_EXIT_SECOND_ARG                                                             \
    NULL                                                                                    /* TODO:not complete */

/* Define			debug error control return.										                    */
#define DEBUG_ERROR_CONTROL_RETURN_VAL                                                                  \
    (debug_error_control_return)

/* Define			debug error control init.										                    */
#define DEBUG_ERROR_CONTROL_INIT(return_type, count, code, ...)                                         \
    static struct debug_error_nest_unit_s debug_error_control_nest_unit;                                \
    static errno_t debug_error_control_error_table[count] = { code, __VA_ARGS__ };                      \
    static return_type DEBUG_ERROR_CONTROL_RETURN_VAL;                                                  \
    debug_error_control_error_table_modify(                                                             \
        &debug_error_control_nest_unit, debug_error_control_error_table);                               \
    debug_error_control_error_string_header_modify(                                                     \
        &debug_error_control_nest_unit, NULL);                                                          \
    _DEBUG_ERROR_CONTROL_SET_(0)

/* Define			debug error control init.										                    */
#define DEBUG_ERROR_CONTROL_STRING_HEADER(header)                                                       \
    debug_error_control_error_string_header_modify(                                                     \
        &debug_error_control_nest_unit, header)

/* Define			debug error control jump.										                    */
#define DEBUG_ERROR_CONTROL_JUMP(index, ...)                                                            \
    do {                                                                                                \
        DEBUG_MICRO_CONTROL_PROBE_NOT_ZERO(index);                                                      \
	    DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM(                                                          \
		    2, __VA_ARGS__, NULL, NULL);                                                                \
	    _DEBUG_ERROR_CONTROL_SET_(                                                                      \
            index, DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                     \
                2, NULL, __VA_ARGS__, NULL));                                                           \
        debug_error_control_nest(debug_error_control_nest_unit);                                        \
        goto DEBUG_ERROR_CONTROL_EXIT_LABLE;                                                            \
    } while (0)

/* Define			debug error control judge.										                    */
#define DEBUG_ERROR_CONTROL_JUDGE(index, ...)                                                           \
    do {                                                                                                \
	    if (debug_error_control_error_table[0] != debug_error_control_error_inquire()) {                \
	        DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM(                                                      \
		        2, __VA_ARGS__, NULL, NULL);                                                            \
            DEBUG_ERROR_CONTROL_JUMP(                                                                   \
                index, DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                 \
                    2, NULL, __VA_ARGS__, NULL));                                                       \
	    }                                                                                               \
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

/* Define			debug error control error.										                    */
#define DEBUG_ERROR_CONTROL_ERROR_STRING()                                                              \
    (debug_error_control_error_string_inquire())

/* Define			debug error control log.										                    */
#define DEBUG_ERROR_CONTROL_LOG(...)                                                                    \
    do {                                                                                                \
        DEBUG_MICRO_CONTROL_PROBE_ARG_MAX(1, __VA_ARGS__);                                              \
        if ((char)0 != debug_error_control_error_table_index_inquire()) {                               \
            DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                            \
                2, printf, __VA_ARGS__, DEBUG_ERROR_CFG_LOGGER)(                                        \
                    "debug_error.error occur: ");                                                       \
            DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                            \
                2, printf, __VA_ARGS__, DEBUG_ERROR_CFG_LOGGER)(                                        \
                    debug_error_control_error_string_inquire());                                        \
            DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                            \
                2, printf, __VA_ARGS__, DEBUG_ERROR_CFG_LOGGER)(                                        \
                    "\r\n");                                                                            \
		}                                                                                               \
    } while (0)

/* Define			debug error control errno init.										                */
#define DEBUG_ERROR_CONTROL_ERRNO_INIT(count, ...)                                                      \
    DEBUG_ERROR_CONTROL_INIT(errno_t, count + 1, 0, __VA_ARGS__)

/* Define			debug error control structure init.										            */
#define DEBUG_ERROR_CONTROL_STRUCTURE_INIT(return_type, count, ...)                                     \
    DEBUG_ERROR_CONTROL_INIT(return_type, count + 1, 0, __VA_ARGS__)

/* Define			debug error control pointer init.										            */
#define DEBUG_ERROR_CONTROL_POINTER_INIT(count, ...)                                                    \
    DEBUG_ERROR_CONTROL_INIT(void *, count + 1, 0, __VA_ARGS__)

/* Define			debug error control log and exit.										            */
#define DEBUG_ERROR_CONTROL_LOG_EXIT(...)                                                               \
    do {                                                                                                \
        DEBUG_ERROR_CONTROL_EXIT DEBUG_MICRO_CONTROL_LEFTBRACKET                                        \
			DEBUG_ERROR_CONTROL_LOG DEBUG_MICRO_CONTROL_LEFTBRACKET									    \
				DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                        \
                    2, printf, __VA_ARGS__, DEBUG_ERROR_CFG_LOGGER));	                                \
            DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM DEBUG_MICRO_CONTROL_LEFTBRACKET                       \
                2, __VA_ARGS__,                                                                         \
                DEBUG_ERROR_CFG_LOG_EXIT_SECOND_ARG,                                                    \
                DEBUG_ERROR_CFG_LOG_EXIT_SECOND_ARG));                                                  \
    } while (0)

/* Define			debug error control set.										                    */
#define _DEBUG_ERROR_CONTROL_SET_(count, ...)                                                           \
    do {                                                                                                \
        debug_error_control_error_table_index_modify(count);                                            \
        debug_error_control_error_string_modify(                                                        \
            &debug_error_control_nest_unit,                                                             \
            DEBUG_MICRO_CONTROL_VA_ARGS_ARG(                                                            \
                2, NULL, __VA_ARGS__, NULL));                                                           \
    } while (0)

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

struct debug_error_nest_unit_s {
	errno_t *error_table_ptr;

	struct {
		char *header_ptr;

		char *body_ptr;
	} string;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

void debug_error_control_error_table_modify(struct debug_error_nest_unit_s *nest_unit,
											errno_t *error_table);

void debug_error_control_error_table_index_modify(char index);

errno_t debug_error_control_error_inquire(void);

char debug_error_control_error_table_index_inquire(void);

void debug_error_control_error_string_header_modify(struct debug_error_nest_unit_s *nest_unit,
													char *string);

void debug_error_control_error_string_modify(struct debug_error_nest_unit_s *nest_unit,
											 char *string);

char *debug_error_control_error_string_inquire(void);

void debug_error_control_nest(struct debug_error_nest_unit_s nest_unit);

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