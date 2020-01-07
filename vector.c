/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "vector.h"
#include "allocator.h"


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
	/* @brief RESERVED This variables will record the identity code of container.						*/
	int	id_code;

	struct {
		/* @brief This variables will record the maximum number of elements.							*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE max_size;

		/* @brief This variables will record the number of elements that
				  the container has currently allocated space for.										*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE capacity;

		/* @brief This variables will record the size that each element will take up.					*/
		CONTAINER_GLOBAL_CFG_SIZE_TYPE mem_size;

		/* @brief This variables will record if the element type equal string type.						*/
		bool string_type;
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
		/* @brief This variables will point to the address of the vector empty callback handler.		*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the vector full callback handler.			*/
		void (*full)(void);

		/* @brief This variables will point to the address of the heap null callback handler.			*/
		void (*null_heap)(void);
	}callback;
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
 * @brief This array will contain all the vector functions address.
 */

int vector_function_address_tables[] =
{
	(int)&vector_control_configuration_init,					/* No.0 : initialize */

	(int)&vector_control_configuration_destroy,					/* No.1 : destroy */

	(int)&vector_control_element_access_at,						/* No.3 : at */

	(int)&vector_control_capacity_empty,						/* No.4 : empty */

	(int)&vector_control_capacity_size,							/* No.5 : size */

	(int)&vector_control_capacity_capacity,						/* No.6 : capacity */

	(int)&vector_control_modifiers_push_back,					/* No.7 : push_back */

	(int)&vector_control_modifiers_erase,						/* No.8 : erase */

	(int)&vector_control_modifiers_copy,						/* No.9 : copy */

	(int)&vector_control_modifiers_swap,						/* No.10 : swap */
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

		vector_control_configuration_callback,
	},
	{
		vector_control_iterators_front,

		vector_control_iterators_back,
	},
	{
		vector_control_element_access_at,

		vector_control_element_access_front,

		vector_control_element_access_back,

		vector_control_element_access_data,
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
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void vector_control_modifiers_set(VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_get(VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination);

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_modifiers_del(VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the vector struct.
 *
 * @param vector container struct
 * @param element_size the size of element
 * @param string_type if the element is the string type
 * @param assign_func pointer to the assign function of element
 * @param free_func pointer to the free function of element
 *
 * @return
 *  - 0    : succeed,initialize the at struct completely
 *  - else : fail
 */

void vector_control_configuration_init(VECTOR_TYPEDEF_PPTR vector,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size, bool string_type,
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
		*data_pack_alloced = allocator_ctrl.allocate(allocator, VECTOR_CFG_DEFAULT_MAX_SIZE,
		(string_type) ?
													 (element_size + VECTOR_CFG_DEFAULT_MAX_SIZE) :
													 (element_size));						/* Allocate #2 */

	if (NULL == vector ||																	/* Check if vector point to NULL			*/
		NULL == vector_alloced ||															/* Check if vector_alloced point to NULL	*/
		NULL == data_pack_alloced) {														/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	vector_alloced->id_code = VECTOR;														/* Assign vector structure					*/
	vector_alloced->info.max_size = VECTOR_CFG_DEFAULT_MAX_SIZE;
	vector_alloced->info.capacity = 0u;
	vector_alloced->info.mem_size = element_size;
	vector_alloced->info.string_type = string_type;
	vector_alloced->allocator = allocator;
	vector_alloced->data = data_pack_alloced;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		vector_alloced->element_handler.assign = assign;
		vector_alloced->element_handler.free = free;
	}

	// TODO : vector callbacks

	*vector = vector_alloced;

	printf("init.vector block : %p \r\n", vector_alloced);									/* Debug only								*/
	printf("init.vector data block : %p \r\n", data_pack_alloced);
}

/**
 * @brief This function will destroy the vector struct and free the space.
 *
 * @param vector container struct
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

	printf("destroy.vector data block : %p \r\n", (*vector)->data);
	printf("destroy.vector block : %p \r\n", (*vector));

	allocator_ctrl.deallocate(allocator, (*vector)->data, 1);																	/* Deallocate #2 */

	(*vector)->info.max_size = 0u;
	(*vector)->info.capacity = 0u;
	(*vector)->allocator = NULL;
	(*vector)->data = NULL;
	(*vector)->element_handler.assign = NULL;
	(*vector)->element_handler.free = NULL;
	(*vector)->callback.empty = NULL;
	(*vector)->callback.full = NULL;
	(*vector)->callback.null_heap = NULL;

	allocator_ctrl.deallocate(allocator, *vector, 1);																			/* deallocate #1 */

	allocator_ctrl.configration.destroy(&allocator);

	*vector = NULL;
}

/**
 * @brief This function will configure the vector element handler.
 *
 * @param vector container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

void vector_control_configuration_element_handler(VECTOR_TYPEDEF_PTR vector,
												  void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(vector);

	vector->element_handler.assign = assign;
	vector->element_handler.free = free;
}

/**
 * @brief This function will
 *
 * @param vector container struct
 * @param empty pointer to the address of element callback that container has no elements when delete element
 * @param full pointer to the address of element callback that container has no elements when add element
 * @param null_heap pointer to the address of element callback that malloc is valid
 *
 * @return NONE
 */

void vector_control_configuration_callback(VECTOR_TYPEDEF_PTR vector,
										   void (*empty)(void), void (*full)(void), void (*null_heap)(void))
{
	assert(vector);

	vector->callback.empty = empty;
	vector->callback.full = full;
	vector->callback.null_heap = null_heap;
}

/**
 * @brief This function will
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_iterators_front(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	// TODO ...
}

/**
 * @brief This function will
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_iterators_back(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	// TODO ...
}

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero,it would be equal or greater than zero
 *
 * @return NONE
 */

void *vector_control_element_access_at(VECTOR_TYPEDEF_PTR vector,
									   CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(vector);
	assert(0 <= position);

	void
		*element = (void *)((int)vector->data + position * vector->info.mem_size);									/* Point destination to the address of the element which at the position location */

	printf("vector.at -> data block : %p | element : %p \r\n", vector->data, element);

	return element;
}

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

extern inline void *vector_control_element_access_front(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector_control_element_access_at(vector, 0);
}

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

extern inline void *vector_control_element_access_back(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector_control_element_access_at(vector, vector->info.capacity);
}

/**
 * @brief This function will returns pointer to the underlying array serving as element storage.
 *
 * @param vector container struct
 *
 * @return pointer to the underlying array serving as element storage
 */

extern inline void *vector_control_element_access_data(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->data;
}

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param vector container struct
 *
 * @return
 *  if the container has no elements
 */

extern inline bool vector_control_capacity_empty(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	if (vector->info.max_size <= vector->info.capacity) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param vector container struct
 *
 * @return
 *  the number of elements in the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE vector_control_capacity_size(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->info.capacity;
}

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param vector container struct
 *
 * @return
 *  the maximum number of elements the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE vector_control_capacity_max_size(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return VECTOR_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE / vector->info.mem_size;
}

/**
 * @brief This function will returns the number of elements that the container has currently allocated space for.
 *
 * @param vector container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE vector_control_capacity_capacity(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->info.capacity;
}

/**
 * @brief This function will increase the capacity of the vector to a size that's greater or equal to new_cap.
 *
 * @param vector container struct
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
 * @param vector container struct
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
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_modifiers_clear(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	if (0 >= vector->info.capacity) {
		if (NULL != vector->callback.empty) {
			vector->callback.empty();
		}

		return;
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pos = 0; element_pos < vector->info.capacity; element_pos++) {
		vector_control_modifiers_set(vector, element_pos, "");
	}

	vector->info.capacity = 0;
}

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

void *vector_control_modifiers_insert(VECTOR_TYPEDEF_PTR vector,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source)
{
	assert(vector);
	assert(0 <= position);
	assert(0 <= amount);
	assert(source);
	assert(*source);

	if (vector->info.max_size <= vector->info.capacity) {
		if (NULL != vector->callback.full) {
			vector->callback.full();
		}

		return NULL;
	}

	void
		**element = allocator_ctrl.allocate(vector->allocator,
											1, sizeof(void **));												/* Allocate vector malloc #3 */

	CONTAINER_GLOBAL_CFG_SIZE_TYPE
		element_amount = vector->info.capacity - position,
		back_element_pos = position + amount;

	if (NULL == element) {																						/* Check if the element point to NULL */
		return NULL;
	}

	printf("vector.insert -> element amount : %d \r\n", element_amount);

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pop = position; element_pop < vector->info.capacity; element_pop++) {		/* Copy the vector to element */
		*(element + element_pop) = allocator_ctrl.allocate(vector->allocator,
														   1, vector->info.mem_size);							/* Allocate	vector malloc #4 */

		vector_control_modifiers_get(vector, element_pop, *(element + element_pop));							/* Copy the element which at the element_pop location to the element */

		printf("vector.insert -> element no.%d : %s \r\n", element_pop, (char *)*(element + element_pop));
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pop = position; element_pop < back_element_pos; element_pop++) {			/* Insert the source to the vector */
		vector_control_modifiers_set(vector, element_pop, *(source + element_pop));

		printf("vector.insert -> source no.%d : %s \r\n", element_pop, (char *)*(source + element_pop));
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_pop = back_element_pos; element_pop < back_element_pos + element_amount; element_pop++) {	/* Insert the elements to the vector */
		vector_control_modifiers_set(vector, element_pop, *(element + element_pop - back_element_pos));
	}

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_cnt = 0; element_cnt < element_amount; element_cnt++) {					/* Free the element */
		allocator_ctrl.deallocate(vector->allocator, *(element + element_cnt), 1);								/* Deallocate #4 */
		*(element + element_cnt) = NULL;																		/* Assign the pointer point to the part copy of vector to NULL */
	}

	allocator_ctrl.deallocate(vector->allocator, *element, 1);													/* Deallocate #3 */
	*element = NULL;																							/* Assign the element to NULL */

	vector->info.capacity += amount;																			/* Change the capacity of vector */

	return vector_control_element_access_at(vector, position);
}

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_erase(VECTOR_TYPEDEF_PTR vector,
									CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination)
{
	assert(vector);
	assert(0 <= position);

	if (0 >= vector->info.capacity) {
		if (NULL != vector->callback.empty) {
			vector->callback.empty();
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
 * @param vector container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void vector_control_modifiers_push_back(VECTOR_TYPEDEF_PTR vector,
										void *source)
{
	assert(vector);
	assert(source);

	if (vector->info.max_size <= vector->info.capacity) {														/* Check if will trigger full vector exception callback */
		if (NULL != vector->callback.full) {
			vector->callback.full();
		}

		return;
	}

	vector_control_modifiers_set(vector, (vector->info.capacity), source);

	vector->info.capacity++;
}

/**
 * @brief This function will removes the last element of the container.
 *
 * @param vector container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void vector_control_modifiers_pop_back(VECTOR_TYPEDEF_PTR vector,
									   void *destination)
{
	assert(vector);
	assert(destination);

	if (vector->info.capacity <= 0) {																			/* Check if will trigger empty vector exception callback */
		if (NULL != vector->callback.empty) {
			vector->callback.empty();
		}

		return;
	}

	vector_control_modifiers_get(vector, (vector->info.capacity) ? vector->info.capacity - 1 : 0, destination);

	vector_control_modifiers_del(vector, (vector->info.capacity) ? vector->info.capacity - 1 : 0);

	vector->info.capacity--;
}

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param vector container struct
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
													 ((*vector)->info.string_type) ?
													 ((*vector)->info.mem_size + VECTOR_CFG_DEFAULT_MAX_SIZE) :
													 ((*vector)->info.mem_size));		/* Malloc	vector malloc #2.1 */

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

	if (NULL == (*destination) ||
		NULL == (*destination)->data) {																	/* Check if destination have been initialized */
		vector_control_configuration_init(destination,													/* if not,then initialize it */
										  source->info.mem_size, source->info.string_type, source->element_handler.assign, source->element_handler.free);
	} else {
		(*destination)->info = source->info;															/* if so,just assign */
		(*destination)->element_handler = source->element_handler;
		(*destination)->callback = source->callback;
	}

	(*destination)->info.capacity = source->info.capacity;

	for (CONTAINER_GLOBAL_CFG_SIZE_TYPE element_amt = 0; element_amt < source->info.capacity; element_amt++) {		/* Copy the destination to source */
		vector_control_modifiers_set(*destination, element_amt, (void *)((int)source->data + element_amt * source->info.mem_size));
	}
}

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param vector container struct
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
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param source pointer to the source
 *
 * @return NONE
 */

void vector_control_modifiers_set(VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source)
{
	assert(vector);
	assert(0 <= position);
	assert(source);

	void
		*destination = (void *)((int)vector->data + position * vector->info.mem_size);									/* Point destination to the address of the element which at the position location */

	//printf("vector.set -> data block : %p | element : %p \r\n", vector->data, destination);

	if (NULL != vector->element_handler.assign) {																		/* Check if assign point to NULL */
		vector->element_handler.assign(destination, source);
	} else {
		if (vector->info.string_type) {																					/* Check if the type of element equal string */
			strcpy(destination, source);
		} else {
			memcpy(destination, source, vector->info.mem_size);															/* Memcpy source to destination */
		}
	}
}

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_get(VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *destination)
{
	assert(vector);
	assert(0 <= position);
	assert(destination);

	void
		*source = (void *)((int)vector->data + position * vector->info.mem_size);							/* Point source to the address of the element which at the position location */

	if (NULL == source) {
		return;
	}

	if (NULL != vector->element_handler.assign) {															/* Check if assign point to NULL */
		vector->element_handler.assign(destination, source);
	} else {
		if (vector->info.string_type) {																		/* Check if the type of element equal string */
			strcpy(destination, source);
		} else {
			memcpy(destination, source, vector->info.mem_size);												/* Memcpy source to destination */
		}
	}
}

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void vector_control_modifiers_del(VECTOR_TYPEDEF_PTR vector,
								  CONTAINER_GLOBAL_CFG_SIZE_TYPE position)
{
	assert(vector);
	assert(0 <= position);

	vector_control_modifiers_set(vector, position, "");

	vector->info.capacity--;
}