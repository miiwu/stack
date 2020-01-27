/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __LIST_H
#define __LIST_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

/*
*********************************************************************************************************
*									    LIST CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    the default max size of list.                                                   */
#define LIST_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define LIST_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		1024u

/* Configure    the type of allocator.                                                                  */
#define LIST_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable delete element equal destroy node.                                            */
#define LIST_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN			1u

/* Configure    if enable integrated structure.                                                         */
#define LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/* Configure    if enable stack debug.																    */
#define LIST_CFG_DEBUG_EN										1u

/*
*********************************************************************************************************
*									        LIST DATA TYPES
*********************************************************************************************************
*/

/* ---------------------------------------- LIST TYPE ----------------------------------------- */
/* Configure    list ptr type.                                                                  */
typedef struct list_t *LIST_TYPEDEF_PTR;

/* Configure    list pptr type.                                                                 */
typedef struct list_t **LIST_TYPEDEF_PPTR;

#if (LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

struct list_control_t {
	struct {
		/* @brief This function will initialize the list struct.                                */
		void (*init)(LIST_TYPEDEF_PPTR list,
					 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
					 void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will destroy the list struct and free the space.                */
		void (*destroy)(LIST_TYPEDEF_PPTR list);

		/* @brief This function will configure the list element handler.                        */
		void (*element_handler)(LIST_TYPEDEF_PTR list,
								void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will configure the list exception callback.                     */
		void (*exception)(LIST_TYPEDEF_PTR list,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the list struct.                                */
		void (*begin)(LIST_TYPEDEF_PTR list);

		/* @brief This function will initialize the list struct.                                */
		void (*end)(LIST_TYPEDEF_PTR list);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(LIST_TYPEDEF_PTR list);

		/* @brief This function will returns a reference to the specified element in the container.     */
		void *(*at)(LIST_TYPEDEF_PTR list);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(LIST_TYPEDEF_PTR list);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		CONTAINER_GLOBAL_CFG_SIZE_TYPE(*max_size)(LIST_TYPEDEF_PTR list);

	   /* @brief This function will returns the number of elements in the container.                    */
		CONTAINER_GLOBAL_CFG_SIZE_TYPE(*size)(LIST_TYPEDEF_PTR list);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(LIST_TYPEDEF_PTR list);

		/* @brief This function will inserts elements after the specified position in the container.    */
		void (*insert_after)(LIST_TYPEDEF_PTR list,
							 CONTAINER_GLOBAL_CFG_SIZE_TYPE position, CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source);

	    /* @brief This function will inserts a new element into a position 
                    after the specified position in the container.                                      */
		void (*emplace_after)(LIST_TYPEDEF_PTR stack,
							  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

		/* @brief This function will removes specified elements from the container.                     */
		void (*erase_after)(LIST_TYPEDEF_PTR list,
							CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

		/* @brief This function will prepends the given element value to the beginning of the container.*/
		void (*push_front)(LIST_TYPEDEF_PTR list,
						   void *source);

		/* @brief This function will inserts a new element to the beginning of the container.           */
		void (*emplace_front)(LIST_TYPEDEF_PTR stack,
							  void *destination);

		/* @brief This function will removes the first element of the container.                        */
		void (*pop_front)(LIST_TYPEDEF_PTR list);

		/* @brief This function will resizes the container to contain count elements. */
		void (*resize)(LIST_TYPEDEF_PPTR list,
					   CONTAINER_GLOBAL_CFG_SIZE_TYPE size);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(LIST_TYPEDEF_PPTR list,
                     LIST_TYPEDEF_PPTR other);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(LIST_TYPEDEF_PPTR destination,
					 LIST_TYPEDEF_PTR source);
	}modifiers;

	struct {
		/* @brief This function will merges two sorted lists into one.                                  */
		void (*merge)(LIST_TYPEDEF_PTR destination,
					  LIST_TYPEDEF_PTR other);

		/* @brief This function will moves elements from another list to list.          */
		void (*splice_after)(LIST_TYPEDEF_PTR list,
							 CONTAINER_GLOBAL_CFG_SIZE_TYPE position, LIST_TYPEDEF_PTR other,
                             CONTAINER_GLOBAL_CFG_SIZE_TYPE first, CONTAINER_GLOBAL_CFG_SIZE_TYPE last);

		/* @brief This function will removes all elements satisfying specific criteria.                 */
		void (*remove)(LIST_TYPEDEF_PTR list,
					   void *data);

		/* @brief This function will              */
		void (*remove_if)(LIST_TYPEDEF_PTR list,
						  bool (*rule)(void *data));

		/* @brief This function will reverses the order of the elements in the container.               */
		void (*reverse)(LIST_TYPEDEF_PTR list);

		/* @brief This function will removes all consecutive duplicate elements from the container.     */
		void (*unique)(LIST_TYPEDEF_PTR list);

		/* @brief This function will sorts the elements in ascending order.                             */
		void (*sort)(LIST_TYPEDEF_PTR list,
					 bool (*comp)(void *dst, void *src, size_t len));
	}list_operations;
};

#endif // (LIST_CONTROL_INTERGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*								    LIST CONROL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list struct
 *
 * @param list the pointer to the forward list struct pointer
 * @param element_size the element memory size of the forward list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_init(LIST_TYPEDEF_PPTR list,
											 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											 void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will destroy the list struct and free the space
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void list_control_configuration_destroy(LIST_TYPEDEF_PPTR list);

/**
 * @brief This function will configure the list element handler
 *
 * @param list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_element_handler(LIST_TYPEDEF_PTR list,
														void (*assign)(void *dst, void *src), void(*free)(void *dst));

/**
 * @brief This function will configure the list exception callback
 *
 * @param list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_exception(LIST_TYPEDEF_PTR list,
												  void (*empty)(void), void (*full)(void));

/**
 * @brief This function will returns a reference to the first element in the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return the reference to the first element in the container
 */

void *list_control_element_access_front(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_control_element_access_at(LIST_TYPEDEF_PTR list,
                                             CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will checks if the container has no elements
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

bool list_control_capacity_empty(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return the maximum number of elements
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE list_control_capacity_max_size(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return the number of elements in the container
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE list_control_capacity_size(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE list_control_capacity_size(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will erases all elements from the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void list_control_modifiers_clear(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_control_modifiers_insert_after(LIST_TYPEDEF_PTR list,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE amount, void **source);

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_control_modifiers_emplace_after(LIST_TYPEDEF_PTR stack,
												  CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param list the pointer to the forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void list_control_modifiers_erase_after(LIST_TYPEDEF_PTR list,
												CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param list the pointer to the forward list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_control_modifiers_push_front(LIST_TYPEDEF_PTR list,
											   void *source);

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param list the pointer to the forward list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_control_modifiers_emplace_front(LIST_TYPEDEF_PTR stack,
												  void *destination);

/**
 * @brief This function will removes the first element of the container
 *
 * @param list the pointer to the forward list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void list_control_modifiers_pop_front(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will increase the capacity of the list to a size
			that's greater or equal to new_cap
 *
 * @param list the pointer to the forward list struct pointer
 * @param size the size of the forward list struct
 *
 * @return NONE
 */

void list_control_modifiers_resize(LIST_TYPEDEF_PPTR list,
										   CONTAINER_GLOBAL_CFG_SIZE_TYPE size);

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param list the pointer to the forward list struct pointer
 * @param other the pointer to the other forward list struct pointer
 *
 * @return NONE
 */

void list_control_modifiers_swap(LIST_TYPEDEF_PPTR list,
                                         LIST_TYPEDEF_PPTR other);

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param source the pointer to the source forward list struct
 *
 * @return NONE
 */

void list_control_modifiers_copy(LIST_TYPEDEF_PPTR destination,
										 LIST_TYPEDEF_PTR source);

/**
 * @brief This function will merges two sorted lists into one
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param source the pointer to the source forward list struct
 *
 * @return NONE
 */

void list_control_list_operations_merge(LIST_TYPEDEF_PTR destination,
												LIST_TYPEDEF_PTR other);

/**
 * @brief This function will moves elements from another list to list
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param other the pointer to the other forward list struct
 *
 * @return NONE
 */

void list_control_list_operations_splice_after(LIST_TYPEDEF_PTR list,
													   CONTAINER_GLOBAL_CFG_SIZE_TYPE position, LIST_TYPEDEF_PTR other,
                                                       CONTAINER_GLOBAL_CFG_SIZE_TYPE first, CONTAINER_GLOBAL_CFG_SIZE_TYPE last);

/**
 * @brief This function will removes all elements satisfying specific criteria
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param data the pointer of data
 *
 * @return NONE
 */

void list_control_list_operations_remove(LIST_TYPEDEF_PTR list,
												 void *data);

/**
 * @brief This function will
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param rule the pointer to the rule-making function
 *
 * @return NONE
 */

void list_control_list_operations_remove_if(LIST_TYPEDEF_PTR list, 
                                                    bool (*rule)(void *data));

/**
 * @brief This function will reverses the order of the elements in the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void list_control_list_operations_reverse(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void list_control_list_operations_unique(LIST_TYPEDEF_PTR list);

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void list_control_list_operations_sort(LIST_TYPEDEF_PTR list,
											   bool (*comp)(void *dst, void *src, size_t len));

/*
*********************************************************************************************************
*                                   VECTOR EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */
extern struct list_control_t list_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__LIST_H