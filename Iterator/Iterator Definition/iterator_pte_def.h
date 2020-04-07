/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ITERATOR_PRIVITE_DEFINITION_H
#define __ITERATOR_PRIVITE_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_def.h"

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
 * @brief This type is the iterator structure
 */

struct iterator_s {
	/* @brief This variables will record the identity code of iterator type.							*/
	enum iterator_type type_id;

	/* @brief This variables will record the iterator common information structure.						*/
	struct iterator_common_information_s info;

	/* @brief This variables will record the allocator unit structure.									*/
	struct allocator_unit_s allocator_unit;

	/* @brief This variables will record the object unit structure.										*/
	struct iterator_object_unit_s object_unit;

	/* @brief This variables will be a external addon, validity only depends on memory allocation.		*/
	char addon[0];
};

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

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

#endif // !__ITERATOR_PRIVITE_DEFINITION_H