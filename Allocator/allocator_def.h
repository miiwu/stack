/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ALLOCATOR_DEFINITION_H
#define __ALLOCATOR_DEFINITION_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <malloc.h>

#include "allocator_cfg.h"

#if (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

#include "debug_component.h"

#endif // (ALLOCATOR_GLOBAL_CFG_DEBUG_COMPONENT_EN)

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure the enum type of allocator.																*/
enum allocator_type_e {
	ALLOCATOR_COMMON = 1u,
};

/**
 * @brief This struct is the allocator structure control module
 */

struct allocator_control_s {
	struct {
		/* @brief This function will initialize the allocator struct.									*/
		errno_t (*init)(void **allocator,
					 void (*lack_of_memory)(void));

		/* @brief This function will destroy the allocator struct.										*/
		void (*destroy)(void **allocator);

		/* @brief This function will configure the exceptions of allocator struct.					    */
		void (*exception)(void **allocator,
						  void (*lack_of_memory)(void));
	}configuration;

	/* @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
			  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).										*/
	void *(*allocate)(void *allocator,
					  ALLOCATOR_GLOBAL_CFG_SIZE_TYPE count, ALLOCATOR_GLOBAL_CFG_SIZE_TYPE size);

	/* @brief This function will deallocates the storage referenced by the pointer block,
			  which must be a pointer obtained by an earlier call to allocate().						*/
	void (*deallocate)(void *allocator,
					   void *block, ALLOCATOR_GLOBAL_CFG_SIZE_TYPE count);
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the container struct and attach to the specified container.
 *
 * @param container the container adapter struct
 *
 * @return the pointer to the specified container function address table.
 */

void *allocator_control_convert_type_to_func_addr_table(enum allocator_type_e type);

/**
 * @brief This function will handle the exception that lack of memory.
 *
 * @param allocator the pointer to allocator
 *
 * @return NONE
 */

void allocator_control_exception_default_lack_of_memory(void *allocator);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

extern void *allocator_common_function_address_tables[];

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the container struct and attach to the specified container.
 *
 * @param container the container adapter struct
 *
 * @return the pointer to the specified container function address table.
 */

inline void *allocator_control_convert_type_to_func_addr_table(enum allocator_type_e type)
{
	void
		*func_addr_table = NULL;

	switch (type) {
		case ALLOCATOR_COMMON:
			func_addr_table = &allocator_common_function_address_tables;
			break;
		default:
			break;
	}

	return func_addr_table;
}

/**
 * @brief This function will handle the exception that lack of memory.
 *
 * @param allocator the pointer to allocator
 *
 * @return NONE
 */

inline void allocator_control_exception_default_lack_of_memory(void *allocator)
{
	assert(allocator);

	printf("allocator.lack of memory \r\n");
}

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ALLOCATOR_DEFINITION_H