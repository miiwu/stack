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
 * @brief This type is the debug error structure.
 */

struct debug_error_s {
	struct debug_error_nest_unit_s;

	char table_index;

	char *string_cache_ptr;
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
 * @brief This variable is the debug error structure.
 */

struct debug_error_s debug_error;

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
debug_error_control_error_table_modify(struct debug_error_nest_unit_s *nest_unit,
									   errno_t *error_table)
{
	DEBUG_ASSERT_CONTROL_POINTER(error_table);

	if (NULL == nest_unit) {
		nest_unit = (struct debug_error_nest_unit_s *) & debug_error;
	}

	nest_unit->error_table_ptr = error_table;
}

extern inline void
debug_error_control_error_table_index_modify(char index)
{
	DEBUG_ASSERT_CONTROL_VARIABLE(index, >= , int, 0);

	debug_error.table_index = index;
}

extern inline errno_t
debug_error_control_error_inquire(void)
{
	return *(debug_error.error_table_ptr + debug_error.table_index);
}

extern inline char
debug_error_control_error_table_index_inquire(void)
{
	return debug_error.table_index;
}

void debug_error_control_error_string_modify(struct debug_error_nest_unit_s *nest_unit,
											 char *string)
{
	if (NULL != string) {
		static size_t length_max;

		size_t length = strlen(string);														/* Calculate the length of the error string */

		if (length_max < length) {
			nest_unit->error_string_ptr = calloc(1, length + 1);

			#if DEBUG_ERROR_CFG_DEBUG_EN

			printf("debug_error.error.string.modify._cache_modify():%p\r\n",
				   nest_unit->error_string_ptr);

			#endif // DEBUG_ERROR_CFG_DEBUG_EN

			debug_error_control_error_string_cache_modify(nest_unit->error_string_ptr);		/* Modify the cache of error string */

			length_max = length;
		} else {
			nest_unit->error_string_ptr
				= debug_error_control_error_string_cache_inquire();							/* Inquire the cache of error string */

			memset(nest_unit->error_string_ptr, '\0', length_max);

			#if DEBUG_ERROR_CFG_DEBUG_EN

			printf("debug_error.error.string.modify._cache_inquire():%p\r\n",
				   nest_unit->error_string_ptr);

			#endif // DEBUG_ERROR_CFG_DEBUG_EN
		}

		strcat(nest_unit->error_string_ptr, string);

		return;
	}

	nest_unit->error_string_ptr = string;
}

char *debug_error_control_error_string_inquire(void)
{
	if (NULL == debug_error.error_string_ptr) {
		errno_t error = debug_error_control_error_inquire();
		debug_error.error_string_ptr =
			strerror(error);
	}

	return debug_error.error_string_ptr;
}

static inline void
debug_error_control_error_string_cache_modify(char *cache)
{
	DEBUG_ASSERT_CONTROL_POINTER(cache);

	if (NULL != debug_error.string_cache_ptr) {
		#if DEBUG_ERROR_CFG_DEBUG_EN

		printf("debug_error.error.string.cache.modify.free():cache:%p .cache:%p\r\n",
			   cache, debug_error.string.body_cache_ptr);

		#endif // DEBUG_ERROR_CFG_DEBUG_EN

		free(debug_error.string_cache_ptr);
	}

	debug_error.string_cache_ptr = cache;
}

static inline void *
debug_error_control_error_string_cache_inquire(void)
{
	return debug_error.string_cache_ptr;
}

extern inline void
debug_error_control_nest(struct debug_error_nest_unit_s nest_unit)
{
	*((struct debug_error_nest_unit_s *) & debug_error) = nest_unit;
}