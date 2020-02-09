/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __TREE_FAMILY_H
#define __TREE_FAMILY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the type of sort algorithm.                                                             */
#define TREE_FAMILY_CFG_SORT_ALGORITHM_TYPE								BUBBLE_SORT

/* Configure    the type of sort algorithm.                                                             */
#define TREE_FAMILY_CFG_DEBUG_EN								        1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This struct is the binary tree structure module
 */

enum tree_family_member_type_e {
	BINARY_TREE_FAMILY_AVL_TREE,

	BINARY_TREE_FAMILY_TWO_THREE_TREE,

	BINARY_TREE_FAMILY_RED_BLACK_TREE,
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct tree_family_chain_node_s {
	void *data;

	CONTAINER_GLOBAL_CFG_SIZE_TYPE hight;

	void *link;
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

struct tree_family_chain_node_data_content_s {
	int key;

	char content[0];
};

/**
 * @brief This struct is the binary tree link node structure module.
 */

typedef struct tree_family_search_node_return_s {
	size_t location;

	struct tree_family_chain_node_s *node;

	struct tree_family_chain_node_s *node_prev;
}tree_family_search_node_return_st;

/**
 * @brief This struct is the binary tree link node structure module.
 */

typedef size_t tree_family_search_match_rule_t(struct tree_family_s *, void *, void *);

/**
 * @brief This struct is the binary tree link node structure module.
 */

typedef void *tree_family_search_recursion_rule_t(struct tree_family_s *, void *, void *);

/**
 * @brief This struct is the binary tree link node structure module.
 */

typedef void tree_family_insert_rule_t(struct tree_family_s *, struct tree_family_search_node_return_s, void *);

/**
 * @brief This struct will control the unique operator.
 */

struct tree_family_node_infomation_s {
	enum tree_family_member_type_e member_type;

	size_t data_mem_len;

	size_t link_mem_len;

	size_t data_element_count;

	size_t link_element_count;
};

/**
 * @brief This struct will control the unique operator.
 */

struct tree_family_node_operator_s {
	tree_family_search_match_rule_t *search_match_rule;

	tree_family_search_recursion_rule_t *search_recursion_rule;

    tree_family_insert_rule_t *insert_rule;
};

/**
 * @brief This struct will contain the tree-family environment.
 */

struct tree_family_control_environment_s {
	struct tree_family_node_infomation_s node_infomation;

	struct tree_family_node_operator_s node_operator;
};

/**
 * @brief This struct is the binary tree structure module
 */

struct tree_family_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e container_type_id;

	/* @brief This variables will record the information of container type.								*/
	struct container_common_information_s info;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_ctrl;

	/* @brief This variables will point to the address of the deque data memory block.					*/
	void *root;

	/* @brief This variables will record the element handler of the container.							*/
	struct container_element_handler_s element_handler;

	/* @brief This variables will record the exception handler of the container.						*/
	struct container_common_exception_s exception;

	/* @brief This variables will point to the address of the list-like shared-pack analysis.			*/
	void (*switch_control)(void);
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This function will get control of the tree-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control(struct tree_family_control_environment_s environment);

/**
 * @brief This function will get control of the tree-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_in_sandbox(struct tree_family_s *tree,
												struct tree_family_control_environment_s environment,
												void (*func_addr)(void *, ...),
												size_t count_param,
												...);

/**
 * @brief This function will initialize the tree struct
 *
 * @param tree the pointer to the tree struct pointer
 * @param element_size the element memory size of the tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_init(struct tree_family_s **tree,
											void (*switch_control)(void),
											enum tree_family_member_type_e member_type,
											enum allocator_type_e allocator_type,
											CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
											void (*assign)(void *dst, void *src), void (*free)(void *dst));

/**
 * @brief This function will destroy the tree struct and free the space
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_configuration_destroy(struct tree_family_s **tree);

/**
 * @brief This function will configure the tree element handler
 *
 * @param tree the pointer to the tree struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_element_handler(struct tree_family_s *tree,
													   void (*assign)(void *dst, void *src), void(*free)(void *dst));

/**
 * @brief This function will configure the tree exception callback
 *
 * @param tree the pointer to the tree struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_exception(struct tree_family_s *tree,
												 void (*empty)(void), void (*full)(void));

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *tree_family_control_element_access_at(struct tree_family_s *tree,
											void *data);

/**
 * @brief This function will checks if the container has no elements
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

extern inline bool tree_family_control_capacity_empty(struct tree_family_s *tree);

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return the maximum number of elements
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE tree_family_control_capacity_max_size(struct tree_family_s *tree);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return the number of elements in the container
 */

extern inline CONTAINER_GLOBAL_CFG_SIZE_TYPE tree_family_control_capacity_size(struct tree_family_s *tree);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void tree_family_control_insert(struct tree_family_s *tree, void *data);

/**
 * @brief This function will erases all elements from the container
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_modifiers_clear(struct tree_family_s *tree);

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void tree_family_control_modifiers_insert_after(struct tree_family_s *tree,
												CONTAINER_GLOBAL_CFG_SIZE_TYPE position,
												CONTAINER_GLOBAL_CFG_SIZE_TYPE amount,
												void **source);

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void tree_family_control_modifiers_emplace_after(struct tree_family_s *stack,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void tree_family_control_modifiers_erase_after(struct tree_family_s *tree,
											   CONTAINER_GLOBAL_CFG_SIZE_TYPE position);

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param tree the pointer to the tree struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void tree_family_control_modifiers_push_front(struct tree_family_s *tree,
											  void *source);

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param tree the pointer to the tree struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void tree_family_control_modifiers_emplace_front(struct tree_family_s *stack,
												 void *destination);

/**
 * @brief This function will removes the first element of the container
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_modifiers_pop_front(struct tree_family_s *tree);

/**
 * @brief This function will increase the capacity of the tree to a size
			that's greater or equal to new_cap
 *
 * @param tree the pointer to the tree struct pointer
 * @param size the size of the tree struct
 *
 * @return NONE
 */

void tree_family_control_modifiers_resize(struct tree_family_s **tree,
										  CONTAINER_GLOBAL_CFG_SIZE_TYPE size);

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param tree the pointer to the tree struct pointer
 * @param other the pointer to the other tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_modifiers_swap(struct tree_family_s **tree,
										struct tree_family_s **other);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

tree_family_search_node_return_st
tree_family_control_search(struct tree_family_s *tree, void *data);

/**
 * @brief This function will finds an element with key equivalent to key.
 *
 * @param tree the pointer to the tree struct pointer
 * @param other the pointer to the other tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_lookup_find(struct tree_family_s *tree,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE key);

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination tree struct pointer
 * @param source the pointer to the source tree struct
 *
 * @return NONE
 */

void tree_family_control_modifiers_copy(struct tree_family_s **destination,
										struct tree_family_s *source);

/**
 * @brief This function will return the memory size of the specified tree type node.
 *
 * @param type the specified tree type
 *
 * @return the memory size of the specified node
 */

size_t tree_family_control_get_node_len(enum tree_family_member_type_e type);

/**
 * @brief This function will initialize the tree node struct.
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void *tree_family_control_init_node(struct tree_family_s *tree);

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_destroy_node(struct tree_family_s *tree,
									  void *node);

/**
 * @brief This function will set the key node into the node.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_data(struct tree_family_s *tree);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_get_data(struct tree_family_chain_node_s *node,
										size_t location);

/**
 * @brief This function will set the key node into the node.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_set_data(struct tree_family_s *tree,
									   void *node,
									   void *data);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_leaf(struct tree_family_s *tree,
										  struct tree_family_chain_node_s *node);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

size_t tree_family_node_control_get_node_type(struct tree_family_s *tree,
											  struct tree_family_chain_node_s *node);

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_preorder_traversal(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node);

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_inorder_traversal(struct tree_family_s *tree,
										   struct tree_family_chain_node_s *node);

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_posorder_traversal(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__TREE_FAMILY_H