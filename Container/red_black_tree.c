/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "red_black_tree.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This enum is the red black tree color structure module.
 */

enum red_black_tree_color_e {
	RED_BLACK_TREE_COLOR_RED,

	RED_BLACK_TREE_COLOR_BLACK
};

/**
 * @brief This struct is the binary tree chain node link structure module.
 */

typedef struct tree_family_chain_node_data_content_s red_black_tree_chain_node_data_st;

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will switch the tree-family control.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_control_switch_control(struct tree_family_s *tree);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the red-black tree's environment.
 */

struct tree_family_control_environment_s red_black_tree_control_environment = {
	TREE_FAMILY_2D_NODE_TYPE,
	{
		NULL,
		//red_black_tree_control_search_match_rule,
		//red_black_tree_control_search_recursion_rule,
		//red_black_tree_control_insert_rule,
		//red_black_tree_control_delete_rule
	}
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
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

void red_black_tree_control_configuration_init(RED_BLACK_TREE_TYPEDEF_PPTR tree,
											   container_size_t element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, red_black_tree_control_switch_control, 2, TREE_FAMILY_RED_BLACK_TREE,
										   RED_BLACK_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_control_switch_control(struct tree_family_s *tree)
{
	tree_family_control_get_control(red_black_tree_control_environment);
}