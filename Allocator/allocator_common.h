/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ALLOCATOR_COMMON_H
#define __ALLOCATOR_COMMON_H

/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/

#include "allocator_def.h"

/*
*********************************************************************************************************
*									        CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure if enable integrated structure.                                                            */
#define ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN			                    1u

/* Configure if enable allocator debug control structure.                                               */
#define ALLOCATOR_CFG_DEBUG_MODE_EN			                                    0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* TODO .                                                                                               */
typedef ALLOCATOR_GLOBAL_CFG_SIZE_TYPE ALLOCATOR_SIZE_TYPEDEF;

/* TODO .                                                                                               */
typedef struct allocator_t *ALLOCATOR_COMMON_TYPEDEF_PTR, **ALLOCATOR_COMMON_TYPEDEF_PPTR;

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the allocator struct.
 *
 * @param allocator the allocator
 * @param lack_of_memory the pointer to the exception handler of lack of heap memory
 *
 * @return NONE
 */

void allocator_control_configration_init(ALLOCATOR_COMMON_TYPEDEF_PPTR allocator,
										 void (*lack_of_memory)(void *));

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return NONE
 */

void allocator_control_configration_destroy(ALLOCATOR_COMMON_TYPEDEF_PPTR allocator);

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 * @param lack_of_memory the pointer to the exception handler of lack of heap memory
 *
 * @return NONE
 */

void allocator_control_configration_exception(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
											  void (*lack_of_memory)(void *));

/**
 * @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
 *  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).
 *
 * @param allocator the allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return return the pointer point to the uninitialized storage which allocated
 */

void *allocator_control_allocate(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
								 ALLOCATOR_SIZE_TYPEDEF count, ALLOCATOR_SIZE_TYPEDEF size);

/**
 * @brief This function will deallocates the storage referenced by the pointer block,
 *  which must be a pointer obtained by an earlier call to allocate().
 *
 * @param allocator the allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return NONE
 */

void allocator_control_deallocate(ALLOCATOR_COMMON_TYPEDEF_PTR allocator,
								  void *block, ALLOCATOR_SIZE_TYPEDEF count);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__ALLOCATOR_COMMON_H
