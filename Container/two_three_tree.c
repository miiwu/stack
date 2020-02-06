/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "two_three_tree.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define TWO_THREE_TREE_GET_DATA_FROM_NODE(node)	((void*)(node))

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
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_s {
	void *data;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE hight;

	void *link;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_data_s {
	int left;

	int right;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_link_s {
	struct two_three_tree_chain_node_s *parent;

	struct two_three_tree_chain_node_s *lchild;

	struct two_three_tree_chain_node_s *mchild;

	struct two_three_tree_chain_node_s *rchild;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_four_node_data_s {
	int left;

	int middle;

	int right;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct two_three_tree_chain_node_four_node_link_s {
	void *parent;

	void *lchild;

	void *mlchild;

	void *mrchild;

	void *rchild;
};

/**
 * @brief This enum is the two-three tree node type structure module.
 */

enum two_three_node_type_e {
	TWO_THREE_TREE_TWO_NODE_TYPE,

	TWO_THREE_TREE_THREE_NODE_TYPE,

	TWO_THREE_TREE_NONE_NODE_TYPE
};

/**
 * @brief This enum is the two-three tree transform into four-node type node information pack structure module.
 */

struct two_three_tree_transform_into_four_node_pack_s {
	struct two_three_tree_chain_node_s *node;		/* the four-node inherit from three-node */

	void *data_before_inherit;						/* the data of the previous three-node */
	void *link_before_inherit;						/* the link of the previous three-node */
};

/**
 * @brief This enum is the two-three tree transform into two-node type node information pack structure module.
 */

struct two_three_tree_transform_into_two_node_pack_s {
	void *key;
	struct two_three_tree_chain_node_s *node;

	void *node_left;
	void *node_right;
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

struct two_three_tree_chain_node_four_node_data_s *two_three_tree_control_four_node_data = NULL;
struct two_three_tree_chain_node_four_node_link_s *two_three_tree_control_four_node_link = NULL;

/*
*********************************************************************************************************
*									LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will switch the tree-family control.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_switch_control(void);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *two_three_tree_control_delete_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										 void *key);

/**
 * @brief This function will swap the node at the specified location in the container
 *			by the stable bubble swap algorithm.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void two_three_tree_control_swap_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE dst_pos,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE src_pos);

/**
 * @brief This function will initialize the tree node struct.
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void *two_three_tree_control_init_node(TWO_THREE_TREE_TYPEDEF_PTR tree);

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void two_three_tree_control_destroy_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										 void *node);

/**
 * @brief This function will control two_three_tree_control_search_node()'s match.
 *
 * @param void
 *
 * @return void
 */

enum two_three_tree_search_node_node_location_e
	two_three_tree_control_search_node_match_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
												  void *node,
												  int key);

/**
 * @brief This function will control two_three_tree_control_search_node()'s recursion.
 *
 * @param void
 *
 * @return void
 */

void *two_three_tree_control_search_node_recursion_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
														void *node,
														int key);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

enum two_three_node_type_e which_type_node(struct two_three_tree_chain_node_s *node);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_transform_control_four_node_to_two_node_new_child(void *node,
																	  struct two_three_tree_chain_node_s *four_node,
																	  bool left_child);

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_four_node_pack_s
	two_three_tree_transform_control_three_node_to_four_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
															 struct two_three_tree_transform_into_two_node_pack_s two_node_pack);

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_two_node_pack_s
	two_three_tree_transform_control_four_node_to_two_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
														   struct two_three_tree_transform_into_four_node_pack_s four_node_pack);

/**
 * @brief This function will set the key node into the node.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_node_control_set_data(TWO_THREE_TREE_TYPEDEF_PTR tree,
										  void *node,
										  int key);

/**
 * @brief This function will transform the tree partially.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_partial_transformation(TWO_THREE_TREE_TYPEDEF_PTR tree,
												   void *node,
												   int key);

/**
 * @brief This function will control two_three_tree_control_insert_node()'s insert rule.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_insert_node_insert_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
													void *node,
													int key);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the tree's node operators.
 */

struct binary_tree_family_node_operator_s two_three_tree_control_node_operator = {
	NULL
	//two_three_tree_control_search_node,
	//two_three_tree_control_insert_node,
	//two_three_tree_control_delete_node,
	//two_three_tree_control_swap_node,
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

void two_three_tree_control_configuration_init(TWO_THREE_TREE_TYPEDEF_PPTR tree,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	binary_tree_family_control_configuration_init(tree, two_three_tree_control_switch_control,
												  TWO_THREE_TREE_CFG_ALLOCATOR_TYPE, element_size, assign, free);

	two_three_tree_control_four_node_data = (*tree)->allocator_ctrl->allocate((*tree)->allocator, 1, sizeof(struct two_three_tree_chain_node_four_node_data_s));
	two_three_tree_control_four_node_link = (*tree)->allocator_ctrl->allocate((*tree)->allocator, 1, sizeof(struct two_three_tree_chain_node_four_node_link_s));

	printf("init.four_node.data:%p link:%p \r\n", two_three_tree_control_four_node_data, two_three_tree_control_four_node_link);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_switch_control(void)
{
	binary_tree_family_control_get_control(BINARY_TREE_FAMILY_TWO_THREE_TREE, two_three_tree_control_node_operator);
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

struct two_three_tree_search_node_return_s two_three_tree_control_search_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
	int key)
{
	assert(tree);

	struct two_three_tree_search_node_return_s
		search_return = { TWO_THREE_TREE_SEARCH_LOCATION_NONE };

	struct two_three_tree_chain_node_s
		*node_current = tree->root;

	while (NULL != node_current) {
		search_return.location = two_three_tree_control_search_node_match_rule(tree, node_current, key);

		if (TWO_THREE_TREE_SEARCH_LOCATION_NONE != search_return.location) {
			search_return.node = node_current;

			return search_return;
		}

		search_return.node_prev = node_current;

		node_current = two_three_tree_control_search_node_recursion_rule(tree, node_current, key);
	}

	return search_return;
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

void two_three_tree_control_insert_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										int key)
{
	assert(tree);

	struct two_three_tree_search_node_return_s
		search_return = { 0 };

	printf("\r\n2-3 tree insert start %c \r\n", (int)key + '0');

	search_return = two_three_tree_control_search_node(tree, key);

	if (TWO_THREE_TREE_SEARCH_LOCATION_NONE == search_return.location) {       /* Can't search the node */
		if (NULL == search_return.node_prev) {
			struct two_three_tree_chain_node_s *node = two_three_tree_control_init_node(tree);

			two_three_tree_node_control_set_data(tree, node, key);

			tree->root = node;

			printf("2-3 tree insert root %p \r\n", node);
		} else {
			two_three_tree_control_insert_node_insert_rule(tree, search_return.node_prev, key);
		}
	}

	printf("2-3 tree insert end %c \r\n", (int)key + '0');
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *two_three_tree_control_delete_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										 void *key)
{
	assert(tree);
	assert(key);

	if (NULL == tree->root ||
		NULL == key) {
		return NULL;
	}

	return NULL;
}

/**
 * @brief This function will swap the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void two_three_tree_control_swap_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE lhs_pos,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE rhs_pos)
{
	assert(tree);
}

/**
 * @brief This function will initialize the tree node struct.
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void *two_three_tree_control_init_node(TWO_THREE_TREE_TYPEDEF_PTR tree)
{
	assert(tree);

	struct two_three_tree_chain_node_s
		*node_alloced = tree->allocator_ctrl->allocate(tree->allocator,
													   1, sizeof(struct two_three_tree_chain_node_s));	/* Allocate #1 */

	void *data_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, sizeof(struct two_three_tree_chain_node_data_s));			/* Allocate #2 */

	void *link_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, sizeof(struct two_three_tree_chain_node_link_s));			/* Allocate #3 */

	if (NULL == tree ||																			/* Check if tree point to NULL			*/
		NULL == node_alloced ||																	/* Check if tree node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	node_alloced->data = data_pack_allocated;
	node_alloced->link = link_pack_allocated;

	return node_alloced;
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void two_three_tree_control_destroy_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
										 void *node)
{
	assert(tree);

	if (NULL == node) {
		return;
	}

	void **data_ptr = node;

	tree->allocator_ctrl->deallocate(tree->allocator, *data_ptr, 1);				/* Deallocate #2 */

	tree->allocator_ctrl->deallocate(tree->allocator, node, 1);					/* Deallocate #1 */

	node = NULL;
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void binary_tree_family_control_preorder_traversal(struct binary_tree_family_s *tree,
												   void *node)
{
	assert(tree);

	struct binary_tree_family_link_node_s
		*node_current = node;

	if (NULL == node) {
		return;
	}

	/* printf */
	binary_tree_family_control_preorder_traversal(tree, node_current->lchild);
	binary_tree_family_control_preorder_traversal(tree, node_current->rchild);
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void binary_tree_family_control_inorder_traversal(struct binary_tree_family_s *tree,
												  void *node)
{
	assert(tree);

	struct binary_tree_family_link_node_s
		*node_current = node;

	if (NULL == node) {
		return;
	}

	binary_tree_family_control_inorder_traversal(tree, node_current->lchild);
	/* printf */
	//printf("left:%d right:%d \r\n", );
	binary_tree_family_control_inorder_traversal(tree, node_current->rchild);
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void binary_tree_family_control_posorder_traversal(struct binary_tree_family_s *tree,
												   void *node)
{
	assert(tree);

	struct binary_tree_family_link_node_s
		*node_current = node;

	if (NULL == node) {
		return;
	}

	binary_tree_family_control_inorder_traversal(tree, node_current->lchild);
	binary_tree_family_control_inorder_traversal(tree, node_current->rchild);
	/* printf */
}

/**
 * @brief This function will set the key node into the node.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_node_control_set_data(TWO_THREE_TREE_TYPEDEF_PTR tree,
										  void *node,
										  int key)
{
	struct two_three_tree_chain_node_data_s
		*data = ((struct two_three_tree_chain_node_s *)node)->data;

	if (NULL != data->left) {
		if (key < data->left) {
			data->right = data->left;
			data->left = key;
		} else {
			data->right = key;
		}
	} else if (NULL != data->right) {
		if (key > data->right) {
			data->left = data->right;
			data->right = key;
		} else {
			data->left = key;
		}
	} else {
		data->left = key;
	}

	printf("set data: L:%d R:%d \r\n", data->left, data->right);
}

/**
 * @brief This function will control two_three_tree_control_search_node()'s match.
 *
 * @param void
 *
 * @return void
 */

enum two_three_tree_search_node_node_location_e
	two_three_tree_control_search_node_match_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
												  void *node,
												  int key)
{
	struct two_three_tree_chain_node_data_s
		*data = ((struct two_three_tree_chain_node_s *)node)->data;

	printf("search.match rule: L:%d R:%d node:%p \r\n", data->left, data->right, node);

	if (data->left == key) {
		return TWO_THREE_TREE_SEARCH_LOCATION_LEFT;
	} else if (data->right == key) {
		return TWO_THREE_TREE_SEARCH_LOCATION_RIGHT;
	}

	return TWO_THREE_TREE_SEARCH_LOCATION_NONE;
}

/**
 * @brief This function will control two_three_tree_control_search_node()'s recursion.
 *
 * @param void
 *
 * @return void
 */

void *two_three_tree_control_search_node_recursion_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
														void *node,
														int key)
{
	struct two_three_tree_chain_node_data_s
		*data = ((struct two_three_tree_chain_node_s *)node)->data;

	struct two_three_tree_chain_node_link_s
		*link = ((struct two_three_tree_chain_node_s *)node)->link;

	if (NULL == data->left &&
		NULL == data->right) {
		return NULL;
	}

	if (data->left > key &&
		data->right < key) {
		return link->mchild;
	} else if (data->right > key) {
		return link->lchild;
	} else if (data->left < key) {
		return link->rchild;
	}
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

enum two_three_node_type_e which_type_node(struct two_three_tree_chain_node_s *node)
{
	if (NULL == node) {
		goto EXIT;
	}

	struct two_three_tree_chain_node_data_s
		*data = ((struct two_three_tree_chain_node_s *)node)->data;

	unsigned short node_member = (0 == data->left) + (0 == data->right);

	switch (node_member) {
		case 0:
			return TWO_THREE_TREE_THREE_NODE_TYPE;
		case 1:
			return TWO_THREE_TREE_TWO_NODE_TYPE;
		default:
			goto EXIT;
	}

EXIT:
	return TWO_THREE_TREE_NONE_NODE_TYPE;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_transform_control_four_node_to_two_node_new_child(void *node,
																	  struct two_three_tree_chain_node_s *four_node,
																	  bool left_child)
{
	struct two_three_tree_chain_node_data_s *data = ((struct two_three_tree_chain_node_s *)node)->data;
	struct two_three_tree_chain_node_link_s *link = ((struct two_three_tree_chain_node_s *)node)->link;
	struct two_three_tree_chain_node_four_node_data_s *four_node_data = four_node->data;
	struct two_three_tree_chain_node_four_node_link_s *four_node_link = four_node->link;

	bool is_root_four_node = false;

	if (NULL == four_node_link->parent) {
		link->parent = four_node;

		is_root_four_node = true;
	} else {
		link->parent = four_node_link->parent;
	}

	if (left_child) {
		data->left = four_node_data->left;

		if (is_root_four_node && (
			NULL != four_node_link->lchild ||
			NULL != four_node_link->mlchild)) {
			link->lchild = four_node_link->lchild;
			link->rchild = four_node_link->mlchild;

			if (NULL != four_node_link->lchild) {
				data = ((struct two_three_tree_chain_node_s *)four_node_link->lchild)->data;
				link = ((struct two_three_tree_chain_node_s *)four_node_link->lchild)->link;

				link->parent = node;

				printf("transform 4-node into new 2-node.Left  old node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
					   four_node_link->lchild, data->left, data->right,
					   link->parent, link->lchild, link->rchild);
			}
			if (NULL != four_node_link->mlchild) {
				data = ((struct two_three_tree_chain_node_s *)four_node_link->mlchild)->data;
				link = ((struct two_three_tree_chain_node_s *)four_node_link->mlchild)->link;

				link->parent = node;

				printf("transform 4-node into new 2-node.Middle Left  old node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
					   four_node_link->mlchild, data->left, data->right,
					   link->parent, link->lchild, link->rchild);
			}
		}

		data = ((struct two_three_tree_chain_node_s *)node)->data;
		link = ((struct two_three_tree_chain_node_s *)node)->link;

		printf("transform 4-node into new 2-node.Left  new node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
			   node, data->left, data->right,
			   link->parent, link->lchild, link->rchild);
	} else {
		data->left = four_node_data->right;

		if (is_root_four_node && (
			NULL != four_node_link->mrchild ||
			NULL != four_node_link->rchild)) {
			link->lchild = four_node_link->mrchild;
			link->rchild = four_node_link->rchild;

			if (NULL != four_node_link->mrchild) {
				data = ((struct two_three_tree_chain_node_s *)four_node_link->mrchild)->data;
				link = ((struct two_three_tree_chain_node_s *)four_node_link->mrchild)->link;

				link->parent = node;

				printf("transform 4-node into new 2-node.Middle Right old node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
					   four_node_link->mrchild, data->left, data->right,
					   link->parent, link->lchild, link->rchild);
			}
			if (NULL != four_node_link->rchild) {
				data = ((struct two_three_tree_chain_node_s *)four_node_link->rchild)->data;
				link = ((struct two_three_tree_chain_node_s *)four_node_link->rchild)->link;

				link->parent = node;

				printf("transform 4-node into new 2-node.Right old node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
					   four_node_link->rchild, data->left, data->right,
					   link->parent, link->lchild, link->rchild);
			}
		}

		data = ((struct two_three_tree_chain_node_s *)node)->data;
		link = ((struct two_three_tree_chain_node_s *)node)->link;

		printf("transform 4-node into new 2-node.Right new node:%p DATA.lchild:%d rchild:%d LINK.parent:%p lchild:%p rchild:%p \r\n",
			   node, data->left, data->right,
			   link->parent, link->lchild, link->rchild);
	}
}

/**
 * @brief This function will transform the three-node into four-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_four_node_pack_s
	two_three_tree_transform_control_three_node_to_four_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
															 struct two_three_tree_transform_into_two_node_pack_s two_node_pack)
{
	struct two_three_tree_chain_node_data_s
		*three_node_data = ((struct two_three_tree_chain_node_s *)two_node_pack.node)->data;
	struct two_three_tree_chain_node_link_s
		*three_node_link = ((struct two_three_tree_chain_node_s *)two_node_pack.node)->link;

	struct two_three_tree_transform_into_four_node_pack_s
		four_node_pack = {
		.node = two_node_pack.node,					/* the node shell of the origin 3-node */
		.data_before_inherit = three_node_data,		/* the data address of the origin 3-node */
		.link_before_inherit = three_node_link		/* the link address of the origin 3-node */
	};

	enum four_node_data_location {
		LEFT,
		MIDDLE,
		RIGHT,
	}data_location;

	printf("transform 3-node into 4-node.3-node:%p DATA.left:%d .right:%d LINK.parent:%p root:%p \r\n",
		   two_node_pack.node,
		   three_node_data->left, three_node_data->right,
		   three_node_link->parent, tree->root);

	if (two_node_pack.key < three_node_data->left) {
		two_three_tree_control_four_node_data->left = two_node_pack.key;
		two_three_tree_control_four_node_data->middle = three_node_data->left;
		two_three_tree_control_four_node_data->right = three_node_data->right;

		data_location = LEFT;
	} else if (two_node_pack.key > three_node_data->right) {
		two_three_tree_control_four_node_data->left = three_node_data->left;
		two_three_tree_control_four_node_data->middle = three_node_data->right;
		two_three_tree_control_four_node_data->right = two_node_pack.key;

		data_location = RIGHT;
	} else {
		two_three_tree_control_four_node_data->left = three_node_data->left;
		two_three_tree_control_four_node_data->middle = two_node_pack.key;
		two_three_tree_control_four_node_data->right = three_node_data->right;

		data_location = MIDDLE;
	}

	two_three_tree_control_four_node_link->parent = three_node_link->parent;

	if (NULL != two_node_pack.node_left &&
		NULL != two_node_pack.node_right) {
		switch (data_location) {
			case LEFT:
				two_three_tree_control_four_node_link->lchild = two_node_pack.node_left;
				two_three_tree_control_four_node_link->mlchild = two_node_pack.node_right;
				two_three_tree_control_four_node_link->mrchild = three_node_link->mchild;
				two_three_tree_control_four_node_link->rchild = three_node_link->rchild;
				break;
			case MIDDLE:
				two_three_tree_control_four_node_link->lchild = three_node_link->lchild;
				two_three_tree_control_four_node_link->mlchild = two_node_pack.node_left;
				two_three_tree_control_four_node_link->mrchild = two_node_pack.node_right;
				two_three_tree_control_four_node_link->rchild = three_node_link->rchild;
				break;
			case RIGHT:
				two_three_tree_control_four_node_link->lchild = three_node_link->lchild;
				two_three_tree_control_four_node_link->mlchild = three_node_link->mchild;
				two_three_tree_control_four_node_link->mrchild = two_node_pack.node_left;
				two_three_tree_control_four_node_link->rchild = two_node_pack.node_right;
				break;
			default:
				break;
		}

		printf("transform 3-node into 4-node.4-node:%p LINK.lchild:%p .mlchild:%p .mrchild:%p .rchild:%p \r\n",
			   four_node_pack.node,
			   two_three_tree_control_four_node_link->lchild, two_three_tree_control_four_node_link->mlchild,
			   two_three_tree_control_four_node_link->mrchild, two_three_tree_control_four_node_link->rchild);
	}

	four_node_pack.node->data = two_three_tree_control_four_node_data;
	four_node_pack.node->link = two_three_tree_control_four_node_link;

	printf("transform 3-node into 4-node.4-node:%p DATA.left:%d .middle:%d .right:%d LINK.parent:%p \r\n",
		   four_node_pack.node,
		   two_three_tree_control_four_node_data->left, two_three_tree_control_four_node_data->middle, two_three_tree_control_four_node_data->right,
		   two_three_tree_control_four_node_link->parent);

	return four_node_pack;
}

/**
 * @brief This function will transform the four-node into two-node.
 *
 * @param void
 *
 * @return void
 */

struct two_three_tree_transform_into_two_node_pack_s
	two_three_tree_transform_control_four_node_to_two_node(TWO_THREE_TREE_TYPEDEF_PTR tree,
														   struct two_three_tree_transform_into_four_node_pack_s four_node_pack)
{
	void
		*node_left = two_three_tree_control_init_node(tree),
		*node_right = two_three_tree_control_init_node(tree);

	if (NULL == node_left ||
		NULL == node_right) {
		return;
	}

	struct two_three_tree_chain_node_four_node_data_s
		*four_node_data = four_node_pack.node->data;
	struct two_three_tree_chain_node_four_node_link_s
		*four_node_link = four_node_pack.node->link;

	struct two_three_tree_chain_node_data_s
		*data = four_node_pack.data_before_inherit;
	struct two_three_tree_chain_node_link_s
		*link = four_node_pack.link_before_inherit;

	struct two_three_tree_transform_into_two_node_pack_s two_node_pack = { 0 };

	two_three_tree_transform_control_four_node_to_two_node_new_child(node_left, four_node_pack.node, true);
	two_three_tree_transform_control_four_node_to_two_node_new_child(node_right, four_node_pack.node, false);

	if (NULL == four_node_link->parent) {					/* If the parent of the four-node is NULL,the node will be the root,recycle the origin three-node */
		printf("-----> transform 4-node into 2-node.3-node root \r\n");

		data->left = four_node_data->middle;
		data->right = 0;

		link->lchild = node_left;
		link->rchild = node_right;

		four_node_pack.node->data = data;
		four_node_pack.node->link = link;

		tree->root = four_node_pack.node;

		goto EXIT;
	} else {
		link = ((struct two_three_tree_chain_node_s *)four_node_link->parent)->link;
		data = ((struct two_three_tree_chain_node_s *)four_node_link->parent)->data;

		printf("transform 4-node into 2-node.4-node parent:%p  DATA.left:%d right:%d\r\n",
			   four_node_link->parent, data->left, data->right);

		switch (which_type_node(four_node_link->parent)) {
			case TWO_THREE_TREE_TWO_NODE_TYPE:
				printf("-----> transform 4-node into 2-node.2-node parent \r\n");

				if (four_node_pack.node == link->lchild) {
					link->lchild = node_left;
					link->mchild = node_right;

					data->left = four_node_data->middle;
				} else if (four_node_pack.node == link->rchild) {
					link->mchild = node_left;
					link->rchild = node_right;

					data->right = four_node_data->middle;
				}

				printf("transform 4-node into 2-node.4-node parent:%p  DATA.left:%d right:%d\r\n",
					   four_node_link->parent, data->left, data->right);

				break;
			case TWO_THREE_TREE_THREE_NODE_TYPE:
				printf("-----> transform 4-node into 3-node.3-node parent \r\n");

				two_node_pack.key = four_node_data->middle;
				two_node_pack.node = four_node_link->parent;
				two_node_pack.node_left = node_left;
				two_node_pack.node_right = node_right;

				data = two_node_pack.node->data;
				link = four_node_pack.link_before_inherit;

				break;
			default:
				break;
		}
	}

EXIT:

	return two_node_pack;
}

/**
 * @brief This function will transform the tree partially.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_partial_transformation(TWO_THREE_TREE_TYPEDEF_PTR tree,
												   void *node,
												   int key)
{
	struct two_three_tree_transform_into_four_node_pack_s four_node_pack = { 0 };

	struct two_three_tree_transform_into_two_node_pack_s two_node_pack = { key,node };

	while (0 != two_node_pack.key) {
		struct two_three_tree_chain_node_link_s
			*link = ((struct two_three_tree_chain_node_s *)two_node_pack.node)->link;

		printf("partial transformation:node:%p parent:%p key:%p \r\n", two_node_pack.node, link->parent, two_node_pack.key);

		four_node_pack = two_three_tree_transform_control_three_node_to_four_node(tree, two_node_pack);

		two_node_pack = two_three_tree_transform_control_four_node_to_two_node(tree, four_node_pack);
	}
}

/**
 * @brief This function will control two_three_tree_control_insert_node()'s insert rule.
 *
 * @param void
 *
 * @return void
 */

void two_three_tree_control_insert_node_insert_rule(TWO_THREE_TREE_TYPEDEF_PTR tree,
													void *node,
													int key)
{
	switch (which_type_node(node)) {
		case TWO_THREE_TREE_TWO_NODE_TYPE:

			printf("2-3 tree insert previous node is 2-node \r\n");

			two_three_tree_node_control_set_data(tree, node, key);
			break;
		case TWO_THREE_TREE_THREE_NODE_TYPE:
			two_three_tree_control_partial_transformation(tree, node, key);
			break;
		default:
			break;
	}
}