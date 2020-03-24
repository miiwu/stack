/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "list_family.h"

#include "container_pte_def.h"

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
 * @brief This variables will record the list_family_member_type_e.
 */

enum list_family_member_type_e list_family_control_type_in_control = LIST;

/**
 * @brief This variables will record the list_node_operator.
 */

struct node_operator_s list_family_control_node_operator = { NULL };

/**
 * @brief This variables will record the list_operations_remove's value.
 */

void *list_family_control_list_operations_remove_value = NULL;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will return the memory size of the specified list_family type node.
 *
 * @param type the specified list_family type
 *
 * @return the memory size of the specified node
 */

static size_t list_family_control_get_node_len(enum list_family_member_type_e type);

/**
* @brief This function will set elements at the specified location in the container.
*
* @param list_family the pointer to the list_family struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param source pointer to the source
*
* @return NONE
*/

static void list_node_control_set_data(list_family_stp list_family,
									   container_size_t position, void *source);

/**
* @brief This function will get elements at the specified location node in the container.
*
* @param list_family the pointer to the list_family struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

static void *list_node_control_get_data(list_family_stp list_family,
										container_size_t position);

/**
* @brief This function will delete elements at the specified location node in the container.
*
* @param list_family the pointer to the list_family struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

static void list_node_control_del_data(list_family_stp list_family,
									   container_size_t position);

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data list_family will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

bool list_family_control_remove_rule(void *data);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void list_family_control_configuration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void list_family_control_configuration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will get control of the list_family-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

inline void list_family_control_get_control(enum list_family_member_type_e type, struct node_operator_s node_operator)
{
	list_family_control_type_in_control = type;
	list_family_control_node_operator = node_operator;
}

/**
 * @brief This function will initialize the list_family struct
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param element_size the element memory size of the list_family struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t list_family_control_configuration_init(list_family_stpp list_family,
											   container_family_switch_control switch_control,
											   enum allocator_type_e allocator_type,
											   container_size_t element_size,
											   generic_type_element_assign_t assign,
											   generic_type_element_free_t free)
{
	assert(list_family);
	assert(switch_control);
	assert(allocator_type);
	assert(element_size);

	static struct container_allocte_package_s
		allocate_package = { 0 };
	static struct container_control_configuration_allocate_return_s
		allocate_return = { 0 };

	allocate_package.allocator_type = allocator_type;
	allocate_package.container_mem_size = sizeof(struct container_family_s);
	allocate_package.arg_list_ptr = NULL;

	if ((allocate_return
		 = container_control_configuration_allocate											/* Allocate the adaptor structure */
		 (list_family, allocate_package))
		.error) {
		return allocate_return.error;
	}

	(*list_family)->container_type_id = list_family_control_type_in_control;						/* Assign list_family structure */

	(*list_family)->info.max_size = LIST_FAMILY_CFG_DEFAULT_MAX_SIZE;
	(*list_family)->info.size = 0u;
	(*list_family)->info.mem_size = element_size;

	(*list_family)->element_handler.assign = assign;
	(*list_family)->element_handler.free = free;

	(*list_family)->allocator_control_ptr = allocate_return.allocator_control_ptr;
	(*list_family)->allocator_ptr = allocate_return.allocator_ptr;

	(*list_family)->element_ptr = NULL;

	(*list_family)->switch_control = switch_control;

	list_family_control_configuration_exception(
		(*list_family)
		, list_family_control_configuration_exception_default_empty_callback
		, list_family_control_configuration_exception_default_full_callback);

	return 0;
}

/**
 * @brief This function will destroy the list_family struct and free the space
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_configuration_destroy(list_family_stpp list_family)
{
	assert(list_family);

	(*list_family)->switch_control((*list_family));

	void *allocator_ptr = (*list_family)->allocator_ptr;

	struct allocator_control_s *allocator_control_ptr = (*list_family)->allocator_control_ptr;

	if (0 < (*list_family)->info.size) {
		struct list_node_s
			*node = NULL;

		for (size_t cnt = 0; cnt < (*list_family)->info.size; cnt++) {
			node = list_family_control_node_operator.del((*list_family), 0);

			list_family_control_destroy_node((*list_family), node);
		}
	}

	allocator_control_ptr->deallocate(allocator_ptr, *list_family, 1);

	allocator_control_ptr->configuration.destroy(&allocator_ptr);

	*list_family = NULL;
}

/**
 * @brief This function will configure the list_family element handler
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_family_control_configuration_element_handler(list_family_stp list_family,
													   generic_type_element_assign_t assign,
													   generic_type_element_free_t free)
{
	assert(list_family);
	assert(assign);
	assert(free);

	list_family->element_handler.assign = assign;
	list_family->element_handler.free = free;
}

/**
 * @brief This function will configure the list_family exception callback
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_family_control_configuration_exception(list_family_stp list_family,
												 void (*empty)(void), void (*full)(void))
{
	assert(list_family);

	if (NULL != empty) {
		list_family->exception.empty = empty;
	}

	if (NULL != full) {
		list_family->exception.full = full;
	}
}

/**
 * @brief This function will returns a reference to the first element in the container
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return the reference to the first element in the container
 */

void *list_family_control_element_access_front(list_family_stp list_family)
{
	assert(list_family);

	return list_node_control_get_data(list_family, 0);
}

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_family_control_element_access_at(list_family_stp list_family,
											container_size_t position)
{
	assert(list_family);

	return list_node_control_get_data(list_family, position);
}

/**
 * @brief This function will checks if the container has no elements
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

extern inline bool list_family_control_capacity_empty(list_family_stp list_family)
{
	assert(list_family);

	if (list_family->info.max_size <= list_family->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return the maximum number of elements
 */

extern inline container_size_t list_family_control_capacity_max_size(list_family_stp list_family)
{
	assert(list_family);

	return list_family->info.max_size;
}

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return the number of elements in the container
 */

extern inline container_size_t list_family_control_capacity_size(list_family_stp list_family)
{
	assert(list_family);

	return list_family->info.size;
}

/**
 * @brief This function will erases all elements from the container
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_clear(list_family_stp list_family)
{
	assert(list_family);

	for (size_t cnt = list_family->info.size; cnt > 0; cnt--) {
		list_family_control_modifiers_erase_after(list_family, 0);
	}
}

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_family_control_modifiers_insert_after(list_family_stp list_family,
												container_size_t position,
												container_size_t amount, void **source)
{
	assert(list_family);
	assert(0 <= position);
	assert(0 < amount);
	assert(source);
	assert(*source);

	list_family->switch_control(list_family);

	void
		*source_addr = NULL;

	container_size_t
		pos_insert_head = list_family->info.size,
		pos_insert_tail = position + amount;

ENSURE_THE_LIST_HAS_ENOUGH_NODE:

	if (pos_insert_tail > pos_insert_head) {												/* Ensure the list_family has enough node */
		for (container_size_t pos = pos_insert_head; pos < pos_insert_tail; pos++) {
			list_family_control_node_operator.set(list_family, pos_insert_head, NULL);
		}
	}

	for (container_size_t pos = position; pos < pos_insert_tail; pos++) {		/* Set the data to the list_family node */
		source_addr = (void *)((size_t)*source + (pos - position) * list_family->info.mem_size);

		if ('\0' != *(char *)list_node_control_get_data(list_family, pos)) {			/* Ensure the list_family node has no data */
			pos_insert_head = position;

			goto ENSURE_THE_LIST_HAS_ENOUGH_NODE;
		}

		#if (LIST_FAMILY_CFG_DEBUG_EN)

		printf("list_family.modifiers.insert_after:No.%d:\"%s\" \r\n", pos, (char *)source_addr);

		#endif // (VECTOR_CFG_DEBUG_EN)

		list_node_control_set_data(list_family, pos, source_addr);
	}
}

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_family_control_modifiers_emplace_after(list_family_stp stack,
												 container_size_t position)
{
}

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_family_control_modifiers_erase_after(list_family_stp list_family,
											   container_size_t position)
{
	assert(list_family);
	assert(0 <= position);

	#if (LIST_FAMILY_CFG_DEBUG_EN)

	printf("list_family.modifiers.earse_after no.%d: \"%s\" \r\n",
		   position, (char *)list_node_control_get_data(list_family, position));

	#endif // (LIST_FAMILY_CFG_DEBUG_EN)

	list_node_control_del_data(list_family, position);
}

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_family_control_modifiers_push_front(list_family_stp list_family,
											  void *source)
{
	assert(list_family);
	assert(source);

	list_family_control_modifiers_insert_after(list_family, 0, 1, &source);

	list_node_control_set_data(list_family, 0, source);
}

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_family_control_modifiers_emplace_front(list_family_stp stack,
												 void *destination)
{
}

/**
 * @brief This function will removes the first element of the container
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_pop_front(list_family_stp list_family)
{
	assert(list_family);

	list_node_control_del_data(list_family, 0);
}

/**
 * @brief This function will increase the capacity of the list_family to a size
			that's greater or equal to new_cap
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param size the size of the list_family struct
 *
 * @return NONE
 */

void list_family_control_modifiers_resize(list_family_stpp list_family,
										  container_size_t size)
{
}

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param other the pointer to the other list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_swap(list_family_stpp list_family,
										list_family_stpp other)
{
	assert(list_family);
	assert(other);

	list_family_stpp
		list_swap = (*list_family)->allocator_control_ptr->allocate((*list_family)->allocator_ptr, 1, sizeof(void *));

	*(list_swap) = *list_family;
	*(list_swap + 1) = *other;

	*list_family = *(list_swap + 1);
	*other = *list_swap;
}

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param source the pointer to the source list_family struct
 *
 * @return NONE
 */

void list_family_control_modifiers_copy(list_family_stpp destination,
										list_family_stp source)
{
	assert(destination);
	assert(source);

	struct list_node_s
		*node_source = (void *)(size_t)(source->element_ptr);

	if (NULL == (*destination) ||										/* Check if destination have been initialized */
		NULL == (*destination)->allocator_ptr ||							/* if not,then initialize it */
		NULL == (*destination)->allocator_control_ptr ||
		NULL == (*destination)->element_ptr) {
		enum allocator_type_e *allocator_type = source->allocator_ptr;

		list_family_control_configuration_init(destination,
											   source->switch_control,
											   *allocator_type,
											   source->info.mem_size, source->element_handler.assign, source->element_handler.free);
	} else {															/* if so,just assign */
		(*destination)->info = source->info;
		(*destination)->element_handler = source->element_handler;
		(*destination)->exception = source->exception;
	}

	for (container_size_t pos = 0; pos < source->info.size; pos++) {
		list_node_control_set_data(*destination, pos, list_node_control_get_data(source, pos));
	}
}

/**
 * @brief This function will merges two sorted lists into one
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param source the pointer to the source list_family struct
 *
 * @return NONE
 */

void list_family_control_list_operations_merge(list_family_stp destination,
											   list_family_stp other)
{
	assert(destination);
	assert(other);

	//list_family_control_list_operations_sort(destination, NULL);
	//list_family_control_list_operations_sort(other, NULL);

	list_family_control_list_operations_splice_after(destination, 0, other, 0, other->info.size);
}

/**
 * @brief This function will moves elements from another list_family to list_family
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param other the pointer to the other list_family struct
 *
 * @return NONE
 */

void list_family_control_list_operations_splice_after(list_family_stp list_family,
													  container_size_t position,
													  list_family_stp other,
													  container_size_t first,
													  container_size_t last)
{
	assert(list_family);
	assert(other);

	list_family->switch_control(list_family);

	struct list_node_s
		*node_other = NULL;

	container_size_t
		pos_tail_splice = position + last - first;

	for (container_size_t pos = position; pos < pos_tail_splice; pos++) {
		#if (LIST_FAMILY_CFG_DEBUG_EN)

		printf("list_family.list_operatons.splice_after.source data no.%d:\"%s\" \r\n",
			   pos, (char *)list_node_control_get_data(other, first));

		#endif // (LIST_FAMILY_CFG_DEBUG_EN)

		node_other = list_family_control_node_operator.del(other, first);

		if (NULL == node_other) {
			return;
		}

		list_family_control_node_operator.set(list_family, pos, node_other);
	}
}

/**
 * @brief This function will removes all elements satisfying specific criteria
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param data the pointer of data
 *
 * @return NONE
 */

void list_family_control_list_operations_remove(list_family_stp list_family,
												void *value)
{
	assert(list_family);
	assert(value);

	list_family_control_list_operations_remove_value = value;

	list_family_control_list_operations_remove_if(list_family, list_family_control_remove_rule);
}

/**
 * @brief This function will
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param rule the pointer to the rule-making function
 *
 * @return NONE
 */

void list_family_control_list_operations_remove_if(list_family_stp list_family, bool (*rule)(void *data))
{
	assert(list_family);
	assert(rule);

	container_size_t
		cnt_reomve = 0,
		*pos_remove = list_family->allocator_control_ptr->allocate(list_family->allocator_ptr, list_family->info.size, sizeof(container_size_t));

	for (container_size_t pos = 0; pos < list_family->info.size; pos++) {	/* Get which node's data is match */
		if (rule(list_node_control_get_data(list_family, pos))) {
			*(pos_remove + cnt_reomve++) = pos;
		}
	}

	struct list_node_s
		*node_del = NULL;

	for (container_size_t cnt = 0; cnt < cnt_reomve; cnt++) {					/* Delete nodes matched */
		#if (LIST_FAMILY_CFG_DEBUG_EN)

		printf("list_family.list_operatons.remove_if.no.%d: \"%s\" \r\n",
			   *(pos_remove + cnt), (char *)list_node_control_get_data(list_family, *(pos_remove + cnt) - cnt));

		#endif // (LIST_FAMILY_CFG_DEBUG_EN)

		list_node_control_del_data(list_family, *(pos_remove + cnt) - cnt);
	}

	list_family->allocator_control_ptr->deallocate(list_family->allocator_ptr, pos_remove, list_family->info.size);
}

/**
 * @brief This function will reverses the order of the elements in the container
 *
 * @param destination the pointer to the destination list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_list_operations_reverse(list_family_stp list_family)
{
	assert(list_family);

	list_family->switch_control(list_family);

	struct  list_node_s
		*node_reverse = NULL;

	container_size_t pos_last_list_node_valid = list_family->info.size - 1;

	for (container_size_t pos = 0; pos <= pos_last_list_node_valid; pos++) {
		node_reverse = list_family_control_node_operator.del(list_family, pos_last_list_node_valid);

		list_family_control_node_operator.set(list_family, pos, node_reverse);
	}
}

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_list_operations_unique(list_family_stp list_family)
{
	assert(list_family);

	list_family->switch_control(list_family);

	char
		*data_prev = list_node_control_get_data(list_family, 0),
		*data = NULL;

	container_size_t
		size_list = list_family->info.size,
		cnt_pos_repetitive = 0,
		(*pos_repetitive_store)[2] = list_family->allocator_control_ptr->allocate(list_family->allocator_ptr,
																				  size_list, sizeof(container_size_t) * 2);

	for (container_size_t pos = 1; pos < size_list; pos++) {
		if (compare_control_equal(data_prev, (data = list_node_control_get_data(list_family, pos)), list_family->info.mem_size)) {
			*(*(pos_repetitive_store + cnt_pos_repetitive) + 0) = pos;
		} else {
			if (*(*(pos_repetitive_store + cnt_pos_repetitive) + 0) != *(*(pos_repetitive_store + cnt_pos_repetitive) + 1)) {
				*(*(pos_repetitive_store + cnt_pos_repetitive) + 1) = pos;

				cnt_pos_repetitive++;
			}

			data_prev = data;
		}
	}

	#if (LIST_FAMILY_CFG_DEBUG_EN)

	for (container_size_t cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		printf("list_family.list_operatons.unique:no.%d from %d to %d is \"%s\" \r\n",
			   cnt, *(*(pos_repetitive_store + cnt) + 0),
			   *(*(pos_repetitive_store + cnt) + 1),
			   (char *)list_node_control_get_data(list_family, *(*(pos_repetitive_store + cnt) + 0)));
	}

	#endif // (LIST_FAMILY_CFG_DEBUG_EN)

	struct  list_node_s
		*node_del = NULL;

	for (container_size_t cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		for (container_size_t pos = *(*(pos_repetitive_store + cnt) + 0); pos <= *(*(pos_repetitive_store + cnt) + 1); pos++) {
			list_family_control_destroy_node(list_family, list_family_control_node_operator.del(list_family, *(*(pos_repetitive_store + cnt) + 0)));
		}
	}

	list_family->allocator_control_ptr->deallocate(list_family->allocator_ptr,
												   pos_repetitive_store, size_list);
}

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void list_family_control_list_operations_sort(list_family_stp list_family,
											  compare_t comp)
{
	assert(list_family);

	list_family->switch_control(list_family);

	if (NULL == comp) {
		comp = compare_control_lesser;
	}

	//struct sort_package_s list_sort_pack = {
	//	.object = list_family,
	//	.len = list_family->info.size,
	//	.mem_len = list_family->info.mem_size,
	//	.get_value_method = list_node_control_get_data,
	//	.swap_method = list_family_control_node_operator.swap,
	//};

	//sort_control(sort_control_convert_type_to_func_addr(BUBBLE_SORT),
	//			 list_sort_pack, comp);
}

/**
 * @brief This function will return the memory size of the specified list_family type node.
 *
 * @param type the specified list_family type
 *
 * @return the memory size of the specified node
 */

size_t list_family_control_get_node_len(enum list_family_member_type_e type)
{
	assert(type);

	size_t mem_size = 0;

	switch (type) {
		case LIST:
			mem_size = sizeof(struct list_node_s);
			break;
		case FORWARD_LIST:
			mem_size = sizeof(struct forward_list_node_s);
			break;
		default:
			break;
	}

	return mem_size;
}

/**
 * @brief This function will initialize the list_family node struct.
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return NONE
 */

void *list_family_control_init_node(list_family_stp list_family)
{
	assert(list_family);

	void *node_alloced = list_family->allocator_control_ptr->allocate(list_family->allocator_ptr,
																	  1, list_family_control_get_node_len(list_family_control_type_in_control));	/* Allocate #1 */

	void *data_pack_allocated = list_family->allocator_control_ptr->allocate(list_family->allocator_ptr,
																			 1, list_family->info.mem_size);			/* Allocate #2 */

	void **data_ptr = (void *)node_alloced;

	if (NULL == list_family ||																			/* Check if list_family point to NULL			*/
		NULL == node_alloced ||																	/* Check if list_family node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	*data_ptr = data_pack_allocated;															/* Assign list_node structure					*/

	return node_alloced;
}

/**
 * @brief This function will destroy list_family node struct and free the space.
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param node the pointer to the list_family node struct pointer
 *
 * @return NONE
 */

void list_family_control_destroy_node(list_family_stp list_family,
									  void *node)
{
	assert(list_family);

	if (NULL == node) {
		return;
	}

	void **data_ptr = node;

	list_family->allocator_control_ptr->deallocate(list_family->allocator_ptr, *data_ptr, 1);				/* Deallocate #2 */

	list_family->allocator_control_ptr->deallocate(list_family->allocator_ptr, node, 1);					/* Deallocate #1 */

	node = NULL;
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param node the pointer to the list_family node struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_node_control_set_data(list_family_stp list_family,
								container_size_t position, void *source)
{
	assert(list_family);
	assert(0 <= position);
	assert(source);

	list_family->switch_control(list_family);

	void *node = list_family_control_node_operator.get(list_family, position);

	if (NULL == node) {
		node = list_family_control_node_operator.set(list_family, position, NULL);

		if (NULL == node) {
			return;
		}
	}

	void **data_ptr = (void *)node;

	if (NULL == *data_ptr &&
		NULL == (*data_ptr = list_family->allocator_control_ptr->allocate(list_family->allocator_ptr, 1, list_family->info.mem_size))) {
		return;
	}

	if (NULL != list_family->element_handler.assign) {																	/* Check if assign point to NULL */
		list_family->element_handler.assign(*data_ptr, source);
	} else {
		memcpy(*data_ptr, source, list_family->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
* @brief This function will get elements at the specified location in the container.
*
* @param list_family the pointer to the list_family struct pointer
* @param node the pointer to the list_family node struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *list_node_control_get_data(list_family_stp list_family,
								 container_size_t position)
{
	assert(list_family);
	assert(0 <= position);

	list_family->switch_control(list_family);

	void *node = list_family_control_node_operator.get(list_family, position);

	if (NULL == node) {
		return NULL;
	}

	char **data_ptr = (void *)node;

	return *data_ptr;
}

/**
* @brief This function will delete elements at the specified location in the container.
*
* @param list_family the pointer to the list_family struct pointer
* @param node the pointer to the list_family node struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void list_node_control_del_data(list_family_stp list_family,
								container_size_t position)
{
	assert(list_family);
	assert(0 <= position);

	list_family->switch_control(list_family);

	void *data_ptr = list_node_control_get_data(list_family, position);

	if (NULL != list_family->element_handler.free) {																	/* Check if assign point to NULL */
		list_family->element_handler.free(data_ptr);
	} else {
		memset(data_ptr, '0', list_family->info.mem_size);															/* Memcpy source to destination */
	}

	#if (LIST_FAMILY_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	list_family_control_destroy_node(list_family, list_family_control_node_operator.del(list_family, position));

	#endif // (LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	if (0 >= list_family->info.size) {
		list_family->exception.empty();

		return;
	}
}

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data list_family will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

bool list_family_control_remove_rule(void *data)
{
	if (0 == strcmp(data, list_family_control_list_operations_remove_value)) {
		return true;
	}

	return false;
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void list_family_control_configuration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void list_family_control_configuration_exception_default_full_callback(void)
{
}