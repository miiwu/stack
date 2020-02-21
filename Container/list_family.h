/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __LIST_FAMILY_H
#define __LIST_FAMILY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

/*
*********************************************************************************************************
*									        CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    the default max size of list.                                                   		*/
#define LIST_FAMILY_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define LIST_FAMILY_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		1024u

/* Configure    if enable delete element equal destroy node.                                            */
#define LIST_FAMILY_CFG_DELETE_ELEMENT_EQUAL_DESTROY_NODE_EN			1u

/* Configure    if enable stack debug.																    */
#define LIST_FAMILY_CFG_DEBUG_EN										1u

/*
*********************************************************************************************************
*									        DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This struct is the forward list structure module
 */

enum list_family_member_type_e {
	LIST_FAMILY_LIST = LIST,

	LIST_FAMILY_FORWARD_LIST = FORWARD_LIST,
};

/**
 * @brief This struct is the forward_list structure module
 */

struct forward_list_node_s {
	/* @brief This variables will point to the address of the list data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list node.										*/
	struct forward_list_node_s *next;
};

/**
 * @brief This struct is the list structure module
 */

struct list_node_s {
	/* @brief This variables will point to the address of the list data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list node.										*/
	struct list_node_s *next;

	/* @brief This variables will pointer to the previous list node.									*/
	struct list_node_s *prev;
};

/**
 * @brief This struct is the list structure module
 */

struct list_family_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e	container_type_id;

	struct {
		/* @brief This variables will record the maximum number of elements.							*/
		container_size_t max_size;

		/* @brief This variables will record the number of elements that
					the container has currently allocated space for.								    */
		container_size_t size;

		/* @brief This variables will record the size that each element will take up.					*/
		container_size_t mem_size;
	}info;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_ctrl;

	/* @brief This variables will pointer to the first list node.										*/
	void *node;

	/* @brief This variables will record the element handler of the container.							*/
	struct container_element_handler_s element_handler;

	struct {
		/* @brief This variables will point to the address of the list empty exception handler.		    */
		void (*empty)(void);

		/* @brief This variables will point to the address of the list full exception handler.			*/
		void (*full)(void);
	}exception;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	void (*switch_control)(void);
};

struct list_family_control_s {
	struct {
		/* @brief This function will initialize the list struct.                                        */
		void (*init)(struct list_family_s **list,
					 container_size_t element_size,
					 void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will destroy the list struct and free the space.                        */
		void (*destroy)(struct list_family_s **list);

		/* @brief This function will configure the list element handler.                                */
		void (*element_handler)(struct list_family_s *list,
								void (*assign)(void *dst, void *src), void (*free)(void *dst));

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
		void (*emplace_after)(struct list_family_s *stack,
							  container_size_t position);

		/* @brief This function will removes specified elements from the container.                     */
		void (*erase_after)(struct list_family_s *list,
							container_size_t position);

		/* @brief This function will prepends the given element value to the beginning of the container.*/
		void (*push_front)(struct list_family_s *list,
						   void *source);

		/* @brief This function will inserts a new element to the beginning of the container.           */
		void (*emplace_front)(struct list_family_s *stack,
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

struct node_operator_s {
	/* @brief This function will return the node at the specified location in the container.			*/
	void *(*get)(struct list_family_s *list,
				 container_size_t pos);

	/* @brief This variables will set the node at the specified location in the container and
				return the node.			                                                            */
	void *(*set)(struct list_family_s *list,
				 container_size_t pos, void *node);

	/* @brief This variables will delete the node at the specified location in the container.			*/
	void *(*del)(struct list_family_s *list,
				 container_size_t pos);

	/* @brief This variables will swap the nodes at the specified location in the container.			*/
	void (*swap)(struct list_family_s *list,
				 container_size_t lhs_pos,
				 container_size_t rhs_pos);
};

/*
*********************************************************************************************************
*								        FUNCTION PROTOTYPES
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
 * @param node_operator the node's operator
 *
 * @return NONE
 */

extern inline void list_family_control_get_control(enum list_family_member_type_e type,
												   struct node_operator_s operator);

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

void list_family_control_configuration_init(struct list_family_s **list,
											void (*switch_control)(void),
											enum allocator_type_e allocator_type,
											container_size_t element_size,
											void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will destroy the list struct and free the space
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void list_family_control_configuration_destroy(struct list_family_s **list);

/**
 * @brief This function will configure the list element handler
 *
 * @param list the pointer to the forward list struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_family_control_configuration_element_handler(struct list_family_s *list,
													   void (*assign)(void *dst, void *src),
													   void(*free)(void *dst));

  /**
   * @brief This function will configure the list exception callback
   *
   * @param list the pointer to the forward list struct pointer
   * @param assign the pointer to the assign element handler of the specified data type
   * @param free the pointer to the free element handler of the specified data type
   *
   * @return NONE
   */

void list_family_control_configuration_exception(struct list_family_s *list,
												 void (*empty)(void), void (*full)(void));

  /**
   * @brief This function will returns a reference to the first element in the container
   *
   * @param list the pointer to the forward list struct pointer
   *
   * @return the reference to the first element in the container
   */

void *list_family_control_element_access_front(struct list_family_s *list);

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param list the pointer to the forward list struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_family_control_element_access_at(struct list_family_s *list,
											container_size_t position);

  /**
   * @brief This function will checks if the container has no elements
   *
   * @param list the pointer to the forward list struct pointer
   *
   * @return
	  - true,the container has no elements
	  - false,the container has elements
   */

bool list_family_control_capacity_empty(struct list_family_s *list);

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return the maximum number of elements
 */

container_size_t list_family_control_capacity_max_size(struct list_family_s *list);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return the number of elements in the container
 */

container_size_t list_family_control_capacity_size(struct list_family_s *list);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

container_size_t list_family_control_capacity_size(struct list_family_s *list);

/**
 * @brief This function will erases all elements from the container
 *
 * @param list the pointer to the forward list struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_clear(struct list_family_s *list);

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

void list_family_control_modifiers_insert_after(struct list_family_s *list,
												container_size_t position,
												container_size_t amount, void **source);

  /**
   * @brief This function will push a new element on top of the stack, and the element is constructed in-place
   *
   * @param list the pointer to the forward list struct pointer
   * @param position the position of element,it would be equal or greater than zero
   *
   * @return NONE
   */

void list_family_control_modifiers_emplace_after(struct list_family_s *stack,
												 container_size_t position);

  /**
   * @brief This function will erases the specified elements from the container
   *
   * @param list the pointer to the forward list struct pointer
   * @param position the position of element,it would be equal or greater than zero
   *
   * @return NONE
   */

void list_family_control_modifiers_erase_after(struct list_family_s *list,
											   container_size_t position);

  /**
   * @brief This function will prepends the given element value to the beginning of the container
   *
   * @param list the pointer to the forward list struct pointer
   * @param source pointer to the source
   *
   * @return NONE
   */

void list_family_control_modifiers_push_front(struct list_family_s *list,
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

void list_family_control_modifiers_emplace_front(struct list_family_s *stack,
												 void *destination);

  /**
   * @brief This function will removes the first element of the container
   *
   * @param list the pointer to the forward list struct pointer
   * @param destination pointer to the destination
   *
   * @return NONE
   */

void list_family_control_modifiers_pop_front(struct list_family_s *list);

/**
 * @brief This function will increase the capacity of the list to a size
			that's greater or equal to new_cap
 *
 * @param list the pointer to the forward list struct pointer
 * @param size the size of the forward list struct
 *
 * @return NONE
 */

void list_family_control_modifiers_resize(struct list_family_s **list,
										  container_size_t size);

  /**
   * @brief This function will exchanges the contents of the container with those of other
   *
   * @param list the pointer to the forward list struct pointer
   * @param other the pointer to the other forward list struct pointer
   *
   * @return NONE
   */

void list_family_control_modifiers_swap(struct list_family_s **list,
										struct list_family_s **other);

  /**
   * @brief This function will copy the contents of the container to those of other
   *
   * @param destination the pointer to the destination forward list struct pointer
   * @param source the pointer to the source forward list struct
   *
   * @return NONE
   */

void list_family_control_modifiers_copy(struct list_family_s **destination,
										struct list_family_s *source);

  /**
   * @brief This function will merges two sorted lists into one
   *
   * @param destination the pointer to the destination forward list struct pointer
   * @param source the pointer to the source forward list struct
   *
   * @return NONE
   */

void list_family_control_list_operations_merge(struct list_family_s *destination,
											   struct list_family_s *other);

  /**
   * @brief This function will moves elements from another list to list
   *
   * @param destination the pointer to the destination forward list struct pointer
   * @param position the position of element,it would be equal or greater than zero
   * @param other the pointer to the other forward list struct
   *
   * @return NONE
   */

void list_family_control_list_operations_splice_after(struct list_family_s *list,
													  container_size_t position, struct list_family_s *other,
													  container_size_t first, container_size_t last);

  /**
   * @brief This function will removes all elements satisfying specific criteria
   *
   * @param destination the pointer to the destination forward list struct pointer
   * @param data the pointer of data
   *
   * @return NONE
   */

void list_family_control_list_operations_remove(struct list_family_s *list,
												void *data);

  /**
   * @brief This function will
   *
   * @param destination the pointer to the destination forward list struct pointer
   * @param rule the pointer to the rule-making function
   *
   * @return NONE
   */

void list_family_control_list_operations_remove_if(struct list_family_s *list,
												   bool (*rule)(void *data));

  /**
   * @brief This function will reverses the order of the elements in the container
   *
   * @param destination the pointer to the destination forward list struct pointer
   *
   * @return NONE
   */

void list_family_control_list_operations_reverse(struct list_family_s *list);

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination forward list struct pointer
 *
 * @return NONE
 */

void list_family_control_list_operations_unique(struct list_family_s *list);

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination forward list struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void list_family_control_list_operations_sort(struct list_family_s *list,
											  bool (*comp)(void *dst, void *src, size_t len));

  /**
   * @brief This function will initialize the list node struct.
   *
   * @param list the pointer to the list struct pointer
   *
   * @return NONE
   */

void *list_family_control_init_node(struct list_family_s *list);

/**
 * @brief This function will destroy list node struct and free the space.
 *
 * @param list the pointer to the list struct pointer
 * @param node the pointer to the list node struct pointer
 *
 * @return NONE
 */

void list_family_control_destroy_node(struct list_family_s *list,
									  void *node);

  /*
  *********************************************************************************************************
  *                                   VECTOR EXTERN GLOBAL VARIABLES
  *********************************************************************************************************
  */

  /*
  *********************************************************************************************************
  *                                             MODULE END
  *********************************************************************************************************
  */

#endif // !__LIST_FAMILY_H