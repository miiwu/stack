/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_ADAPTOR_FAMILY_H
#define __CONTAINER_ADAPTOR_FAMILY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container.h"

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

void *container_control_convert_type_to_func_addr_table(enum container_type_e type);

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

/**
 * @brief This function will initialize the container struct and attach to the specified container.
 *
 * @param container the container adapter struct
 *
 * @return the pointer to the specified container function address table.
 */

extern inline void *container_control_convert_type_to_func_addr_table(enum container_type_e type)
{
	void
		*func_addr_table = NULL;

	switch (type) {
		#if (CONTAINER_FAMILY_LEVEL_CFG_BINARY_TREE_EN)

		#endif // (CONTAINER_FAMILY_LEVEL_CFG_BINARY_TREE_EN)

		#if (CONTAINER_FAMILY_LEVEL_CFG_RED_BLACK_TREE_EN)

		#endif // (CONTAINER_FAMILY_LEVEL_CFG_RED_BLACK_TREE_EN)

		#if (CONTAINER_FAMILY_LEVEL_CFG_B_TREE_EN)

		#endif // (CONTAINER_FAMILY_LEVEL_CFG_B_TREE_EN)

		#if (CONTAINER_FAMILY_LEVEL_CFG_ARRAY_EN)

		case ARRAY:
			func_addr_table = &array_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_ARRAY_EN)

			#if (CONTAINER_FAMILY_LEVEL_CFG_VECTOR_EN)

		case VECTOR:
			func_addr_table = &vector_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_VECTOR_EN)

			#if (CONTAINER_FAMILY_LEVEL_CFG_FORWARD_LIST_EN)

		case FORWARD_LIST:
			func_addr_table = &forward_list_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_FORWARD_LIST_EN)

			#if (CONTAINER_FAMILY_LEVEL_CFG_LIST_EN)

		case LIST:
			func_addr_table = &list_function_address_tables;
			break;

			#endif // (CONTAINER_FAMILY_LEVEL_CFG_LIST_EN)
			break;
		default:
			break;
	}

	return func_addr_table;
}

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__CONTAINER_ADAPTOR_FAMILY_H