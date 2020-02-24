/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

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
#define BINARY_SEARCH_TREE_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define BINARY_SEARCH_TREE_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/* Configure    if enable debug mode.																	*/
#define BINARY_SEARCH_TREE_CFG_DEBUG_EN											1u

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
 * @brief This function will initialize the tree struct
 *
 * @param tree the pointer to the tree struct pointer
 * @param element_size the element memory size of the tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void binary_search_tree_control_configuration_init(struct tree_family_s **tree,
												   container_size_t element_size,
												   void (*assign)(void *dst, void *src),
												   void (*free)(void *dst));

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

struct tree_family_control_environment_s
	binary_search_tree_control_get_environment(void);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This struct will record the binary search tree's node operator.
 */

struct tree_family_node_operator_s binary_search_tree_control_node_operator;

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__BINARY_SEARCH_TREE_H