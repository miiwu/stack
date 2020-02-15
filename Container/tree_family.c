/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "tree_family.h"

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

/**
 * @brief This variables will record the tree_node_operator.
 */

struct tree_family_control_environment_s tree_family_control_environment = { 0 };

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will return the memory size of the specified tree type node.
 *
 * @param type the specified tree type
 *
 * @return the memory size of the specified node
 */

static size_t tree_family_control_get_node_len(enum tree_family_member_type_e type);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

void *tree_family_sort_algorithm_control_get_data(void *object, size_t loc);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

void tree_family_sort_algorithm_control_swap_data(void *object, size_t lhs, size_t rhs);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool tree_family_node_control_compare_greater(void *lhs, void *rhs, size_t len);

/**
* @brief This function will destroy all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_destroy_posorder_traversal_operator(struct tree_family_s *tree,
															 void *node,
															 size_t data_element_count);

/**
* @brief This function will replace the switch_control() before enter control sandbox.
*
* @param void
*
* @return void
*/

void tree_family_control_switch_control_in_sandbox(void);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will get control of the tree-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

extern inline void tree_family_control_get_control(struct tree_family_control_environment_s environment)
{
	tree_family_control_environment = environment;
}

/**
 * @brief This function will run the func_addr() in sandbox with specified environment.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_in_sandbox(struct tree_family_s *tree,
												struct tree_family_control_environment_s environment,
												void (*func_addr)(void *, ...),
												size_t count_param,
												...)
{
	void *switch_control_tree = tree->switch_control;										/* Store current tree's switch control address */

	tree->switch_control = tree_family_control_switch_control_in_sandbox;

	tree_family_control_environment = environment;

	void *param_func[8] = { NULL };

	va_list va_ptr = NULL;

	va_start(va_ptr, count_param);

	for (size_t cnt = 0; cnt < count_param; cnt++) {
		param_func[cnt] = (void *)va_arg(va_ptr, size_t);
	}

	va_end(va_ptr);

	func_addr(param_func[0], param_func[1], param_func[2], param_func[3],
			  param_func[4], param_func[5], param_func[6], param_func[7]);					/* If the function's parameters are greater than 8,
																								i think you need to split the function into pieces */

	tree->switch_control = switch_control_tree;												/* Recovery current tree's switch control address */
}

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

void tree_family_control_configuration_init(struct tree_family_s **tree,
											void (*switch_control)(void),
											size_t degree,
											enum tree_family_member_type_e member_type,
											enum allocator_type_e allocator_type,
											CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(tree);
	assert(0 <= element_size);

	void
		*allocator = NULL;

	struct allocator_control_s
		*allocator_ctrl = NULL;

	allocator_ctrl = allocator_control_convert_type_to_func_addr_table(allocator_type);	/* Variables pointer to	the function address table of
																							specified container type		*/

	allocator_ctrl->configration.init(&allocator, NULL);

	struct tree_family_s
		*tree_alloced = allocator_ctrl->allocate(allocator,
												 1, sizeof(struct tree_family_s));	/* Allocate #1 */

	if (NULL == tree ||																	/* Check if tree point to NULL			*/
		NULL == tree_alloced) {															/* Check if tree_alloced point to NULL	*/
		return;
	}

	tree_alloced->container_type_id = member_type;										/* Assign tree structure					*/

	tree_alloced->info.max_size = 0;
	tree_alloced->info.size = 0u;
	tree_alloced->info.mem_size = element_size;
	tree_alloced->info.degree = degree;
	tree_alloced->info.minimum_key = (size_t)ceil((float)degree / 2) - 1;

	tree_alloced->allocator = allocator;
	tree_alloced->allocator_ctrl = allocator_ctrl;

	tree_alloced->root = NULL;

	tree_alloced->exception.empty = tree_family_control_configration_exception_default_empty_callback;
	tree_alloced->exception.full = tree_family_control_configration_exception_default_full_callback;

	tree_alloced->switch_control = switch_control;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		tree_alloced->element_handler.assign = assign;
		tree_alloced->element_handler.free = free;
	}

	*tree = tree_alloced;

	#if (TREE_FAMILY_CFG_DEBUG_EN)												/* Debug only								*/

	printf("tree.configuration.init:allocator : %p \r\n", allocator);
	printf("tree.configuration.init:tree block : %p \r\n", tree_alloced);

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the tree struct and free the space
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_configuration_destroy(struct tree_family_s **tree)
{
	assert(tree);

	(*tree)->switch_control();

	void *allocator = (*tree)->allocator;

	struct allocator_control_s *allocator_ctrl = (*tree)->allocator_ctrl;

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("tree.configuration.destroy:tree block : %p \r\n", (*tree));
	printf("tree.configuration.destroy:allocator : %p \r\n", allocator);

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	tree_family_control_posorder_traversal(*tree, (*tree)->root,
										   tree_family_control_destroy_posorder_traversal_operator);

	allocator_ctrl->deallocate(allocator, *tree, 1);																			/* deallocate #1 */

	allocator_ctrl->configration.destroy(&allocator);

	*tree = NULL;
}

/**
 * @brief This function will configure the tree element handler
 *
 * @param tree the pointer to the tree struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_element_handler(struct tree_family_s *tree,
													   void (*assign)(void *dst, void *src), void(*free)(void *dst))
{
	assert(tree);
	assert(assign);
	assert(free);

	tree->element_handler.assign = assign;
	tree->element_handler.free = free;
}

/**
 * @brief This function will configure the tree exception callback
 *
 * @param tree the pointer to the tree struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_exception(struct tree_family_s *tree,
												 void (*empty)(void), void (*full)(void))
{
	assert(tree);

	if (NULL == empty) {
		tree->exception.empty = empty;
	}

	if (NULL == full) {
		tree->exception.full = full;
	}
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

extern inline tree_family_search_node_return_st
tree_family_control_search(struct tree_family_s *tree, void *data)
{
	assert(tree);

	tree->switch_control();

	tree_family_search_node_return_st search_return = { 0xff };

	struct tree_family_chain_node_s *node_current = tree->root;

	while (NULL != node_current) {
		search_return.location = tree_family_control_environment.node_operator.search_match_rule(tree, node_current, data);

		if (0xff != search_return.location) {
			search_return.node = node_current;

			return search_return;
		}

		search_return.node_prev = node_current;

		node_current = tree_family_control_environment.node_operator.search_recursion_rule(tree, node_current, data);
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

void tree_family_control_insert(struct tree_family_s *tree, void *data)
{
	assert(tree);

	tree->switch_control();

	tree_family_search_node_return_st
		search_return = { 0 };

	search_return = tree_family_control_search(tree, data);

	if (0xff == search_return.location) {													/* Can't search the node */
		if (NULL == search_return.node_prev) {
			tree->root = tree_family_control_init_node(tree);

			tree_family_node_control_set_data(tree, tree->root, data);
		} else {
			tree_family_control_environment.node_operator.insert_rule(tree, search_return, data);
		}
	}
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *tree_family_control_delete(struct tree_family_s *tree,
								 void *data)
{
	assert(tree);
	assert(data);

	tree->switch_control();

	struct tree_family_search_node_return_s
		search_return = { 0 };

	search_return = tree_family_control_search(tree, data);

	if (0xff != search_return.location) {								/* Can search the node */
		tree_family_control_environment.node_operator.delete_rule(tree, search_return, data);
	}

	return NULL;
}

/**
 * @brief This function will initialize the tree node struct.
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void *tree_family_control_init_node(struct tree_family_s *tree)
{
	assert(tree);

	struct tree_family_chain_node_s
		*node_alloced = tree->allocator_ctrl->allocate(tree->allocator,
													   1, sizeof(struct tree_family_chain_node_s));	/* Allocate #1 */

	void *data_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, tree_family_control_environment.node_infomation.data_mem_len);					/* Allocate #2 */

	void *link_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, tree_family_control_environment.node_infomation.link_mem_len);					/* Allocate #3 */

	if (NULL == tree ||																				/* Check if tree point to NULL					*/
		NULL == node_alloced ||																		/* Check if tree node point to NULL				*/
		NULL == data_pack_allocated ||																/* Check if tree node data pack point to NULL	*/
		NULL == link_pack_allocated) {																/* Check if tree node link pack point to NULL	*/
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

void tree_family_control_destroy_node(struct tree_family_s *tree,
									  void **node)
{
	assert(tree);

	if (NULL == *node) {
		return;
	}

	struct tree_family_chain_node_s *node_destroy = *node;

	tree->allocator_ctrl->deallocate(tree->allocator, node_destroy->data, 1);				/* Deallocate #2 */

	tree->allocator_ctrl->deallocate(tree->allocator, node_destroy->link, 1);				/* Deallocate #3 */

	tree->allocator_ctrl->deallocate(tree->allocator, *node, 1);							/* Deallocate #1 */

	*node = NULL;
}

/**
 * @brief This function will set the key node into the node.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_data(struct tree_family_s *tree)
{
	struct two_three_tree_chain_node_data_s
		*block_data_allocated = tree->allocator_ctrl->allocate(tree->allocator, 1,
															   tree_family_control_environment.node_infomation.data_mem_len);

	if (NULL == block_data_allocated) {
		return NULL;
	}

	return block_data_allocated;
}

/**
 * @brief This function will destroy the data.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_data(struct tree_family_s *tree,
										   void **data)
{
	assert(tree);
	assert(data);

	tree->allocator_ctrl->deallocate(tree->allocator, *data, 1);

	*data = NULL;
}

/**
 * @brief This function will return the specified data of the node.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_get_data(struct tree_family_s *tree,
										struct tree_family_chain_node_s *node,
										size_t location)
{
	assert(node);

	void ***data_node = (void ***)node;

	if (location >= tree->info.degree) {				/* Get the data far right */
		location = tree->info.degree - 1;
		while (0 < location &&
			   NULL == *((void **)data_node + location)) {
			location--;
		}
	}

	return *((void **)data_node + location);
}

/**
 * @brief This function will set the data into the node.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_set_data(struct tree_family_s *tree,
									   struct tree_family_chain_node_s *node,
									   void *data)
{
	assert(tree);
	assert(node);

	tree->switch_control();

	void ***data_node = (void ***)node;

	if (NULL == data_node ||
		NULL == data) {
		return;
	}

	size_t
		count_data = tree_family_control_environment.node_infomation.data_element_count;

	if (0 == tree_family_node_control_get_node_type(tree, node)) {
		**data_node = tree_family_node_control_init_data(tree);

		if (NULL == **data_node) {
			return;
		}

		memcpy(**data_node, data, tree->info.mem_size);
	} else {
		void
			*data_cpy = tree_family_node_control_init_data(tree),
			*node_data_sort = tree->allocator_ctrl->allocate(tree->allocator, count_data + 1, sizeof(void *));

		if (NULL == data_cpy ||
			NULL == node_data_sort) {
			return;
		}

		memcpy(data_cpy, data, tree->info.mem_size);

		for (size_t cnt = 0; cnt < count_data; cnt++) {
			*((void **)node_data_sort + cnt) = (void *)((size_t)*data_node + cnt * sizeof(void *));
		}

		*((void **)node_data_sort + count_data) = &data_cpy;

		struct sort_package_s sort_package = {
			.object = node_data_sort,
			.len = count_data + 1,
			.mem_len = tree->info.mem_size,
			.get_value_method = tree_family_sort_algorithm_control_get_data,
			.swap_method = tree_family_sort_algorithm_control_swap_data,
			.compare_method = tree_family_node_control_compare_greater,
		};

		sort_algorithm_control(sort_algorithm_control_convert_type_to_func_addr(TREE_FAMILY_CFG_SORT_ALGORITHM_TYPE),
							   sort_package,
							   tree_family_node_control_compare_greater);
	}
}

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_del_data(struct tree_family_s *tree,
										struct tree_family_chain_node_s *node,
										size_t location)
{
	assert(node);

	void *data_del = NULL;

	if (location >= tree->info.degree) {				/* Get the data far right */
		location = tree->info.degree - 1;
		while (0 < location &&
			   NULL == *((void **)node->data + location)) {
			location--;
		}
	}

	data_del = *((void **)node->data + location);

	for (size_t id = location; id < tree->info.degree - 1; id++) {
		*((void **)node->data + id) = *((void **)node->data + id + 1);
	}

	return data_del;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

size_t tree_family_node_control_get_node_type(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node)
{
	assert(tree);
	assert(node);

	tree->switch_control();

	void ***data_node = (void ***)node;

	size_t count_have_data = 0;

	for (size_t cnt = 0; cnt < tree_family_control_environment.node_infomation.data_element_count; cnt++) {
		if (NULL != *(*data_node + cnt)) {
			count_have_data++;
		}
	}

	//if (0 != count_have_data) {
	//	return count_have_data;
	//}
	return count_have_data;
}

/**
 * @brief This function will return the family member of the node.
 *
 * @param tree the pointer to the tree
 * @param node the pointer to the node
 * @param id the id member that the parent is 0,children are greater than 0
 *
 * @return void
 */

void *tree_family_node_control_get_family_member(struct tree_family_s *tree,
												 struct tree_family_chain_node_s *node,
												 size_t id)
{
	assert(tree);
	assert(node);

	tree->switch_control();

	void **link_node = *((void **)node + 1);

	if (tree->info.degree + 1 < id) {
		return NULL;
	} else if (tree->info.degree + 1 == id) {
		size_t id_far_right = tree->info.degree;
		while (2 < id_far_right &&
			   NULL == *((void **)link_node + id_far_right)) {
			id_far_right--;
		}

		return *((void **)link_node + id_far_right);
	}

	return *(link_node + id);
}

/**
 * @brief This function will return if one of the parent's left child is node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_left_child(struct tree_family_s *tree,
												struct tree_family_chain_node_s *node,
												struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);
	assert(parent);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return false;
	}

	size_t
		link_id_far_left = 1,
		link_id_far_right = tree_family_node_control_get_node_type(tree, parent) + 1;

	while (link_id_far_right > link_id_far_left &&
		   node != *((void **)parent->link + link_id_far_left)) {
		link_id_far_left++;
	}

	if (link_id_far_right > link_id_far_left) {
		return true;
	}

	return false;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_right_child(struct tree_family_s *tree,
												 struct tree_family_chain_node_s *node,
												 struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return false;
	}

	size_t
		link_id_far_left = 1,
		link_id_far_right = tree_family_node_control_get_node_type(tree, parent) + 1;

	while (link_id_far_left < link_id_far_right &&
		   node != *((void **)parent->link + link_id_far_right)) {
		link_id_far_right--;
	}

	if (link_id_far_left < link_id_far_right) {
		return true;
	}

	return false;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

size_t tree_family_node_control_get_relation_with_parent(struct tree_family_s *tree,
														 struct tree_family_chain_node_s *node,
														 struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return 0xff;
	}

	for (size_t id = 1; id <= tree->info.degree + 1; id++) {
		if (node == *((void **)parent->link + id)) {
			return id;
		}
	}

	return 0xff;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_leaf(struct tree_family_s *tree,
										  struct tree_family_chain_node_s *node)
{
	assert(node);

	tree->switch_control();

	if (NULL == node) {
		return false;
	}

	void
		**link_node = node->link;

	size_t count_have_brother = 0;

	for (size_t cnt = 1; cnt < tree_family_control_environment.node_infomation.link_element_count; cnt++) {
		if (NULL != *(link_node + cnt)) {
			count_have_brother++;
		}
	}

	if (0 < count_have_brother) {
		return false;
	} else {
		return true;
	}
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

void *tree_family_sort_algorithm_control_get_data(void *object, size_t loc)
{
	assert(object);

	char ***object_shift = ((char ***)object + loc);

	return **object_shift;
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

void tree_family_sort_algorithm_control_swap_data(void *object, size_t lhs, size_t rhs)
{
	assert(object);

	char
		***object_lhs = ((char ***)object + lhs),
		***object_rhs = ((char ***)object + rhs),
		*tmp = **object_lhs;

	**object_lhs = **object_rhs;
	**object_rhs = tmp;
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool tree_family_node_control_compare_greater(void *lhs, void *rhs, size_t len)
{
	assert(len);

	if (NULL == lhs) {						/* Regard NULL is the greatest value */
		return true;
	} else if (NULL == rhs) {
		return false;
	}

	for (size_t cnt = 1; cnt <= len; cnt++) {
		if (*((char *)lhs + len - cnt) > *((char *)rhs + len - cnt)) {
			return true;
		}
	}

	return false;
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_preorder_traversal(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator)
{
	assert(tree);

	tree->switch_control();

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	operator(tree, node, tree_family_control_environment.node_infomation.data_element_count);

	for (size_t cnt = 1; cnt < tree_family_control_environment.node_infomation.link_element_count; cnt++) {
		tree_family_control_preorder_traversal(tree, *(link + cnt), operator);
	}
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_inorder_traversal(struct tree_family_s *tree,
										   struct tree_family_chain_node_s *node,
										   tree_family_traversal_operator_t *operator)
{
	assert(tree);

	tree->switch_control();

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	tree_family_control_inorder_traversal(tree, *(link + 1), operator);

	operator(tree, node, tree_family_control_environment.node_infomation.data_element_count);

	for (size_t cnt = 2; cnt < tree_family_control_environment.node_infomation.link_element_count; cnt++) {
		tree_family_control_inorder_traversal(tree, *(link + cnt), operator);
	}
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_posorder_traversal(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator)
{
	assert(tree);

	tree->switch_control();

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	for (size_t cnt = 1; cnt < tree_family_control_environment.node_infomation.link_element_count; cnt++) {
		tree_family_control_posorder_traversal(tree, *(link + cnt), operator);
	}

	operator(tree, node, tree_family_control_environment.node_infomation.data_element_count);
}

/**
 * @brief This function will get the node's precursor node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the precursor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_precursor(struct tree_family_s *tree,
								  struct tree_family_chain_node_s *node,
								  size_t location)
{
	assert(tree);
	assert(node);

	tree->switch_control();

	size_t
		id_parent = 0,
		id_far_left = location + 1,
		id_far_right = location + 2;

	tree_family_get_precursor_and_successor_return_st
		get_precursor_successor_return = { 0 };
	struct tree_family_chain_node_s
		*node_current = tree_family_node_control_get_family_member(tree, node, id_far_left);						/* Get the node's left child */

	printf("\"%s\"'s ", (char *)*((void **)node->data + location));

	if (NULL != node_current) {																						/* If the node's left child is valid */
		void *node_tmp = NULL;

		while (NULL != (node_tmp = tree_family_node_control_get_family_member(tree, node_current, id_far_right))) {	/* Get the node_current's right child,then assign to the node */
			node_current = node_tmp;																				/* Assign the node to the node_current */
		}

		goto EXIT;
	} else {
		node_current = tree_family_node_control_get_family_member(tree, node, id_parent);							/* Get the node's parent,then assign to the node_current */

		while (NULL != node_current &&
			   !tree_family_node_control_get_if_right_child(tree, node, node_current)) {
			node = node_current;																					/* Set the node as his own parent */
			node_current = tree_family_node_control_get_family_member(tree, node, id_parent);						/* Get the node's parent,then assign to the node_current */
		}

		goto EXIT;
	}

EXIT:

	/*if (NULL != node_current && 1 < (id_far_right = tree_family_node_control_get_node_type(tree,node_current))) {
		while (0 < id_far_right &&
			   NULL == *((void **)node_current->data + id_far_right)) {
			id_far_right--;
		}
	} else {
		id_far_right = 0;
	}

	if (NULL != node_current && 2 < tree->info.degree) {
		id_far_right = tree_family_node_control_get_relation_with_parent(tree, node, node_current) - 2;
	} else {
		id_far_right = 0;
	}*/

	if (NULL != node_current) {
		get_precursor_successor_return.node = node_current;
		get_precursor_successor_return.location = id_far_right;
		get_precursor_successor_return.data = *((void **)node_current->data + id_far_right);
	}

	printf("precursor is %p's No.%d:\"%s\"\r\n",
		   get_precursor_successor_return.node,
		   get_precursor_successor_return.location,
		   (char *)get_precursor_successor_return.data);

	return get_precursor_successor_return;
}

/**
 * @brief This function will get the node's successor node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_successor(struct tree_family_s *tree,
								  struct tree_family_chain_node_s *node,
								  size_t location)
{
	assert(tree);
	assert(node);

	tree->switch_control();

	size_t
		id_parent = 0,
		id_far_left = location + 1,
		id_far_right = location + 2;

	tree_family_get_precursor_and_successor_return_st
		get_precursor_successor_return = { 0 };
	struct tree_family_chain_node_s
		*node_current = tree_family_node_control_get_family_member(tree, node, id_far_right);						/* Get the node's right child */

	printf("\"%s\"'s ", (char *)*((void **)node->data + location));

	if (NULL != node_current) {																						/* If the node's right child is valid */
		while (NULL != (node = tree_family_node_control_get_family_member(tree, node_current, id_far_left))) {		/* Get the node_current's left child,then assign to the node */
			node_current = node;																					/* Assign the node to the node_current */
		}

		goto EXIT;
	} else {
		node_current = tree_family_node_control_get_family_member(tree, node, id_parent);							/* Get the node's parent,then assign to the node_current */

		bool result = false;

		while (NULL != node_current &&
			   !(result = tree_family_node_control_get_if_left_child(tree, node, node_current))) {
			node = node_current;																					/* Set the node as his own parent */
			node_current = tree_family_node_control_get_family_member(tree, node, id_parent);						/* Get the node's parent,then assign to the node_current */
		}

		goto EXIT;
	}

EXIT:

	id_far_left = 0;

	if (NULL != node_current) {
		get_precursor_successor_return.node = node_current;
		get_precursor_successor_return.location = id_far_left;
		get_precursor_successor_return.data = *((void **)node_current->data + id_far_left);
	}

	printf("successor is %p's No.%d:\"%s\"\r\n",
		   get_precursor_successor_return.node,
		   get_precursor_successor_return.location,
		   (char *)get_precursor_successor_return.data);

	return get_precursor_successor_return;
}

/**
* @brief This function will print all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_traversal_printer(struct tree_family_s *tree,
										   void *node,
										   size_t data_element_count)
{
	printf("node:%p data: ", node);

	char ***data = node;

	for (size_t cnt = 0; cnt < data_element_count; cnt++) {
		if (NULL != *(*data + cnt)) {
			printf("\"%s\" ", *(*data + cnt));
		}
	}

	printf("\r\n");
}

/**
* @brief This function will destroy all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_destroy_posorder_traversal_operator(struct tree_family_s *tree,
															 void *node,
															 size_t data_element_count)
{
	printf("will destroy ");

	tree_family_control_traversal_printer(tree, node, data_element_count);

	//if (2 <= tree_family_node_control_get_node_type(tree, node)) {		/* Not binary node */
	//
	//}

	//tree_family_control_destroy_node(tree, &node);
}

/**
* @brief This function will replace the switch_control() before enter control sandbox.
*
* @param void
*
* @return void
*/

void tree_family_control_switch_control_in_sandbox(void)
{
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configration_exception_default_full_callback(void)
{
}