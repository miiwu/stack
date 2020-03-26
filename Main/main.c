#include "main_cfg.h"

void main(void)
{
	#if	(MAIN_DEBUG_COMPONENT_EN)

	main_debug_component();

	#endif

	#if	(MAIN_ALGORITHM_EN)

	main_algorithm();

	#endif

	#if	(MAIN_ALLOCATOR_EN)

	main_allocator();

	#endif

	#if	(MAIN_ITERATOR_EN)

	main_iterator();

	#endif

	#if	(MAIN_GENERIC_TYPE_EN)

	main_generic_type();

	#endif

	#if	(MAIN_B_TREE_EN)

	main_b_tree();

	#endif

	#if	(MAIN_BINARY_SEARCH_TREE_EN)

	main_binary_search_tree();

	#endif

	#if	(MAIN_RED_BLACK_TREE_EN)

	main_red_black_tree();

	#endif

	#if	(MAIN_ARRAY_EN)

	main_array();

	#endif

	#if	(MAIN_VECTOR_EN)

	main_vector();

	#endif

	#if	(MAIN_FORWARD_LIST_EN)

	main_forward_list();

	#endif

	#if	(MAIN_LIST_EN)

	main_list();

	#endif

	#if	(MAIN_STACK_EN)

	main_stack();

	#endif

	#if	(MAIN_QUEUE_EN)

	main_queue();

	#endif

	#if	(MAIN_PRIORITY_QUEUE_EN)

	main_priority_queue();

	#endif

	return;
}