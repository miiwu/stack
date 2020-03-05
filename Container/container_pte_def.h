/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_PRIVITE_DEFINITION_H
#define __CONTAINER_PRIVITE_DEFINITION_H

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

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This struct is the array_family structure module
 */

struct container_s {
	/* @brief This variables will record the identity code of container type.							*/
	enum container_type_e container_type_id;

	/* @brief This variables will record the common information of the container.						*/
	struct container_common_information_s info;

	/* @brief This variables will record the element handler of the container.							*/
	struct container_generic_type_element_handler_s element_handler;

	/* @brief This variables will record the common exception of the container.							*/
	struct container_common_exception_s exception;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_control_ptr;

	/* @brief This variables will point to the allocator.												*/
	void *allocator_ptr;

	/* @brief This variables will point to the address of the element.									*/
	void *element_ptr;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	char *addon[0];
};

/**
 * @brief This struct is the array_family structure module
 */

struct container_family_s {
	/* @brief This variables will record the identity code of container type.							*/
	enum container_type_e container_type_id;

	/* @brief This variables will record the common information of the container.						*/
	struct container_common_information_s info;

	/* @brief This variables will record the element handler of the container.							*/
	struct container_generic_type_element_handler_s element_handler;

	/* @brief This variables will record the common exception of the container.							*/
	struct container_common_exception_s exception;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_control_ptr;

	/* @brief This variables will point to the allocator.												*/
	void *allocator_ptr;

	/* @brief This variables will point to the address of the element.									*/
	void *element_ptr;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	container_family_switch_control switch_control;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	char *addon[0];
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

#endif // !__CONTAINER_PRIVITE_DEFINITION_H