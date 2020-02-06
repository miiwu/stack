/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "binary_tree_family.h"

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
 * @brief This variables will record the binary_tree_family_member_type_e.
 */

enum binary_tree_family_member_type_e binary_tree_family_control_type_in_control = BINARY_TREE_FAMILY_AVL_TREE;

/**
 * @brief This variables will record the tree_node_operator.
 */

struct binary_tree_family_node_operator_s binary_tree_family_control_node_operator = { NULL };

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

static size_t binary_tree_family_control_get_node_len(enum binary_tree_family_member_type_e type);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void binary_tree_family_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void binary_tree_family_control_configration_exception_default_full_callback(void);

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

extern inline void binary_tree_family_control_get_control(enum binary_tree_family_member_type_e type,
														  struct binary_tree_family_node_operator_s node_operator)
{
	binary_tree_family_control_type_in_control = type;
	binary_tree_family_control_node_operator = node_operator;
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

void binary_tree_family_control_configuration_init(struct binary_tree_family_s **tree,
												   void (*switch_control)(void),
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

	struct binary_tree_family_s
		*tree_alloced = allocator_ctrl->allocate(allocator,
												 1, sizeof(struct binary_tree_family_s));	/* Allocate #1 */

	if (NULL == tree ||																	/* Check if tree point to NULL			*/
		NULL == tree_alloced) {															/* Check if tree_alloced point to NULL	*/
		return;
	}

	tree_alloced->container_type_id = binary_tree_family_control_type_in_control;						/* Assign tree structure					*/

	tree_alloced->info.max_size = 0;
	tree_alloced->info.size = 0u;
	tree_alloced->info.mem_size = element_size;

	tree_alloced->allocator = allocator;
	tree_alloced->allocator_ctrl = allocator_ctrl;

	tree_alloced->root = NULL;

	tree_alloced->exception.empty = binary_tree_family_control_configration_exception_default_empty_callback;
	tree_alloced->exception.full = binary_tree_family_control_configration_exception_default_full_callback;

	tree_alloced->switch_control = switch_control;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		tree_alloced->element_handler.assign = assign;
		tree_alloced->element_handler.free = free;
	}

	*tree = tree_alloced;

	#if (VECTOR_CFG_DEBUG_EN)												/* Debug only								*/

	printf("tree.configuration.init:allocator : %p \r\n", allocator);
	printf("tree.configuration.init:tree block : %p \r\n", tree_alloced);

	#endif // (VECTOR_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the tree struct and free the space
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void binary_tree_family_control_configuration_destroy(struct binary_tree_family_s **tree)
{
	assert(tree);

	(*tree)->switch_control();

	void *allocator = (*tree)->allocator;

	struct allocator_control_s *allocator_ctrl = (*tree)->allocator_ctrl;

	#if (VECTOR_CFG_DEBUG_EN)

	printf("tree.configuration.destroy:allocator : %p \r\n", allocator);
	printf("tree.configuration.destroy:tree block : %p \r\n", (*tree));
	printf("tree.configuration.destroy:tree node block : %p \r\n", (*tree)->node);

	#endif // (VECTOR_CFG_DEBUG_EN)

	if (0 < (*tree)->info.size) {
		struct tree_node_s
			*node = NULL;

		for (size_t cnt = 0; cnt < (*tree)->info.size; cnt++) {
			node = binary_tree_family_control_node_operator.del((*tree), 0);

			binary_tree_family_control_destroy_node((*tree), node);
		}
	}

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

void binary_tree_family_control_configuration_element_handler(struct binary_tree_family_s *tree,
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

void binary_tree_family_control_configuration_exception(struct binary_tree_family_s *tree,
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
//
///**
// * @brief This function will returns a reference to the first element in the container
// *
// * @param tree the pointer to the tree struct pointer
// *
// * @return the reference to the first element in the container
// */
//
//void *binary_tree_family_control_element_access_front(struct binary_tree_family_s *tree)
//{
//	assert(tree);
//
//	return tree_node_control_get_data(tree, 0);
//}
//
///**
// * @brief This function will returns a reference to the specified element in the container.
// *
// * @param tree the pointer to the tree struct pointer
// * @param position the position of node,it would be equal or greater than zero
// *
// * @return NONE
// */
//
//void *binary_tree_family_control_element_access_at(struct binary_tree_family_s *tree,
//												   CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
//{
//	assert(tree);
//
//	return tree_node_control_get_data(tree, position);
//}
//
///**
// * @brief This function will checks if the container has no elements
// *
// * @param tree the pointer to the tree struct pointer
// *
// * @return
//	- true,the container has no elements
//	- false,the container has elements
// */
//
//extern inline bool binary_tree_family_control_capacity_empty(struct binary_tree_family_s *tree)
//{
//	assert(tree);
//
//	if (tree->info.max_size <= tree->info.size) {
//		return true;
//	} else {
//		return false;
//	}
//}
//
///**
// * @brief This function will returns the maximum number of elements the container
//			is able to hold due to system or library implementation limitations
// *
// * @param tree the pointer to the tree struct pointer
// *
// * @return the maximum number of elements
// */
//
//extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE binary_tree_family_control_capacity_max_size(struct binary_tree_family_s *tree)
//{
//	assert(tree);
//
//	return tree->info.max_size;
//}
//
///**
// * @brief This function will returns the number of elements in the container
// *
// * @param tree the pointer to the tree struct pointer
// *
// * @return the number of elements in the container
// */
//
//extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE binary_tree_family_control_capacity_size(struct binary_tree_family_s *tree)
//{
//	assert(tree);
//
//	return tree->info.size;
//}
//
///**
// * @brief This function will erases all elements from the container
// *
// * @param tree the pointer to the tree struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_clear(struct binary_tree_family_s *tree)
//{
//	assert(tree);
//
//	for (size_t cnt = tree->info.size; cnt > 0; cnt--) {
//		binary_tree_family_control_modifiers_erase_after(tree, 0);
//	}
//}
//
///**
// * @brief This function will inserts elements after the specified position in the container
// *
// * @param tree the pointer to the tree struct pointer
// * @param position the position of element,it would be equal or greater than zero
// * @param amount the amount of the source
// * @param source pointer to the source
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_insert_after(struct binary_tree_family_s *tree,
//													   CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
//													   CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
//{
//	assert(tree);
//	assert(0 <= position);
//	assert(0 < amount);
//	assert(source);
//	assert(*source);
//
//	tree->switch_control();
//
//	void
//		*source_addr = NULL;
//
//	CONTAINER_GLOBAL_CFG_SIZE_TYPE
//		pos_insert_head = tree->info.size,
//		pos_insert_tail = position + amount;
//
//ENSURE_THE_LIST_HAS_ENOUGH_NODE:
//
//	if (pos_insert_tail > pos_insert_head) {												/* Ensure the tree has enough node */
//		for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = pos_insert_head; pos < pos_insert_tail; pos++) {
//			binary_tree_family_control_node_operator.set(tree, pos_insert_head, NULL);
//		}
//	}
//
//	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = position; pos < pos_insert_tail; pos++) {		/* Set the data to the tree node */
//		source_addr = (void *)((size_t)*source + (pos - position) * tree->info.mem_size);
//
//		if ('\0' != *(char *)tree_node_control_get_data(tree, pos)) {			/* Ensure the tree node has no data */
//			pos_insert_head = position;
//
//			goto ENSURE_THE_LIST_HAS_ENOUGH_NODE;
//		}
//
//		#if (LIST_FAMILY_CFG_DEBUG_EN)
//
//		printf("tree.modifiers.insert_after:No.%d:\"%s\" \r\n", pos, (char *)source_addr);
//
//		#endif // (VECTOR_CFG_DEBUG_EN)
//
//		tree_node_control_set_data(tree, pos, source_addr);
//	}
//}
//
///**
// * @brief This function will push a new element on top of the stack, and the element is constructed in-place
// *
// * @param tree the pointer to the tree struct pointer
// * @param position the position of element,it would be equal or greater than zero
// * @param destination pointer to the destination
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_emplace_after(struct binary_tree_family_s *stack,
//														CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
//{
//}
//
///**
// * @brief This function will erases the specified elements from the container
// *
// * @param tree the pointer to the tree struct pointer
// * @param position the position of element,it would be equal or greater than zero
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_erase_after(struct binary_tree_family_s *tree,
//													  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
//{
//	assert(tree);
//	assert(0 <= position);
//
//	#if (LIST_FAMILY_CFG_DEBUG_EN)
//
//	printf("tree.modifiers.earse_after no.%d: \"%s\" \r\n",
//		   position, (char *)tree_node_control_get_data(tree, position));
//
//	#endif // (LIST_FAMILY_CFG_DEBUG_EN)
//
//	tree_node_control_del_data(tree, position);
//}
//
///**
// * @brief This function will prepends the given element value to the beginning of the container
// *
// * @param tree the pointer to the tree struct pointer
// * @param source pointer to the source
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_push_front(struct binary_tree_family_s *tree,
//													 void *source)
//{
//	assert(tree);
//	assert(source);
//
//	binary_tree_family_control_modifiers_insert_after(tree, 0, 1, &source);
//
//	tree_node_control_set_data(tree, 0, source);
//}
//
///**
// * @brief This function will Inserts a new element to the beginning of the container.
//			The element is constructed through std::allocator_traits::construct,
//			which typically uses placement-new to construct the element in-place
//			at the location provided by the container.
//			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
// *
// * @param tree the pointer to the tree struct pointer
// * @param destination pointer to the destination
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_emplace_front(struct binary_tree_family_s *stack,
//														void *destination)
//{
//}
//
///**
// * @brief This function will removes the first element of the container
// *
// * @param tree the pointer to the tree struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_pop_front(struct binary_tree_family_s *tree)
//{
//	assert(tree);
//
//	tree_node_control_del_data(tree, 0);
//}
//
///**
// * @brief This function will increase the capacity of the tree to a size
//			that's greater or equal to new_cap
// *
// * @param tree the pointer to the tree struct pointer
// * @param size the size of the tree struct
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_resize(struct binary_tree_family_s **tree,
//												 CONTAINER_GLOBAL_CFG_SIZE_TYPE size)
//{
//}
//
///**
// * @brief This function will exchanges the contents of the container with those of other
// *
// * @param tree the pointer to the tree struct pointer
// * @param other the pointer to the other tree struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_swap(struct binary_tree_family_s **tree,
//											   struct binary_tree_family_s **other)
//{
//	assert(tree);
//	assert(other);
//
//	struct binary_tree_family_s **
//		tree_swap = (*tree)->allocator_ctrl->allocate((*tree)->allocator, 1, sizeof(void *));
//
//	*(tree_swap) = *tree;
//	*(tree_swap + 1) = *other;
//
//	*tree = *(tree_swap + 1);
//	*other = *tree_swap;
//}
//
///**
// * @brief This function will finds an element with key equivalent to key.
// *
// * @param tree the pointer to the tree struct pointer
// * @param other the pointer to the other tree struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_lookup_find(struct binary_tree_family_s *tree,
//											CONTAINER_GLOBAL_CFG_SIZE_TYPE key)
//{
//	assert(tree);
//}
//
///**
// * @brief This function will copy the contents of the container to those of other
// *
// * @param destination the pointer to the destination tree struct pointer
// * @param source the pointer to the source tree struct
// *
// * @return NONE
// */
//
//void binary_tree_family_control_modifiers_copy(struct binary_tree_family_s **destination,
//											   struct binary_tree_family_s *source)
//{
//	assert(destination);
//	assert(source);
//
//	struct tree_node_s
//		*node_source = (void *)(size_t)(source->root);
//
//	if (NULL == (*destination) ||										/* Check if destination have been initialized */
//		NULL == (*destination)->allocator ||							/* if not,then initialize it */
//		NULL == (*destination)->allocator_ctrl ||
//		NULL == (*destination)->root) {
//		enum allocator_type_e *allocator_type = source->allocator;
//
//		binary_tree_family_control_configuration_init(destination,
//													  source->switch_control,
//													  *allocator_type,
//													  source->info.mem_size, source->element_handler.assign, source->element_handler.free);
//	} else {															/* if so,just assign */
//		(*destination)->info = source->info;
//		(*destination)->element_handler = source->element_handler;
//		(*destination)->exception = source->exception;
//	}
//
//	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos < source->info.size; pos++) {
//		tree_node_control_set_data(*destination, pos, tree_node_control_get_data(source, pos));
//	}
//}

/**
 * @brief This function will return the memory size of the specified tree type node.
 *
 * @param type the specified tree type
 *
 * @return the memory size of the specified node
 */

size_t binary_tree_family_control_get_node_len(enum binary_tree_family_member_type_e type)
{
	assert(type);

	size_t mem_size = 0;

	//switch (type) {
	//	case LIST:
	//		mem_size = sizeof(struct tree_node_s);
	//		break;
	//	case FORWARD_LIST:
	//		mem_size = sizeof(struct forward_tree_node_s);
	//		break;
	//	default:
	//		break;
	//}

	return mem_size;
}

/**
 * @brief This function will initialize the tree node struct.
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void *binary_tree_family_control_init_node(struct binary_tree_family_s *tree)
{
	assert(tree);

	void *node_alloced = tree->allocator_ctrl->allocate(tree->allocator,
														1, binary_tree_family_control_get_node_len(binary_tree_family_control_type_in_control));	/* Allocate #1 */

	void *data_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, tree->info.mem_size);			/* Allocate #2 */

	void **data_ptr = (void *)node_alloced;

	if (NULL == tree ||																			/* Check if tree point to NULL			*/
		NULL == node_alloced ||																	/* Check if tree node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	*data_ptr = data_pack_allocated;															/* Assign tree_node structure					*/

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

void binary_tree_family_control_destroy_node(struct binary_tree_family_s *tree,
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
//
///**
// * @brief This function will destroy tree node struct and free the space.
// *
// * @param tree the pointer to the tree struct pointer
// * @param node the pointer to the tree node struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_preorder_traversal(struct binary_tree_family_s *tree,
//												   void *node)
//{
//	assert(tree);
//
//	struct binary_tree_family_link_node_s
//		*node_current = node;
//
//	if (NULL == node) {
//		return;
//	}
//
//	/* printf */
//	binary_tree_family_control_preorder_traversal(tree, node_current->lchild);
//	binary_tree_family_control_preorder_traversal(tree, node_current->rchild);
//}
//
///**
// * @brief This function will destroy tree node struct and free the space.
// *
// * @param tree the pointer to the tree struct pointer
// * @param node the pointer to the tree node struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_inorder_traversal(struct binary_tree_family_s *tree,
//												  void *node)
//{
//	assert(tree);
//
//	struct binary_tree_family_link_node_s
//		*node_current = node;
//
//	if (NULL == node) {
//		return;
//	}
//
//	binary_tree_family_control_inorder_traversal(tree, node_current->lchild);
//	/* printf */
//	binary_tree_family_control_inorder_traversal(tree, node_current->rchild);
//}
//
///**
// * @brief This function will destroy tree node struct and free the space.
// *
// * @param tree the pointer to the tree struct pointer
// * @param node the pointer to the tree node struct pointer
// *
// * @return NONE
// */
//
//void binary_tree_family_control_posorder_traversal(struct binary_tree_family_s *tree,
//												   void *node)
//{
//	assert(tree);
//
//	struct binary_tree_family_link_node_s
//		*node_current = node;
//
//	if (NULL == node) {
//		return;
//	}
//
//	binary_tree_family_control_inorder_traversal(tree, node_current->lchild);
//	binary_tree_family_control_inorder_traversal(tree, node_current->rchild);
//	/* printf */
//}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void binary_tree_family_control_configration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void binary_tree_family_control_configration_exception_default_full_callback(void)
{
}