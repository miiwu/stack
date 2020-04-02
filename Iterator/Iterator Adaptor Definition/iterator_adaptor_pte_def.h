/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ITERATOR_ADAPTOR_PRIVITE_DEFINITION_H
#define __ITERATOR_ADAPTOR_PRIVITE_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_adaptor_def.h"

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
 * @brief This type is the iterator adaptor structure.
 */

struct iterator_adaptor_s {
    /* @brief RESERVED This variables will record the identity code of iterator_ptr type.				*/
    enum iterator_type_e iterator_type_id;

    /* @brief This variables will point to the allocator_ptr control.									*/
    struct allocator_control_s *allocator_control_ptr;

    /* @brief This variables will point to the allocator_ptr.											*/
    void *allocator_ptr;

	/* @brief This variables is the unit of the iterator.											    */
    struct iterator_unit_s iterator_unit;

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

#endif // !__ITERATOR_ADAPTOR_PRIVITE_DEFINITION_H