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

/**
 * @brief This function will log the stack back trace link when destroy and clean the allocator struct.
 *
 * @param
 *
 * @return NONE
 */

errno_t allocator_control_configuration_destroy_log(struct allocator_s *allocator);

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
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(type, >= , int, 0);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);

	static struct allocator_exception_s exception = { NULL };

	if (NULL == ((*allocator)
				 = calloc(1,																/* Allocate the allocator structure */
						  sizeof(struct allocator_s)))) {
		return -1;
	}

	if (0 != package.memory_manage_length
		&& NULL == ((*allocator)->memory_manage_unit.memory_manage_ptr
					= calloc(1,																/* Allocate the allocator memory manage structure */
							 package.memory_manage_length))) {
		return -2;
	}

	if (NULL != package.memory_manage_ptr &&
		NULL == memcpy((*allocator)->memory_manage_unit.memory_manage_ptr,
					   package.memory_manage_ptr,
					   package.memory_manage_length)) {
		return 1;
	}

	(*allocator)->allocator_type_id = type;
	(*allocator)->info.match = 0u;
	(*allocator)->memory_manage_unit.control = package.control;

	allocator_control_configuration_exception((*allocator),									/* Default the exception of the allocator */
											  exception);

	#if (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	debug_capture_stack_back_trace_link_init(&(*allocator)->stack_back_trace_link_ptr, 256);

	#endif

	return 0;
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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(*allocator);

	#if (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	printf("allocator.destroy:memory free status : %d \r\n", (*allocator)->info.match);

	if ((int)0 < (int)((*allocator)->info.match)) {
		allocator_control_configuration_destroy_log((*allocator));
	}

	debug_capture_stack_back_trace_link_destroy(&(*allocator)->stack_back_trace_link_ptr);

	#endif // (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	free((*allocator));																	    /* Deallocate the allocator structure */

	(*allocator) = NULL;

	return 0;
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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);

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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(count, > , int, 0);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(size, > , int, 0);

	static void *block_alloced;

	if (NULL == (block_alloced
				 = allocator->memory_manage_unit.control
				 .allocate(allocator->memory_manage_unit.memory_manage_ptr                  /* Allocate the memory block by the memory manage unit */
						   , count, size))) {
		allocator->exception.lack_of_memory(allocator);                                     /* Enter exception */

		return NULL;
	}

	allocator->info.match += 1;

	#if (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	debug_capture_stack_back_trace_link_mark(allocator->stack_back_trace_link_ptr, 1);

	#endif // (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	return block_alloced;
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
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(block);

	allocator->info.match -= 1;

	if (allocator->memory_manage_unit.control
		.deallocate(allocator->memory_manage_unit.memory_manage_ptr,						/* Deallocate the memory block by the memory manage unit */
					block)) {
		return 1;
	}

	#if (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	debug_capture_stack_back_trace_link_link(allocator->stack_back_trace_link_ptr, 1);

	#endif // (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

	return 0;
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

/**
 * @brief This function will log the stack back trace link when destroy and clean the allocator struct.
 *
 * @param
 *
 * @return NONE
 */

errno_t allocator_control_configuration_destroy_log(struct allocator_s *allocator)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(allocator);

	printf("\r\n-----------------------------------stack trace string table begin-----------------------------------\r\n");
	stack_back_trace_stpp stack_back_trace_tmp = malloc(sizeof(void *));
	if (NULL == stack_back_trace_tmp) {
		return 1;
	}

	debug_capture_stack_back_trace_link_get_trace_ptr(allocator->stack_back_trace_link_ptr, stack_back_trace_tmp);

	printf("\r\n-----------------------------------stack trace mark string table begin-----------------------------------\r\n");
	debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 0));

	printf("\r\n-----------------------------------stack trace link string table begin-----------------------------------\r\n");
	debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 1));

	printf("\r\n-----------------------------------stack trace string table end-----------------------------------\r\n");

	return 0;
}