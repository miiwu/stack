/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "forward_list.h"

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
 * @brief This struct is the forward_list structure module
 */

struct forward_list_node_t {
	/* @brief This variables will point to the address of the forward_list data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list node.										*/
	struct forward_list_node_t *next;
};

/**
 * @brief This struct is the forward_list structure module
 */

struct forward_list_t {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type	container_type_id;

	struct {
		/* @brief This variables will record the maximum number of elements.							*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE max_size;

		/* @brief This variables will record the number of elements that
				  the container has currently allocated space for.										*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE size;

		/* @brief This variables will record the size that each element will take up.					*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE mem_size;
	}info;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_t *allocator_ctrl;

	/* @brief This variables will pointer to the first list node.										*/
	struct forward_list_node_t *node;

	/* @brief This variables will record the element handler of the container.							*/
	struct element_handler_t element_handler;

	struct {
		/* @brief This variables will point to the address of the forward_list empty exception handler.		*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the forward_list full exception handler.			*/
		void (*full)(void);
	}exception;
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

/**
 * @brief This array will contain all the universal forward_list functions address.
 */

void *forward_list_function_address_tables[] =
{
	(void *)&forward_list_control_configuration_init,					/* No.0 : initialize */

	(void *)&forward_list_control_configuration_destroy,					/* No.1 : destroy */

	(void *)&forward_list_control_element_access_front,						/* No.3 : at */

	(void *)&forward_list_control_capacity_empty,						/* No.4 : empty */

	(void *)&forward_list_control_capacity_size,							/* No.5 : size */

	(void *)&forward_list_control_capacity_max_size,						/* No.6 : max_size */

	(void *)&forward_list_control_modifiers_insert_after,						/* No.7 : insert */

	(void *)&forward_list_control_modifiers_erase_after,						/* No.8 : erase */

	//(void *)&forward_list_control_modifiers_swap,						/* No.9 : swap */

	//(void *)&forward_list_control_modifiers_copy,						/* No.10 : copy */
};

#if (FORWARD_LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the forward_list functions conveniently.
 */

struct forward_list_control_t forward_list_ctrl = {
	{
		forward_list_control_configuration_init,
		forward_list_control_configuration_destroy,
		forward_list_control_configuration_element_handler,
		forward_list_control_configuration_exception,
	},
	{
		NULL
	},
	{
		forward_list_control_element_access_front,
	},
	{
		forward_list_control_capacity_empty,
		forward_list_control_capacity_max_size,
		forward_list_control_capacity_size,
	},
	{
		forward_list_control_modifiers_clear,
		forward_list_control_modifiers_insert_after,
		forward_list_control_modifiers_emplace_after,
		forward_list_control_modifiers_erase_after,
		forward_list_control_modifiers_push_front,
		forward_list_control_modifiers_emplace_front,
		forward_list_control_modifiers_pop_front,
		forward_list_control_modifiers_resize,
		forward_list_control_modifiers_swap,
		forward_list_control_modifiers_copy,
	},
	{
		forward_list_control_list_operations_merge,
		forward_list_control_list_operations_splice_after,
		forward_list_control_list_operations_remove,
		forward_list_control_list_operations_remove_if,
		forward_list_control_list_operations_reverse,
		forward_list_control_list_operations_unique,
		forward_list_control_list_operations_sort,
	}
};

#endif

void *forward_list_control_list_operations_remove_value = NULL;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the forward list node struct.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_init_node(FORWARD_LIST_TYPEDEF_PTR forward_list);

/**
 * @brief This function will destroy forward list node struct and free the space.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 *
 * @return NONE
 */

void forward_list_control_destroy_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
									   struct forward_list_node_t *node);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_set_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position, struct forward_list_node_t *node);

/**
* @brief This function will get the node at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param position the position of node,it would be equal or greater than zero
*
* @return the node at the specified location in the container
*/

struct forward_list_node_t *forward_list_control_get_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_del_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
								   CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will swap the node at the specified location in the container
 *			by the stable bubble swap algorithm.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_swap_node_stable_bubble_swap(FORWARD_LIST_TYPEDEF_PTR forward_list,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE dst_pos,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE src_pos);

/**
* @brief This function will set elements at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param source pointer to the source
*
* @return NONE
*/

void forward_list_node_control_set_data(FORWARD_LIST_TYPEDEF_PTR forward_list,
										CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

/**
* @brief This function will get elements at the specified location node in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *forward_list_node_control_get_data(FORWARD_LIST_TYPEDEF_PTR forward_list,
										 CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
* @brief This function will delete elements at the specified location node in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void forward_list_node_control_del_data(FORWARD_LIST_TYPEDEF_PTR forward_list,
										CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data forward list will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

bool forward_list_control_remove_rule(void *data);

/**
* @brief This function will compare if the left-hand-side lesser than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side lesser than the right-hand-side
*	- true	yes
*	- false	no
*/

bool forward_list_control_default_sort_comp_lesser(void *lhs, void *rhs, size_t len);

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

bool forward_list_control_default_sort_comp_greater(void *lhs, void *rhs, size_t len);

/**
* @brief This function will compare if the left-hand-side equal with the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side equal with the right-hand-side
*	- true	yes
*	- false	no
*/

bool forward_list_control_default_sort_comp_equal(void *lhs, void *rhs, size_t len);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void forward_list_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void forward_list_control_configration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the forward_list struct
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param element_size the element memory size of the forward list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void forward_list_control_configuration_init(FORWARD_LIST_TYPEDEF_PPTR forward_list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(forward_list);
	assert(0 <= element_size);

	void
		*allocator = NULL;

	struct allocator_control_t
		*allocator_ctrl = NULL;

	allocator_ctrl = allocator_control_convert_type_to_func_addr_table(FORWARD_LIST_CFG_ALLOCATOR_TYPE);	/* Variables pointer to	the function address table of
																															specified container type		*/

	allocator_ctrl->configration.init(&allocator, NULL);

	struct forward_list_t
		*forward_list_alloced = (struct forward_list_t *)allocator_ctrl->allocate(allocator,
																				  1, sizeof(struct forward_list_t));	/* Allocate #1 */

	if (NULL == forward_list ||																	/* Check if forward_list point to NULL			*/
		NULL == forward_list_alloced) {															/* Check if forward_list_alloced point to NULL	*/
		return;
	}

	forward_list_alloced->container_type_id = FORWARD_LIST;												/* Assign forward_list structure					*/

	forward_list_alloced->info.max_size = FORWARD_LIST_CFG_DEFAULT_MAX_SIZE;
	forward_list_alloced->info.size = 0u;
	forward_list_alloced->info.mem_size = element_size;

	forward_list_alloced->allocator = allocator;
	forward_list_alloced->allocator_ctrl = allocator_ctrl;

	forward_list_alloced->node = NULL;

	forward_list_alloced->element_handler.assign = NULL;
	forward_list_alloced->element_handler.free = NULL;

	forward_list_alloced->exception.empty = forward_list_control_configration_exception_default_empty_callback;
	forward_list_alloced->exception.full = forward_list_control_configration_exception_default_full_callback;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		forward_list_alloced->element_handler.assign = assign;
		forward_list_alloced->element_handler.free = free;
	}

	*forward_list = forward_list_alloced;

	#if (VECTOR_CFG_DEBUG_EN)												/* Debug only								*/

	printf("forward list.configuration.init:allocator : %p \r\n", allocator);
	printf("forward list.configuration.init:forward_list block : %p \r\n", forward_list_alloced);

	#endif // (VECTOR_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the forward_list struct and free the space
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_configuration_destroy(FORWARD_LIST_TYPEDEF_PPTR forward_list)
{
	assert(forward_list);

	void
		*allocator = (*forward_list)->allocator;

	struct allocator_control_t
		*allocator_ctrl = (*forward_list)->allocator_ctrl;

	#if (VECTOR_CFG_DEBUG_EN)

	printf("forward list.configuration.destroy:allocator : %p \r\n", allocator);
	printf("forward list.configuration.destroy:forward_list block : %p \r\n", (*forward_list));
	printf("forward list.configuration.destroy:forward_list node block : %p \r\n", (*forward_list)->node);

	#endif // (VECTOR_CFG_DEBUG_EN)

	if (0 < (*forward_list)->info.size) {
		struct forward_list_node_t
			*node = (*forward_list)->node,
			*node_next = node->next;

		for (size_t cnt = 0; cnt < (*forward_list)->info.size; cnt++) {
			node_next = node->next;

			forward_list_control_destroy_node((*forward_list), node);

			node = node_next;
		}
	}

	(*forward_list)->container_type_id = 0u;														/* Assign forward_list structure					*/

	(*forward_list)->info.max_size = 0u;
	(*forward_list)->info.size = 0u;
	(*forward_list)->info.mem_size = 0u;

	(*forward_list)->allocator = NULL;

	(*forward_list)->node = NULL;

	(*forward_list)->exception.empty = NULL;
	(*forward_list)->exception.full = NULL;

	allocator_ctrl->deallocate(allocator, *forward_list, 1);																			/* deallocate #1 */

	allocator_ctrl->configration.destroy(&allocator);

	*forward_list = NULL;
}

/**
 * @brief This function will configure the forward_list element handler
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void forward_list_control_configuration_element_handler(FORWARD_LIST_TYPEDEF_PTR forward_list,
														void (*assign)(void *dst, void *src), void(*free)(void *dst))
{
	assert(forward_list);
	assert(assign);
	assert(free);

	forward_list->element_handler.assign = assign;
	forward_list->element_handler.free = free;
}

/**
 * @brief This function will configure the forward_list exception callback
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void forward_list_control_configuration_exception(FORWARD_LIST_TYPEDEF_PTR forward_list,
												  void (*empty)(void), void (*full)(void))
{
	assert(forward_list);

	if (NULL == empty) {
		forward_list->exception.empty = empty;
	}

	if (NULL == full) {
		forward_list->exception.full = full;
	}
}

/**
 * @brief This function will returns a reference to the first element in the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return the reference to the first element in the container
 */

void *forward_list_control_element_access_front(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	return forward_list_node_control_get_data(forward_list, 0);
}

/**
 * @brief This function will checks if the container has no elements
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

inline bool forward_list_control_capacity_empty(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	if (forward_list->info.max_size <= forward_list->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return the maximum number of elements
 */

inline CONTAINER_GLOBAL_CFG_SIZE_TYPE forward_list_control_capacity_max_size(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	return forward_list->info.max_size;
}

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return the number of elements in the container
 */

inline CONTAINER_GLOBAL_CFG_SIZE_TYPE forward_list_control_capacity_size(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	return forward_list->info.size;
}

/**
 * @brief This function will erases all elements from the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_clear(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	for (size_t cnt = forward_list->info.size; cnt > 0; cnt--) {
		forward_list_control_modifiers_erase_after(forward_list, 0);
	}
}

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_control_modifiers_insert_after(FORWARD_LIST_TYPEDEF_PTR forward_list,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
{
	assert(forward_list);
	assert(0 <= position);
	assert(0 < amount);
	assert(source);
	assert(*source);

	void
		*source_addr = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		pos_insert_head = forward_list->info.size,
		pos_insert_tail = position + amount;

ENSURE_THE_FORWARD_LIST_HAS_ENOUGH_NODE:

	if (pos_insert_tail > pos_insert_head) {												/* Ensure the forward list has enough node */
		for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = pos_insert_head; pos < pos_insert_tail; pos++) {
			forward_list_control_set_node(forward_list, pos_insert_head, NULL);
		}
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = position; pos < pos_insert_tail; pos++) {		/* Set the data to the forward list node */
		source_addr = (void *)((size_t)*source + (pos - position) * forward_list->info.mem_size);

		if ('\0' != *(char *)forward_list_node_control_get_data(forward_list, pos)) {			/* Ensure the forward list node has no data */
			pos_insert_head = position;

			goto ENSURE_THE_FORWARD_LIST_HAS_ENOUGH_NODE;
		}

		#if (VECTOR_CFG_DEBUG_EN)

		printf("forward_list.modifiers.insert_after:No.%d:\"%s\" \r\n", pos, (char *)source_addr);

		#endif // (VECTOR_CFG_DEBUG_EN)

		forward_list_node_control_set_data(forward_list, pos, source_addr);
	}
}

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void forward_list_control_modifiers_emplace_after(FORWARD_LIST_TYPEDEF_PTR stack,
												  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
}

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_modifiers_erase_after(FORWARD_LIST_TYPEDEF_PTR forward_list,
												CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert(0 <= position);

	#if (FORWARD_LIST_CFG_DEBUG_EN)

	printf("forward_list.modifiers.earse_after no.%d: \" %s \" \r\n",
		   position, (char *)forward_list_node_control_get_data(forward_list, position));

	#endif // (FORWARD_LIST_CFG_DEBUG_EN)

	forward_list_node_control_del_data(forward_list, position);
}

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_control_modifiers_push_front(FORWARD_LIST_TYPEDEF_PTR forward_list,
											   void *source)
{
	assert(forward_list);

	struct forward_list_node_t
		*node_tmp = forward_list_control_init_node(forward_list);						/* Initialize a new node */

	node_tmp->next = forward_list_control_get_node(forward_list, 0);

	forward_list->node = node_tmp;

	forward_list_node_control_set_data(forward_list, 0, source);

	forward_list->info.size++;
}

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void forward_list_control_modifiers_emplace_front(FORWARD_LIST_TYPEDEF_PTR stack,
												  void *destination)
{
}

/**
 * @brief This function will removes the first element of the container
 *
 * @param forward_list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_pop_front(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	forward_list_node_control_del_data(forward_list, 0);
}

/**
 * @brief This function will increase the capacity of the forward_list to a size
			that's greater or equal to new_cap
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param size the size of the forward list struct
 *
 * @return NONE
 */

void forward_list_control_modifiers_resize(FORWARD_LIST_TYPEDEF_PPTR forward_list,
										   CONTAINER_GLOBAL_CFG_SIZE_TYPE size)
{
}

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param other the pointer to the other forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_modifiers_swap(FORWARD_LIST_TYPEDEF_PPTR forward_list,
										 FORWARD_LIST_TYPEDEF_PPTR other)
{
	assert(forward_list);
	assert(other);

	FORWARD_LIST_TYPEDEF_PPTR
		forward_list_swap = (*forward_list)->allocator_ctrl->allocate((*forward_list)->allocator, 1, sizeof(void *));

	*(forward_list_swap) = *forward_list;
	*(forward_list_swap + 1) = *other;

	*forward_list = *(forward_list_swap + 1);
	*other = *forward_list_swap;
}

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param source the pointer to the source forward list struct
 *
 * @return NONE
 */

void forward_list_control_modifiers_copy(FORWARD_LIST_TYPEDEF_PPTR destination,
										 FORWARD_LIST_TYPEDEF_PTR source)
{
	assert(destination);
	assert(source);

	struct forward_list_node_t
		*node_source = (void *)(size_t)(source->node);

	if (NULL == (*destination) ||
		NULL == (*destination)->allocator ||
		NULL == (*destination)->allocator_ctrl ||
		NULL == (*destination)->node) {																	/* Check if destination have been initialized */
		forward_list_control_configuration_init(destination,													/* if not,then initialize it */
												source->info.mem_size, source->element_handler.assign, source->element_handler.free);
	} else {
		(*destination)->info = source->info;															/* if so,just assign */
		(*destination)->element_handler = source->element_handler;
		(*destination)->exception = source->exception;
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos < source->info.size; pos++) {
		forward_list_node_control_set_data(*destination, pos, forward_list_node_control_get_data(source, pos));
	}
}

/**
 * @brief This function will merges two sorted lists into one
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param source the pointer to the source forward list struct
 *
 * @return NONE
 */

void forward_list_control_list_operations_merge(FORWARD_LIST_TYPEDEF_PTR destination,
												FORWARD_LIST_TYPEDEF_PTR other)
{
	assert(destination);
	assert(other);

	forward_list_control_list_operations_sort(destination, NULL);
	forward_list_control_list_operations_sort(other, NULL);

	forward_list_control_list_operations_splice_after(destination, 0, other, 0, other->info.size);
}

/**
 * @brief This function will moves elements from another forward_list to forward_list
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param other the pointer to the other forward list struct
 *
 * @return NONE
 */

void forward_list_control_list_operations_splice_after(FORWARD_LIST_TYPEDEF_PTR forward_list,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
													   FORWARD_LIST_TYPEDEF_PTR other,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE first,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE last)
{
	assert(forward_list);
	assert(other);

	struct forward_list_node_t
		*node_other = forward_list_control_get_node(other, first),
		*node_next_other = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		pos_tail_splice = position + last - first;

	if (NULL == node_other) {
		return;
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = position; pos < pos_tail_splice; pos++) {
		#if (FORWARD_LIST_CFG_DEBUG_EN)

		printf("forward_list.list_operatons.splice_after.source data no.%d:\"%s\" \r\n",
			   pos, (char *)node_other->data);

		#endif // (FORWARD_LIST_CFG_DEBUG_EN)

		node_next_other = node_other->next;

		forward_list_control_del_node(other, first);

		forward_list_control_set_node(forward_list, pos, node_other);

		node_other = node_next_other;
	}
}

/**
 * @brief This function will removes all elements satisfying specific criteria
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param data the pointer of data
 *
 * @return NONE
 */

void forward_list_control_list_operations_remove(FORWARD_LIST_TYPEDEF_PTR forward_list,
												 void *value)
{
	assert(forward_list);
	assert(value);

	forward_list_control_list_operations_remove_value = value;

	forward_list_control_list_operations_remove_if(forward_list, forward_list_control_remove_rule);
}

/**
 * @brief This function will
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param rule the pointer to the rule-making function
 *
 * @return NONE
 */

void forward_list_control_list_operations_remove_if(FORWARD_LIST_TYPEDEF_PTR forward_list, bool (*rule)(void *data))
{
	assert(forward_list);
	assert(rule);

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		cnt_reomve = 0,
		*pos_remove = forward_list->allocator_ctrl->allocate(forward_list->allocator, forward_list->info.size, sizeof(CONTAINER_GLOBAL_CFG_SIZE_TYPE));

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos < forward_list->info.size; pos++) {	/* Get which node's data is match */
		if (rule(forward_list_node_control_get_data(forward_list, pos))) {
			*(pos_remove + cnt_reomve++) = pos;
		}
	}

	struct  forward_list_node_t
		*node_del = NULL;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE cnt = 0; cnt < cnt_reomve; cnt++) {					/* Delete nodes matched */
		#if (FORWARD_LIST_CFG_DEBUG_EN)

		printf("forward_list.list_operatons.remove_if.no.%d: \"%s\" \r\n",
			   *(pos_remove + cnt), (char *)forward_list_node_control_get_data(forward_list, *(pos_remove + cnt) - cnt));

		#endif // (FORWARD_LIST_CFG_DEBUG_EN)

		forward_list_node_control_del_data(forward_list, *(pos_remove + cnt) - cnt);
	}

	forward_list->allocator_ctrl->deallocate(forward_list->allocator, pos_remove, forward_list->info.size);
}

/**
 * @brief This function will reverses the order of the elements in the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_list_operations_reverse(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	struct  forward_list_node_t
		*node_reverse = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE pos_last_forward_list_node_valid = forward_list->info.size - 1;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 0; pos <= pos_last_forward_list_node_valid; pos++) {
		node_reverse = forward_list_control_get_node(forward_list, pos_last_forward_list_node_valid);

		forward_list_control_del_node(forward_list, pos_last_forward_list_node_valid);

		forward_list_control_set_node(forward_list, pos, node_reverse);
	}
}

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void forward_list_control_list_operations_unique(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	char
		*data_prev = forward_list_node_control_get_data(forward_list, 0),
		*data = NULL;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		size_forward_list = forward_list->info.size,
		cnt_pos_repetitive = 0,
		(*pos_repetitive_store)[2] = forward_list->allocator_ctrl->allocate(forward_list->allocator,
																			size_forward_list, sizeof(CONTAINER_GLOBAL_CFG_SIZE_TYPE) * 2);

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = 1; pos < size_forward_list; pos++) {
		if (forward_list_control_default_sort_comp_equal(data_prev, (data = forward_list_node_control_get_data(forward_list, pos)), forward_list->info.mem_size)) {
			*(*(pos_repetitive_store + cnt_pos_repetitive) + 0) = pos;
		} else {
			if (*(*(pos_repetitive_store + cnt_pos_repetitive) + 0) != *(*(pos_repetitive_store + cnt_pos_repetitive) + 1)) {
				*(*(pos_repetitive_store + cnt_pos_repetitive) + 1) = pos;

				cnt_pos_repetitive++;
			}

			data_prev = data;
		}
	}

	#if (FORWARD_LIST_CFG_DEBUG_EN)

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		printf("forward_list.list_operatons.unique:no.%d from %d to %d is \"%s\" \r\n",
			   cnt, *(*(pos_repetitive_store + cnt) + 0),
			   *(*(pos_repetitive_store + cnt) + 1),
			   (char *)forward_list_node_control_get_data(forward_list, *(*(pos_repetitive_store + cnt) + 0)));
	}

	#endif // (FORWARD_LIST_CFG_DEBUG_EN)

	struct  forward_list_node_t
		*node_del = NULL;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		for (CONTAINER_GLOBAL_CFG_SIZE_TYPE pos = *(*(pos_repetitive_store + cnt) + 0); pos <= *(*(pos_repetitive_store + cnt) + 1); pos++) {
			node_del = forward_list_control_get_node(forward_list, *(*(pos_repetitive_store + cnt) + 0));

			forward_list_control_del_node(forward_list, *(*(pos_repetitive_store + cnt) + 0));

			forward_list_control_destroy_node(forward_list, node_del);
		}
	}

	forward_list->allocator_ctrl->deallocate(forward_list->allocator,
											 pos_repetitive_store, size_forward_list);
}

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void forward_list_control_list_operations_sort(FORWARD_LIST_TYPEDEF_PTR forward_list,
											   bool (*comp)(void *dst, void *src, size_t len))
{
	assert(forward_list);

	if (NULL == comp) {
		comp = forward_list_control_default_sort_comp_greater;
	}

	struct forward_list_node_t
		*node_head = forward_list->node,
		*node_prev = NULL;

	for (size_t cnt = 0; cnt < forward_list->info.size - 1; cnt++) {
		for (size_t ct = 0; ct < forward_list->info.size - cnt - 1; ct++) {
			if (comp(forward_list_node_control_get_data(forward_list, ct), forward_list_node_control_get_data(forward_list, ct + 1), forward_list->info.mem_size)) {
				#if (FORWARD_LIST_CFG_DEBUG_EN)

				//printf("forward_list.list_operatons.sort.no.%d-%d: %d \"%s\" swap %d \"%s\" \r\n",
				//	   cnt, ct, ct, (char *)forward_list_node_control_get_data(forward_list, ct), ct + 1, (char *)forward_list_node_control_get_data(forward_list, ct + 1));

				#endif // (FORWARD_LIST_CFG_DEBUG_EN)

				forward_list_control_swap_node_stable_bubble_swap(forward_list, ct, ct + 1);
			}
		}
	}
}

/**
 * @brief This function will initialize the forward list node struct.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_init_node(FORWARD_LIST_TYPEDEF_PTR forward_list)
{
	assert(forward_list);

	struct forward_list_node_t
		*node_alloced = forward_list->allocator_ctrl->allocate(forward_list->allocator,
															   1, sizeof(struct forward_list_node_t));

	void
		*data_pack_allocated = forward_list->allocator_ctrl->allocate(forward_list->allocator,
																	  1, forward_list->info.mem_size);			/* Allocate #2 */

	if (NULL == forward_list ||																	/* Check if forward_list point to NULL			*/
		NULL == node_alloced ||																	/* Check if forward_list node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	node_alloced->data = data_pack_allocated;													/* Assign forward_list_node structure					*/
	node_alloced->next = NULL;

	#if (VECTOR_CFG_DEBUG_EN)												/* Debug only								*/

	printf("forward list.modifiers.init node:node block : %p \r\n", node_alloced);
	printf("forward list.modifiers.init node:node date block : %p \r\n", data_pack_allocated);

	#endif // (VECTOR_CFG_DEBUG_EN)

	return node_alloced;
}

/**
 * @brief This function will destroy forward list node struct and free the space.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 *
 * @return NONE
 */

void forward_list_control_destroy_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
									   struct forward_list_node_t *node)
{
	assert(forward_list);

	if (NULL == node) {
		return;
	}

	#if (VECTOR_CFG_DEBUG_EN)												/* Debug only								*/

	printf("forward list.modifiers.destroy node:node block : %p \r\n", (*node));
	printf("forward list.modifiers.destroy node:node date block : %p \r\n", (*node)->data);

	#endif // (VECTOR_CFG_DEBUG_EN)

	forward_list->allocator_ctrl->deallocate(forward_list->allocator, node->data, 1);																/* Deallocate #2 */

	node->data = NULL;												/* Assign forward_list structure					*/
	node->next = NULL;

	forward_list->allocator_ctrl->deallocate(forward_list->allocator, node, 1);																		/* deallocate #1 */

	node = NULL;
}

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_set_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position, struct forward_list_node_t *node)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	if (NULL == node) {
		node = forward_list_control_init_node(forward_list);

		if (NULL == node) {
			return NULL;
		}
	}

	struct forward_list_node_t
		*node_prev = NULL;

	node->next = forward_list_control_get_node(forward_list, position);				/* Merge the node that in forward_list position to node */

	node_prev = forward_list_control_get_node(forward_list, position - 1);

	if (NULL == node_prev) {														/* If the previous node is NULL,the node must be the head. */
		forward_list->node = node;
	} else {
		node_prev->next = node;
	}

	forward_list->info.size++;

	return node;
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

struct forward_list_node_t *forward_list_control_get_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
	CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert((0 <= position));

	if (forward_list->info.max_size <= position ||
		0 > position) {
		return NULL;
	}

	struct forward_list_node_t
		**current_node = &forward_list->node;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		currrent_position = 0;

LOOP:

	if (NULL == current_node ||
		NULL == *current_node ||
		currrent_position >= position) {
		return *current_node;
	}

	current_node = &(*current_node)->next;

	currrent_position++;

	goto LOOP;
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_del_node(FORWARD_LIST_TYPEDEF_PTR forward_list,
								   CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert((0 <= position));

	struct forward_list_node_t
		*node_del = forward_list_control_get_node(forward_list, position),
		*node_prev = forward_list_control_get_node(forward_list, position - 1);

	if (forward_list->info.max_size <= position ||
		0 > position ||
		NULL == node_del ||
		((0 < position - 1) ?
		(false) :
		 (NULL == node_prev))) {
		return;
	}

	if (NULL != node_prev) {
		node_prev->next = node_del->next;
	} else {
		forward_list->node = node_del->next;
	}

	forward_list->info.size--;
}

/**
 * @brief This function will swap the node at the specified location in the container
 *			by the stable bubble swap algorithm.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void forward_list_control_swap_node_stable_bubble_swap(FORWARD_LIST_TYPEDEF_PTR forward_list,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE dst_pos,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE src_pos)
{
	assert(forward_list);

	if (forward_list->info.size <= dst_pos ||
		forward_list->info.size <= src_pos) {
		return;
	}

	if (dst_pos > src_pos) {
		CONTAINER_GLOBAL_CFG_SIZE_TYPE tmp = dst_pos;

		dst_pos = src_pos;
		src_pos = tmp;
	}

	struct forward_list_node_t
		*node_dst = forward_list_control_get_node(forward_list, dst_pos),
		*node_dst_prev = forward_list_control_get_node(forward_list, dst_pos - 1),
		*node_dst_next = node_dst->next,
		*node_src = forward_list_control_get_node(forward_list, src_pos),
		*node_src_prev = forward_list_control_get_node(forward_list, src_pos - 1),
		*node_src_next = node_src->next;

	if ((size_t)node_src != (size_t)node_dst_next) {
		node_src->next = node_dst_next;
	}

	if (NULL != node_dst_prev) {
		node_dst_prev->next = node_src;
	} else {
		forward_list->node = node_src;
	}

	if ((size_t)node_dst != (size_t)node_src_prev) {
		node_src_prev->next = node_dst;
	} else {
		node_src->next = node_dst;
	}

	node_dst->next = node_src_next;
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param node the pointer to the forward list node struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void forward_list_node_control_set_data(FORWARD_LIST_TYPEDEF_PTR forward_list,
										CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source)
{
	assert(forward_list);
	assert(0 <= position);
	assert(source);

	struct forward_list_node_t
		*node = forward_list_control_get_node(forward_list, position);

	if (NULL == node) {
		node = forward_list_control_set_node(forward_list, position, NULL);

		if (NULL == node) {
			return;
		}
	}

	if (NULL == (node)->data) {
		(node)->data = forward_list->allocator_ctrl->allocate(forward_list->allocator,
															  1, forward_list->info.mem_size);/* Allocate #2 */

		if (NULL == (node)->data) {
			return;
		}
	}

	if (NULL != forward_list->element_handler.assign) {																		/* Check if assign point to NULL */
		forward_list->element_handler.assign((node)->data, source);
	} else {
		memcpy((node)->data, source, forward_list->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
* @brief This function will get elements at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param node the pointer to the forward list node struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *forward_list_node_control_get_data(FORWARD_LIST_TYPEDEF_PTR forward_list,
										 CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert(0 <= position);

	struct forward_list_node_t
		*node = forward_list_control_get_node(forward_list, position);

	if (NULL == node) {
		return NULL;
	}

	return node->data;
}

/**
* @brief This function will delete elements at the specified location in the container.
*
* @param forward_list the pointer to the forward list struct pointer
* @param node the pointer to the forward list node struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void forward_list_node_control_del_data(FORWARD_LIST_TYPEDEF_PTR forward_list,
										CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(forward_list);
	assert(0 <= position);

	forward_list_node_control_set_data(forward_list, position, "");

	#if (FORWARD_LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	struct forward_list_node_t
		*node_prev = forward_list->node,
		*node_destroy = forward_list_control_get_node(forward_list, position);

	if (NULL == node_destroy) {
		return;
	}

	if (0 < position) {
		forward_list_control_get_node(forward_list, position - 1)->next = node_destroy->next;
	} else {
		forward_list->node = forward_list->node->next;
	}

	forward_list_control_destroy_node(forward_list,
									  node_destroy);

	forward_list->info.size--;

	#endif // (FORWARD_LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	if (0 >= forward_list->info.size) {
		forward_list->exception.empty();

		return;
	}
}

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data forward list will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

bool forward_list_control_remove_rule(void *data)
{
	if (0 == strcmp(data, forward_list_control_list_operations_remove_value)) {
		return true;
	}

	return false;
}

/**
* @brief This function will compare if the left-hand-side lesser than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side lesser than the right-hand-side
*	- true	yes
*	- false	no
*/

bool forward_list_control_default_sort_comp_lesser(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) < *((char *)rhs + cnt)) {
			return true;
		}
	}

	return false;
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

bool forward_list_control_default_sort_comp_greater(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) > *((char *)rhs + cnt)) {
			return true;
		}
	}

	return false;
}

/**
* @brief This function will compare if the left-hand-side equal with the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side equal with the right-hand-side
*	- true	yes
*	- false	no
*/

bool forward_list_control_default_sort_comp_equal(void *lhs, void *rhs, size_t len)
{
	assert(lhs);
	assert(rhs);
	assert(len);

	size_t cnt_equal_hit = 0;

	for (size_t cnt = 0; cnt < len; cnt++) {
		if (*((char *)lhs + cnt) == *((char *)rhs + cnt)) {
			cnt_equal_hit++;
		} else {
			return false;
		}
	}

	if (len == cnt_equal_hit) {
		return true;
	} else {
		return false;
	}
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void forward_list_control_configration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void forward_list_control_configration_exception_default_full_callback(void)
{
}