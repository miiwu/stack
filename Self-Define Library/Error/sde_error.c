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

#define ERROR_CFG_CACHE_NEST_UNIT_TABLE_GROWTH															\
	1

#define ERROR_CFG_CACHE_STRING_GROWTH																	\
	1

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
 * @brief This type is the error string unit structure.
 */

struct error_string_unit_s {
	size_t length;

	char *content_ptr;
};

/**
 * @brief This type is the error fault unit structure.
 */

struct error_fault_unit_s {
	const char *const string_ptr;
};

/**
 * @brief This type is the error structure.
 */

struct error_s {
	struct error_code_s {
		struct error_code_table_s {
			size_t index;
		}table;
	}code;

	struct error_string_s {
		struct error_string_message_unit_s {
			char *message_ptr;
			size_t code;
			char *function_ptr;
			char *file_ptr;
			size_t line;
		}message_unit;

		const struct error_string_unit_s format;

		struct error_string_unit_s;
	}string;

	struct error_fault_s {
		struct error_fault_unit_s out_of_memory;

		void (*before_loop)(void);
	}fault;

	struct error_label_s {
		bool longjmp;

		jmp_buf jmp_buf[10];
	}label;

	struct error_nest_s {
		size_t frames;

		struct error_nest_unit_s *nest_unit_ptr;
	}nest;

	struct error_cache_s {
		struct error_cache_string_s {
			size_t length;

			char *string_ptr;
		}string;
		struct error_cache_nest_unit_s {
			size_t frames;

			struct error_nest_unit_s **table_ptr;
		}nest_unit;
	}cache;
};

/**
 * @brief This type is the error nest unit structure.
 */

struct error_nest_unit_s {
	struct error_nest_unit_code_table_s {
		size_t count;

		errno_t *table_ptr;
	}code_table;
};

/*
 *********************************************************************************************************
 *                                            LOCAL TABLES
 *********************************************************************************************************
 */

/**
 * @brief This variable is the error nest unit inquire table.
 */

bool error_nest_unit_inquire_table[][3] = {
	{ true, false, false },
	{ true, false, false },
	{ true, true, false }
};

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This variable is the default error code table.
 */

errno_t error_code_table[] = {
	ERROR_CFG_NOERROR
};

/**
 * @brief This variable is the default error code table.
 */

struct error_nest_unit_s error_nest_unit = {
	.code_table.count = 1,
	.code_table.table_ptr = error_code_table,
};

/**
 * @brief This variable is the error structure.
 */

struct error_s error = {
	.string.format.content_ptr = ERROR_CFG_STRING_HEAD
		"error occurs:\r\n    "
		"String: \"%s\"\r\n    "
		"Code: %d\r\n    "
		"Func: \"%s\"\r\n    "
		"File: \"%s\"\r\n    "
		"Line: %d\r\n",
	.string.format.length = 105,
	.fault.out_of_memory.string_ptr = ERROR_CFG_STRING_HEAD
		"fault:\r\n    "
		"out of memory\r\n",
	.nest.nest_unit_ptr = &error_nest_unit,
};

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

char *error_control_cache_string_inquire(size_t length);

struct error_nest_unit_s
	*error_control_cache_nest_unit_table_inquire(size_t index);

void *error_control_cache_inquire(void *table,
								  size_t *table_frames,
								  size_t element_size,
								  size_t frames,
								  size_t growth,
								  bool copy);

void *error_control_nest_unit_code_table_inquire(size_t count);

struct error_nest_unit_s
	*error_control_cache_nest_unit_inquire(size_t index);

void *error_control_fault(struct error_fault_unit_s fault_unit);

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
error_control_code_table_index_modify(size_t index)
{
	ASSERT_VARIABLE(index, >= , int, 0);

	error.code.table.index = index;
}

extern inline size_t
error_control_code_table_index_inquire(void)
{
	return error.code.table.index;
}

extern inline void
error_control_code_table_modify(size_t count, ...)
{
	va_list va_ptr;

	va_start(va_ptr, count);

	errno_t *code_table_ptr
		= error_control_nest_unit_code_table_inquire(count);

	for (size_t i = 0; i < count; i++) {
		code_table_ptr[i] = va_arg(va_ptr, errno_t);
	}

	va_end(va_ptr);
}

extern inline errno_t
error_control_code_inquire(void)
{
	errno_t *code_table_ptr
		= error.nest.nest_unit_ptr->code_table.table_ptr;

	return *(code_table_ptr + error.code.table.index);
}

extern void error_control_string_modify(char *message,
										size_t code,
										char *function,
										char *file,
										size_t line)
{
	error.string.message_unit.message_ptr = message;
	error.string.message_unit.code = code;
	error.string.message_unit.function_ptr = function;
	error.string.message_unit.file_ptr = file;
	error.string.message_unit.line = line;

	error.string.length = error.string.format.length;
	error.string.length += code / 10 + 1;
	error.string.length += strlen(function);
	error.string.length += strlen(file);
	error.string.length += line / 10 + 1;

	if (NULL != message) {
		error.string.length += strlen(message);
	}
}

extern char *error_control_string_inquire(void)
{
	error.string.content_ptr = error_control_cache_string_inquire(error.string.length);			/* Inquire the cache */

	if (NULL == error.string.message_unit.message_ptr) {
		errno_t code = error_control_code_inquire();
		error.string.message_unit.message_ptr = strerror(code);
	}

	if (error.string.message_unit.code) {
		sprintf(error.string.content_ptr,
				error.string.format.content_ptr,
				error.string.message_unit.message_ptr,
				error.string.message_unit.code,
				error.string.message_unit.function_ptr,
				error.string.message_unit.file_ptr,
				error.string.message_unit.line);
	}

	return error.string.content_ptr;
}

extern inline jmp_buf
*error_control_label_inquire(size_t index)
{
	ASSERT_VARIABLE(index, > , int, 0);

#if ERROR_CFG_DEBUG_EN

	LOG_DIAGNOSE("index: %d\r\n",
				 index);

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
error_control_nest(enum error_control_type_e control_type)
{
	static enum error_control_type_e
		last_control_type;

#if ERROR_CFG_DEBUG_EN

	LOG_DIAGNOSE("control type: .now: %d .last: %d \r\n",
				 control_type,
				 last_control_type);

#endif // ERROR_CFG_DEBUG_EN

	switch (control_type) {
		case ERROR_CONTROL_INIT:
			error.nest.frames++;
			error.label.longjmp = false;
			break;
		case ERROR_CONTROL_TRAP:
			break;
		case ERROR_CONTROL_EXIT:
			error.nest.frames--;
			break;
		default:
			break;
	}

	if (error_nest_unit_inquire_table[last_control_type][control_type]) {
		size_t index = 0;

		if (error.nest.frames) {
			index = error.nest.frames - 1;
		}

		error.nest.nest_unit_ptr
			= error_control_cache_nest_unit_inquire(index);

	#if ERROR_CFG_DEBUG_EN

		LOG_DIAGNOSE("_cache_nest_unit_inquire().nest unit : % p.frame : % d\r\n",
					 error.nest.nest_unit_ptr,
					 error.nest.frames);

	#endif // ERROR_CFG_DEBUG_EN
	}

	last_control_type = control_type;
}

static struct error_nest_unit_s
*error_control_cache_nest_unit_table_inquire(size_t index)
{
	return error_control_cache_inquire(&error.cache.nest_unit.table_ptr,
									   &error.cache.nest_unit.frames,
									   sizeof(void *),
									   index,
									   ERROR_CFG_CACHE_NEST_UNIT_TABLE_GROWTH,
									   true);
}

static struct error_nest_unit_s
*error_control_cache_nest_unit_inquire(size_t index)
{
	error_control_cache_nest_unit_table_inquire(index);

	return error_control_cache_inquire(&error.cache.nest_unit.table_ptr[index],
									   NULL,
									   sizeof(struct error_nest_unit_s),
									   0,
									   1,
									   false);
}

static void
*error_control_nest_unit_code_table_inquire(size_t count)
{
	struct error_nest_unit_s *nest_unit_ptr =
		error.nest.nest_unit_ptr;

	return error_control_cache_inquire(&nest_unit_ptr->code_table.table_ptr,
									   &nest_unit_ptr->code_table.count,
									   sizeof(errno_t),
									   count,
									   0,
									   false);
}

static inline char
*error_control_cache_string_inquire(size_t length)
{
	return error_control_cache_inquire(&error.cache.string.string_ptr,
									   &error.cache.string.length,
									   sizeof(char),
									   length,
									   ERROR_CFG_CACHE_STRING_GROWTH,
									   false);
}

static void
*error_control_cache_inquire(void *table,
							 size_t *table_frames,
							 size_t element_size,
							 size_t frames,
							 size_t growth,
							 bool copy)
{
	size_t **table_ptr = table;

	if ((NULL == table_frames && NULL == *table_ptr)
		|| (NULL != table_frames && *table_frames < frames + growth)) {
		void *block = calloc(frames + growth, element_size);

		if (NULL == block) {
			goto FAULT_OUT_OF_MEMORY;
		}

		if ((NULL == table_frames && NULL == *table_ptr)) {
			goto ASSIGN_TABLE;
		}

		if (*table_ptr) {
			if (copy) {
				memcpy(block,
					   *table_ptr,
					   (*table_frames) * element_size);
			}

			free(*table_ptr);
		}

		*table_frames = frames + growth;

	ASSIGN_TABLE:
		*table_ptr = block;
	}

	return *table_ptr;

FAULT_OUT_OF_MEMORY:
	return error_control_fault(error.fault.out_of_memory);
}

extern inline void
error_control_fault_before_loop(void (*before_loop)(void))
{
	error.fault.before_loop = before_loop;
}

static void
*error_control_fault(struct error_fault_unit_s fault_unit)
{
	LOG(fault_unit.string_ptr);

	if (NULL != error.fault.before_loop) {
		error.fault.before_loop();
	}

	while (1);

	return NULL;
}