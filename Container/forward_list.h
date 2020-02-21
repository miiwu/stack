/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __FORWARD_LIST_H
#define __FORWARD_LIST_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "list_family.h"

/*
*********************************************************************************************************
*									    FORWARD_LIST CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define FORWARD_LIST_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define FORWARD_LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/*
*********************************************************************************************************
*									        FORWARD_LIST DATA TYPES
*********************************************************************************************************
*/

/* Configure    forward_list ptr type.                                                                  */
typedef struct list_family_s
*FORWARD_LIST_TYPEDEF_PTR,
**FORWARD_LIST_TYPEDEF_PPTR;

/*
*********************************************************************************************************
*								    FORWARD_LIST CONROL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the forward_list struct
 *
 * @param forward_list the pointer to the forward list struct pointer
 * @param element_size the element memory size of the forward list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void forward_list_control_configuration_init(FORWARD_LIST_TYPEDEF_PPTR forward_list,
											 container_size_t element_size,
											 void (*assign)(void *dst, void *src), void (*free)(void *dst));

/*
*********************************************************************************************************
*                                   VECTOR EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (FORWARD_LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */

extern struct list_family_control_s forward_list_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__FORWARD_LIST_H