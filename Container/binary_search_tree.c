/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "binary_search_tree.h"

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
 * @brief This struct is the binary search tree chain node link structure module.
 */

struct binary_search_tree_chain_node_link_s {
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
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_switch_control(struct tree_family_s *tree);

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_match_rule(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node,
											 void *data);

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_recursion_rule(struct tree_family_s *tree,
												 struct tree_family_chain_node_s **node,
												 void *data);

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_insert_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data);

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_delete_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the red-black tree's environment.
 */

struct tree_family_control_environment_s binary_search_tree_control_environment = {
	TREE_FAMILY_2D_NODE_TYPE,
	{
		binary_search_tree_control_search_match_rule,
		binary_search_tree_control_search_recursion_rule,
		binary_search_tree_control_insert_rule,
		binary_search_tree_control_delete_rule
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

void binary_search_tree_control_configuration_init(struct tree_family_s **tree,
												   container_size_t element_size,
												   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(tree, binary_search_tree_control_switch_control, 2, TREE_FAMILY_RED_BLACK_TREE,
										   BINARY_SEARCH_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_switch_control(struct tree_family_s *tree)
{
	tree_family_control_get_control(binary_search_tree_control_environment);
}

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_match_rule(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node,
											 void *data)
{
	assert(tree);
	assert(node);
	assert(data);

	container_size_t location = 0;

	for (; location < tree->info.degree - 1; location++) {
		if (NULL != *((void **)node->data + location) &&
			compare_control_equal(data, *((void **)node->data + location), tree->info.mem_size)) {
			goto EXIT;
		}
	}

	location = SEARCH_CODE_NO_SUCH_ELEMENT;

EXIT:

	#if (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	printf("search.match rule:node:%p Data ",
		   node);

	for (size_t cnt = 0; cnt < tree->info.degree - 1; cnt++) {
		printf("No.%d:\"%s\"-%p ", cnt, (char *)*((void **)node->data + cnt), *((void **)node->data + cnt));
	}

	printf("-->match:%p location:%d\r\n", (0xff != location) ? *((void **)node->data + location) : NULL, location);

	#endif // (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	return location;
}

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_recursion_rule(struct tree_family_s *tree,
												 struct tree_family_chain_node_s **node,
												 void *data)
{
	assert(tree);
	assert(node);
	assert(*node);
	assert(data);

	container_size_t evaluation_level = LINK_OPERATOR_CODE_CHILD_FAR_LEFT;

	for (; evaluation_level < tree->info.degree; evaluation_level++) {
		if ((NULL == *((void **)(*node)->data + evaluation_level - 1) ||				/* If the data of this evaluation_level is NULL,the previous would the far right one */
			(NULL != *((void **)(*node)->data + evaluation_level - 1) &&				/* If the data of this evaluation_level isn't NULL,and the data is lesser than the data of this evaluation_level */
			 compare_control_lesser(data, *((void **)(*node)->data + evaluation_level - 1),
									tree->info.mem_size)))) {
			goto EXIT;
		}
	}

	evaluation_level = tree->info.degree;												/* the id of link far right */

EXIT:

	#if (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	printf("search.recursion rule:(*node):%p Link ",
		(*node));

	for (size_t cnt = 1; cnt <= tree->info.degree; cnt++) {
		printf("No.%d:%p ", cnt, *((void **)(*node)->link + cnt));
	}

	printf("-->next:%p evaluation_level:%d\r\n", *((void **)(*node)->link + evaluation_level), evaluation_level);

	#endif // (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	*node = *((void **)(*node)->link + evaluation_level);								/* Recursion to it's child */

	return evaluation_level;
}

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_insert_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data)
{
	assert(tree);
	assert(data);

	void
		*data_operator = search_return.node_prev->data,
		*link_operatpr = search_return.node_prev->link;

	struct tree_family_chain_node_s *node = tree_family_control_init_node(tree);
	void *data_cpy = tree->allocator_ctrl->allocate(tree->allocator, 1, tree->info.mem_size);

	if (NULL == data_cpy) {
		return;
	}

	memcpy(data_cpy, data, tree->info.mem_size);

	*((void **)node->data) = data_cpy;
	*((void **)node->link) = search_return.node_prev;

	struct tree_family_chain_node_s *node_current = 0;

	if (tree->info.degree <= search_return.estimate) {
		*((void **)link_operatpr + 2) = node;
	} else {
		*((void **)link_operatpr + 1) = node;
	}
}

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_delete_rule(struct tree_family_s *tree,
											struct tree_family_search_node_return_s search_return,
											void *data)
{
}