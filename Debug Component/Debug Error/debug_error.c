/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_error.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                           LOCAL CONSTANTS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                          LOCAL DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            LOCAL TABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This variable is the debug error control error pointer.
 */

errno_t *debug_error_control_error_ptr;

/**
 * @brief This variable is the debug error control error string.
 */

char *debug_error_control_error_string;

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

extern inline errno_t
debug_error_control_error_inquire(void)
{
	if (NULL == debug_error_control_error_ptr) {
		while (1) {
		}
	}

	return *debug_error_control_error_ptr;
}

extern inline void
debug_error_control_error_modify(errno_t error)
{
	if (NULL == debug_error_control_error_ptr) {
		while (1) {
		}
	}

	*debug_error_control_error_ptr = error;
}

extern inline void
debug_error_control_error_pointer_modify(void *pointer)
{
	assert(NULL != pointer);

	debug_error_control_error_ptr = pointer;
}

extern inline char *
debug_error_control_error_string_inquire(void)
{
	if (NULL == debug_error_control_error_string) {
		static errno_t error;

		if (error = debug_error_control_error_inquire()) {
			debug_error_control_error_string = strerror(error);
		}
	}

	return debug_error_control_error_string;
}

extern inline void
debug_error_control_error_string_modify(char *string)
{
	debug_error_control_error_string = string;
}