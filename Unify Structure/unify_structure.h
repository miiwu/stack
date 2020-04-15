/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __UNIFY_STRUCTURE_H
#define __UNIFY_STRUCTURE_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_component.h"

#include "allocator.h"

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
 * @brief This type is the unify structure construct package structure.
 */

struct unify_structure_construct_package_s {
	errno_t error;

	struct allocator_unit_s allocator_unit;
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/**
 * @brief This function will construct the structure and initialize the allocator unit.
 *
 * @param structure the pointer to structure
 * @param package the package of the unify structure allocate
 *
 * @return the construct package
 */

struct unify_structure_construct_package_s
	unify_structure_control_construct(void **structure,
									  enum allocator_type_e allocator_type,
									  size_t structure_mem_size);

/**
 * @brief This function will destruct the structure and destroy the allocator unit.
 *
 * @param structure the pointer to structure
 * @param allocator_unit the package of the unify structure allocator unit
 *
 * @return the error code
 */

errno_t
unify_structure_control_destruct(void **structure,
								 struct allocator_unit_s allocator_unit);

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__UNIFY_STRUCTURE_H