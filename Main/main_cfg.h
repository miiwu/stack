#ifndef __MAIN_CFG_H
#define __MAIN_CFG_H

#include "container.h"

#define MAIN_STACK_EN				0u

#define MAIN_QUEUE_EN				0u

#define MAIN_VECTOR_EN				0u

#define MAIN_FORWARD_LIST_EN		1u

#define MAIN_LIST_EN				0u

#if	(MAIN_QUEUE_EN)

void main_queue(void);

#endif

#if	(MAIN_VECTOR_EN)

void main_vector(void);

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


#endif // __MAIN_CFG_H
