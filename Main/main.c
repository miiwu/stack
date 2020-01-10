#include "main_cfg.h"

void main(void)
{

#if	(MAIN_QUEUE_EN)

	main_queue();

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

	return;
}