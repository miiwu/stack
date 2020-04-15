/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_ADAPOTR_PRIVITE_DEFINITION_H
#define __CONTAINER_ADAPOTR_PRIVITE_DEFINITION_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/**
 * @brief This struct is the container adaptor structure.
 */

struct container_adaptor_s {
	/* @brief RESERVED This variables will record the identity code of container_ptr type.				*/
	enum container_type_e	container_type_id;

	/* @brief This variables will record the allocator unit of the container.							*/
	struct allocator_unit_s allocator_unit;

	/* @brief This variables will point to the function address table of front container_ptr type.		*/
	struct container_control_s *container_control_ptr;

	/* @brief This variables will point to the container_ptr.											*/
	void *container_ptr;

	/* @brief This variables will be a external addon, validity only depends on memory allocation.		*/
	char addon[0];
};

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

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

#endif // !__CONTAINER_ADAPOTR_PRIVITE_DEFINITION_H