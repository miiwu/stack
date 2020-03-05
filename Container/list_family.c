/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "list_family.h"

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
 * @brief This function will return the memory size of the specified list type node.
 *
 * @param type the specified list type
 *
 * @return the memory size of the specified node
 */

static size_t list_family_control_get_node_len(enum list_family_member_type_e type);

/**
* @brief This function will set elements at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param source pointer to the source
*
* @return NONE
*/

static void list_node_control_set_data(struct list_family_s *list,
									   container_size_t position, void *source);

/**
* @brief This function will get elements at the specified location node in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

static void *list_node_control_get_data(struct list_family_s *list,
										container_size_t position);

/**
* @brief This function will delete elements at the specified location node in the container.
*
* @param list the pointer to the list struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

static void list_node_control_del_data(struct list_family_s *list,
									   container_size_t position);

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data list will give
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
 * @brief This function will get control of the list-family controller.
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
 * @brief This function will initialize the list struct
 *
 * @param list the pointer to the list struct pointer
 * @param element_size the element memory size of the list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t list_family_control_configuration_init(struct list_family_s **list,
											void (*switch_control)(void),
											enum allocator_type_e allocator_type,
											container_size_t element_size,
											generic_type_element_assign_t assign,
											generic_type_element_free_t free)
{
	assert(list);
	assert(0 <= element_size);

	void
		*allocator = NULL;

	struct allocator_control_s
		*allocator_ctrl = NULL;

	allocator_ctrl = allocator_control_convert_type_to_func_addr_table(allocator_type);	/* Variables pointer to	the function address table of
																							specified container type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);

	struct list_family_s
		*list_alloced = allocator_ctrl->allocate(allocator,
												 1, sizeof(struct list_family_s));	/* Allocate #1 */

	if (NULL == list ||																	/* Check if list point to NULL			*/
		NULL == list_alloced) {															/* Check if list_alloced point to NULL	*/
		return 1;
	}

	list_alloced->container_type_id = list_family_control_type_in_control;						/* Assign list structure					*/

	list_alloced->info.max_size = LIST_FAMILY_CFG_DEFAULT_MAX_SIZE;
	list_alloced->info.size = 0u;
	list_alloced->info.mem_size = element_size;

	list_alloced->allocator = allocator;
	list_alloced->allocator_ctrl = allocator_ctrl;

	list_alloced->node = NULL;

	list_alloced->exception.empty = list_family_control_configuration_exception_default_empty_callback;
	list_alloced->exception.full = list_family_control_configuration_exception_default_full_callback;

	list_alloced->switch_control = switch_control;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		list_alloced->element_handler.assign = assign;
		list_alloced->element_handler.free = free;
	}

	*list = list_alloced;

	return 0;
}

/**
 * @brief This function will destroy the list struct and free the space
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void list_family_control_configuration_destroy(struct list_family_s **list)
{
	assert(list);

	(*list)->switch_control();

	void *allocator = (*list)->allocator;

	struct allocator_control_s *allocator_ctrl = (*list)->allocator_ctrl;

	#if (VECTOR_CFG_DEBUG_EN)

	printf("list.configuration.destroy:allocator : %p \r\n", allocator);
	printf("list.configuration.destroy:list block : %p \r\n", (*list));
	printf("list.configuration.destroy:list node block : %p \r\n", (*list)->node);

	#endif // (VECTOR_CFG_DEBUG_EN)

	if (0 < (*list)->info.size) {
		struct list_node_s
			*node = NULL;

		for (size_t cnt = 0; cnt < (*list)->info.size; cnt++) {
			node = list_family_control_node_operator.del((*list), 0);

			list_family_control_destroy_node((*list), node);
		}
	}

	(*list)->container_type_id = 0u;														/* Assign list structure					*/

	(*list)->info.max_size = 0u;
	(*list)->info.size = 0u;
	(*list)->info.mem_size = 0u;

	(*list)->allocator = NULL;

	(*list)->node = NULL;

	(*list)->exception.empty = NULL;
	(*list)->exception.full = NULL;

	allocator_ctrl->deallocate(allocator, *list, 1);																			/* deallocate #1 */

	allocator_ctrl->configuration.destroy(&allocator);

	*list = NULL;
}

/**
 * @brief This function will configure the list element handler
 *
 * @param list the pointer to the list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_family_control_configuration_element_handler(struct list_family_s *list,
													   generic_type_element_assign_t assign,
													   generic_type_element_free_t free)
{
	assert(list);
	assert(assign);
	assert(free);

	list->element_handler.assign = assign;
	list->element_handler.free = free;
}

/**
 * @brief This function will configure the list exception callback
 *
 * @param list the pointer to the list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_family_control_configuration_exception(struct list_family_s *list,
												 void (*empty)(void), void (*full)(void))
{
	assert(list);

	if (NULL == empty) {
		list->exception.empty = empty;
	}

	if (NULL == full) {
		list->exception.full = full;
	}
}

/**
 * @brief This function will returns a reference to the first element in the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return the reference to the first element in the container
 */

void *list_family_control_element_access_front(struct list_family_s *list)
{
	assert(list);

	return list_node_control_get_data(list, 0);
}

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_family_control_element_access_at(struct list_family_s *list,
											container_size_t position)
{
	assert(list);

	return list_node_control_get_data(list, position);
}

/**
 * @brief This function will checks if the container has no elements
 *
 * @param list the pointer to the list struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

extern inline bool list_family_control_capacity_empty(struct list_family_s *list)
{
	assert(list);

	if (list->info.max_size <= list->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param list the pointer to the list struct pointer
 *
 * @return the maximum number of elements
 */

extern inline container_size_t list_family_control_capacity_max_size(struct list_family_s *list)
{
	assert(list);

	return list->info.max_size;
}

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return the number of elements in the container
 */

extern inline container_size_t list_family_control_capacity_size(struct list_family_s *list)
{
	assert(list);

	return list->info.size;
}

/**
 * @brief This function will erases all elements from the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_clear(struct list_family_s *list)
{
	assert(list);

	for (size_t cnt = list->info.size; cnt > 0; cnt--) {
		list_family_control_modifiers_erase_after(list, 0);
	}
}

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_family_control_modifiers_insert_after(struct list_family_s *list,
												container_size_t position,
												container_size_t amount, void **source)
{
	assert(list);
	assert(0 <= position);
	assert(0 < amount);
	assert(source);
	assert(*source);

	list->switch_control();

	void
		*source_addr = NULL;

	container_size_t
		pos_insert_head = list->info.size,
		pos_insert_tail = position + amount;

ENSURE_THE_LIST_HAS_ENOUGH_NODE:

	if (pos_insert_tail > pos_insert_head) {												/* Ensure the list has enough node */
		for (container_size_t pos = pos_insert_head; pos < pos_insert_tail; pos++) {
			list_family_control_node_operator.set(list, pos_insert_head, NULL);
		}
	}

	for (container_size_t pos = position; pos < pos_insert_tail; pos++) {		/* Set the data to the list node */
		source_addr = (void *)((size_t)*source + (pos - position) * list->info.mem_size);

		if ('\0' != *(char *)list_node_control_get_data(list, pos)) {			/* Ensure the list node has no data */
			pos_insert_head = position;

			goto ENSURE_THE_LIST_HAS_ENOUGH_NODE;
		}

		#if (LIST_FAMILY_CFG_DEBUG_EN)

		printf("list.modifiers.insert_after:No.%d:\"%s\" \r\n", pos, (char *)source_addr);

		#endif // (VECTOR_CFG_DEBUG_EN)

		list_node_control_set_data(list, pos, source_addr);
	}
}

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_family_control_modifiers_emplace_after(struct list_family_s *stack,
												 container_size_t position)
{
}

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param list the pointer to the list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_family_control_modifiers_erase_after(struct list_family_s *list,
											   container_size_t position)
{
	assert(list);
	assert(0 <= position);

	#if (LIST_FAMILY_CFG_DEBUG_EN)

	printf("list.modifiers.earse_after no.%d: \"%s\" \r\n",
		   position, (char *)list_node_control_get_data(list, position));

	#endif // (LIST_FAMILY_CFG_DEBUG_EN)

	list_node_control_del_data(list, position);
}

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param list the pointer to the list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_family_control_modifiers_push_front(struct list_family_s *list,
											  void *source)
{
	assert(list);
	assert(source);

	list_family_control_modifiers_insert_after(list, 0, 1, &source);

	list_node_control_set_data(list, 0, source);
}

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param list the pointer to the list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_family_control_modifiers_emplace_front(struct list_family_s *stack,
												 void *destination)
{
}

/**
 * @brief This function will removes the first element of the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_pop_front(struct list_family_s *list)
{
	assert(list);

	list_node_control_del_data(list, 0);
}

/**
 * @brief This function will increase the capacity of the list to a size
			that's greater or equal to new_cap
 *
 * @param list the pointer to the list struct pointer
 * @param size the size of the list struct
 *
 * @return NONE
 */

void list_family_control_modifiers_resize(struct list_family_s **list,
										  container_size_t size)
{
}

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param list the pointer to the list struct pointer
 * @param other the pointer to the other list struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_swap(struct list_family_s **list,
										struct list_family_s **other)
{
	assert(list);
	assert(other);

	struct list_family_s **
		list_swap = (*list)->allocator_ctrl->allocate((*list)->allocator, 1, sizeof(void *));

	*(list_swap) = *list;
	*(list_swap + 1) = *other;

	*list = *(list_swap + 1);
	*other = *list_swap;
}

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination list struct pointer
 * @param source the pointer to the source list struct
 *
 * @return NONE
 */

void list_family_control_modifiers_copy(struct list_family_s **destination,
										struct list_family_s *source)
{
	assert(destination);
	assert(source);

	struct list_node_s
		*node_source = (void *)(size_t)(source->node);

	if (NULL == (*destination) ||										/* Check if destination have been initialized */
		NULL == (*destination)->allocator ||							/* if not,then initialize it */
		NULL == (*destination)->allocator_ctrl ||
		NULL == (*destination)->node) {
		enum allocator_type_e *allocator_type = source->allocator;

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
 * @param destination the pointer to the destination list struct pointer
 * @param source the pointer to the source list struct
 *
 * @return NONE
 */

void list_family_control_list_operations_merge(struct list_family_s *destination,
											   struct list_family_s *other)
{
	assert(destination);
	assert(other);

	//list_family_control_list_operations_sort(destination, NULL);
	//list_family_control_list_operations_sort(other, NULL);

	list_family_control_list_operations_splice_after(destination, 0, other, 0, other->info.size);
}

/**
 * @brief This function will moves elements from another list to list
 *
 * @param destination the pointer to the destination list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param other the pointer to the other list struct
 *
 * @return NONE
 */

void list_family_control_list_operations_splice_after(struct list_family_s *list,
													  container_size_t position,
													  struct list_family_s *other,
													  container_size_t first,
													  container_size_t last)
{
	assert(list);
	assert(other);

	list->switch_control();

	struct list_node_s
		*node_other = NULL;

	container_size_t
		pos_tail_splice = position + last - first;

	for (container_size_t pos = position; pos < pos_tail_splice; pos++) {
		#if (LIST_FAMILY_CFG_DEBUG_EN)

		printf("list.list_operatons.splice_after.source data no.%d:\"%s\" \r\n",
			   pos, (char *)list_node_control_get_data(other, first));

		#endif // (LIST_FAMILY_CFG_DEBUG_EN)

		node_other = list_family_control_node_operator.del(other, first);

		if (NULL == node_other) {
			return;
		}

		list_family_control_node_operator.set(list, pos, node_other);
	}
}

/**
 * @brief This function will removes all elements satisfying specific criteria
 *
 * @param destination the pointer to the destination list struct pointer
 * @param data the pointer of data
 *
 * @return NONE
 */

void list_family_control_list_operations_remove(struct list_family_s *list,
												void *value)
{
	assert(list);
	assert(value);

	list_family_control_list_operations_remove_value = value;

	list_family_control_list_operations_remove_if(list, list_family_control_remove_rule);
}

/**
 * @brief This function will
 *
 * @param destination the pointer to the destination list struct pointer
 * @param rule the pointer to the rule-making function
 *
 * @return NONE
 */

void list_family_control_list_operations_remove_if(struct list_family_s *list, bool (*rule)(void *data))
{
	assert(list);
	assert(rule);

	container_size_t
		cnt_reomve = 0,
		*pos_remove = list->allocator_ctrl->allocate(list->allocator, list->info.size, sizeof(container_size_t));

	for (container_size_t pos = 0; pos < list->info.size; pos++) {	/* Get which node's data is match */
		if (rule(list_node_control_get_data(list, pos))) {
			*(pos_remove + cnt_reomve++) = pos;
		}
	}

	struct  list_node_t
		*node_del = NULL;

	for (container_size_t cnt = 0; cnt < cnt_reomve; cnt++) {					/* Delete nodes matched */
		#if (LIST_FAMILY_CFG_DEBUG_EN)

		printf("list.list_operatons.remove_if.no.%d: \"%s\" \r\n",
			   *(pos_remove + cnt), (char *)list_node_control_get_data(list, *(pos_remove + cnt) - cnt));

		#endif // (LIST_FAMILY_CFG_DEBUG_EN)

		list_node_control_del_data(list, *(pos_remove + cnt) - cnt);
	}

	list->allocator_ctrl->deallocate(list->allocator, pos_remove, list->info.size);
}

/**
 * @brief This function will reverses the order of the elements in the container
 *
 * @param destination the pointer to the destination list struct pointer
 *
 * @return NONE
 */

void list_family_control_list_operations_reverse(struct list_family_s *list)
{
	assert(list);

	list->switch_control();

	struct  list_node_t
		*node_reverse = NULL;

	container_size_t pos_last_list_node_valid = list->info.size - 1;

	for (container_size_t pos = 0; pos <= pos_last_list_node_valid; pos++) {
		node_reverse = list_family_control_node_operator.del(list, pos_last_list_node_valid);

		list_family_control_node_operator.set(list, pos, node_reverse);
	}
}

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination list struct pointer
 *
 * @return NONE
 */

void list_family_control_list_operations_unique(struct list_family_s *list)
{
	assert(list);

	list->switch_control();

	char
		*data_prev = list_node_control_get_data(list, 0),
		*data = NULL;

	container_size_t
		size_list = list->info.size,
		cnt_pos_repetitive = 0,
		(*pos_repetitive_store)[2] = list->allocator_ctrl->allocate(list->allocator,
																	size_list, sizeof(container_size_t) * 2);

	for (container_size_t pos = 1; pos < size_list; pos++) {
		if (compare_control_equal(data_prev, (data = list_node_control_get_data(list, pos)), list->info.mem_size)) {
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
		printf("list.list_operatons.unique:no.%d from %d to %d is \"%s\" \r\n",
			   cnt, *(*(pos_repetitive_store + cnt) + 0),
			   *(*(pos_repetitive_store + cnt) + 1),
			   (char *)list_node_control_get_data(list, *(*(pos_repetitive_store + cnt) + 0)));
	}

	#endif // (LIST_FAMILY_CFG_DEBUG_EN)

	struct  list_node_t
		*node_del = NULL;

	for (container_size_t cnt = 0; cnt < cnt_pos_repetitive; cnt++) {
		for (container_size_t pos = *(*(pos_repetitive_store + cnt) + 0); pos <= *(*(pos_repetitive_store + cnt) + 1); pos++) {
			list_family_control_destroy_node(list, list_family_control_node_operator.del(list, *(*(pos_repetitive_store + cnt) + 0)));
		}
	}

	list->allocator_ctrl->deallocate(list->allocator,
									 pos_repetitive_store, size_list);
}

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination list struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void list_family_control_list_operations_sort(struct list_family_s *list,
											  compare_t *comp)
{
	assert(list);

	list->switch_control();

	if (NULL == comp) {
		comp = compare_control_lesser;
	}

	struct sort_package_s list_sort_pack = {
		.object = list,
		.len = list->info.size,
		.mem_len = list->info.mem_size,
		.get_value_method = list_node_control_get_data,
		.swap_method = list_family_control_node_operator.swap,
	};

	sort_algorithm_control(sort_algorithm_control_convert_type_to_func_addr(BUBBLE_SORT),
						   list_sort_pack, comp);
}

/**
 * @brief This function will return the memory size of the specified list type node.
 *
 * @param type the specified list type
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
 * @brief This function will initialize the list node struct.
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void *list_family_control_init_node(struct list_family_s *list)
{
	assert(list);

	void *node_alloced = list->allocator_ctrl->allocate(list->allocator,
														1, list_family_control_get_node_len(list_family_control_type_in_control));	/* Allocate #1 */

	void *data_pack_allocated = list->allocator_ctrl->allocate(list->allocator,
															   1, list->info.mem_size);			/* Allocate #2 */

	void **data_ptr = (void *)node_alloced;

	if (NULL == list ||																			/* Check if list point to NULL			*/
		NULL == node_alloced ||																	/* Check if list node point to NULL			*/
		NULL == data_pack_allocated) {															/* Check if data_pack_alloced point to NULL	*/
		return NULL;
	}

	*data_ptr = data_pack_allocated;															/* Assign list_node structure					*/

	return node_alloced;
}

/**
 * @brief This function will destroy list node struct and free the space.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 *
 * @return NONE
 */

void list_family_control_destroy_node(struct list_family_s *list,
									  void *node)
{
	assert(list);

	if (NULL == node) {
		return;
	}

	void **data_ptr = node;

	list->allocator_ctrl->deallocate(list->allocator, *data_ptr, 1);				/* Deallocate #2 */

	list->allocator_ctrl->deallocate(list->allocator, node, 1);					/* Deallocate #1 */

	node = NULL;
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_node_control_set_data(struct list_family_s *list,
								container_size_t position, void *source)
{
	assert(list);
	assert(0 <= position);
	assert(source);

	list->switch_control();

	void *node = list_family_control_node_operator.get(list, position);

	if (NULL == node) {
		node = list_family_control_node_operator.set(list, position, NULL);

		if (NULL == node) {
			return;
		}
	}

	void **data_ptr = (void *)node;

	if (NULL == *data_ptr &&
		NULL == (*data_ptr = list->allocator_ctrl->allocate(list->allocator, 1, list->info.mem_size))) {
		return;
	}

	if (NULL != list->element_handler.assign) {																	/* Check if assign point to NULL */
		list->element_handler.assign(*data_ptr, source);
	} else {
		memcpy(*data_ptr, source, list->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
* @brief This function will get elements at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param node the pointer to the list node struct pointer
* @param position the position of element,it would be equal or greater than zero
* @param destination pointer to the destination
*
* @return NONE
*/

void *list_node_control_get_data(struct list_family_s *list,
								 container_size_t position)
{
	assert(list);
	assert(0 <= position);

	list->switch_control();

	void *node = list_family_control_node_operator.get(list, position);

	if (NULL == node) {
		return NULL;
	}

	char **data_ptr = (void *)node;

	return *data_ptr;
}

/**
* @brief This function will delete elements at the specified location in the container.
*
* @param list the pointer to the list struct pointer
* @param node the pointer to the list node struct pointer
* @param position the position of element,it would be equal or greater than zero
*
* @return NONE
*/

void list_node_control_del_data(struct list_family_s *list,
								container_size_t position)
{
	assert(list);
	assert(0 <= position);

	list->switch_control();

	void *data_ptr = list_node_control_get_data(list, position);

	if (NULL != list->element_handler.free) {																	/* Check if assign point to NULL */
		list->element_handler.free(data_ptr);
	} else {
		memset(data_ptr, '0', list->info.mem_size);															/* Memcpy source to destination */
	}

	#if (LIST_FAMILY_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	list_family_control_destroy_node(list, list_family_control_node_operator.del(list, position));

	#endif // (LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN)

	if (0 >= list->info.size) {
		list->exception.empty();

		return;
	}
}

/**
* @brief This function will control the remove run under the rule of remove_if.
*
* @param data the pointer to the data list will give
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
* @brief This function will sort the object by the comp.
*
* @param data the pointer to the data list will give
*
* @return if the data match the rule
*	- true	yes
*	- false	no
*/

void list_family_control_sort_algorithm_bubble_sort(struct sort_package_s sort_package,
													bool (*comp)(void *, void *, size_t))
{
	char
		*value_lhs = NULL,
		*value_rhs = NULL;

	for (size_t cnt = 0; cnt < sort_package.len - 1; cnt++) {
		for (size_t ct = 0; ct < sort_package.len - cnt - 1; ct++) {
			if (NULL == sort_package.get_value_method) {								/* Get the value */
				value_lhs = (void *)((size_t)sort_package.object + ct * sort_package.mem_len);
				value_rhs = (void *)((size_t)sort_package.object + (ct + 1) * sort_package.mem_len);
			} else {
				value_lhs = sort_package.get_value_method(sort_package.object, ct);
				value_rhs = sort_package.get_value_method(sort_package.object, ct + 1);
			}

			if (NULL == value_lhs ||
				NULL == value_rhs) {
				return;
			}

			if (comp(value_lhs, value_rhs, sort_package.mem_len)) {						/* Compare the value */
				printf("sort_algorithm.bubble_sort.no.%d-%d: %d \"%s\" swap %d \"%s\" \r\n",
					   cnt, ct, ct, value_lhs, ct + 1, value_rhs);

				sort_package.swap_method(sort_package.object, ct, ct + 1);
			}
		}
	}
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