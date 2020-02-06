/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "avl_tree.h"

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

void avl_tree_control_switch_control(void);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return the node at the specified location in the container
 */

void *avl_tree_control_search_node(AVL_TREE_TYPEDEF_PTR tree,
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

void *avl_tree_control_insert_node(AVL_TREE_TYPEDEF_PTR tree,
								   struct binary_tree_family_link_node_s *node);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *avl_tree_control_delete_node(AVL_TREE_TYPEDEF_PTR tree,
								   struct binary_tree_family_link_node_s *node);

/**
 * @brief This function will swap the node at the specified location in the container
 *			by the stable bubble swap algorithm.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void avl_tree_control_swap_node(AVL_TREE_TYPEDEF_PTR tree,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE dst_pos,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE src_pos);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *avl_tree_control_delete_node_get_successor_part(AVL_TREE_TYPEDEF_PTR tree,
													  struct binary_tree_family_link_node_s *node);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the tree's node operators.
 */

struct binary_tree_family_node_operator_s avl_tree_control_node_operator = {
	NULL
	//avl_tree_control_search_node,
	//avl_tree_control_insert_node,
	//avl_tree_control_delete_node,
	//avl_tree_control_swap_node,
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

void avl_tree_control_configuration_init(AVL_TREE_TYPEDEF_PPTR tree,
										 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
										 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	binary_tree_family_control_configuration_init(tree, avl_tree_control_switch_control,
												  AVL_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void avl_tree_control_switch_control(void)
{
	binary_tree_family_control_get_control(BINARY_TREE_FAMILY_AVL_TREE, avl_tree_control_node_operator);
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *avl_tree_control_search_node(AVL_TREE_TYPEDEF_PTR tree,
								   void *key)
{
	assert(tree);

	struct binary_tree_family_search_node_return_s
		search_return = { NULL };

	struct binary_tree_family_link_node_s
		**node_current = (struct binary_tree_family_link_node_s **) & tree->root;

	void
		*data = (*node_current)->data;

LOOP:

	if (NULL == *node_current ||
		NULL == data) {
		return NULL;
	}

	if (compare_control_equal(data, key, tree->info.mem_size)) {
		search_return.node = *node_current;
		return &search_return;
	}

	search_return.node_prev = *node_current;

	if (compare_control_greater(data, key, tree->info.mem_size)) {       /*  */
		node_current = &(*node_current)->lchild;
		data = (*node_current)->data;
	} else if (compare_control_lesser(data, key, tree->info.mem_size)) {
		node_current = &(*node_current)->rchild;
		data = (*node_current)->data;
	}

	goto LOOP;
}

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void *avl_tree_control_insert_node(AVL_TREE_TYPEDEF_PTR tree,
								   struct binary_tree_family_link_node_s *node)
{
	assert(tree);

	struct binary_tree_family_search_node_return_s
		*search_return = NULL;

	if (NULL == (void *)(search_return = avl_tree_control_search_node(tree, node->data))) {       /* Can't search the node */
		node = binary_tree_family_control_init_node(tree);

		if (NULL == tree->root) {
			tree->root = node;
		} else if (compare_control_greater(search_return->node_prev->data, node->data, tree->info.mem_size)) {       /*  */
			search_return->node_prev->lchild = node;
		} else if (compare_control_lesser(search_return->node_prev->data, node->data, tree->info.mem_size)) {
			search_return->node_prev->rchild = node;
		}
	}

	return node;
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *avl_tree_control_delete_node(AVL_TREE_TYPEDEF_PTR tree,
								   struct binary_tree_family_link_node_s *node)
{
	assert(tree);
	assert(node);

	if (NULL == tree->root ||
		NULL == node) {
		return NULL;
	}

	if (NULL == node->lchild &&
		NULL == node->rchild) {
		if (NULL == node->parent) {                 /* Parent of the node is not valid,it will be the root */
			tree->root = NULL;
		} else {
			if (node->parent->lchild == node) {
				node->parent->lchild = NULL;
			} else if (node->parent->rchild == node) {
				node->parent->rchild = NULL;
			}
		}
	} else if (NULL == node->lchild) {
		if (NULL == node->parent) {                 /* Left child of the node is not valid */
			tree->root = node->rchild;
			node->rchild->parent = tree->root;
		} else {
			node->parent->rchild = node->rchild;
			node->rchild->parent = node->parent;
		}
	} else if (NULL == node->rchild) {
		if (NULL == node->parent) {                 /* Right child of the node is not valid */
			tree->root = node->lchild;
			node->lchild->parent = tree->root;
		} else {
			node->parent->lchild = node->lchild;
			node->lchild->parent = node->parent;
		}
	} else {
		struct binary_tree_family_link_node_s
			*node_successor = avl_tree_control_delete_node_get_successor_part(tree, node);

		if (tree->root == node) {
			tree->root = node_successor;
		} else {
			if (node->parent->lchild == node) {
				node->parent->lchild = node_successor;
			} else if (node->parent->rchild == node) {
				node->parent->rchild = node_successor;
			}
			node_successor->parent = node->parent;
		}

		node_successor->lchild = node->lchild;
	}

	return node;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void avl_tree_control_left_rotate_node(AVL_TREE_TYPEDEF_PTR tree,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(tree);
	assert((0 <= position));
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *avl_tree_control_delete_node_get_successor_part(AVL_TREE_TYPEDEF_PTR tree,
													  struct binary_tree_family_link_node_s *node)
{
	assert(tree);

	struct binary_tree_family_link_node_s
		*node_successor_parent = node,
		*node_successor = node->rchild,
		*node_current = NULL;

	if (NULL != node_successor) {
		node_current = node_successor->lchild;
	}

	while (NULL != node_current) {
		node_successor_parent = node_successor;
		node_successor = node_current;
		node_current = node_current->lchild;
	}

	if (node_successor != node->rchild) {
		node_successor_parent->lchild = node_successor->rchild;
		node_successor->rchild = node->rchild;
	}

	return node_successor;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *avl_tree_control_get_precursor_node(AVL_TREE_TYPEDEF_PTR tree,
										  struct binary_tree_family_link_node_s *node)
{
	assert(tree);

	struct binary_tree_family_link_node_s
		*node_precursor_parent = node,
		*node_precursor = node->lchild,
		*node_current = node->lchild->rchild;

	return node_precursor;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void avl_tree_control_right_rotate_node(AVL_TREE_TYPEDEF_PTR tree,
										CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(tree);
	assert((0 <= position));
}

/**
 * @brief This function will swap the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void avl_tree_control_swap_node(AVL_TREE_TYPEDEF_PTR tree,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE lhs_pos,
								CONTAINER_GLOBAL_CFG_SIZE_TYPE rhs_pos)
{
	assert(tree);
}