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

#include "list_family.h"

/*
*********************************************************************************************************
*									    LIST CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define LIST_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define LIST_CFG_INTEGRATED_STRUCTURE_MODE_EN					1u

/*
*********************************************************************************************************
*									        LIST DATA TYPES
*********************************************************************************************************
*/

/* Configure    list ptr type.                                                                          */
typedef struct list_family_s
*list_stp,
**list_stpp;

/**
 * @brief This struct will contain all the forward list function.
 */

struct list_control_s {
	struct {
		/* @brief This function will initialize the list struct.                                        */
		void (*init)(struct list_family_s **list,
					 container_size_t element_size,
					 generic_type_element_assign_t assign,
					 generic_type_element_free_t free);

		/* @brief This function will destroy the list struct and free the space.                        */
		void (*destroy)(struct list_family_s **list);

		/* @brief This function will configure the list element handler.                                */
		void (*element_handler)(struct list_family_s *list,
								generic_type_element_assign_t assign,
								generic_type_element_free_t free);

		/* @brief This function will configure the list exception callback.                             */
		void (*exception)(struct list_family_s *list,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the list struct.                                        */
		void (*begin)(struct list_family_s *list);

		/* @brief This function will initialize the list struct.                                        */
		void (*end)(struct list_family_s *list);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(struct list_family_s *list);

		/* @brief This function will returns a reference to the specified element in the container.     */
		void *(*at)(struct list_family_s *list,
					container_size_t position);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(struct list_family_s *list);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		container_size_t(*max_size)(struct list_family_s *list);

	   /* @brief This function will returns the number of elements in the container.                    */
		container_size_t(*size)(struct list_family_s *list);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(struct list_family_s *list);

		/* @brief This function will inserts elements after the specified position in the container.    */
		void (*insert_after)(struct list_family_s *list,
							 container_size_t position,
							 container_size_t amount, void **source);

		/* @brief This function will inserts a new element into a position
					after the specified position in the container.                                      */
		void (*emplace_after)(struct list_family_s *list,
							  container_size_t position);

		/* @brief This function will removes specified elements from the container.                     */
		void (*erase_after)(struct list_family_s *list,
							container_size_t position);

		/* @brief This function will prepends the given element value to the beginning of the container.*/
		void (*push_front)(struct list_family_s *list,
						   void *source);

		/* @brief This function will inserts a new element to the beginning of the container.           */
		void (*emplace_front)(struct list_family_s *list,
							  void *destination);

		/* @brief This function will removes the first element of the container.                        */
		void (*pop_front)(struct list_family_s *list);

		/* @brief This function will resizes the container to contain count elements. */
		void (*resize)(struct list_family_s **list,
					   container_size_t size);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(struct list_family_s **list,
					 struct list_family_s **other);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(struct list_family_s **destination,
					 struct list_family_s *source);
	}modifiers;

	struct {
		/* @brief This function will merges two sorted lists into one.                                  */
		void (*merge)(struct list_family_s *destination,
					  struct list_family_s *other);

		/* @brief This function will moves elements from another list to list.                          */
		void (*splice_after)(struct list_family_s *list,
							 container_size_t position, struct list_family_s *other,
							 container_size_t first, container_size_t last);

		/* @brief This function will removes all elements satisfying specific criteria.                 */
		void (*remove)(struct list_family_s *list,
					   void *data);

		/* @brief This function will              */
		void (*remove_if)(struct list_family_s *list,
						  bool (*rule)(void *data));

		/* @brief This function will reverses the order of the elements in the container.               */
		void (*reverse)(struct list_family_s *list);

		/* @brief This function will removes all consecutive duplicate elements from the container.     */
		void (*unique)(struct list_family_s *list);

		/* @brief This function will sorts the elements in ascending order.                             */
		void (*sort)(struct list_family_s *list,
					 bool (*comp)(void *dst, void *src, size_t len));
	}list_operations;
};

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

void list_control_configuration_init(list_stpp list,
									 container_size_t element_size,
									 generic_type_element_assign_t assign,
									 generic_type_element_free_t free);

/*
*********************************************************************************************************
*                                   VECTOR EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This array will contain all the universal list functions address.
 */

extern void *list_function_address_tables[];

#if (LIST_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the list functions conveniently.
 */

extern struct list_control_s list_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__LIST_H