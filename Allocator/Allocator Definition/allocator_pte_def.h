/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ALLOCATOR_PRIVITE_DEFINITION_H
#define __ALLOCATOR_PRIVITE_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "allocator_def.h"

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
 * @brief This type is the allocator structure.
 */

struct allocator_s {
	/* @brief This variables will record the identity code of allocator type.					        */
	enum allocator_type_e allocator_type_id;

	/* @brief This variables will record the information of the allocator.					            */
	struct allocator_information_s info;

	/* @brief This variables will record the exception of the allocator.					            */
	struct allocator_exception_s exception;

	/* @brief This variables will record the addon of the allocator.					                */
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

#endif // !__ALLOCATOR_PRIVITE_DEFINITION_H