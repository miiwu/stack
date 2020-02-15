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

/**
 * @brief This struct is the binary tree chain node link structure module.
 */

struct red_black_tree_chain_node_link_s {
    void *parent;

    void *lchild;

    void *rchild;
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

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

size_t red_black_tree_control_search_match_rule(RED_BLACK_TREE_TYPEDEF_PTR tree,
                                                void *node,
                                                void *data);

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

void *red_black_tree_control_search_recursion_rule(RED_BLACK_TREE_TYPEDEF_PTR tree,
                                                   void *node,
                                                   void *data);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the red-black tree's environment.
 */

struct tree_family_control_environment_s red_black_tree_control_environment = {
    {
        TREE_FAMILY_RED_BLACK_TREE,
        sizeof(red_black_tree_chain_node_data_st),
        sizeof(struct red_black_tree_chain_node_link_s),
        sizeof(red_black_tree_chain_node_data_st) / sizeof(void *),
        sizeof(struct red_black_tree_chain_node_link_s) / sizeof(void *),
    },
    {
        red_black_tree_control_search_match_rule,
        red_black_tree_control_search_recursion_rule,
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
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

    tree_family_control_configuration_init(tree, red_black_tree_control_switch_control, 2,TREE_FAMILY_RED_BLACK_TREE,
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
	tree_family_control_get_control(red_black_tree_control_environment);
}

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

size_t red_black_tree_control_search_match_rule(RED_BLACK_TREE_TYPEDEF_PTR tree,
                                                void *node,
                                                void *data)
{
    assert(tree);

	void *node_data = ((struct tree_family_chain_node_s *)node)->data;

	if (NULL == node_data) {
		goto EXIT;
	}

	#if (RED_BLACK_TREE_CFG_DEBUG_EN)

	printf("search.match rule:node:%p L:%c-%d R:%c-%d \r\n",
		   node,
		   TWO_THREE_TREE_GET_KEY_FROM_NODE(node, left), TWO_THREE_TREE_GET_KEY_FROM_NODE(node, left),
		   TWO_THREE_TREE_GET_KEY_FROM_NODE(node, right), TWO_THREE_TREE_GET_KEY_FROM_NODE(node, right));

	#endif // (RED_BLACK_TREE_CFG_DEBUG_EN)

	if (compare_control_equal(data, node_data, tree->info.mem_size)) {
		return true;
	}

EXIT:

	return false;
}

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

void *red_black_tree_control_search_recursion_rule(RED_BLACK_TREE_TYPEDEF_PTR tree,
                                                   void *node,
                                                   void *data)
{
    assert(tree);

	struct two_three_tree_chain_node_data_s
		*node_data = ((struct tree_family_chain_node_s *)node)->data;

	struct red_black_tree_chain_node_link_s
		*link = ((struct tree_family_chain_node_s *)node)->link;

	if (NULL == node_data) {
		goto EXIT;
	}

    if (compare_control_lesser(data, node_data, tree->info.mem_size)) {
		return link->lchild;
	} else if (compare_control_greater(data, node_data, tree->info.mem_size)) {
		return link->rchild;
	}

EXIT:
	return NULL;
}