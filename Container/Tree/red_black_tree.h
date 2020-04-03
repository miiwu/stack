/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __RED_BLACK_TREE_H
#define __RED_BLACK_TREE_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "binary_search_tree.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define RED_BLACK_TREE_CFG_ALLOCATOR_TYPE								    CONCEPT_ALLOCATOR

/* Configure    if enable integrated structure.                                                         */
#define RED_BLACK_TREE_CFG_INTEGRATED_STRUCTURE_MODE_EN					1u

/* Configure    if enable debug mode.																	*/
#define RED_BLACK_TREE_CFG_DEBUG_EN											1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the binary search tree typedef.
 */

typedef tree_family_stp
red_black_tree_stp,
*red_black_tree_stpp;

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the red_black_tree struct
 *
 * @param red_black_tree the pointer to the red_black_tree struct pointer
 * @param element_size the element memory size of the red_black_tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void red_black_tree_control_configuration_init(red_black_tree_stpp red_black_tree,
											   container_size_t element_size,
											   generic_type_element_assign_t assign,
											   generic_type_element_free_t free);

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

#endif // !__RED_BLACK_TREE_H