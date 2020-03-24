/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "sort.h"

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

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/

/**
 * @brief This type is the sort algorithm category enum.
 */

void *sort_control_algorithm_address_table[] = {
	sort_control_bubble_sort,
};

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will get the element of object.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the element pointer
 */

void *sort_control_common_get_element(struct sort_package_s sort_package,
									  size_t index);

/**
 * @brief This function will get the address of element.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the address of the element
 */

void *sort_control_common_get_address(struct sort_package_s sort_package,
									  size_t index);

/**
 * @brief This function will compare the elements.
 *
 * @param sort_package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

errno_t sort_control_common_compare(struct sort_package_s package,
									size_t left,
									size_t right);

/**
 * @brief This function will swap the elements.
 *
 * @param sort_package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

errno_t sort_control_common_swap(struct sort_package_s package,
								 size_t left,
								 size_t right);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will sort the object by the comp and the sort algorithm is distinguished by
 *		   the sort_algorithm_addr that will get by xxx_convert_type_to_func_addr_table().
 *
 * @param data the pointer to the data list will give
 *
 * @return void
 */

extern inline errno_t
sort_control(enum sort_algorithm_type type,
			 struct sort_package_s package)
{
	assert(0 <= package.left);
	assert(0 <= package.right);
	assert(package.left < package.right);
	assert(package.mem_len);
	assert(package.object_ptr);
	assert((package.object_operator.get_element_ptr || package.object_operator.get_address_ptr)
		   ? (package.object_operator.get_element_ptr && package.object_operator.get_address_ptr)
		   : (true));																		/* Assert if both the operators valid */

	sort_t sort = sort_control_algorithm_address_table[type];								/* Get the sort algorithm function address */

	return sort(package);
}

/**
 * @brief This function will get the element of object.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the element pointer
 */

static inline void
*sort_control_common_get_element(struct sort_package_s sort_package,
								 size_t index)
{
	assert(0 <= index);

	static void *value;

	if (NULL == sort_package.object_operator.get_element_ptr) {								/* If the object operator is valid */
		value = *(void **)((size_t)sort_package												/* Calculate the element */
						   .object_ptr + index * sort_package.mem_len);
	} else {
		value = sort_package.object_operator												/* Get the element */
			.get_element_ptr(sort_package.object_ptr, index);
	}

	return value;
}

/**
 * @brief This function will get the address of element.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the address of the element
 */

static inline void
*sort_control_common_get_address(struct sort_package_s sort_package,
								 size_t index)
{
	assert(0 <= index);

	static void *address;

	if (NULL == sort_package.object_operator.get_element_ptr) {								/* If the object operator is valid */
		address = (void *)((size_t)sort_package												/* Calculate the address */
						   .object_ptr + index * sort_package.mem_len);
	} else {
		address = sort_package.object_operator												/* Get the address */
			.get_address_ptr(sort_package.object_ptr, index);
	}

	return address;
}

/**
 * @brief This function will compare the elements.
 *
 * @param sort_package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

static inline errno_t
sort_control_common_compare(struct sort_package_s package,
							size_t left,
							size_t right)
{
	assert(0 <= left);
	assert(0 <= right);

	static void
		*value_lhs,
		*value_rhs;

	value_lhs = sort_control_common_get_element(package, left);
	value_rhs = sort_control_common_get_element(package, right);

	if (NULL == value_lhs &&
		NULL == value_rhs) {
		return 0xff;
	}

	#if (SORT_CFG_DEBUG_EN)

	printf("sort_algorithm.compare: lhs:\"%s\" rhs:\"%s\" \r\n"
		   , value_lhs, value_rhs);

	#endif // (SORT_CFG_DEBUG_EN)

	if (package.compare_ptr(value_lhs, value_rhs, package.mem_len_key)) {
		return 1;
	}

	return 0;
}

/**
 * @brief This function will swap the elements.
 *
 * @param sort_package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

static inline errno_t
sort_control_common_swap(struct sort_package_s package,
						 size_t left,
						 size_t right)
{
	assert(0 <= left);
	assert(0 <= right);

	static void
		*address_lhs,
		*address_rhs;

	address_lhs = sort_control_common_get_address(package, left);
	address_rhs = sort_control_common_get_address(package, right);

	if (NULL == address_lhs &&
		NULL == address_rhs) {
		return 1;
	}

	#if (SORT_CFG_DEBUG_EN)

	printf("sort_algorithm.swap: lhs:%p rhs:%p \r\n"
		   , address_lhs, address_rhs);

	#endif // (SORT_CFG_DEBUG_EN)

	if (package.swap_ptr(address_lhs, address_rhs, package.mem_len)) {						/* Swap the value */
		return 2;
	}

	return 0;
}

/**
 * @brief This function will sort the object by the bubble sort algorithm.
 *
 * @param sort_package the information package of the sort
 *
 * @return void
 */

errno_t sort_control_bubble_sort(struct sort_package_s package)
{
	assert(0 <= package.left);
	assert(0 <= package.right);
	assert(package.left < package.right);
	assert(package.mem_len);
	assert(package.object_ptr);
	assert((package.object_operator.get_element_ptr || package.object_operator.get_address_ptr)
		   ? (package.object_operator.get_element_ptr && package.object_operator.get_address_ptr)
		   : (true));																		/* Assert if both the operators valid */

	static char
		*value_lhs,
		*value_rhs;
	static void
		*address_lhs,
		*address_rhs;

	if (0u == package.mem_len_key) {
		package.mem_len_key = package.mem_len;												/* Default the memory length of the object's compare key */
	}

	if (NULL == package.compare_ptr) {														/* Default the compare function */
		package.compare_ptr = SORT_CFG_DEFAULT_COMPARE_ADDRESS;
	}

	if (NULL == package.swap_ptr) {															/* Default the swap function */
		package.swap_ptr = SORT_CFG_DEFAULT_SWAP_ADDRESS;
	}

	for (size_t cnt = package.left; cnt < package.right; cnt++) {
		for (size_t ct = package.left; ct < package.right - cnt; ct++) {
			errno_t error_compare
				= sort_control_common_compare(package, ct, ct + 1);							/* Compare the value */

			if (true == error_compare) {
				if (!sort_control_common_swap(package, ct, ct + 1)) {						/* Swap the value */
					return 2;
				}
			} else if (0xff == error_compare) {
				return  1;
			}
		}
	}

	return 0;
}