/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "sde_assert.h"

#include "sde_log.h"

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

/**
 * @brief This type is the assert error string structure.
 */

struct assert_s {
	struct assert_string_s {
		const char *const format_ptr;

		size_t length;

		char *string_ptr;
	}string;
};

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
 * @brief This variable is the assert error string structure.
 */

struct assert_s assert = {
	.string.format_ptr = "\r\n"
		"sde.assert failed:\r\n    "
		"Expr: \"%s\"\r\n    "
		"Func: \"%s\"\r\n    "
		"File: \"%s\"\r\n    "
		"Line: %zd\r\n",
};

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

void assert_control_string_modify(char *expression,
								  char *function,
								  char *file,
								  size_t line)
{
	assert.string.length = 81;																/* Length of the format */
	assert.string.length += strlen(expression);
	assert.string.length += strlen(function);
	assert.string.length += strlen(file);
	assert.string.length += line / 10 + 1;

	assert.string.string_ptr = calloc(1, assert.string.length + 1);							/* Allocate the memory */

	if (NULL == assert.string.string_ptr) {													/* Format the string */
		assert.string.string_ptr = "\r\n"
			"sde_lib.assert.fault:\r\n    "
			"out of memory";
	} else {
		sprintf(assert.string.string_ptr,
				assert.string.format_ptr,
				expression, function, file, line);
	}
}

extern inline char *
assert_control_string_inquire(void)
{
	return assert.string.string_ptr;
}