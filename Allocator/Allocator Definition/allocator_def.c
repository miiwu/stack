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

void *allocator_function_address_table_set[2] = {
	#ifdef __CONCEPT_ALLOCATOR_H

	& concept_allocator_function_address_table,

	#else

	NULL,

	#endif // __CONCEPT_ALLOCATOR_H
	#ifdef __CONCEPT_ALLOCATOR_H

	& concept_allocator_function_address_table,

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
	return allocator_function_address_table_set[type];
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

	#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

	printf("allocator.destroy:memory free status : %d \r\n", (*allocator)->info.size);

	if (0 < (*allocator)->info.size) {
		printf("\r\n-----------------------------------stack trace string table begin-----------------------------------\r\n");
		STACK_BACK_TRACE_TYPEDEF_PPTR stack_back_trace_tmp = malloc(sizeof(void *));
		if (NULL == stack_back_trace_tmp) {
			return;
		}

		debug_capture_stack_back_trace_link_get_trace_ptr((*allocator)->capture_stack_back_trace_link, stack_back_trace_tmp);

		printf("\r\n-----------------------------------stack trace mark string table begin-----------------------------------\r\n");
		debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 0));

		printf("\r\n-----------------------------------stack trace link string table begin-----------------------------------\r\n");
		debug_capture_stack_back_trace_convert_to_string(*(stack_back_trace_tmp + 1));

		printf("\r\n-----------------------------------stack trace string table end-----------------------------------\r\n");
	}

	debug_capture_stack_back_trace_link_destroy(&(*allocator)->capture_stack_back_trace_link);

	#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

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
 * @brief This function will be called when the allocator exception of lack of memory.
 *
 * @param void
 *
 * @return void
 */

void allocator_control_exception_default_lack_of_memory(struct allocator_s *allocator)
{
	printf("allocator_control.exception.lack_of_memory! \r\n");
}