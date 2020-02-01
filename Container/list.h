/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __LIST_H
#define __LIST_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "list_family.h"

/*
*********************************************************************************************************
*									    LIST CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define LIST_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/*
*********************************************************************************************************
*									        LIST DATA TYPES
*********************************************************************************************************
*/

/* Configure    list ptr type.                                                                          */
typedef struct list_family_s *LIST_TYPEDEF_PTR;

/* Configure    list pptr type.                                                                         */
typedef struct list_family_s **LIST_TYPEDEF_PPTR;

/*
*********************************************************************************************************
*								    LIST CONROL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the list struct
 *
 * @param list the pointer to the forward list struct pointer
 * @param element_size the element memory size of the forward list struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void list_control_configuration_init(LIST_TYPEDEF_PPTR list,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									 void (*assign)(void *dst, void *src), void (*free)(void *dst));

/*
*********************************************************************************************************
*                                   VECTOR EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (LIST_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the list functions conveniently.
 */

extern struct list_family_control_s list_ctrl;

#endif

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__LIST_H