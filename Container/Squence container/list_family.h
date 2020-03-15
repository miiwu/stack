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

/* Configure    the default max size of list_family.                                                   		*/
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
 * @brief This type is the list_family family typedef
 */

typedef struct container_family_s
*list_family_stp,
**list_family_stpp;

/**
 * @brief This struct is the forward list_family structure module
 */

enum list_family_member_type_e {
	LIST_FAMILY_LIST = LIST,

	LIST_FAMILY_FORWARD_LIST = FORWARD_LIST,
};

/**
 * @brief This struct is the forward_list structure module
 */

struct forward_list_node_s {
	/* @brief This variables will point to the address of the list_family data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list_family node.										*/
	struct forward_list_node_s *next;
};

/**
 * @brief This struct is the list_family structure module
 */

struct list_node_s {
	/* @brief This variables will point to the address of the list_family data memory block.					*/
	void *data;

	/* @brief This variables will pointer to the next list_family node.										*/
	struct list_node_s *next;

	/* @brief This variables will pointer to the previous list_family node.									*/
	struct list_node_s *prev;
};

/**
 * @brief This type will contain all the universal node operators.
 */

struct node_operator_s {
	/* @brief This function will return the node at the specified location in the container.			*/
	void *(*get)(list_family_stp list_family,
				 container_size_t pos);

	/* @brief This variables will set the node at the specified location in the container and
				return the node.			                                                            */
	void *(*set)(list_family_stp list_family,
				 container_size_t pos, void *node);

	/* @brief This variables will delete the node at the specified location in the container.			*/
	void *(*del)(list_family_stp list_family,
				 container_size_t pos);

	/* @brief This variables will swap the nodes at the specified location in the container.			*/
	void (*swap)(list_family_stp list_family,
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
 * @brief This function will initialize the list_family struct
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

extern inline void list_family_control_get_control(enum list_family_member_type_e type,
												   struct node_operator_s operator);

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
											   generic_type_element_free_t free);

	/**
	 * @brief This function will destroy the list_family struct and free the space
	 *
	 * @param list_family the pointer to the forward list_family struct pointer
	 *
	 * @return NONE
	 */

void list_family_control_configuration_destroy(list_family_stpp list_family);

/**
 * @brief This function will configure the list_family element handler
 *
 * @param list_family the pointer to the forward list_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_family_control_configuration_element_handler(list_family_stp list_family,
													   generic_type_element_assign_t assign,
													   generic_type_element_free_t free);

  /**
   * @brief This function will configure the list_family exception callback
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param assign the pointer to the assign element handler of the specified data type
   * @param free the pointer to the free element handler of the specified data type
   *
   * @return NONE
   */

void list_family_control_configuration_exception(list_family_stp list_family,
												 void (*empty)(void), void (*full)(void));

  /**
   * @brief This function will returns a reference to the first element in the container
   *
   * @param list_family the pointer to the forward list_family struct pointer
   *
   * @return the reference to the first element in the container
   */

void *list_family_control_element_access_front(list_family_stp list_family);

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param list_family the pointer to the forward list_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *list_family_control_element_access_at(list_family_stp list_family,
											container_size_t position);

  /**
   * @brief This function will checks if the container has no elements
   *
   * @param list_family the pointer to the forward list_family struct pointer
   *
   * @return
	  - true,the container has no elements
	  - false,the container has elements
   */

bool list_family_control_capacity_empty(list_family_stp list_family);

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param list_family the pointer to the forward list_family struct pointer
 *
 * @return the maximum number of elements
 */

container_size_t list_family_control_capacity_max_size(list_family_stp list_family);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list_family the pointer to the forward list_family struct pointer
 *
 * @return the number of elements in the container
 */

container_size_t list_family_control_capacity_size(list_family_stp list_family);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param list_family the pointer to the forward list_family struct pointer
 *
 * @return NONE
 */

container_size_t list_family_control_capacity_size(list_family_stp list_family);

/**
 * @brief This function will erases all elements from the container
 *
 * @param list_family the pointer to the forward list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_modifiers_clear(list_family_stp list_family);

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param list_family the pointer to the forward list_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void list_family_control_modifiers_insert_after(list_family_stp list_family,
												container_size_t position,
												container_size_t amount, void **source);

  /**
   * @brief This function will push a new element on top of the stack, and the element is constructed in-place
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param position the position of element,it would be equal or greater than zero
   *
   * @return NONE
   */

void list_family_control_modifiers_emplace_after(list_family_stp stack,
												 container_size_t position);

  /**
   * @brief This function will erases the specified elements from the container
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param position the position of element,it would be equal or greater than zero
   *
   * @return NONE
   */

void list_family_control_modifiers_erase_after(list_family_stp list_family,
											   container_size_t position);

  /**
   * @brief This function will prepends the given element value to the beginning of the container
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param source pointer to the source
   *
   * @return NONE
   */

void list_family_control_modifiers_push_front(list_family_stp list_family,
											  void *source);

  /**
   * @brief This function will Inserts a new element to the beginning of the container.
			  The element is constructed through std::allocator_traits::construct,
			  which typically uses placement-new to construct the element in-place
			  at the location provided by the container.
			  The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param destination pointer to the destination
   *
   * @return NONE
   */

void list_family_control_modifiers_emplace_front(list_family_stp stack,
												 void *destination);

  /**
   * @brief This function will removes the first element of the container
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param destination pointer to the destination
   *
   * @return NONE
   */

void list_family_control_modifiers_pop_front(list_family_stp list_family);

/**
 * @brief This function will increase the capacity of the list_family to a size
			that's greater or equal to new_cap
 *
 * @param list_family the pointer to the forward list_family struct pointer
 * @param size the size of the forward list_family struct
 *
 * @return NONE
 */

void list_family_control_modifiers_resize(list_family_stpp list_family,
										  container_size_t size);

  /**
   * @brief This function will exchanges the contents of the container with those of other
   *
   * @param list_family the pointer to the forward list_family struct pointer
   * @param other the pointer to the other forward list_family struct pointer
   *
   * @return NONE
   */

void list_family_control_modifiers_swap(list_family_stpp list_family,
										list_family_stpp other);

  /**
   * @brief This function will copy the contents of the container to those of other
   *
   * @param destination the pointer to the destination forward list_family struct pointer
   * @param source the pointer to the source forward list_family struct
   *
   * @return NONE
   */

void list_family_control_modifiers_copy(list_family_stpp destination,
										list_family_stp source);

  /**
   * @brief This function will merges two sorted lists into one
   *
   * @param destination the pointer to the destination forward list_family struct pointer
   * @param source the pointer to the source forward list_family struct
   *
   * @return NONE
   */

void list_family_control_list_operations_merge(list_family_stp destination,
											   list_family_stp other);

  /**
   * @brief This function will moves elements from another list_family to list_family
   *
   * @param destination the pointer to the destination forward list_family struct pointer
   * @param position the position of element,it would be equal or greater than zero
   * @param other the pointer to the other forward list_family struct
   *
   * @return NONE
   */

void list_family_control_list_operations_splice_after(list_family_stp list_family,
													  container_size_t position, list_family_stp other,
													  container_size_t first, container_size_t last);

  /**
   * @brief This function will removes all elements satisfying specific criteria
   *
   * @param destination the pointer to the destination forward list_family struct pointer
   * @param data the pointer of data
   *
   * @return NONE
   */

void list_family_control_list_operations_remove(list_family_stp list_family,
												void *data);

  /**
   * @brief This function will
   *
   * @param destination the pointer to the destination forward list_family struct pointer
   * @param rule the pointer to the rule-making function
   *
   * @return NONE
   */

void list_family_control_list_operations_remove_if(list_family_stp list_family,
												   bool (*rule)(void *data));

  /**
   * @brief This function will reverses the order of the elements in the container
   *
   * @param destination the pointer to the destination forward list_family struct pointer
   *
   * @return NONE
   */

void list_family_control_list_operations_reverse(list_family_stp list_family);

/**
 * @brief This function will removes all consecutive duplicate elements from the container
 *
 * @param destination the pointer to the destination forward list_family struct pointer
 *
 * @return NONE
 */

void list_family_control_list_operations_unique(list_family_stp list_family);

/**
 * @brief This function will sorts the elements in ascending order
 *
 * @param destination the pointer to the destination list_family struct pointer
 * @param comp the pointer to the compare function that you wish
 *
 * @return NONE
 */

void list_family_control_list_operations_sort(list_family_stp list_family,
											  compare_t comp);

/**
 * @brief This function will initialize the list_family node struct.
 *
 * @param list_family the pointer to the list_family struct pointer
 *
 * @return NONE
 */

void *list_family_control_init_node(list_family_stp list_family);

/**
 * @brief This function will destroy list_family node struct and free the space.
 *
 * @param list_family the pointer to the list_family struct pointer
 * @param node the pointer to the list_family node struct pointer
 *
 * @return NONE
 */

void list_family_control_destroy_node(list_family_stp list_family,
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