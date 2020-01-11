/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

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

/*
*********************************************************************************************************
*									     CONROL CONFIG DEFINES
*********************************************************************************************************
*/

/* Configure the default size of the allocator memory pool size.                                        */
#define ALLOCATOR_CFG_MEMORY_POOL_SIZE			                                102400u

/* Configure the type of the allocator size.                                                            */
#define ALLOCATOR_CFG_SIZE_TYPE			                                        size_t

/* Configure if enable integrated structure.                                                            */
#define ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN			                    1u

/* Configure if enable allocator debug control structure.                                               */
#define ALLOCATOR_CFG_DEBUG_MODE_EN			                                    1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* TODO .                                                                                               */
typedef ALLOCATOR_CFG_SIZE_TYPE ALLOCATOR_SIZE_TYPEDEF;

/* TODO .                                                                                               */
typedef struct allocator_t *ALLOCATOR_TYPEDEF_PTR;

/* TODO .                                                                                               */
typedef struct allocator_t **ALLOCATOR_TYPEDEF_PPTR;

#if (ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

struct allocator_control_t {
	struct {
		/* @brief This function will initialize the allocator struct.									*/
		void (*init)(ALLOCATOR_TYPEDEF_PPTR allocator,
					 void (*lack_of_memory)(void));

		/* @brief This function will destroy the allocator struct.										*/
		void (*destroy)(ALLOCATOR_TYPEDEF_PPTR allocator);

		/* @brief This function will configure the exceptions of allocator struct.					    */
		void (*exception)(ALLOCATOR_TYPEDEF_PTR allocator,
						  void (*lack_of_memory)(void));
	}configration;

	/* @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage by calling
			  malloc(n * sizeof(Type)) or calloc(n,sizeof(Type)).										*/
	void *(*allocate)(ALLOCATOR_TYPEDEF_PTR allocator,
					  ALLOCATOR_SIZE_TYPEDEF count, ALLOCATOR_SIZE_TYPEDEF size);

	/* @brief This function will deallocates the storage referenced by the pointer block,
			  which must be a pointer obtained by an earlier call to allocate().						*/
	void (*deallocate)(ALLOCATOR_TYPEDEF_PTR allocator,
					   void *block, ALLOCATOR_SIZE_TYPEDEF size);
};

#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

struct allocator_debug_control_t {
	/* @brief This function will detect memory free status of the allocator struct.					    */
	ALLOCATOR_SIZE_TYPEDEF(*detect_memory_free_status)(ALLOCATOR_TYPEDEF_PTR allocator);
};

#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

#endif // (ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*								        CONROL FUNCTION PROTOTYPES
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

void allocator_control_configration_init(ALLOCATOR_TYPEDEF_PPTR allocator,
										 void (*lack_of_memory)(void));

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return NONE
 */

void allocator_control_configration_destroy(ALLOCATOR_TYPEDEF_PPTR allocator);

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 * @param lack_of_memory the pointer to the exception handler of lack of heap memory
 *
 * @return NONE
 */

void allocator_control_configration_expection(ALLOCATOR_TYPEDEF_PTR allocator,
											  void (*lack_of_memory)(void));

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

void *allocator_control_allocate(ALLOCATOR_TYPEDEF_PTR allocator,
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

void allocator_control_deallocate(ALLOCATOR_TYPEDEF_PTR allocator,
								  void *block, ALLOCATOR_SIZE_TYPEDEF count);

#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

/**
 * @brief This function will detect memory free status of the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return the memory free status of the allocator struct
 */

ALLOCATOR_SIZE_TYPEDEF allocator_control_memory_detect_memory_free_status(ALLOCATOR_TYPEDEF_PTR allocator);

#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

#if (ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

extern struct allocator_control_t allocator_ctrl;

#if (ALLOCATOR_CFG_DEBUG_MODE_EN)

extern struct allocator_debug_control_t allocator_dbg_ctrl;

#endif // (ALLOCATOR_CFG_DEBUG_MODE_EN)

#endif // (ALLOCATOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // __ALLOCATOR_H
