#ifndef __MAIN_CFG_H
#define __MAIN_CFG_H

#include "debug_component.h"

#include "container.h"

#include "allocator.h"

#define MAIN_DEBUG_COMPONENT_EN		0u

#define MAIN_ALLOCATOR_EN			0u

#define MAIN_B_TREE_EN				1u

#define MAIN_BINARY_SEARCH_TREE_EN	1u

#define MAIN_RED_BLACK_TREE_EN		1u

#define MAIN_ARRAY_EN				0u

#define MAIN_VECTOR_EN				0u

#define MAIN_DEQUE_EN				0u

#define MAIN_FORWARD_LIST_EN		0u

#define MAIN_LIST_EN				0u

#define MAIN_STACK_EN				0u

#define MAIN_QUEUE_EN				0u

#define MAIN_PRIORITY_QUEUE_EN		0u

#if	(MAIN_DEBUG_COMPONENT_EN)

void main_debug_component(void);

#endif

#if	(MAIN_ALLOCATOR_EN)

void main_allocator(void);

#endif

#if	(MAIN_B_TREE_EN)

void main_b_tree(void);

#endif

#if	(MAIN_BINARY_SEARCH_TREE_EN)

void main_binary_search_tree(void);

#endif

#if	(MAIN_RED_BLACK_TREE_EN)

void main_red_black_tree(void);

#endif

#if	(MAIN_ARRAY_EN)

void main_array(void);

#endif

#if	(MAIN_VECTOR_EN)

void main_vector(void);

#endif

#if	(MAIN_DEQUE_EN)

void main_deque(void);

#endif

#if	(MAIN_FORWARD_LIST_EN)

void main_forward_list(void);

#endif

#if	(MAIN_LIST_EN)

void main_list(void);

#endif

#if	(MAIN_STACK_EN)

void main_stack(void);

#endif

#if	(MAIN_QUEUE_EN)

void main_queue(void);

#endif

#if	(MAIN_PRIORITY_QUEUE_EN)

void main_priority_queue(void);

#endif

#endif // !__MAIN_CFG_H
