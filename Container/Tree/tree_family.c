/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "tree_family.h"

#include "container_pte_def.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define LINK_OPERATOR_IS_PARENT(id)																	\
	(LINK_OPERATOR_CODE_PARENT == (id))

#define LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)															\
	(LINK_OPERATOR_CODE_CHILD_FAR_RIGHT >= (id) &&														\
	(tree_family_control_node_infomation.link_element_count - 1) <= (id))

#define LINK_OPERATOR_IS_CHILD_FAR_LEFT(id)															\
	(LINK_OPERATOR_CODE_CHILD_FAR_LEFT == (id))

#define DATA_OPERATOR_IS_DATA_FAR_RIGHT(id)															\
	(DATA_OPERATOR_CODE_DATA_FAR_RIGHT >= (id) &&														\
	(tree_family_control_node_infomation.data_element_count - 1) <= (id))

#define DATA_OPERATOR_IS_DATA_FAR_LEFT(id)																\
	(DATA_OPERATOR_CODE_DATA_FAR_LEFT == (id))

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
 * @brief This variables will record the tree_family control environment.
 */

struct tree_family_control_environment_s tree_family_control_environment = { 0 };

/**
 * @brief This variables will record the tree_family's node information in control.
 */

struct tree_family_node_infomation_s tree_family_control_node_infomation = { 0 };

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will call when get control of the tree_family-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_callback(enum tree_family_node_type_e member_type);

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

void *tree_family_sort_algorithm_control_get_data(void *object,
												  container_size_t loc);

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

void tree_family_sort_algorithm_control_swap_data(void *object,
												  container_size_t lhs, container_size_t rhs);

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

bool tree_family_node_control_compare_greater(void *lhs,
											  void *rhs, container_size_t len);

/**
* @brief This function will destroy all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_destroy_posorder_traversal_operator(tree_family_stp tree_family,
															 void *node,
															 container_size_t data_element_count);

/**
* @brief This function will replace the switch_control(tree_family) before enter control sandbox.
*
* @param void
*
* @return void
*/

void tree_family_control_switch_control_in_sandbox(tree_family_stp tree_family);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configuration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configuration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This variables will record the tree_family's data sort package.
 */

struct sort_package_s tree_family_control_data_sort_package = {
	.object = NULL,
	.len = 0u,
	.mem_len = 0u,
	.get_value_method = tree_family_sort_algorithm_control_get_data,
	.swap_method = tree_family_sort_algorithm_control_swap_data,
	.compare_method = tree_family_node_control_compare_greater,
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will get control of the tree_family-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

extern inline void tree_family_control_get_control(struct tree_family_control_environment_s environment)
{
	if (tree_family_control_environment.member_type != environment.member_type) {
		tree_family_control_environment = environment;

		tree_family_control_get_control_callback(environment.member_type);
	}
}

/**
 * @brief This function will run the func_addr() in sandbox with specified environment.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_in_sandbox(tree_family_stp tree_family,
												struct tree_family_control_environment_s environment,
												void (*func_addr)(void *, ...),
												size_t count_param,
												...)
{
	tree_family_control_environment = environment;

	tree_family_control_get_control_callback(environment.member_type);

	void *switch_control_tree = tree_family->switch_control;										/* Store current tree_family's switch control address */

	tree_family->switch_control = tree_family_control_switch_control_in_sandbox;

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

	tree_family->switch_control = switch_control_tree;												/* Recovery current tree_family's switch control address */
}

/**
 * @brief This function will call when get control of the tree_family-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

static inline void tree_family_control_get_control_callback(enum tree_family_member_type_e member_type)
{
	enum tree_family_node_type_e node_type = member_type & 0x0f;

	tree_family_control_node_infomation.member_type = member_type;
	tree_family_control_node_infomation.data_element_count = node_type - 1;
	tree_family_control_node_infomation.link_element_count = node_type + 1;
	tree_family_control_node_infomation.id_data_far_right = node_type - 2;
	tree_family_control_node_infomation.id_link_far_right = node_type;
	tree_family_control_node_infomation.link_mem_len =
		tree_family_control_node_infomation.link_element_count * sizeof(void *);
}

/**
 * @brief This function will initialize the tree_family struct
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param element_size the element memory size of the tree_family struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t tree_family_control_configuration_init(tree_family_stpp tree_family,
											container_family_switch_control switch_control,
											container_size_t degree,
											container_size_t key_size,
											enum tree_family_member_type_e member_type,
											enum allocator_type_e allocator_type,
											container_size_t element_size,
											generic_type_element_assign_t assign,
											generic_type_element_free_t free)
{
	assert(tree_family);
	assert(switch_control);
	assert(allocator_type);
	assert(element_size);

	static struct container_allocte_package_s
		allocate_package = { 0 };
	static struct container_control_configuration_allocate_return_s
		allocate_return = { 0 };
	static struct tree_family_extra_infomation_s
		extra_infomation = { 0 };

	allocate_package.allocator_type = allocator_type;
	allocate_package.container_mem_size 
		= sizeof(struct container_family_s) + sizeof(struct tree_family_extra_infomation_s);
	allocate_package.arg_list_ptr = NULL;

	if ((allocate_return
		 = container_control_configuration_allocate											/* Allocate the adaptor structure */
		 (tree_family, allocate_package))
		.error) {
		return allocate_return.error;
	}

	(*tree_family)->container_type_id = member_type;						/* Assign tree_family structure */

	(*tree_family)->info.max_size = TREE_FAMILY_CFG_NODE_COUNT_MAX;
	(*tree_family)->info.size = 0u;
	(*tree_family)->info.mem_size = element_size;

	(*tree_family)->element_handler.assign = assign;
	(*tree_family)->element_handler.free = free;

	(*tree_family)->allocator_control_ptr = allocate_return.allocator_control_ptr;
	(*tree_family)->allocator_ptr = allocate_return.allocator_ptr;

	(*tree_family)->element_ptr = NULL;

	(*tree_family)->switch_control = switch_control;

	extra_infomation.degree = degree;
	extra_infomation.minimum_amt_key = (size_t)ceil((float)degree / 2) - 1;
	extra_infomation.mem_size_key = key_size;

	memcpy(&(*tree_family)->addon, 
		   &extra_infomation, 
		   sizeof(struct tree_family_extra_infomation_s));

	tree_family_control_configuration_exception(
		(*tree_family)
		, tree_family_control_configuration_exception_default_empty_callback
		, tree_family_control_configuration_exception_default_full_callback);

	return 0;
}

/**
 * @brief This function will destroy the tree_family struct and free the space
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return NONE
 */

errno_t tree_family_control_configuration_destroy(tree_family_stpp tree_family)
{
	assert(tree_family);

	(*tree_family)->switch_control(*tree_family);

	void *allocator_ptr = (*tree_family)->allocator_ptr;

	struct allocator_control_s *allocator_control_ptr = (*tree_family)->allocator_control_ptr;

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("tree_family.configuration.destroy:tree_family block : %p \r\n", (*tree_family));
	printf("tree_family.configuration.destroy:allocator_ptr : %p \r\n", allocator_ptr);

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	tree_family_control_posorder_traversal(*tree_family, (*tree_family)->element_ptr,
										   tree_family_control_destroy_posorder_traversal_operator);

	allocator_control_ptr->deallocate(allocator_ptr, *tree_family, 1);																			/* deallocate #1 */

	allocator_control_ptr->configuration.destroy(&allocator_ptr);

	*tree_family = NULL;

	return 0;
}

/**
 * @brief This function will configure the tree_family element handler
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_element_handler(tree_family_stp tree_family,
													   generic_type_element_assign_t assign,
													   generic_type_element_free_t free)
{
	assert(tree_family);
	assert(assign);
	assert(free);

	tree_family->element_handler.assign = assign;
	tree_family->element_handler.free = free;
}

/**
 * @brief This function will configure the tree_family exception callback
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_exception(tree_family_stp tree_family,
												 void (*empty)(void), void (*full)(void))
{
	assert(tree_family);

	if (NULL == empty) {
		tree_family->exception.empty = empty;
	}

	if (NULL == full) {
		tree_family->exception.full = full;
	}
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

tree_family_search_node_return_st
tree_family_control_search(tree_family_stp tree_family, void *data)
{
	assert(tree_family);

	tree_family_search_node_return_st search_return = { SEARCH_CODE_NO_SUCH_ELEMENT };

	if (NULL == data) {
		goto EXIT;
	}

	tree_family->switch_control(tree_family);

	struct tree_family_chain_node_s *node_current = tree_family->element_ptr;

	while (NULL != node_current) {
		search_return.location = tree_family_control_environment.node_operator.search_match_rule(tree_family, node_current, data);

		if (SEARCH_CODE_NO_SUCH_ELEMENT != search_return.location) {
			search_return.node = node_current;
			search_return.content = (void *)((size_t)(*((void **)node_current->data + search_return.location)) +
											 tree_family_control_environment.extra_info.mem_size_key);

			goto EXIT;
		}

		search_return.node_prev = node_current;

		search_return.estimate = tree_family_control_environment.node_operator.search_recursion_rule(tree_family, &node_current, data);
	}

EXIT:

	return search_return;
}

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void tree_family_control_insert(tree_family_stp tree_family, void *data)
{
	assert(tree_family);

	if (NULL == data) {
		return;
	}

	tree_family->switch_control(tree_family);

	tree_family_search_node_return_st
		search_return = tree_family_control_search(tree_family, data);

	if (SEARCH_CODE_NO_SUCH_ELEMENT == search_return.location) {													/* Can't search the node */
		if (NULL == search_return.node_prev) {
			void *data_cpy = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr, 1, tree_family->info.mem_size);

			tree_family->element_ptr = tree_family_control_init_node(tree_family);

			if (NULL != tree_family->element_ptr &&
				NULL != data_cpy) {
				memcpy(data_cpy, data, tree_family->info.mem_size);
				tree_family_node_control_set_data(tree_family, tree_family->element_ptr, data_cpy, DATA_OPERATOR_CODE_DATA_FAR_LEFT);
			}
		} else {
			tree_family_control_environment.node_operator.insert_rule(tree_family, search_return, data);
		}
	}
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void tree_family_control_delete(tree_family_stp tree_family,
								void *data)
{
	assert(tree_family);
	assert(data);

	tree_family->switch_control(tree_family);

	struct tree_family_search_node_return_s
		search_return = tree_family_control_search(tree_family, data);

	if (SEARCH_CODE_NO_SUCH_ELEMENT != search_return.location) {							/* Can search the node */
		void *item_del =
			tree_family_control_environment.
			node_operator.
			delete_rule(tree_family, search_return, data);

		if (NULL != item_del) {
			if (TREE_FAMILY_B_TREE > tree_family->container_type_id) {
				tree_family_control_destroy_node(tree_family, &item_del);
			} else {
				tree_family_node_control_destroy_data(tree_family, &item_del);
			}
		}
	}
}

/**
 * @brief This function will initialize the tree_family node struct.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return NONE
 */

void *tree_family_control_init_node(tree_family_stp tree_family)
{
	assert(tree_family);

	struct tree_family_chain_node_s
		*node_alloced = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr,
													   1, sizeof(struct tree_family_chain_node_s));	/* Allocate #1 */

	void *data_pack_allocated = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr,
															   1, tree_family->info.mem_size);				/* Allocate #2 */

	void *link_pack_allocated = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr,
															   1, tree_family_control_node_infomation.link_mem_len);					/* Allocate #3 */

	if (NULL == tree_family ||																				/* Check if tree_family point to NULL					*/
		NULL == node_alloced ||																		/* Check if tree_family node point to NULL				*/
		NULL == data_pack_allocated ||																/* Check if tree_family node data pack point to NULL	*/
		NULL == link_pack_allocated) {																/* Check if tree_family node link pack point to NULL	*/
		return NULL;
	}

	node_alloced->data = data_pack_allocated;
	node_alloced->link = link_pack_allocated;

	return node_alloced;
}

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_destroy_node(tree_family_stp tree_family,
									  void **node)
{
	assert(tree_family);

	if (NULL == *node) {
		return;
	}

	struct tree_family_chain_node_s *node_destroy = *node;

	tree_family->allocator_control_ptr->deallocate(tree_family->allocator_ptr, node_destroy->data, 1);				/* Deallocate #2 */

	tree_family->allocator_control_ptr->deallocate(tree_family->allocator_ptr, node_destroy->link, 1);				/* Deallocate #3 */

	tree_family->allocator_control_ptr->deallocate(tree_family->allocator_ptr, *node, 1);							/* Deallocate #1 */

	*node = NULL;
}

/**
 * @brief This function will initialize the tree_family node's data struct.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_data(tree_family_stp tree_family)
{
	struct tree_family_chain_node_data_content_s
		*block_data_allocated = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr, 1,
															   tree_family->info.mem_size);

	return block_data_allocated;
}

/**
 * @brief This function will destroy the data.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_data(tree_family_stp tree_family,
										   void **data)
{
	assert(tree_family);
	assert(data);

	tree_family->allocator_control_ptr->deallocate(tree_family->allocator_ptr, *data, 1);

	*data = NULL;
}

/**
 * @brief This function will set the data into the node.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_set_data(tree_family_stp tree_family,
									   struct tree_family_chain_node_s *node,
									   void *data,
									   container_size_t id)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	if (NULL == data ||
		NULL != *((void **)node->data + 												/* If have enough space for the data */
				  tree_family_control_node_infomation.id_data_far_right)) {
		return;
	}

	if (DATA_OPERATOR_IS_DATA_FAR_RIGHT(id)) {											/* Determine the data's id */
		if (NULL != *((void **)node->data + DATA_OPERATOR_CODE_DATA_FAR_LEFT)) {		/* Set the data as the far right one */
			id = tree_family_control_node_infomation.id_data_far_right;

			while (NULL == *((void **)node->link + id) &&
				   DATA_OPERATOR_CODE_DATA_FAR_LEFT < --id);
		}
	}

	container_size_t id_data = tree_family_control_node_infomation.id_data_far_right;

	while (id < id_data &&																/* Sort the data to make a space */
		   NULL != *((void **)node->data + id_data)) {
		*((void **)node->data + id_data) = *((void **)node->data + --id_data);
	}

	*((void **)node->data + id) = data;													/* Set the data to the space */
}

/**
 * @brief This function will insert the data into the node,which means have to sort.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_insert_data(tree_family_stp tree_family,
										  struct tree_family_chain_node_s *node,
										  void *data)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	if (NULL == node->data ||
		NULL == data) {
		return;
	}

	void *data_node = node->data;

	if (0 == tree_family_node_control_get_node_type(tree_family, node)) {
		*((void **)data_node) = tree_family_node_control_init_data(tree_family);

		if (NULL == *((void **)data_node)) {
			return;
		}

		memcpy(*((void **)data_node), data, tree_family->info.mem_size);
	} else {
		void
			*data_cpy = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr, 1, tree_family->info.mem_size),
			*data_package_sort = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr, 			/* The package which store the address of the node's data */
																tree_family_control_node_infomation.data_element_count + 1,
																sizeof(void *));

		if (NULL == data_cpy ||
			NULL == data_package_sort) {
			return;
		}

		memcpy(data_cpy, data, tree_family->info.mem_size);

		for (size_t id_data = DATA_OPERATOR_CODE_DATA_FAR_LEFT; id_data < tree_family_control_node_infomation.data_element_count; id_data++) {
			*((void **)data_package_sort + id_data) = (void *)((size_t)data_node + id_data * sizeof(void *));
		}

		*((void **)data_package_sort + tree_family_control_node_infomation.data_element_count) = &data_cpy;

		tree_family_control_data_sort_package.object = data_package_sort;
		tree_family_control_data_sort_package.len = tree_family_control_node_infomation.data_element_count + 1;
		tree_family_control_data_sort_package.mem_len = tree_family_control_environment.extra_info.mem_size_key;

		sort_algorithm_control(sort_algorithm_control_convert_type_to_func_addr(TREE_FAMILY_CFG_SORT_ALGORITHM_TYPE),
							   tree_family_control_data_sort_package,						/* Sort the address of the data in the data package by the data's key */
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

void *tree_family_node_control_del_data(tree_family_stp tree_family,
										struct tree_family_chain_node_s *node,
										container_size_t id)
{
	assert(node);

	if (DATA_OPERATOR_IS_DATA_FAR_RIGHT(id)) {				/* Get the data far right */
		id = tree_family_control_environment.extra_info.degree - 1;
		while (0 < id &&
			   NULL == *((void **)node->data + id)) {
			id--;
		}
	}

	void *data_del = *((void **)node->data + id);

	for (size_t id_link = id; id_link < tree_family_control_environment.extra_info.degree - 2; id_link++) {
		*((void **)node->data + id_link) = *((void **)node->data + id_link + 1);
	}

	*((void **)node->data + tree_family_control_environment.extra_info.degree - 2) = NULL;

	return data_del;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

container_size_t tree_family_node_control_get_node_type(tree_family_stp tree_family,
														struct tree_family_chain_node_s *node)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	void *data_node = node->data;

	container_size_t count_have_data = 0;

	for (size_t cnt = 0; cnt < tree_family_control_node_infomation.data_element_count; cnt++) {
		if (NULL != *((void **)data_node + cnt)) {
			count_have_data++;
		}
	}

	return count_have_data;
}

/**
 * @brief This function will initialize the tree_family node's link struct.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_link(tree_family_stp tree_family)
{
	struct tree_family_chain_node_data_content_s
		*block_link_allocated = tree_family->allocator_control_ptr->allocate(tree_family->allocator_ptr, 1,
															   tree_family_control_node_infomation.link_mem_len);

	return block_link_allocated;
}

/**
 * @brief This function will destroy the link.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_link(tree_family_stp tree_family,
										   void **link)
{
	assert(tree_family);
	assert(link);

	tree_family->allocator_control_ptr->deallocate(tree_family->allocator_ptr, *link, 1);

	*link = NULL;
}

/**
 * @brief This function will return the family member of the node.
 *
 * @param tree_family the pointer to the tree_family
 * @param node the pointer to the node
 * @param id the id member that the parent is 0,children are greater than 0
 *
 * @return void
 */

void *tree_family_node_control_get_family_member(tree_family_stp tree_family,
												 struct tree_family_chain_node_s *node,
												 container_size_t id)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	void **link_node = *((void **)node + 1);

	if (LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)) {
		container_size_t id_far_right = tree_family_control_environment.extra_info.degree;
		while (2 < id_far_right &&
			   NULL == *((void **)link_node + id_far_right)) {
			id_far_right--;
		}

		return *((void **)link_node + id_far_right);
	}

	return *(link_node + id);
}

/**
 * @brief This function will get the node's available brother node.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the node's available brother node
 */

void *tree_family_node_control_get_neighbour(tree_family_stp tree_family,
											 struct tree_family_chain_node_s *node,
											 struct tree_family_chain_node_s *parent,
											 container_size_t relation_with_parent)
{
	assert(tree_family);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		goto FAIL;
	}

	if (LINK_OPERATOR_CODE_PARENT == relation_with_parent &&
		LINK_OPERATOR_CODE_PARENT == (relation_with_parent = 								/* Get the relation id with parent */
									  tree_family_node_control_get_relation_with_parent(tree_family, node, parent))) {
		goto FAIL;
	} else if (LINK_OPERATOR_CODE_CHILD_FAR_LEFT == relation_with_parent) {
		return *((void **)parent->link + LINK_OPERATOR_CODE_CHILD_FAR_LEFT + 1);
	} else if (LINK_OPERATOR_CODE_CHILD_FAR_RIGHT == relation_with_parent) {
		return *((void **)parent->link + tree_family_control_environment.extra_info.degree);
	}

	container_size_t
		minimum = tree_family_control_environment.extra_info.minimum_amt_key,
		type_node = 0,
		location = 0;

	const int offset[2] = { 1,-1 };															/* Prefer the left one */

	void *neignbour[2] = {
		*((void **)parent->link + relation_with_parent + offset[0]) ,
		*((void **)parent->link + relation_with_parent + offset[1]) };

	for (size_t side = 0; side < 2; side++) {
		if (NULL != neignbour[side] &&
			minimum <= (type_node = tree_family_node_control_get_node_type(tree_family, neignbour[side]))) {
			location = relation_with_parent + offset[side];
			minimum = type_node;
		}
	}

	if (0 >= location) {
	FAIL:
		return NULL;
	}

	return *((void **)parent->link + location);
}

/**
 * @brief This function will set the child of the node,and return the link's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_set_child(tree_family_stp tree_family,
										 struct tree_family_chain_node_s *node,
										 struct tree_family_chain_node_s *family_member,
										 container_size_t id)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	if (NULL == family_member ||
		LINK_OPERATOR_IS_PARENT(id)) {
		goto EXIT;
	}

	if (LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)) {
		if (NULL != *((void **)node->link + (id = 1))) {								/* If the first one is NULL */
			while (tree_family_control_environment.extra_info.degree > id++ &&
				   NULL != *((void **)node->link + id)) {
			}
		}
	} else if (LINK_OPERATOR_IS_CHILD_FAR_LEFT(id)) {
		if (NULL != *((void **)node->link + id)) {
			if (NULL == *((void **)node->link + (id = tree_family_control_environment.extra_info.degree))) {			/* Have enough space for the family member */
				while (1 < --id &&
					   NULL != *((void **)node->link + id)) {
					*((void **)node->link + id + 1) = *((void **)node->link + id);
				}
			}
		}
	}

	*((void **)family_member->link + LINK_OPERATOR_CODE_PARENT) = node;
	*((void **)node->link + id) = family_member;

EXIT:

	return family_member;
}

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_del_family_member(tree_family_stp tree_family,
												 struct tree_family_chain_node_s *node,
												 container_size_t id)
{
	assert(tree_family);
	assert(node);

	void *family_member_del = NULL;

	if (LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)) {										/* Get the child far right */
		id = tree_family_control_environment.extra_info.degree;
		while (1 < id &&
			   NULL == *((void **)node->link + id)) {
			id--;
		}
	}

	family_member_del = *((void **)node->link + id);

	for (size_t id_link = (LINK_OPERATOR_IS_PARENT(id)) ? tree_family_control_environment.extra_info.degree : id; 		/* Sort the child member */
		 id_link < tree_family_control_environment.extra_info.degree; id_link++) {
		*((void **)node->link + id_link) = *((void **)node->link + id_link + 1);
	}

	*((void **)node->link + tree_family_control_environment.extra_info.degree) = NULL;

	return family_member_del;
}

/**
 * @brief This function will return if one of the parent's left child is node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_left_child(tree_family_stp tree_family,
												struct tree_family_chain_node_s *node,
												struct tree_family_chain_node_s *parent)
{
	assert(tree_family);
	assert(node);
	assert(parent);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return false;
	}

	container_size_t
		link_id_far_left = 1,
		link_id_far_right = tree_family_node_control_get_node_type(tree_family, parent) + 1;

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

bool tree_family_node_control_get_if_right_child(tree_family_stp tree_family,
												 struct tree_family_chain_node_s *node,
												 struct tree_family_chain_node_s *parent)
{
	assert(tree_family);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return false;
	}

	container_size_t
		link_id_far_left = 1,
		link_id_far_right = tree_family_node_control_get_node_type(tree_family, parent) + 1;

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

container_size_t
tree_family_node_control_get_relation_with_parent(tree_family_stp tree_family,
												  struct tree_family_chain_node_s *node,
												  struct tree_family_chain_node_s *parent)
{
	assert(tree_family);
	assert(node);

	if ((NULL == parent &&
		 NULL == (parent = *((void **)node->link))) ||
		node == parent) {
		goto FAIL;
	}

	for (size_t id = 1; id <= tree_family_control_environment.extra_info.degree + 1; id++) {
		if (node == *((void **)parent->link + id)) {
			return id;
		}
	}

FAIL:

	return LINK_OPERATOR_CODE_PARENT;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_leaf(tree_family_stp tree_family,
										  struct tree_family_chain_node_s *node)
{
	assert(node);

	tree_family->switch_control(tree_family);

	if (NULL == node) {
		return false;
	}

	void
		**link_node = node->link;

	container_size_t count_have_brother = 0;

	for (size_t cnt = 1; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
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

static inline void *tree_family_sort_algorithm_control_get_data(void *object,
																container_size_t loc)
{
	assert(object);

	return **((char ***)object + loc);
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

static inline void tree_family_sort_algorithm_control_swap_data(void *object,
																container_size_t lhs,
																container_size_t rhs)
{
	assert(object);

	MODIFY_SEQUENCE_CONTROL_SWAP((size_t)(**((char ***)object + lhs)), (size_t)(**((char ***)object + rhs)));
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

bool tree_family_node_control_compare_greater(void *lhs, void *rhs,
											  container_size_t len)
{
	if (NULL == lhs) {						/* Regard NULL as the greatest value */
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
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_preorder_traversal(tree_family_stp tree_family,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator)
{
	assert(tree_family);

	tree_family->switch_control(tree_family);

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	operator(tree_family, node, tree_family_control_node_infomation.data_element_count);

	for (size_t cnt = 1; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		tree_family_control_preorder_traversal(tree_family, *(link + cnt), operator);
	}
}

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_inorder_traversal(tree_family_stp tree_family,
										   struct tree_family_chain_node_s *node,
										   tree_family_traversal_operator_t *operator)
{
	assert(tree_family);

	tree_family->switch_control(tree_family);

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	tree_family_control_inorder_traversal(tree_family, *(link + 1), operator);

	operator(tree_family, node, tree_family_control_node_infomation.data_element_count);

	for (size_t cnt = 2; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		tree_family_control_inorder_traversal(tree_family, *(link + cnt), operator);
	}
}

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_posorder_traversal(tree_family_stp tree_family,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator)
{
	assert(tree_family);

	tree_family->switch_control(tree_family);

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	for (size_t cnt = 1; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		tree_family_control_posorder_traversal(tree_family, *(link + cnt), operator);
	}

	operator(tree_family, node, tree_family_control_node_infomation.data_element_count);
}

/**
 * @brief This function will get the node's precursor node.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the precursor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_precursor(tree_family_stp tree_family,
								  struct tree_family_chain_node_s *node,
								  container_size_t location)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	container_size_t
		id_parent = 0,
		id_far_left = location + 1,
		id_far_right = location + 2;

	tree_family_get_precursor_and_successor_return_st
		get_precursor_successor_return = { 0 };
	struct tree_family_chain_node_s
		*node_current = tree_family_node_control_get_family_member(tree_family, node, id_far_left);						/* Get the node's left child */

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("\"%s\"'s ", (char *)*((void **)node->data + location));

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	if (NULL != node_current) {																						/* If the node's left child is valid */
		while (NULL != (node = tree_family_node_control_get_family_member(tree_family,										/* Get the node_current's right child,then assign to the node */
																		  node_current,
																		  LINK_OPERATOR_CODE_CHILD_FAR_RIGHT))) {
			node_current = node;																					/* Assign the node to the node_current */
		}

		if (NULL != node_current) {																					/* It must be the leaf node,and get the far right data of the node */
			if (2 < tree_family_control_environment.extra_info.degree) {
				id_far_right = tree_family_node_control_get_node_type(tree_family, node_current);
				while (0 < id_far_right &&
					   NULL == *((void **)node_current->data + id_far_right)) {
					id_far_right--;
				}

				goto EXIT;
			}
		}
	} else {
		if (1 < tree_family_node_control_get_node_type(tree_family, node) &&												/* If the node is multi-node */
			2 <= id_far_left) {
			node_current = node;

			id_far_right = id_far_left - 2;

			goto EXIT;
		} else {
			node_current = tree_family_node_control_get_family_member(tree_family, node, id_parent);							/* Get the node's parent,then assign to the node_current */

			while (NULL != node_current &&
				   !tree_family_node_control_get_if_right_child(tree_family, node, node_current)) {
				node = node_current;																					/* Set the node as his own parent */
				node_current = tree_family_node_control_get_family_member(tree_family, node, id_parent);						/* Get the node's parent,then assign to the node_current */
			}

			if (NULL != node) {
				if (2 < tree_family_control_environment.extra_info.degree) {
					id_far_right = tree_family_node_control_get_relation_with_parent(tree_family, node, node_current) - 2;

					goto EXIT;
				}
			}
		}
	}

	id_far_right = 0;

EXIT:

	if (NULL != node_current) {
		get_precursor_successor_return.node = node_current;
		get_precursor_successor_return.location = id_far_right;
		get_precursor_successor_return.data = *((void **)node_current->data + id_far_right);
	}

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("precursor is %p's No.%d:\"%s\"-%d \r\n",
		   get_precursor_successor_return.node,
		   get_precursor_successor_return.location,
		   (char *)get_precursor_successor_return.data,
		   (size_t)TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_DATA(get_precursor_successor_return.data) - '0');

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	return get_precursor_successor_return;
}

/**
 * @brief This function will get the root of the tree_family.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

extern inline void
*tree_family_control_get_root(tree_family_stp tree_family)
{
	assert(tree_family);

	return tree_family->element_ptr;
}

/**
 * @brief This function will get the extra information block of tree_family.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

extern inline struct tree_family_extra_infomation_s
tree_family_control_get_extra_infomation(tree_family_stp tree_family)
{
	struct tree_family_extra_infomation_s
		*extra_info_ptr = (struct tree_family_extra_infomation_s*)tree_family->addon;

	return *extra_info_ptr;
}

/**
 * @brief This function will get the node's successor node.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_successor(tree_family_stp tree_family,
								  struct tree_family_chain_node_s *node,
								  container_size_t location)
{
	assert(tree_family);
	assert(node);

	tree_family->switch_control(tree_family);

	container_size_t
		id_parent = 0,
		id_far_left = location + 1,
		id_far_right = location + 2;

	tree_family_get_precursor_and_successor_return_st
		get_precursor_successor_return = { 0 };
	struct tree_family_chain_node_s
		*node_current = tree_family_node_control_get_family_member(tree_family, node, id_far_right);						/* Get the node's right child */

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("\"%s\"'s ", (char *)*((void **)node->data + location));

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	if (NULL != node_current) {																						/* If the node's right child is valid */
		while (NULL != (node = tree_family_node_control_get_family_member(tree_family, node_current, LINK_OPERATOR_CODE_CHILD_FAR_LEFT))) {		/* Get the node_current's left child,then assign to the node */
			node_current = node;																					/* Assign the node to the node_current */
		}
	} else {
		if (1 < tree_family_node_control_get_node_type(tree_family, node)) {												/* If the node is multi-node */
			node_current = node;

			id_far_left = id_far_right - 1;

			goto EXIT;
		} else {
			node_current = tree_family_node_control_get_family_member(tree_family, node, id_parent);						/* Get the node's parent,then assign to the node_current */

			while (NULL != node_current &&
				   !tree_family_node_control_get_if_left_child(tree_family, node, node_current)) {
				node = node_current;																				/* Set the node as his own parent */
				node_current = tree_family_node_control_get_family_member(tree_family, node, id_parent);					/* Get the node's parent,then assign to the node_current */
			}

			if (NULL != node) {
				id_far_left = tree_family_node_control_get_relation_with_parent(tree_family, node, node_current) - 2 + 1;

				goto EXIT;
			}
		}
	}

	id_far_left = 0;

EXIT:

	if (NULL != node_current) {
		get_precursor_successor_return.node = node_current;
		get_precursor_successor_return.location = id_far_left;
		get_precursor_successor_return.data = *((void **)node_current->data + id_far_left);
	}

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("successor is %p's No.%d:\"%s\"-%d \r\n",
		   get_precursor_successor_return.node,
		   get_precursor_successor_return.location,
		   (char *)get_precursor_successor_return.data,
		   (size_t)TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_DATA(get_precursor_successor_return.data) - '0');

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	return get_precursor_successor_return;
}

/**
* @brief This function will print all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_traversal_printer(tree_family_stp tree_family,
										   void *node,
										   container_size_t data_element_count)
{
	printf("node:%p data: ", node);

	char ***data = node;

	for (size_t id_data = DATA_OPERATOR_CODE_DATA_FAR_LEFT; id_data < data_element_count; id_data++) {
		if (NULL != *(*data + id_data)) {
			if (DATA_OPERATOR_CODE_DATA_FAR_LEFT < id_data) {
				printf("\r\n");
			}
			printf("key:\"%s\"-%d content:\"%s\" ", 
				   *(*data + id_data), *(*(*data + id_data)) - '0', 
				   (char *)((size_t)(*(*data + id_data)) 
							+ tree_family_control_environment.extra_info.mem_size_key));
		}
	}

	printf("data_addr:%p link_addr:%p \r\n",
		   *((void **)node + 0), *((void **)node + 1));
}

/**
* @brief This function will destroy all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_destroy_posorder_traversal_operator(tree_family_stp tree_family,
															 void *node,
															 container_size_t data_element_count)
{
	printf("will destroy ");

	tree_family_control_traversal_printer(tree_family, node, data_element_count);

	//if (2 <= tree_family_node_control_get_node_type(tree_family, node)) {		/* Not binary node */
	//
	//}

	//tree_family_control_destroy_node(tree_family, &node);
}

/**
* @brief This function will replace the switch_control(tree_family) before enter control sandbox.
*
* @param void
*
* @return void
*/

void tree_family_control_switch_control_in_sandbox(tree_family_stp tree_family)
{
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configuration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configuration_exception_default_full_callback(void)
{
}