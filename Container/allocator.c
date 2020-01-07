/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "allocator.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

/**
 * @brief This struct is the allocator structure module
 */

struct allocator_t {
	struct {
		/* @brief This variables will record the capacity of allocator allocated.						*/
        ALLOCATOR_SIZE_TYPEDEF capacity;
	}info;

    /* @brief This variables will point to the address of allocator memory pool.					    */
    void *memory_pool;

    struct {
        /* @brief This variables will point to the exception handler of lack of memory.			        */
        void (*lack_of_memory)(void);
    }exception;
};

struct memory_control_t {
	/* @brief This variables will record which memory block is available by check bit.					*/
    int available[ALLOCATOR_CFG_MEMORY_POOL_SIZE / sizeof(int) * 8];

	/* @brief This variables will point to the address of memory pool.					                */
	void *memory_pool_ptr;

	/* @brief This variables will point to the next allocate entry point address.					    */
	void *entry_point_ptr;

	/* @brief This variables will record the size of allocator memory pool.						        */
	ALLOCATOR_SIZE_TYPEDEF memory_pool_size;
};

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This struct will control all the allocator functions conveniently.
 */

struct allocator_control_t allocator_ctrl = {
    allocator_control_configration_init,
    
    allocator_control_configration_destroy,
    
    allocator_control_configration_expection,
    
    allocator_control_allocate,

    allocator_control_deallocate,
};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
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
										 void (*lack_of_memory)(void))
{
	assert(allocator);

	struct allocator_t
		*allocator_alloced = (struct allocator_t *)calloc(1, sizeof(struct allocator_t));			/* Malloc #1 */

    if (NULL == allocator_alloced) {
        return;
    }

    allocator_alloced->info.capacity = 0u;			                                                    /* Assign the allocator struct */
    allocator_alloced->exception.lack_of_memory = lack_of_memory;

    (*allocator) = allocator_alloced;
}

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 *
 * @return NONE
 */

void allocator_control_configration_destroy(ALLOCATOR_TYPEDEF_PPTR allocator)
{
	assert(allocator);

    if (0 < (*allocator)->info.capacity) {
        printf("destroy.allocator capacity : %d \r\n", (*allocator)->info.capacity);
    }

    free((*allocator));																	            /* Free #1 */
}

/**
 * @brief This function will destroy and clean the allocator struct.
 *
 * @param allocator the allocator
 * @param lack_of_memory the pointer to the exception handler of lack of heap memory
 *
 * @return NONE
 */

void allocator_control_configration_expection(ALLOCATOR_TYPEDEF_PTR allocator,
											  void (*lack_of_memory)(void))
{
	assert(allocator);

	// TODO Statement ...																	/* TODO	*/
}

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
								 ALLOCATOR_SIZE_TYPEDEF count, ALLOCATOR_SIZE_TYPEDEF size)
{
	assert(allocator);

	void
		**block_alloced = calloc(count, size);			                        /* Malloc #2 : allocates the storage to block_alloced */

    if (NULL == block_alloced) {
        allocator->exception.lack_of_memory();

        return NULL;
    }

    allocator->info.capacity += count;

    return (void*)block_alloced;
}

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
								  void *block, ALLOCATOR_SIZE_TYPEDEF size)
{
	assert(allocator);

    allocator->info.capacity--;

    free(block);																	            /* Free #1 */
}

/**
 * @brief This function will allocates n * sizeof(Type) bytes of uninitialized storage.
 *
 * @param allocator the allocator
 * @param count the amount of blocks
 * @param size the size of block
 *
 * @return NONE
 */

void allocator_control_memory_alloc(ALLOCATOR_TYPEDEF_PTR allocator,
                                  void *block, ALLOCATOR_SIZE_TYPEDEF size)
{
    assert(allocator);

    allocator->info.capacity--;

    free(block);																	            /* Free #1 */
}