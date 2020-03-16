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

/**
 *                                          CONFIGRATION
 */

/* Configure    the type of sort algorithm.                                                             */
#define TREE_FAMILY_CFG_SORT_ALGORITHM_TYPE								BUBBLE_SORT

/* Configure    the type of sort algorithm.                                                             */
#define TREE_FAMILY_CFG_NODE_COUNT_MAX								    100

/* Configure    the type of sort algorithm.                                                             */
#define TREE_FAMILY_CFG_DEBUG_EN								        1u

/**
 *                                          DEBUG OPERATOR
 */

#define TREE_FAMILY_DEBUG_OPERATOR_GET_DATA_FROM_NODE(node,id)			                                \
    (*((void**)(((struct tree_family_chain_node_s *)(node))->data) + (id)))

#define TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_DATA(data)				                                \
    ((NULL != data)?((char)*((void**)(data) + (0))):(0u))

#define TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_NODE(node,id)			                                \
    TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_DATA(TREE_FAMILY_DEBUG_OPERATOR_GET_DATA_FROM_NODE(node,id))

#define TREE_FAMILY_DEBUG_OPERATOR_GET_LINK_FROM_NODE(node)				                                \
    ((void**)(((struct tree_family_chain_node_s *)(node))->link))

#define TREE_FAMILY_DEBUG_OPERATOR_GET_FAMILY_MEMBER_FROM_LINK(link,id)	                                \
    ((NULL != link)?((*((void**)(link) + (id)))):(0u))

#define TREE_FAMILY_DEBUG_OPERATOR_GET_FAMILY_MEMBER_FROM_NODE(node,id)	                                \
    TREE_FAMILY_DEBUG_OPERATOR_GET_FAMILY_MEMBER_FROM_LINK(TREE_FAMILY_DEBUG_OPERATOR_GET_LINK_FROM_NODE(node),id)

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This type is the array family typedef
 */

typedef struct container_family_s
*tree_family_stp,
**tree_family_stpp;

/**
 * @brief This struct is the binary tree_family structure module
 */

enum tree_family_member_type_e {
	TREE_FAMILY_BINARY_TREE = 0x02,

	TREE_FAMILY_AVL_TREE = 0x12,

	TREE_FAMILY_RED_BLACK_TREE = 0x22,

	TREE_FAMILY_B_TREE = 0x03,

	TREE_FAMILY_4D_B_TREE = 0x04,

	TREE_FAMILY_5D_B_TREE = 0x05,

	TREE_FAMILY_6D_B_TREE = 0x06,

	TREE_FAMILY_7D_B_TREE = 0x07,
};

/**
 * @brief This struct is the binary tree_family structure module
 */

enum tree_family_node_type_e {
	TREE_FAMILY_2D_NODE_TYPE = 2,

	TREE_FAMILY_3D_NODE_TYPE,

	TREE_FAMILY_4D_NODE_TYPE,

	TREE_FAMILY_5D_NODE_TYPE,

	TREE_FAMILY_6D_NODE_TYPE,

	TREE_FAMILY_7D_NODE_TYPE,
};

/**
 * @brief This struct is the binary tree_family structure module
 */

enum tree_family_search_code_type_e {
	SEARCH_CODE_NO_SUCH_ELEMENT = 0xff,
};

/**
 * @brief This struct is the binary tree_family structure module
 */

enum tree_family_link_operator_code_type_e {
	LINK_OPERATOR_CODE_PARENT = 0x00,

	LINK_OPERATOR_CODE_CHILD_FAR_LEFT = 0x01,

	LINK_OPERATOR_CODE_CHILD_FAR_RIGHT = 0xff,
};

/**
 * @brief This struct is the binary tree_family structure module
 */

enum tree_family_data_operator_code_type_e {
	DATA_OPERATOR_CODE_DATA_FAR_LEFT = 0x00,

	DATA_OPERATOR_CODE_DATA_FAR_RIGHT = 0xff,
};

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

struct tree_family_chain_node_s {
	void *data;

	void *link;
};

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

struct tree_family_chain_node_data_content_s {
	int key;                                                                                /* TODO:Make the key is limited by the mem_size_key,may save some memory */

	char content[0];
};

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

typedef struct tree_family_search_node_return_s {
	container_size_t location;

	container_size_t estimate;

	void *content;

	struct tree_family_chain_node_s *node;

	struct tree_family_chain_node_s *node_prev;
}tree_family_search_node_return_st;

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

typedef struct tree_family_get_precursor_and_successor_return_s {
	container_size_t location;

	void *data;

	struct tree_family_chain_node_s *node;
}tree_family_get_precursor_and_successor_return_st;

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

typedef container_size_t tree_family_search_match_rule_t(tree_family_stp tree_family,
														 struct tree_family_chain_node_s *node,
														 void *data);

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

typedef container_size_t tree_family_search_recursion_rule_t(tree_family_stp tree_family,
															 struct tree_family_chain_node_s **node,
															 void *data);

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

typedef void *tree_family_insert_and_delete_rule_t(tree_family_stp tree_family,
												   struct tree_family_search_node_return_s search_return,
												   void *data);

/**
 * @brief This struct is the binary tree_family link node structure module.
 */

typedef void tree_family_traversal_operator_t(tree_family_stp tree_family,
											  struct tree_family_chain_node_s *node,
											  container_size_t data_element_count);

/**
 * @brief This struct will control the unique operator.
 */

struct tree_family_node_infomation_s {
	enum tree_family_member_type_e member_type;

	//container_size_t data_mem_len;                /* Manage by tree_family_s */

	container_size_t link_mem_len;

	container_size_t id_data_far_right;

	container_size_t id_link_far_right;

	container_size_t data_element_count;

	container_size_t link_element_count;
};

/**
 * @brief This struct will control the unique operator.
 */

struct tree_family_node_operator_s {
	tree_family_search_match_rule_t *search_match_rule;

	tree_family_search_recursion_rule_t *search_recursion_rule;

	tree_family_insert_and_delete_rule_t *insert_rule;

	tree_family_insert_and_delete_rule_t *delete_rule;
};

/**
 * @brief This struct will contain the extra information of tree_family-family.
 */

struct tree_family_extra_infomation_s {
	/* @brief This variables will record the size that each element will take up.						*/
	container_size_t mem_size_key;

	/* @brief This variables will record the degree of the tree_family											*/
	container_size_t degree;

	/* @brief This variables will record the degree of the tree_family											*/
	container_size_t minimum_amt_key;
};

/**
 * @brief This struct will contain the tree_family-family environment.
 */

struct tree_family_control_environment_s {
	enum tree_family_member_type_e member_type;

	struct tree_family_node_operator_s node_operator;

    struct tree_family_extra_infomation_s extra_info;
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
 * @brief This function will get control of the tree_family-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control(struct tree_family_control_environment_s environment);

/**
 * @brief This function will get control of the tree_family-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_in_sandbox(tree_family_stp tree_family,
												struct tree_family_control_environment_s environment,
												void (*func_addr)(void *, ...),
												size_t count_param,
												...);

/**
 * @brief This function will initialize the tree_family struct
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param element_size the element memory size of the tree_family struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

errno_t tree_family_control_configuration_init(tree_family_stpp tree_family,
											container_family_switch_control switch_control,
											container_size_t degree,
											container_size_t key_size,
											enum tree_family_member_type_e member_type,
											enum allocator_type_e allocator_type,
											container_size_t element_size,
											generic_type_element_assign_t assign,
											generic_type_element_free_t free);

/**
 * @brief This function will destroy the tree_family struct and free the space
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return NONE
 */

errno_t tree_family_control_configuration_destroy(tree_family_stpp tree_family);

/**
 * @brief This function will configure the tree_family element handler
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_element_handler(tree_family_stp tree_family,
													   generic_type_element_assign_t assign,
													   generic_type_element_free_t free);

/**
 * @brief This function will configure the tree_family exception callback
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_exception(tree_family_stp tree_family,
												 void (*empty)(void), void (*full)(void));

/**
 * @brief This function will returns a reference to the specified element in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void *tree_family_control_element_access_at(tree_family_stp tree_family,
											void *data);

/**
 * @brief This function will checks if the container has no elements
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return
	- true,the container has no elements
	- false,the container has elements
 */

extern inline bool tree_family_control_capacity_empty(tree_family_stp tree_family);

/**
 * @brief This function will returns the maximum number of elements the container
			is able to hold due to system or library implementation limitations
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return the maximum number of elements
 */

extern inline container_size_t tree_family_control_capacity_max_size(tree_family_stp tree_family);

/**
 * @brief This function will returns the number of elements in the container
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return the number of elements in the container
 */

extern inline container_size_t tree_family_control_capacity_size(tree_family_stp tree_family);

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void tree_family_control_insert(tree_family_stp tree_family, void *data);

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void tree_family_control_delete(tree_family_stp tree_family,
								void *data);

/**
 * @brief This function will erases all elements from the container
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return NONE
 */

void tree_family_control_modifiers_clear(tree_family_stp tree_family);

/**
 * @brief This function will inserts elements after the specified position in the container
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of the source
 * @param source pointer to the source
 *
 * @return NONE
 */

void tree_family_control_modifiers_insert_after(tree_family_stp tree_family,
												container_size_t position,
												container_size_t amount,
												void **source);

/**
 * @brief This function will push a new element on top of the stack, and the element is constructed in-place
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void tree_family_control_modifiers_emplace_after(tree_family_stp stack,
												 container_size_t position);

/**
 * @brief This function will erases the specified elements from the container
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of element,it would be equal or greater than zero
 *
 * @return NONE
 */

void tree_family_control_modifiers_erase_after(tree_family_stp tree_family,
											   container_size_t position);

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void tree_family_control_modifiers_push_front(tree_family_stp tree_family,
											  void *source);

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void tree_family_control_modifiers_emplace_front(tree_family_stp stack,
												 void *destination);

/**
 * @brief This function will removes the first element of the container
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return NONE
 */

void tree_family_control_modifiers_pop_front(tree_family_stp tree_family);

/**
 * @brief This function will increase the capacity of the tree_family to a size
			that's greater or equal to new_cap
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param size the size of the tree_family struct
 *
 * @return NONE
 */

void tree_family_control_modifiers_resize(tree_family_stpp tree_family,
										  container_size_t size);

/**
 * @brief This function will exchanges the contents of the container with those of other
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param other the pointer to the other tree_family struct pointer
 *
 * @return NONE
 */

void tree_family_control_modifiers_swap(tree_family_stpp tree_family,
										tree_family_stpp other);

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

tree_family_search_node_return_st
tree_family_control_search(tree_family_stp tree_family, void *data);

/**
 * @brief This function will finds an element with key equivalent to key.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param other the pointer to the other tree_family struct pointer
 *
 * @return NONE
 */

void tree_family_control_lookup_find(tree_family_stp tree_family,
									 container_size_t key);

/**
 * @brief This function will copy the contents of the container to those of other
 *
 * @param destination the pointer to the destination tree_family struct pointer
 * @param source the pointer to the source tree_family struct
 *
 * @return NONE
 */

void tree_family_control_modifiers_copy(tree_family_stpp destination,
										tree_family_stp source);

/**
 * @brief This function will initialize the tree_family node struct.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 *
 * @return NONE
 */

void *tree_family_control_init_node(tree_family_stp tree_family);

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_destroy_node(tree_family_stp tree_family,
									  void **node);

/**
 * @brief This function will set the key node into the node.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_data(tree_family_stp tree_family);

/**
 * @brief This function will destroy the data.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_data(tree_family_stp tree_family,
										   void **data);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_get_data(tree_family_stp tree_family,
										struct tree_family_chain_node_s *node,
										container_size_t id);

/**
 * @brief This function will set the data into the node.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_set_data(tree_family_stp tree_family,
									   struct tree_family_chain_node_s *node,
									   void *data,
									   container_size_t id);

/**
 * @brief This function will insert the data into the node,which means have to sort.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_insert_data(tree_family_stp tree_family,
										  struct tree_family_chain_node_s *node,
										  void *data);

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_del_data(tree_family_stp tree_family,
										struct tree_family_chain_node_s *node,
										container_size_t id);

/**
 * @brief This function will initialize the tree_family node's link struct.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_link(tree_family_stp tree_family);

/**
 * @brief This function will destroy the link.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_link(tree_family_stp tree_family,
										   void **link);

/**
 * @brief This function will return the family member of the node.
 *
 * @param tree_family the pointer to the tree_family
 * @param node the pointer to the node
 * @param id the id member that the parent is 0,children are greater than 0
 *
 * @return void
 */

void *tree_family_node_control_get_family_member(tree_family_stp tree_family,
												 struct tree_family_chain_node_s *node,
												 container_size_t id);

/**
 * @brief This function will get the node's available brother node.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the node's available brother node
 */

void *tree_family_node_control_get_neighbour(tree_family_stp tree_family,
											 struct tree_family_chain_node_s *node,
											 struct tree_family_chain_node_s *parent,
											 container_size_t relation_with_parent);

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_set_child(tree_family_stp tree_family,
										 struct tree_family_chain_node_s *node,
										 struct tree_family_chain_node_s *family_member,
										 container_size_t id);

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_del_family_member(tree_family_stp tree_family,
												 struct tree_family_chain_node_s *node,
												 container_size_t id);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

container_size_t tree_family_node_control_get_relation_with_parent(tree_family_stp tree_family,
																   struct tree_family_chain_node_s *node,
																   struct tree_family_chain_node_s *parent);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_leaf(tree_family_stp tree_family,
										  struct tree_family_chain_node_s *node);

/**
 * @brief This function will return if one of the parent's left child is node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_left_child(tree_family_stp tree_family,
												struct tree_family_chain_node_s *node,
												struct tree_family_chain_node_s *parent);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_right_child(tree_family_stp tree_family,
												 struct tree_family_chain_node_s *node,
												 struct tree_family_chain_node_s *parent);

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

container_size_t tree_family_node_control_get_node_type(tree_family_stp tree_family,
														struct tree_family_chain_node_s *node);

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_preorder_traversal(tree_family_stp tree_family,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator);

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_inorder_traversal(tree_family_stp tree_family,
										   struct tree_family_chain_node_s *node,
										   tree_family_traversal_operator_t *operator);

/**
 * @brief This function will destroy tree_family node struct and free the space.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to the tree_family node struct pointer
 *
 * @return NONE
 */

void tree_family_control_posorder_traversal(tree_family_stp tree_family,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator);

/**
 * @brief This function will get the node's precursor node.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the precursor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_precursor(tree_family_stp tree_family,
								  struct tree_family_chain_node_s *node,
								  container_size_t id_data);

/**
 * @brief This function will get the node's successor node.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_successor(tree_family_stp tree_family,
								  struct tree_family_chain_node_s *node,
								  container_size_t id_data);

/**
 * @brief This function will get the extra information block of tree_family family control block.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

struct tree_family_extra_infomation_s
tree_family_control_get_extra_infomation(tree_family_stp tree_family);

/**
 * @brief This function will get the root of the tree_family.
 *
 * @param tree_family the pointer to the tree_family struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

extern inline void
*tree_family_control_get_root(tree_family_stp tree_family);

/**
* @brief This function will print all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_traversal_printer(tree_family_stp tree_family,
										   void *node,
										   container_size_t data_element_count);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configuration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configuration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__TREE_FAMILY_H