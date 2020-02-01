/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ARRAY_H
#define __ARRAY_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "array_family.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the default max size of array.                                                         */
#define ARRAY_CFG_DEFAULT_MAX_SIZE								100u

/* Configure    if enable integrated structure.                                                         */
#define ARRAY_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE		1024u

/* Configure    the type of allocator.                                                                  */
#define ARRAY_CFG_ALLOCATOR_TYPE                               ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define ARRAY_CFG_INTERGRATED_STRUCTURE_MODE_EN			        1u

/*
*********************************************************************************************************
*									            DATA TYPES
*********************************************************************************************************
*/

/* Configure    array ptr type.                                                                        */
typedef struct array_family_s
*ARRAY_TYPEDEF_PTR,
**ARRAY_TYPEDEF_PPTR;

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the array struct.
 *
 * @param array the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void array_control_configuration_init(ARRAY_TYPEDEF_PPTR array,
									  CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									  void (*assign)(void *dst, void *src), void (*free)(void *dst));

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (ARRAY_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the array functions conveniently.
 */

extern struct array_family_control_s array_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ARRAY_H