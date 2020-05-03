/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "allocator_pte_def.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/* Configure    if enable allocator stack back trace file string.										*/
#define ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FILE_EN										0u

/* Configure    allocator stack back trace string format.												*/
#define ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FORMAT													\
	"func: %-75s file: %s line: %d \r\n"

#if (!ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FILE_EN)

#undef ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FORMAT
#define ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FORMAT													\
	"func: %-75s\r\n"

#endif // (ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FILE_EN)

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

void *allocator_function_address_table_set[] = {
	#ifdef __CONCEPT_ALLOCATOR_H

	& concept_allocator_control_function_address_table,

	#else

	NULL,

	#endif // __CONCEPT_ALLOCATOR_H
	#ifdef __CONCEPT_ALLOCATOR_H

	& concept_allocator_control_function_address_table,

	#else

	NULL,

	#endif // __CONCEPT_ALLOCATOR_H
};

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will be called when the allocator exception of lack of memory.
 *
 * @param void
 *
 * @return void
 */

void allocator_control_exception_default_lack_of_memory(struct allocator_s *allocator);

#if (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

/**
 * @brief This function will log the stack back trace link when destroy allocator struct.
 *
 * @param void
 *
 * @return the error code
 */

errno_t allocator_control_configuration_destroy_stack_back_trace_log(struct allocator_s *allocator);

#endif // (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

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

/**
 * @brief This function will return the function address table of the specified allocator.
 *
 * @param type the type of the allocator
 *
 * @return the function address table of the specified allocator
 */

extern inline struct allocator_control_s
*allocator_control_get_function_address_table(enum allocator_type_e type)
{
	DEBUG_ASSERT_CONTROL_VARIABLE(type, >= , int, 0);

	return allocator_function_address_table_set[type];
}

/**
 * @brief This function will initialize the allocator struct.
 *
 * @param allocator the pointer of allocator address
 * @param type the type of the allocator
 *
 * @return the error code
 */

extern inline errno_t
allocator_control_configuration_init(struct allocator_s **allocator,
									 enum allocator_type_e type,
									 struct allocator_memory_manage_init_package_s package)
{
	DEBUG_ASSERT_CONTROL_POINTER(allocator);
	DEBUG_ASSERT_CONTROL_VARIABLE(type, >= , int, 0);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(5, -1, -2, 1, 2, 3);
	DEBUG_ERROR_CONTROL_STRING_HEADER("allocator_control.configuration.init.error.");

	static struct allocator_exception_s exception = { NULL };

	if (NULL == ((*allocator)
				 = calloc(1,																/* Allocate the allocator structure */
						  sizeof(struct allocator_s)))) {
		DEBUG_ERROR_CONTROL_JUMP(1, "calloc():allocator block");
	}

	if (0 != package.memory_manage_length
		&& NULL == ((*allocator)->memory_manage_unit.memory_manage_ptr
					= calloc(1,																/* Allocate the allocator memory manage structure */
							 package.memory_manage_length))) {
		DEBUG_ERROR_CONTROL_JUMP(2, "calloc():memory manage block");
	}

	if (NULL != package.memory_manage_ptr
		&& NULL == memcpy((*allocator)->memory_manage_unit.memory_manage_ptr,
						  package.memory_manage_ptr,
						  package.memory_manage_length)) {
		DEBUG_ERROR_CONTROL_JUMP(3, "memcpy():package.memory_manage fail");
	}

	(*allocator)->allocator_type_id = type;
	(*allocator)->info.match = 0u;
	(*allocator)->memory_manage_unit.control = package.control;

	allocator_control_configuration_exception((*allocator),									/* Default the exception of the allocator */
											  exception);

	#if (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	if (debug_capture_stack_back_trace_init(&(*allocator)->stack_back_trace_package			/* Initialize the memory manage stack back trace package */
											.allocate_ptr, 256)) {
		DEBUG_ERROR_CONTROL_JUMP(4, "debug_capture_stack_back_trace_init():allocate_ptr fail");
	}

	if (debug_capture_stack_back_trace_init(&(*allocator)->stack_back_trace_package			/* Initialize the memory manage stack back trace package */
											.deallocate_ptr, 256)) {
		DEBUG_ERROR_CONTROL_JUMP(5, "debug_capture_stack_back_trace_init():deallocate_ptr fail");
	}

	#endif

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param
 *
 * @return NONE
 */

errno_t allocator_control_configuration_destroy(struct allocator_s **allocator)
{
	DEBUG_ASSERT_CONTROL_POINTER(allocator);
	DEBUG_ASSERT_CONTROL_POINTER(*allocator);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(3, 1, 2, 3);
	DEBUG_ERROR_CONTROL_STRING_HEADER("allocator_control.configuration.destroy.error.");

	#if (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	printf("allocator_control.destroy:memory free status : %d \r\n", (*allocator)->info.match);

	if ((int)0 != (int)(*allocator)->info.match
		&& allocator_control_configuration_destroy_stack_back_trace_log((*allocator))) {
		DEBUG_ERROR_CONTROL_JUMP(1, "_stack_back_trace_log():fail");
	}

	if (debug_capture_stack_back_trace_destroy(&(*allocator)->stack_back_trace_package		/* Destroy the memory manage stack back trace package */
											   .allocate_ptr)) {
		DEBUG_ERROR_CONTROL_JUMP(2, "_stack_back_trace_destroy():allocate_ptr fail");
	}

	if (debug_capture_stack_back_trace_destroy(&(*allocator)->stack_back_trace_package		/* Destroy the memory manage stack back trace package */
											   .deallocate_ptr)) {
		DEBUG_ERROR_CONTROL_JUMP(3, "_stack_back_trace_destroy():deallocate_ptr fail");
	}

	#endif // (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	free((*allocator));																	    /* Deallocate the allocator structure */

	(*allocator) = NULL;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will config the exception of the allocator.
 *
 * @param
 *
 * @return NONE
 */

errno_t allocator_control_configuration_exception(struct allocator_s *allocator,
												  struct allocator_exception_s exception)
{
	DEBUG_ASSERT_CONTROL_POINTER(allocator);

	if (NULL == exception.lack_of_memory) {
		allocator->exception.lack_of_memory = allocator_control_exception_default_lack_of_memory;
	} else {
		allocator->exception.lack_of_memory = exception.lack_of_memory;
	}

	return 0;
}

/**
 * @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
 *			malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).
 *
 * @param allocator the pointer of allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return return the pointer point to the uninitialized storage which allocated
 */

void *allocator_control_allocate(struct allocator_s *allocator,
								 size_t count, size_t size)
{
	DEBUG_ASSERT_CONTROL_POINTER(allocator);
	DEBUG_ASSERT_CONTROL_VARIABLE(count, > , int, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE(size, > , int, 0);

	DEBUG_ERROR_CONTROL_INIT(void *, 3, 1);
	DEBUG_ERROR_CONTROL_STRING_HEADER("allocator_control.allocate.error.");
	
	#if (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	if (debug_capture_stack_back_trace(allocator->stack_back_trace_package.					/* Trace and store the stack when the allocate() is called */
									   allocate_ptr, 1)) {
		DEBUG_ERROR_CONTROL_JUMP(1,"_stack_back_trace():fail");
	}

	#endif // (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	if (NULL == (DEBUG_ERROR_CONTROL_RETURN_VAL
				 = allocator->memory_manage_unit.control
				 .allocate(allocator->memory_manage_unit.memory_manage_ptr                  /* Allocate the memory block by the memory manage unit */
						   , count, size))) {
		allocator->exception.lack_of_memory(allocator);                                     /* Enter exception */

		DEBUG_ERROR_CONTROL_JUMP(2, "memory_manage_control.allocate():fail");
	}

	allocator->info.match += 1;

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will deallocates the storage referenced by the pointer block,
 *			which must be a pointer obtained by an earlier call to allocate().
 *
 * @param allocator the pointer of allocator
 * @param block the pointer of block
 *
 * @return NONE
 */

errno_t allocator_control_deallocate(struct allocator_s *allocator,
									 void *block)
{
	DEBUG_ASSERT_CONTROL_POINTER(allocator);
	DEBUG_ASSERT_CONTROL_POINTER(block);

	DEBUG_ERROR_CONTROL_ERRNO_INIT(2, 1, 2);
	DEBUG_ERROR_CONTROL_STRING_HEADER("allocator_control.deallocate.error.");

	allocator->info.match -= 1;

	#if (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	if (debug_capture_stack_back_trace(allocator->stack_back_trace_package.					/* Trace and store the stack when the deallocate() is called */
									   deallocate_ptr, 1)) {
		DEBUG_ERROR_CONTROL_JUMP(1, "_stack_back_trace(): fail");
	}

	#endif // (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

	if (allocator->memory_manage_unit.control
		.deallocate(allocator->memory_manage_unit.memory_manage_ptr,						/* Deallocate the memory block by the memory manage unit */
					block)) {
		DEBUG_ERROR_CONTROL_JUMP(2, "memory_manage_control.deallocate():fail");
	}

	DEBUG_ERROR_CONTROL_LOG_EXIT();
}

/**
 * @brief This function will be called when the allocator exception of lack of memory.
 *
 * @param void
 *
 * @return void
 */

void allocator_control_exception_default_lack_of_memory(struct allocator_s *allocator)
{
	printf("allocator_control.exception.lack_of_memory! \r\n");

	while (true) {
	}
}

#if (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)

/**
 * @brief This function will log the stack back trace link when destroy allocator struct.
 *
 * @param void
 *
 * @return the error code
 */

errno_t allocator_control_configuration_destroy_stack_back_trace_log(struct allocator_s *allocator)
{
	DEBUG_ASSERT_CONTROL_POINTER(allocator);

	printf("\r\n----------------------------------- allocator.stack_back_trace_log -----------------------------------\r\n");

	static struct stack_back_trace_string_package_s string_package;
	static struct stack_back_trace_count_package_s count_package;
	static stack_back_trace_stp stack_back_trace_ptr;
	static size_t type_count;
	static bool log_twice;

	log_twice = false;
	do {
		type_count = 0;
		do {
			stack_back_trace_ptr															/* Calculate the address of the stack_back_trace_ptr by the log_twice */
				= *((stack_back_trace_stpp)&allocator->stack_back_trace_package + log_twice);
			count_package																	/* Get the count package of the stack_back_trace_ptr */
				= debug_capture_stack_back_trace_get_count_package(stack_back_trace_ptr);

			if (count_package.type_count > type_count) {
				printf("\r\nallocator.stack_back_trace.log.%s #%d/%d \r\n",
					   (!log_twice) ? "allocate" : "deallocate",
					   type_count + 1, count_package.type_count);

				string_package																/* Convert the stack_back_trace_ptr to string */
					= debug_capture_stack_back_trace_convert_to_string(stack_back_trace_ptr,
																	   type_count);

				for (size_t ct = 0; ct < string_package.frames; ct++) {
					#if (ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FILE_EN)

					printf(ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FORMAT,
						   (string_package.string + ct)->name_ptr,
						   (string_package.string + ct)->file_name_ptr,
						   (string_package.string + ct)->file_line);

					#else

					printf(ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FORMAT,
						   (string_package.string + ct)->name_ptr);

					#endif // (ALLOCATOR_CFG_STACK_BACK_TRACE_STRING_FILE_EN)
				}
			}
		} while (count_package.type_count > ++type_count);
	} while (!(log_twice++));

	printf("\r\n----------------------------------- allocator.stack_back_trace_log end -----------------------------------\r\n");

	return 0;
}

#endif // (ALLOCATOR_GLOBAL_CFG_STACK_BACK_TRACE_EN)