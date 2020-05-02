/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_error.h"

#include "debug_assert.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

#define DEBUG_ERROR_CFG_DEBUG_EN										0u

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
 * @brief This type is the debug error control error string structure.
 */

struct debug_error_s {
	struct debug_error_table_s {
		errno_t *table_ptr;

		char index;
	} table;

	struct debug_error_string_s {
		char *header_ptr;

		char *body_ptr;

		char *cache_ptr;
	} string;
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
 * @brief This variable is the debug error control error string structure.
 */

struct debug_error_s debug_error_control_error;

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

void debug_error_control_error_string_cache_modify(char *cache);

void *debug_error_control_error_string_cache_inquire(void);

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

extern inline void
debug_error_control_error_table_modify(errno_t *error_table)
{
	DEBUG_ASSERT_CONTROL_POINTER(error_table);

	debug_error_control_error.table.table_ptr = error_table;
}

extern inline void
debug_error_control_error_table_index_modify(char index)
{
	DEBUG_ASSERT_CONTROL_VARIABLE(index, >= , int, 0);

	debug_error_control_error.table.index = index;
}

extern inline errno_t
debug_error_control_error_inquire(void)
{
	return *(debug_error_control_error.table.table_ptr + debug_error_control_error.table.index);
}

extern inline char
debug_error_control_error_table_index_inquire(void)
{
	return debug_error_control_error.table.index;
}

extern inline void
debug_error_control_error_string_header_modify(char *string)
{
	debug_error_control_error.string.header_ptr = string;
}

void debug_error_control_error_string_modify(char *string)
{
	if (NULL != string
		&& NULL != debug_error_control_error.string.header_ptr) {
		size_t length = 0;
		static size_t length_max;

		length += strlen(debug_error_control_error.string.header_ptr);						/* Calculate the length of the error string */
		length += strlen(string);

		if (length_max < length) {
			debug_error_control_error.string.body_ptr = calloc(1, length + 1);

			#if DEBUG_ERROR_CFG_DEBUG_EN

			printf("debug_error.error.string.modify._cache_modify():%p\r\n",
				   debug_error_control_error.string.body_ptr);

			#endif // DEBUG_ERROR_CFG_DEBUG_EN

			debug_error_control_error_string_cache_modify(debug_error_control_error.string.body_ptr);
																							/* Modify the cache of error string */

			length_max = length;
		} else {
			debug_error_control_error.string.body_ptr
				= debug_error_control_error_string_cache_inquire();							/* Inquire the cache of error string */

			memset(debug_error_control_error.string.body_ptr, '\0', length_max);

			#if DEBUG_ERROR_CFG_DEBUG_EN

			printf("debug_error.error.string.modify._cache_inquire():%p\r\n",
				   debug_error_control_error.string.body_ptr);

			#endif // DEBUG_ERROR_CFG_DEBUG_EN
		}

		strcat(debug_error_control_error.string.body_ptr,
			   debug_error_control_error.string.header_ptr);
		strcat(debug_error_control_error.string.body_ptr, string);

		return;
	}

	debug_error_control_error.string.body_ptr = string;
}

char *debug_error_control_error_string_inquire(void)
{
	if (NULL == debug_error_control_error.string.body_ptr) {
		if (NULL == debug_error_control_error.string.header_ptr) {
			static errno_t error;
			static char *string;

			if (0u == (error = debug_error_control_error_inquire())) {
				debug_error_control_error.string.body_ptr =
					"_INIT() not appoint error code correctly "
					"or _JUMP() not appoint error string"
					",but try to _LOG()!";
			} else {
				debug_error_control_error.string.body_ptr =
					strerror(error);
			}
		} else {
			if (NULL == debug_error_control_error.string.body_ptr) {
				debug_error_control_error.string.body_ptr =
					"_JUMP() not appoint error string"
					",but have called _STRING_HEADER()!";
			}
		}
	}

	return debug_error_control_error.string.body_ptr;
}

static inline void
debug_error_control_error_string_cache_modify(char *cache)
{
	DEBUG_ASSERT_CONTROL_POINTER(cache);

	if (NULL != debug_error_control_error.string.cache_ptr) {
		#if DEBUG_ERROR_CFG_DEBUG_EN

		printf("debug_error.error.string.cache.modify.free():cache:%p .cache:%p\r\n",
			   cache, debug_error_control_error.string.body_cache_ptr);

		#endif // DEBUG_ERROR_CFG_DEBUG_EN

		free(debug_error_control_error.string.cache_ptr);
	}

	debug_error_control_error.string.cache_ptr = cache;
}

static inline void *
debug_error_control_error_string_cache_inquire(void)
{
	return debug_error_control_error.string.cache_ptr;
}