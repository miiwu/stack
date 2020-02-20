/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __TWO_THREE_TREE_H
#define __TWO_THREE_TREE_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "tree_family.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define B_TREE_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define B_TREE_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/* Configure    if enable integrated structure.                                                         */
#define B_TREE_CFG_DEBUG_EN					                        0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This struct is the binary tree link node structure module.
 */

enum b_tree_search_node_node_location_e {
	TWO_THREE_TREE_SEARCH_LOCATION_LEFT,

	TWO_THREE_TREE_SEARCH_LOCATION_RIGHT,

	TWO_THREE_TREE_SEARCH_LOCATION_NONE = 0xff,
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the tree struct
 *
 * @param tree the pointer to the tree struct pointer
 * @param element_size the element memory size of the tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void b_tree_control_configuration_init(struct tree_family_s **tree,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE degree,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									   void (*assign)(void *dst, void *src), void (*free)(void *dst));

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

#endif // !__TWO_THREE_TREE_H