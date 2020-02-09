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
#define TWO_THREE_TREE_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define TWO_THREE_TREE_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/* Configure    if enable integrated structure.                                                         */
#define TWO_THREE_TREE_CFG_DEBUG_EN					                        1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    red-black-tree type.																	*/
typedef struct tree_family_s
*TWO_THREE_TREE_TYPEDEF_PTR,
**TWO_THREE_TREE_TYPEDEF_PPTR;;

/**
 * @brief This struct is the binary tree link node structure module.
 */

enum two_three_tree_search_node_node_location_e {
	TWO_THREE_TREE_SEARCH_LOCATION_LEFT,

	TWO_THREE_TREE_SEARCH_LOCATION_RIGHT,

	TWO_THREE_TREE_SEARCH_LOCATION_NONE = 0xff,
};

typedef struct two_three_tree_chain_node_data_s *TWO_THREE_TREE_CHAIN_NODE_DATA_PTR;

typedef struct two_three_tree_chain_node_link_s *TWO_THREE_TREE_CHAIN_NODE_LINK_PTR;

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

void two_three_tree_control_configuration_init(TWO_THREE_TREE_TYPEDEF_PPTR tree,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

struct tree_family_search_node_return_s two_three_tree_control_search(TWO_THREE_TREE_TYPEDEF_PTR tree,
	void *key);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void two_three_tree_control_insert(TWO_THREE_TREE_TYPEDEF_PTR tree,
								   void *data);

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