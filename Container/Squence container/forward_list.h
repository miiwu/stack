/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __FORWARD_LIST_H
#define __FORWARD_LIST_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "list_family.h"

/*
*********************************************************************************************************
*									    FORWARD_LIST CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define FORWARD_LIST_CFG_ALLOCATOR_TYPE								    CONCEPT_ALLOCATOR

/* Configure    if enable integrated structure.                                                         */
#define FORWARD_LIST_CFG_INTEGRATED_STRUCTURE_MODE_EN					1u

/*
*********************************************************************************************************
*									        FORWARD_LIST DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the forward list structure typedef
 */

typedef list_family_stp
forward_list_stp,
*forward_list_stpp;

/**
 * @brief This struct will contain all the forward list function.
 */

struct forward_list_control_s {
	struct {
		/* @brief This function will initialize the list struct.                                        */
		errno_t(*init)(forward_list_stpp list,
					   container_size_t element_size,
					   generic_type_element_assign_t assign,
					   generic_type_element_free_t free);

		  /* @brief This function will destroy the list struct and free the space.                        */
		void (*destroy)(forward_list_stpp list);

		/* @brief This function will configure the list element handler.                                */
		void (*element_handler)(forward_list_stp list,
								generic_type_element_assign_t assign,
								generic_type_element_free_t free);

		/* @brief This function will configure the list exception callback.                             */
		void (*exception)(forward_list_stp list,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the list struct.                                        */
		void (*begin)(forward_list_stp list);

		/* @brief This function will initialize the list struct.                                        */
		void (*end)(forward_list_stp list);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(forward_list_stp list);

		/* @brief This function will returns a reference to the specified element in the container.     */
		void *(*at)(forward_list_stp list,
					container_size_t position);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(forward_list_stp list);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		container_size_t(*max_size)(forward_list_stp list);

	   /* @brief This function will returns the number of elements in the container.                    */
		container_size_t(*size)(forward_list_stp list);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(forward_list_stp list);

		/* @brief This function will inserts elements after the specified position in the container.    */
		void (*insert_after)(forward_list_stp list,
							 container_size_t position,
							 container_size_t amount, void **source);

		/* @brief This function will inserts a new element into a position
					after the specified position in the container.                                      */
		void (*emplace_after)(forward_list_stp stack,
							  container_size_t position);

		/* @brief This function will removes specified elements from the container.                     */
		void (*erase_after)(forward_list_stp list,
							container_size_t position);

		/* @brief This function will prepends the given element value to the beginning of the container.*/
		void (*push_front)(forward_list_stp list,
						   void *source);

		/* @brief This function will inserts a new element to the beginning of the container.           */
		void (*emplace_front)(forward_list_stp stack,
							  void *destination);

		/* @brief This function will removes the first element of the container.                        */
		void (*pop_front)(forward_list_stp list);

		/* @brief This function will resizes the container to contain count elements. */
		void (*resize)(forward_list_stpp list,
					   container_size_t size);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(forward_list_stpp list,
					 forward_list_stpp other);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(forward_list_stpp destination,
					 forward_list_stp source);
	}modifiers;

	struct {
		/* @brief This function will merges two sorted lists into one.                                  */
		void (*merge)(forward_list_stp destination,
					  forward_list_stp other);

		/* @brief This function will moves elements from another list to list.                          */
		void (*splice_after)(forward_list_stp list,
							 container_size_t position, forward_list_stp other,
							 container_size_t first, container_size_t last);

		/* @brief This function will removes all elements satisfying specific criteria.                 */
		void (*remove)(forward_list_stp list,
					   void *data);

		/* @brief This function will              */
		void (*remove_if)(forward_list_stp list,
						  bool (*rule)(void *data));

		/* @brief This function will reverses the order of the elements in the container.               */
		void (*reverse)(forward_list_stp list);

		/* @brief This function will removes all consecutive duplicate elements from the container.     */
		void (*unique)(forward_list_stp list);

		/* @brief This function will sorts the elements in ascending order.                             */
		void (*sort)(forward_list_stp list,
					 bool (*comp)(void *dst, void *src, size_t len));
	}list_operations;
};

/*
*********************************************************************************************************
*								    FORWARD_LIST CONROL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

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

errno_t forward_list_control_configuration_init(forward_list_stpp forward_list,
												container_size_t element_size,
												generic_type_element_assign_t assign,
												generic_type_element_free_t free);

   /*
   *********************************************************************************************************
   *                                   VECTOR EXTERN GLOBAL VARIABLES
   *********************************************************************************************************
   */

   /**
	* @brief This array will contain all the universal forward_list functions address.
	*/

extern void *forward_list_function_address_tables[];

#if (FORWARD_LIST_CFG_INTEGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */

extern struct forward_list_control_s forward_list_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__FORWARD_LIST_H