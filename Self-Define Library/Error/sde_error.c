/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "sde_error.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

#define ERROR_CFG_DEBUG_EN																				\
	0u

#define ERROR_CFG_STRING_HEAD																			\
	"\r\n""sde.error."

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
 * @brief This type is the error structure.
 */

struct error_s {
	struct error_code_s {
		errno_t *table_ptr;

		size_t index;
	}code_table;

	struct error_string_s {
		struct error_string_message_unit_s {
			char *message_ptr;
			size_t code;
			char *file_ptr;
			size_t line;
		}message_unit;

		const char *const format_ptr;

		char *string_ptr;

		size_t length;

		struct error_string_fault_s {
			const char *const out_of_menory_ptr;
		}fault;
	}string;

	struct error_cache_s {
		char *cache_ptr;

		size_t length;
	}cache;

	struct error_label_s {
		bool longjmp;

		jmp_buf jmp_buf[10];
	}label;
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
 * @brief This variable is the default error code table.
 */

errno_t error_code_table[] = {
	0
};

/**
 * @brief This variable is the error structure.
 */

struct error_s error = {
	.code_table.table_ptr = error_code_table,
	.string.format_ptr = ERROR_CFG_STRING_HEAD
		"error occured:\r\n    "
		"String: \"%s\"\r\n    "
		"Code: %d\r\n    "
		"File: \"%s\"\r\n    "
		"Line: %d\r\n",
	.string.fault.out_of_menory_ptr = ERROR_CFG_STRING_HEAD
		"fault:\r\n    "
		"out of memory\r\n",
};

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

void error_control_string_message_unit_modify(char *message,
											  size_t code,
											  char *file,
											  size_t line);

void error_control_cache_modify(char symbol);

char *error_control_cache_inquire(size_t length);

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
error_control_code_table_index_modify(char index)
{
	ASSERT_VARIABLE(index, >= , int, 0);

	error.code_table.index = index;
}

extern inline size_t
error_control_code_table_index_inquire(void)
{
	return error.code_table.index;
}

extern inline errno_t
error_control_code_inquire(void)
{
	return *(error.code_table.table_ptr + error.code_table.index);
}

void error_control_string_modify(char *message,
								 size_t code,
								 char *file,
								 size_t line)
{
	error_control_string_message_unit_modify(message, code, file, line);

	error.string.length = strlen(error.string.format_ptr);
	error.string.length += code / 10 + 1;
	error.string.length += strlen(file);
	error.string.length += line / 10 + 1;

	if (NULL != message) {
		error.string.length += strlen(message);
	}

	error_control_cache_modify('\0');
}

char *error_control_string_inquire(void)
{
	error.string.string_ptr = error_control_cache_inquire(error.string.length);			/* Inquire the cache */

	if (NULL == error.string.string_ptr) {
		error.string.string_ptr = (char *)error.string.fault.out_of_menory_ptr;
	} else {
		if (NULL == error.string.message_unit.message_ptr) {
			errno_t code = error_control_code_inquire();
			error.string.message_unit.message_ptr = strerror(code);
		}

		if (error.string.message_unit.code) {
			sprintf(error.string.string_ptr,
					error.string.format_ptr,
					error.string.message_unit.message_ptr,
					error.string.message_unit.code,
					error.string.message_unit.file_ptr,
					error.string.message_unit.line);
		}
	}

	return error.string.string_ptr;
}

extern inline jmp_buf
*error_control_label_inquire(size_t index)
{
	ASSERT_VARIABLE(index, > , int, 0);

#if ERROR_CFG_DEBUG_EN

	printf("%s().index: %d\r\n", __FUNCTION__, index);

#endif // ERROR_CFG_DEBUG_EN

	return &error.label.jmp_buf[index - 1];
}

extern inline int
error_control_label_longjmp_modify(int value)
{
	return error.label.longjmp = value;
}

extern inline bool
error_control_label_longjmp_inquire(void)
{
	return error.label.longjmp;
}

extern inline void
error_control_nest(struct error_nest_unit_s nest_unit)
{
	error.code_table.table_ptr = nest_unit.code_table_ptr;

	error.label.longjmp = false;
}

static inline void
error_control_string_message_unit_modify(char *message,
										 size_t code,
										 char *file,
										 size_t line)
{
	error.string.message_unit.message_ptr = message;
	error.string.message_unit.code = code;
	error.string.message_unit.file_ptr = file;
	error.string.message_unit.line = line;
}

static inline void
error_control_cache_modify(char symbol)
{
	if (NULL != error.cache.cache_ptr) {
		memset(error.cache.cache_ptr, symbol, error.cache.length);
	}
}

static inline char
*error_control_cache_inquire(size_t length)
{
	if (error.cache.length < length) {
		if (error.cache.cache_ptr) {
			free(error.cache.cache_ptr);
		}

		error.cache.cache_ptr = calloc(1, length + 1);

		error.cache.length = length;
	}

	return error.cache.cache_ptr;
}