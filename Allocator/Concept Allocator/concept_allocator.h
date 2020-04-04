/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONCEPT_ALLOCATOR_H
#define __CONCEPT_ALLOCATOR_H

/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/

#include "allocator_def.h"

/*
*********************************************************************************************************
*									        CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure if enable allocator debug control structure.                                               */
#define ALLOCATOR_CFG_DEBUG_MODE_EN			                                    0u

/* Configure if enable integrated structure.                                                            */
#define ALLOCATOR_CFG_INTEGRATED_STRUCTURE_MODE_EN			                    1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the concept allocator structure typedef.
 */

typedef struct allocator_s
*concept_allocator_stp,
**concept_allocator_stpp;

/**
 * @brief This type is the concept allocator control structure.
 */

struct concept_allocator_control_s {
	struct {
		/* @brief This function will initialize the allocator struct.									*/
		errno_t(*init)(concept_allocator_stpp allocator);

		  /* @brief This function will destroy the allocator struct.								    */
		errno_t(*destroy)(concept_allocator_stpp allocator);

		/* @brief This function will configure the exceptions of allocator struct.					    */
		errno_t(*exception)(struct allocator_s *allocator,
							struct allocator_exception_s exception);
	}configuration;

	/* @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
			  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).										*/
	void *(*allocate)(concept_allocator_stp allocator,
					  size_t count, size_t size);

	/* @brief This function will deallocates the storage referenced by the pointer block,
			  which must be a pointer obtained by an earlier call to allocate().						*/
	errno_t(*deallocate)(concept_allocator_stp allocator,
						 void *block);
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the allocator struct.
 *
 * @param allocator the pointer of allocator address
 *
 * @return NONE
 */

errno_t concept_allocator_control_configuration_init(concept_allocator_stpp allocator);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This variable is the concept allocator function address table.
 */

extern void *concept_allocator_control_function_address_table[];

/**
 * @brief This const variable is the concept allocator control structure.
 */

extern const struct concept_allocator_control_s concept_allocator_control;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__CONCEPT_ALLOCATOR_H
