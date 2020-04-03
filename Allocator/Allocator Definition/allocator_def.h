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

#include "debug_component.h"

#include "allocator.h"

#include "allocator_cfg.h"

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

/**
 * @brief This type is the allocator type enum.
 */

enum allocator_type_e {
	CONCEPT_ALLOCATOR = 1u,
};

/**
 * @brief This type is the allocator size typedef.
 */

typedef ALLOCATOR_GLOBAL_CFG_SIZE_TYPE allocator_size_t;

/**
 * @brief This type is the allocator information structure.
 */

struct allocator_information_s {
	/* @brief This variables will record the size of allocator allocated.						    */
	allocator_size_t size;
};

/**
 * @brief This type is the allocator exception structure.
 */

struct allocator_exception_s {
	/* @brief This variables will point to the exception handler of lack of memory.			        */
	void (*lack_of_memory)(void *allocator);
};

/**
 * @brief This type is the allocator memory control structure.
 */

struct memory_control_s {
	/* @brief This variables will record which memory block is available by check bit.					*/
	int available[ALLOCATOR_GLOBAL_CFG_MEMORY_POOL_SIZE / sizeof(int) * 8];

	/* @brief This variables will point to the address of memory pool.					                */
	void *memory_pool_ptr;

	/* @brief This variables will point to the next allocate entry point address.					    */
	void *entry_point_ptr;

	/* @brief This variables will record the size of allocator memory pool.						        */
	allocator_size_t memory_pool_size;
};

/**
 * @brief This type is the allocator control structure.
 */

struct allocator_control_s {
	struct {
		/* @brief This function will initialize the allocator struct.									*/
		errno_t(*init)(struct allocator_s **allocator,
					   void (*lack_of_memory)(void));

		  /* @brief This function will destroy the allocator struct.										*/
		errno_t(*destroy)(struct allocator_s **allocator);

		/* @brief This function will configure the exceptions of allocator struct.					    */
		errno_t(*exception)(struct allocator_s *allocator,
							void (*lack_of_memory)(void));
	}configuration;

	/* @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
			  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).										*/
	void *(*allocate)(struct allocator_s *allocator,
					  ALLOCATOR_GLOBAL_CFG_SIZE_TYPE count, ALLOCATOR_GLOBAL_CFG_SIZE_TYPE size);

	/* @brief This function will deallocates the storage referenced by the pointer block,
			  which must be a pointer obtained by an earlier call to allocate().						*/
	errno_t(*deallocate)(struct allocator_s *allocator,
						 void *block, ALLOCATOR_GLOBAL_CFG_SIZE_TYPE count);
};

/**
 * @brief This type is the unit of the allocator.
 */

struct allocator_unit_s {
	struct allocator_control_s *control_ptr;

	void *allocator_ptr;
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will return the function address table of the specified allocator.
 *
 * @param type the type of the allocator
 *
 * @return the function address table of the specified allocator
 */

void *allocator_control_get_function_address_table(enum allocator_type_e type);

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param
 *
 * @return NONE
 */

errno_t allocator_control_configuration_destroy(struct allocator_s **allocator);

/**
 * @brief This function will config the exception of the allocator.
 *
 * @param
 *
 * @return NONE
 */

errno_t allocator_control_configuration_exception(struct allocator_s *allocator,
												  void (*lack_of_memory)(void *));

   /*
   *********************************************************************************************************
   *                                       EXTERN GLOBAL VARIABLES
   *********************************************************************************************************
   */

   /*
   *********************************************************************************************************
   *                                            FUNCTIONS
   *********************************************************************************************************
   */

   /*
   *********************************************************************************************************
   *                                             MODULE END
   *********************************************************************************************************
   */

#endif // !__ALLOCATOR_DEFINITION_H