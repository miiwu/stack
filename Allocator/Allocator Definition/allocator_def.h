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
 * @brief This type is the allocator memory manage control structure.
 */

struct allocator_memory_manage_control_s {
	void *(*allocate)(void *memory_manage, size_t count, size_t size);

	errno_t(*deallocate)(void *memory_manage, void *block);
};

/**
 * @brief This type is the package of the allocator memory manage initialization.
 */

struct allocator_memory_manage_init_package_s {
	struct allocator_memory_manage_control_s control;

	allocator_size_t memory_manage_length;

	void *memory_manage_ptr;
};

/**
 * @brief This type is the allocator control structure.
 */

struct allocator_control_s {
	struct {
		/* @brief This function will initialize the allocator struct.									*/
		errno_t(*init)(struct allocator_s **allocator);

		  /* @brief This function will destroy the allocator struct.								    */
		errno_t(*destroy)(struct allocator_s **allocator);

		/* @brief This function will configure the exceptions of allocator struct.					    */
		errno_t(*exception)(struct allocator_s *allocator,
							struct allocator_exception_s exception);
	}configuration;

	/* @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
			  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).										*/
	void *(*allocate)(struct allocator_s *allocator,
					  allocator_size_t count,
					  allocator_size_t size);

	/* @brief This function will deallocates the storage referenced by the pointer block,
			  which must be a pointer obtained by an earlier call to allocate().						*/
	errno_t(*deallocate)(struct allocator_s *allocator,
						 void *block);
};

/**
 * @brief This type is the unit of the allocator.
 */

struct allocator_unit_s {
	struct allocator_control_s *control_ptr;

	struct allocator_s *allocator_ptr;
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

struct allocator_control_s *allocator_control_get_function_address_table(enum allocator_type_e type);

/**
 * @brief This function will initialize the allocator struct.
 *
 * @param allocator the pointer of allocator address
 * @param type the type of the allocator
 *
 * @return the error code
 */

errno_t
allocator_control_configuration_init(struct allocator_s **allocator,
									 enum allocator_type_e type,
									 struct allocator_memory_manage_init_package_s package);

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
												  struct allocator_exception_s exception);

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
								 size_t count, size_t size);

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
									 void *block);

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