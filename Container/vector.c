/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "vector.h"

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

/* Configure    vector type.                                                                            */
typedef VECTOR_CFG_ALLOCATOR_TYPE *VECTOR_ALLOCATOR_TYPEDEF_PTR;

/**
 * @brief This struct is the vector structure module
 */

struct vector_t {
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
	VECTOR_ALLOCATOR_TYPEDEF_PTR allocator;

	/* @brief This variables will point to the address of the vector data memory block.					*/
	void *data;

	struct {
		/* @brief This variables will point to the address of the vector element assign handler.		*/
		void (*assign)(void *dst, void *src);

		/* @brief This variables will point to the address of the vector element free handler.			*/
		void (*free)(void *dst);
	}element_handler;

	struct {
		/* @brief This variables will point to the address of the vector empty exception handler.		*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the vector full exception handler.			*/
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
 * @brief This array will contain all the universal vector functions address.
 */

void *vector_function_address_tables[] =
{
	(void *)&vector_control_configuration_init,					/* No.0 : initialize */

	(void *)&vector_control_configuration_destroy,					/* No.1 : destroy */

	(void *)&vector_control_element_access_at,						/* No.3 : at */

	(void *)&vector_control_capacity_empty,						/* No.4 : empty */

	(void *)&vector_control_capacity_size,							/* No.5 : size */

	(void *)&vector_control_capacity_max_size,						/* No.6 : max_size */

	(void *)&vector_control_modifiers_insert,						/* No.7 : insert */

	(void *)&vector_control_modifiers_erase,						/* No.8 : erase */

	(void *)&vector_control_modifiers_swap,						/* No.9 : swap */

	(void *)&vector_control_modifiers_copy,						/* No.10 : copy */
};

#if (VECTOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */

struct vector_control_t vector_ctrl = {
	{
		vector_control_configuration_init,

		vector_control_configuration_destroy,

		vector_control_configuration_element_handler,

		vector_control_configuration_exception,
	},
	{
		vector_control_iterators_front,

		vector_control_iterators_back,
	},
	{
		vector_control_element_access_at,

		vector_control_element_access_data,

		vector_control_element_access_front,

		vector_control_element_access_back,
	},
	{
		vector_control_capacity_empty,

		vector_control_capacity_size,

		vector_control_capacity_max_size,

		vector_control_capacity_capacity,

		vector_control_capacity_reserve,

		vector_control_capacity_shrink_to_fit,
	},
	{
		vector_control_modifiers_clear,

		vector_control_modifiers_insert,

		vector_control_modifiers_erase,

		vector_control_modifiers_push_back,

		vector_control_modifiers_pop_back,

		vector_control_modifiers_resize,

		vector_control_modifiers_copy,

		vector_control_modifiers_swap,
	}
};

#endif

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void vector_control_modifiers_set(const VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_get(const VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination);

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_modifiers_del(const VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to insert.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_configration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the vector struct.
 *
 * @param vector the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void vector_control_configuration_init(VECTOR_TYPEDEF_PPTR vector,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									   void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(vector);
	assert(0 <= element_size);

	VECTOR_ALLOCATOR_TYPEDEF_PTR
		allocator = NULL;

	allocator_ctrl.configration.init(&allocator, NULL);

	struct vector_t
		*vector_alloced = (struct vector_t *)allocator_ctrl.allocate(allocator,
																	 1, sizeof(struct vector_t));	/* Allocate #1 */

	void
		*data_pack_alloced = allocator_ctrl.allocate(allocator,
													 VECTOR_CFG_DEFAULT_MAX_SIZE, element_size);	/* Allocate #2 */

	if (NULL == vector ||																	/* Check if vector point to NULL			*/
		NULL == vector_alloced ||															/* Check if vector_alloced point to NULL	*/
		NULL == data_pack_alloced) {														/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	vector_alloced->container_type_id = VECTOR;												/* Assign vector structure					*/

	vector_alloced->info.max_size = VECTOR_CFG_DEFAULT_MAX_SIZE;
	vector_alloced->info.size = 0u;
	vector_alloced->info.mem_size = element_size;

	vector_alloced->allocator = allocator;

	vector_alloced->data = data_pack_alloced;

	vector_alloced->element_handler.assign = NULL;
	vector_alloced->element_handler.free = NULL;

	vector_alloced->exception.empty = vector_control_configration_exception_default_empty_callback;
	vector_alloced->exception.full = vector_control_configration_exception_default_full_callback;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		vector_alloced->element_handler.assign = assign;
		vector_alloced->element_handler.free = free;
	}

	// TODO : vector callbacks

	*vector = vector_alloced;

	printf("init.vector allocator : %p \r\n    ", allocator);									/* Debug only								*/
	printf("init.vector block : %p \r\n    ", vector_alloced);
	printf("init.vector data block : %p \r\n    ", data_pack_alloced);
}

/**
 * @brief This function will destroy the vector struct and free the space.
 *
 * @param vector the pointer to the container struct pointer
 *
 * @return
 *  - 0    : succeed,destroy the vector struct and free the space completely
 *  - else : fail
 */

void vector_control_configuration_destroy(VECTOR_TYPEDEF_PPTR vector)
{
	assert(vector);

	VECTOR_ALLOCATOR_TYPEDEF_PTR
		allocator = (*vector)->allocator;

	printf("destroy.vector data block : %p \r\n    ", (*vector)->data);

	allocator_ctrl.deallocate(allocator, (*vector)->data, (*vector)->info.max_size);	/* Deallocate #2 */

	(*vector)->container_type_id = 0u;													/* Assign vector structure					*/

	(*vector)->info.max_size = 0u;
	(*vector)->info.size = 0u;
	(*vector)->info.mem_size = 0u;

	(*vector)->allocator = NULL;

	(*vector)->data = NULL;

	(*vector)->exception.empty = NULL;
	(*vector)->exception.full = NULL;

	printf("destroy.vector block : %p \r\n    ", (*vector));

	allocator_ctrl.deallocate(allocator, *vector, 1);																			/* deallocate #1 */

	printf("destroy.vector allocator : %p \r\n    ", allocator);

	allocator_ctrl.configration.destroy(&allocator);

	*vector = NULL;
}

/**
 * @brief This function will configure the vector element handler.
 *
 * @param vector the pointer to the container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

void vector_control_configuration_element_handler(const VECTOR_TYPEDEF_PTR vector,
												  void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(vector);
	assert(assign);
	assert(free);

	vector->element_handler.assign = assign;
	vector->element_handler.free = free;
}

/**
 * @brief This function will configure the vector exception callback.
 *
 * @param vector the pointer to the container struct
 * @param empty the pointer to the handler that container has no elements when the container temp to insert
 * @param full the pointer to the handler that container has no elements when the container temp to erase
 *
 * @return NONE
 */

void vector_control_configuration_exception(const VECTOR_TYPEDEF_PTR vector,
											void (*empty)(void), void (*full)(void))
{
	assert(vector);

	if (NULL == empty) {
		vector->exception.empty = empty;
	}

	if (NULL == full) {
		vector->exception.full = full;
	}
}

/**
 * @brief This function will
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

void vector_control_iterators_front(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	// TODO ...
}

/**
 * @brief This function will
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

void vector_control_iterators_back(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	// TODO ...
}

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero,it would be equal or greater than zero
 *
 * @return NONE
 */

void *vector_control_element_access_at(const VECTOR_TYPEDEF_PTR vector,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(vector);
	assert(0 <= position);

	void
		*element = (void *)((size_t)(vector->data) + position * vector->info.mem_size);									/* Point destination to the address of the element which at the position location */

	printf("vector.at -> data block : %p | element : %p \r\n    ", vector->data, element);

	return element;
}

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

extern inline void *vector_control_element_access_front(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector_control_element_access_at(vector, 0);
}

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

extern inline void *vector_control_element_access_back(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector_control_element_access_at(vector, vector->info.size);
}

/**
 * @brief This function will returns pointer to the underlying array serving as element storage.
 *
 * @param vector the pointer to the container struct
 *
 * @return pointer to the underlying array serving as element storage
 */

extern inline void *vector_control_element_access_data(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->data;
}

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param vector the pointer to the container struct
 *
 * @return
 *  if the container has no elements
 */

extern inline bool vector_control_capacity_empty(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	if (vector->info.max_size <= vector->info.size) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param vector the pointer to the container struct
 *
 * @return
 *  the number of elements in the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE vector_control_capacity_size(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->info.size;
}

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param vector the pointer to the container struct
 *
 * @return
 *  the maximum number of elements the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE vector_control_capacity_max_size(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return VECTOR_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE / vector->info.mem_size;
}

/**
 * @brief This function will returns the number of elements that the container has currently allocated space for.
 *
 * @param vector the pointer to the container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE vector_control_capacity_capacity(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->info.size * vector->info.mem_size;
}

/**
 * @brief This function will increase the capacity of the vector to a size that's greater or equal to new_cap.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param size the size of elements
 *
 * @return NONE
 */

void vector_control_capacity_reserve(VECTOR_TYPEDEF_PPTR vector,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE size)
{
	assert(vector);
	assert(0 <= size);

	// TODO...
}

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

void vector_control_capacity_shrink_to_fit(VECTOR_TYPEDEF_PPTR vector)
{
	assert(vector);

	// TODO...
}

/**
 * @brief This function will erases all elements from the container.
 *
 * @param vector the pointer to the container struct
 *
 * @return NONE
 */

void vector_control_modifiers_clear(const VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	if (0 >= vector->info.size) {
		if (NULL != vector->exception.empty) {
			vector->exception.empty();
		}

		return;
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = 0; element_pos < vector->info.size; element_pos++) {
		vector_control_modifiers_set(vector, element_pos, "");
	}

	vector->info.size = 0;
}

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

void *vector_control_modifiers_insert(const VECTOR_TYPEDEF_PTR vector,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
{
	assert(vector);
	assert(0 <= position);
	assert(0 <= amount);
	assert(source);
	assert(*source);

	if (vector->info.max_size <= vector->info.size) {
		if (NULL != vector->exception.full) {
			vector->exception.full();
		}

		return NULL;
	}

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		element_amount = vector->info.size - position,
		back_element_pos = position + amount;

	void
		*element_block = allocator_ctrl.allocate(vector->allocator,
												 element_amount, vector->info.mem_size),								/* Allocate	vector malloc #3 */
		**element = allocator_ctrl.allocate(vector->allocator,
											1, sizeof(void **));												/* Allocate vector malloc #4 */

	if (NULL == element) {																						/* Check if the element point to NULL */
		return NULL;
	}

	*element = element_block;

	printf("vector.insert -> element amount : %d \r\n    ", element_amount);

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = position; element_pos < vector->info.size; element_pos++) {		/* Copy the vector to element */
		size_t
			element_addr = (size_t)element_block + element_pos * vector->info.mem_size;

		vector_control_modifiers_get(vector, element_pos, (void *)element_addr);								/* Copy the element which at the element_pos location to the element */

		printf("vector.insert -> element no.%d : %s \r\n    ", element_pos, (char *)element_addr);
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = 0; element_pos < back_element_pos - position; element_pos++) {			/* Insert the source to the vector */
		size_t
			source_addr = (size_t)*source + element_pos * vector->info.mem_size;

		vector_control_modifiers_set(vector, element_pos + position, (void *)source_addr);

		printf("vector.insert -> source no.%d : %s \r\n    ", element_pos, (char *)source_addr);
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = back_element_pos; element_pos < back_element_pos + element_amount; element_pos++) {	/* Insert the elements to the vector */
		size_t
			element_plus_insert_addr = (size_t)element_block + (element_pos - back_element_pos) * vector->info.mem_size;

		vector_control_modifiers_set(vector, element_pos, (void *)element_plus_insert_addr);
	}

	allocator_ctrl.deallocate(vector->allocator, element_block, 1);;												/* Deallocate #3 */
	allocator_ctrl.deallocate(vector->allocator, element, 1);													/* Deallocate #4 */
	element_block = NULL;
	element = NULL;																								/* Assign the element to NULL */

	vector->info.size += amount;																				/* Change the capacity of vector */

	return vector_control_element_access_at(vector, position);
}

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_erase(const VECTOR_TYPEDEF_PTR vector,
									CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination)
{
	assert(vector);
	assert(0 <= position);

	if (0 >= vector->info.size) {
		if (NULL != vector->exception.empty) {
			vector->exception.empty();
		}

		return;
	}

	if (NULL != destination) {																					/* Only get the element which at the position location when destination not point to NULL*/
		vector_control_modifiers_get(vector, position, destination);
	}

	vector_control_modifiers_del(vector, position);
}

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param vector the pointer to the container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void vector_control_modifiers_push_back(const VECTOR_TYPEDEF_PTR vector,
										void *source)
{
	assert(vector);
	assert(source);

	if (vector->info.max_size <= vector->info.size) {														/* Check if will trigger full vector exception callback */
		if (NULL != vector->exception.full) {
			vector->exception.full();
		}

		return;
	}

	vector_control_modifiers_set(vector, (vector->info.size), source);

	vector->info.size++;
}

/**
 * @brief This function will removes the last element of the container.
 *
 * @param vector the pointer to the container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void vector_control_modifiers_pop_back(const VECTOR_TYPEDEF_PTR vector,
									   void *destination)
{
	assert(vector);
	assert(destination);

	if (vector->info.size <= 0) {																			/* Check if will trigger empty vector exception callback */
		if (NULL != vector->exception.empty) {
			vector->exception.empty();
		}

		return;
	}

	vector_control_modifiers_get(vector, (vector->info.size) ? vector->info.size - 1 : 0, destination);

	vector_control_modifiers_del(vector, (vector->info.size) ? vector->info.size - 1 : 0);

	vector->info.size--;
}

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param vector the pointer to the container struct
 * @param count the count of elements
 *
 * @return NONE
 */

void vector_control_modifiers_resize(VECTOR_TYPEDEF_PPTR vector,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE count)
{
	assert(vector);
	assert(0 <= count);

	if ((*vector)->info.max_size >= count) {
		return;
	}

	allocator_ctrl.deallocate((*vector)->allocator, (*vector)->data, 1);									/* Deallocate #2.1 */

	void
		*data_pack_alloced = allocator_ctrl.allocate((*vector)->allocator,
													 count,
													 (*vector)->info.mem_size);								/* Malloc	vector malloc #2.1 */

	if (NULL == data_pack_alloced) {
		return;
	}

	(*vector)->info.max_size = count;
	(*vector)->data = data_pack_alloced;
}

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

void vector_control_modifiers_copy(VECTOR_TYPEDEF_PPTR destination,
								   VECTOR_TYPEDEF_PTR source)
{
	assert(destination);
	assert(source);

	void
		*source_data = (void *)(size_t)(source->data);

	if (NULL == (*destination) ||
		NULL == (*destination)->data) {																	/* Check if destination have been initialized */
		vector_control_configuration_init(destination,													/* if not,then initialize it */
										  source->info.mem_size, source->element_handler.assign, source->element_handler.free);
	} else {
		(*destination)->info = source->info;															/* if so,just assign */
		(*destination)->element_handler = source->element_handler;
		(*destination)->exception = source->exception;
	}

	(*destination)->info.size = source->info.size;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_amt = 0; element_amt < source->info.size; element_amt++) {
		vector_control_modifiers_set(*destination,
									 element_amt,
									 (void *)((size_t)source_data + element_amt * source->info.mem_size));/* Copy the destination to source */
	}
}

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param vector the pointer to the container struct
 * @param other container struct
 *
 * @return NONE
 */

void vector_control_modifiers_swap(VECTOR_TYPEDEF_PPTR vector,
								   VECTOR_TYPEDEF_PPTR other)
{
	assert(vector);
	assert(other);
	assert(*vector);

	VECTOR_TYPEDEF_PTR
		vector_swap = NULL;

	vector_control_modifiers_copy(&vector_swap, *other);

	vector_control_modifiers_copy(other, *vector);

	vector_control_modifiers_copy(vector, vector_swap);
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void vector_control_modifiers_set(const VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source)
{
	assert(vector);
	assert(0 <= position);
	assert(source);

	void
		*destination = (void *)((size_t)(vector->data) + position * vector->info.mem_size);									/* Point destination to the address of the element which at the position location */

	//printf("size of vector : %d \r\n    ", sizeof(struct vector_t));
	//printf("address of assign : %p \r\n    ", &vector->element_handler.assign);
	//printf("address of free : %p \r\n    ", &vector->element_handler.free);

	//printf("vector.set -> data block : %p | element : %p \r\n    ", vector->data, destination);

	if (NULL != vector->element_handler.assign) {																		/* Check if assign point to NULL */
		vector->element_handler.assign(destination, source);
	} else {
		memcpy(destination, source, vector->info.mem_size);															/* Memcpy source to destination */
	}
}

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_get(const VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination)
{
	assert(vector);
	assert(0 <= position);
	assert(destination);

	void
		*source = (void *)((size_t)(vector->data) + position * vector->info.mem_size);							/* Point source to the address of the element which at the position location */

	if (NULL == source) {
		return;
	}

	if (NULL != vector->element_handler.assign) {															/* Check if assign point to NULL */
		vector->element_handler.assign(destination, source);
	} else {
		memcpy(destination, source, vector->info.mem_size);													/* Memcpy source to destination */
	}
}

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_modifiers_del(const VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(vector);
	assert(0 <= position);
	
	vector_control_modifiers_set(vector, position, "");

	vector->info.size--;
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to insert.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_configration_exception_default_empty_callback(void)
{
	printf("\r\nthe vector has no elements when you temp to insert \r\n    ");
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param vector the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_configration_exception_default_full_callback(void)
{
	printf("\r\nthe vector has no elements when you temp to erase \r\n    ");
}