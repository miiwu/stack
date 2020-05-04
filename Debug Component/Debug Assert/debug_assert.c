/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_assert.h"

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
 * @brief This type is the debug assert control error string structure.
 */

struct debug_assert_control_error_string_s {
	char *string_ptr;

	char *cache_ptr;
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
 * @brief This variable is the debug assert control error string structure.
 */

struct debug_assert_control_error_string_s debug_assert_control_error_string;

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

void debug_assert_control_error_string_modify(char *expression,
											  char *function,
											  char *file,
											  size_t line)
{
	const char *format = "Assert Failed: \"%s\"\r\n    "
		"Func:\"%s\"\r\n    "
		"File:\"%s\"\r\n    "
		"Line:%ld\r\n";

	size_t length = 55;
	static size_t length_max;

	length += strlen(expression);
	length += strlen(function);
	length += strlen(file);
	length += line / 10 + 1;

	if (length_max < length) {
		debug_assert_control_error_string.string_ptr = calloc(1, length + 1);
		debug_assert_control_error_string.cache_ptr = debug_assert_control_error_string.string_ptr;

		length_max = length;
	} else {
		debug_assert_control_error_string.string_ptr = debug_assert_control_error_string.cache_ptr;
	}

	if (NULL == debug_assert_control_error_string.string_ptr) {
		debug_assert_control_error_string.string_ptr =
			"Assert Failed: "
			"no more space for generating error string";
	} else {
		sprintf_s(debug_assert_control_error_string.string_ptr, length,
				  format, expression, function, file, line);
	}
}

extern inline char *
debug_assert_control_error_string_inquire(void)
{
	return debug_assert_control_error_string.string_ptr;
}