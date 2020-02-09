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
 * @brief This struct is the red black tree link node structure module.
 */

struct red_black_tree_data_s {
	/* @brief This variables will record the data of the node.										    */
	void *data;

	/* @brief This variables will record the key of the node.										    */
	CONTAINER_GLOBAL_CFG_SIZE_TYPE key;

	/* @brief This variables will record the color of the node.										    */
	enum red_black_tree_color_e color;
};

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

void red_black_tree_control_switch_control(void);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the tree's node operators.
 */

struct tree_family_node_operator_s red_black_tree_control_node_operator = {
    NULL
	//red_black_tree_control_get_node,
	//red_black_tree_control_set_node,
	//red_black_tree_control_del_node,
	//red_black_tree_control_swap_node,
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
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, red_black_tree_control_switch_control, BINARY_TREE_FAMILY_RED_BLACK_TREE,
												  RED_BLACK_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void red_black_tree_control_switch_control(void)
{
	//tree_family_control_get_control(BINARY_TREE_FAMILY_RED_BLACK_TREE, red_black_tree_control_node_operator);
}