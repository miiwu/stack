/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the AT definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_DEFINATION_H
#define __CONTAINER_DEFINATION_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdbool.h"
#include "assert.h"
#include "malloc.h"

#include "allocator.h"

/*
*********************************************************************************************************
*												DEFINES
*********************************************************************************************************
*/

/* Configure    container global size type.                                                                       */
#define CONTAINER_GLOBAL_CFG_SIZE_TYPE															size_t

/*
*********************************************************************************************************
*									         DATA TYPES
*********************************************************************************************************
*/

/* Configure the enum category of container.															*/
enum container_category {
	SEQUENCE_CONTAINERS = 0x10,

	ASSOCIATIVE_CONTAINERS = 0x20,

	UNORDERED_ASSOCIATIVE_CONTAINERS = 0x30,

	CONTAINERS_ADAPTORS = 0x40,

	SPAN = 0x50,
};

/* Configure the enum type of container.																*/
enum container_type {
	VECTOR = SEQUENCE_CONTAINERS,
	DEQUE,
	LIST,

	SET = ASSOCIATIVE_CONTAINERS,
	MAP,

	UNORDERED_SET = UNORDERED_ASSOCIATIVE_CONTAINERS,

	STACK = CONTAINERS_ADAPTORS,
	QUEUE,
};

/* Configure the enum function type of container.														*/
enum container_function_type {
	INITIALIZE,
	DESTROY,
	
	AT,

	EMPTY,
	SIZE,
	CAPACITY,

	PUSH_BACK,
	ERASE,
	COPY,
	SWAP
};

/*
*********************************************************************************************************
*								        FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the stack struct and attach to the specified container.
 *
 * @param stack container adapter struct
 * @param container the pointer to container
 *
 * @return NONE
 */

inline int *container_control_convert_type_to_func_addr_table(enum container_type type);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This array will contain all the vector functions address.
 */

extern int vector_function_address_tables[];

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the stack struct and attach to the specified container.
 *
 * @param stack container adapter struct
 * @param container the pointer to container
 *
 * @return NONE
 */

inline int *container_control_convert_type_to_func_addr_table(enum container_type type)
{
	int
		*func_addr_table = NULL;

	switch (type) {
		case VECTOR:
			func_addr_table = (int *)&vector_function_address_tables;
			break;
		case DEQUE:
			break;
		case LIST:
			break;
		case SET:
			break;
		case MAP:
			break;
		case UNORDERED_SET:
			break;
		case STACK:
			break;
		case QUEUE:
			break;
		default:
			break;
	}

	return func_addr_table;
}

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // __CONTAINER_DEFINATION_H