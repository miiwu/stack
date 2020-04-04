/*
 ************************************************************************************************************************
 *                                  DEBUG COMPONENT OF CAPATURE STACK BACK TRACE FUNCTIONS
 *
 * File    : DEBUG_CAPATURE_STACK_BACK_TRACE.C
 * By      : Miao Mico
 * Version : V0.01.00
 *
 * FIRST ENLIGHTENMENT : https://gist.github.com/t-mat/7979300
 * SECONDARY REFERANCE : https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb204633(v=vs.85)?redirectedfrom=MSDN
 *
 ************************************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "debug_stack_back_trace.h"

#include "debug_assert.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/* Define			the max depth of the capture stack back trace.										*/
#define TRACE_MAX_DEPTH																					\
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH

/* Define			the get address of the pointer.														*/
#define GET_ADDRESS_VIA_PTR(pointer,mem_type,index)														\
	(void*)((size_t)(pointer) + index * mem_type)

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
 * @brief This type is the stack back trace frame typedef.
 */

typedef void
*single_back_trace_t,
*back_trace_t[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH],
*(*back_trace_tp)[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH];

/**
 * @brief This type is the stack back trace frame typedef.
 */

typedef WORD
back_trace_frame_t,
*back_trace_frame_tp;

/**
 * @brief This type is the stack back trace string structure typedef.
 */

typedef struct stack_back_trace_string_t
stack_back_trace_string_st[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH],
(*stack_back_trace_string_stp)[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH];

/**
 * @brief This type is the stack back trace line structure typedef.
 */

typedef IMAGEHLP_LINE64
*back_trace_line_tp;

/**
 * @brief This type is the stack back trace structure.
 */

struct stack_back_trace_t {
	/* @brief This variables will record the max types.					                */
	stack_back_trace_size_t max_type_count;

	/* @brief This variables will record how many types is recorded.					                */
	stack_back_trace_size_t type_count;

	/* @brief This variables will record the amount of back trace.					                    */
	stack_back_trace_size_t *back_trace_count_ptr;

	/* @brief This variables will record the back trace.					                            */
	back_trace_tp back_trace_ptr;

	/* @brief This variables will record the back trace frames.											*/
	back_trace_frame_tp back_trace_frames_ptr;

	/* @brief This variables will record the hash value of back trace.					                */
	stack_back_trace_hash_tp back_trace_hash_ptr;
};

/**
 * @brief This type is the stack back trace link structure.
 */

struct stack_back_trace_link_t {
	/* @brief This variables will record the trace value of the both stack.					            */
	struct stack_back_trace_t *mark_ptr;

	/* @brief This variables will record the hash value of the both stack.					            */
	struct stack_back_trace_t *link_ptr;
};

/**
 * @brief This type is the stack back trace string structure.
 */

struct stack_back_trace_string_t {
	/* @brief This variables will record the max types.													*/
	size_t name_len;

	/* @brief This variables will record how many types is recorded.					                */
	char *name_ptr;

	/* @brief This variables will record the trace value of the both stack.					            */
	size_t file_line;

	/* @brief This variables will record the trace value of the both stack.					            */
	size_t file_line_len;

	/* @brief This variables will record the hash value of the both stack.					            */
	char *file_name_ptr;
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

stack_back_trace_size_t
g_pre_single_trace_len = sizeof(single_back_trace_t),
g_pre_trace_len = sizeof(single_back_trace_t) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH,
g_pre_frame_len = sizeof(back_trace_frame_t);

stack_back_trace_stp global_link_stack_back_trace_tmp = NULL;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

bool debug_capture_stack_back_trace_empty_callback(stack_back_trace_stp stack_back_trace);

/**
 * @brief This function will convert the back trace struct to the symbol description.
 *
 * @param symbol the pointer to symbol description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t capture_stack_back_trace_convert_to_symbol(stack_back_trace_string_stp string,
												   back_trace_t trace,
												   back_trace_frame_t frames);

/**
 * @brief This function will convert the back trace struct to the line description.
 *
 * @param symbol the pointer to line description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t capture_stack_back_trace_convert_to_line(stack_back_trace_string_stp string,
												 back_trace_t trace,
												 back_trace_frame_t frames);

/*
 *********************************************************************************************************
 *                                            FUNCTIONS
 *********************************************************************************************************
 */

/**
 * @brief This function will initialize the capture stack back trace struct.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param count the amount of type stack situation
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_init(stack_back_trace_stpp stack_back_trace,
											stack_back_trace_size_t count)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(count, > , int, 0);

	if (NULL == ((*stack_back_trace)
				 = calloc(1, sizeof(struct stack_back_trace_t)))) {
		return 1;
	}

	if (NULL == ((*stack_back_trace)->back_trace_count_ptr
				 = calloc(count, sizeof(stack_back_trace_size_t)))) {
		return 2;
	}

	if (NULL == ((*stack_back_trace)->back_trace_ptr
				 = calloc(count, sizeof(single_back_trace_t) * TRACE_MAX_DEPTH))) {
		return 3;
	}

	if (NULL == ((*stack_back_trace)->back_trace_frames_ptr
				 = calloc(count, sizeof(back_trace_frame_t)))) {
		return 4;
	}

	if (NULL == ((*stack_back_trace)->back_trace_hash_ptr
				 = calloc(count, sizeof(stack_back_trace_hash_t)))) {
		return 5;
	}

	(*stack_back_trace)->max_type_count = count;
	(*stack_back_trace)->type_count = 0u;

	return 0;
}

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_destroy(stack_back_trace_stpp stack_back_trace)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("trace:%p frames:%p hash:%p capture stack back trace.destroy:block \r\n",
		   *(*stack_back_trace)->back_trace_ptr, (*stack_back_trace)->back_trace_frames_ptr, (*stack_back_trace)->back_trace_hash_ptr);

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	free(*(*stack_back_trace)->back_trace_ptr);
	free((*stack_back_trace)->back_trace_frames_ptr);
	free((*stack_back_trace)->back_trace_hash_ptr);
	free((*stack_back_trace)->back_trace_count_ptr);

	free((*stack_back_trace));

	(*stack_back_trace) = NULL;

	return 0;
}

/**
 * @brief This function will back trace the stack.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param frames_to_skip the amount of stack the capture back trace will skip
 * @param frames_to_capture the amount of stack the capture back trace will capture
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace(stack_back_trace_stp stack_back_trace,
									   stack_back_trace_size_t frames_to_skip)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);
	DEBUG_ASSERT_CONTROL_VARIABLE_PRINTF(frames_to_skip, >= , int, 0);

	void *back_trace_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	ULONG stack_back_trace_hash_tmp = 0;
	SYMBOL_INFO back_trace_symbol_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	IMAGEHLP_LINE64 back_trace_line_tpmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };

	back_trace_frame_t back_trace_frames_tmp
		= CaptureStackBackTrace(frames_to_skip + 1,
								DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH,
								back_trace_tmp,
								&stack_back_trace_hash_tmp);								/* Capture the stack */

	back_trace_frames_tmp -= DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_MAIN_DEPTH;					/* Skip the frames to the main depth */

	if (stack_back_trace->max_type_count <= stack_back_trace->type_count &&
		10 > (stack_back_trace->type_count / stack_back_trace->max_type_count) &&			/* Exclude it have been reduced to a negative number */
		false == debug_capture_stack_back_trace_empty_callback(stack_back_trace)) {
		return 1;
	}

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		stack_back_trace_hash_t
			hash = *(stack_back_trace->back_trace_hash_ptr + cnt);

		if (hash == stack_back_trace_hash_tmp) {
			stack_back_trace->back_trace_count_ptr[cnt] += 1;

			return 2;
		}
	}

	for (stack_back_trace_size_t index = 0; index < DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH; index++) {
		*(*(stack_back_trace->back_trace_ptr + stack_back_trace->type_count) + index) = back_trace_tmp[index];
	}

	memcpy((void *)(stack_back_trace->back_trace_frames_ptr + stack_back_trace->type_count),
		   (void *)&back_trace_frames_tmp, sizeof(back_trace_frame_t));

	memcpy((void *)(stack_back_trace->back_trace_hash_ptr + stack_back_trace->type_count),
		   (void *)&stack_back_trace_hash_tmp, sizeof(stack_back_trace_hash_t));

	stack_back_trace->back_trace_count_ptr[stack_back_trace->type_count] = 1;

	stack_back_trace->type_count++;

	return 0;
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

bool debug_capture_stack_back_trace_empty_callback(stack_back_trace_stp stack_back_trace)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);

	stack_back_trace->type_count -= 1;

	printf("stack back trace buffer is empty,it will cover the last one. \r\n");

	return true;
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_reduce_count(stack_back_trace_stp stack_back_trace,
													stack_back_trace_hash_t hash)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);

	if (0u == hash) {
		#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		printf("capture stack back trace.reduce count:NULL_HASH\r\n");

		#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		return 1;
	}

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		if (hash == *(stack_back_trace->back_trace_hash_ptr + cnt)) {
			if (0u < *(stack_back_trace->back_trace_count_ptr + cnt)) {
				*(stack_back_trace->back_trace_count_ptr + cnt) -= 1;
			}

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("capture stack back trace.reduce count:No.%d reduce to %d \r\n", cnt, *(stack_back_trace->back_trace_count_ptr + cnt));

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			return 2;
		}
	}

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace.reduce count:NULL_TRACE_HASH_MATCH\r\n");

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	return 0;
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_convert_to_string(stack_back_trace_stp stack_back_trace)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);

	stack_back_trace_string_st back_trace_string_tmp = { 0 };
	back_trace_frame_t frame_tmp = 0;
	back_trace_tp trace_tmp = 0;

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		if (0u < *(stack_back_trace->back_trace_count_ptr + cnt)) {
			trace_tmp = (stack_back_trace->back_trace_ptr + cnt);
			frame_tmp = *(stack_back_trace->back_trace_frames_ptr + cnt);

			capture_stack_back_trace_convert_to_symbol(&back_trace_string_tmp,
													   *trace_tmp,
													   frame_tmp);

			capture_stack_back_trace_convert_to_line(&back_trace_string_tmp,
													 *trace_tmp,
													 frame_tmp);

			for (size_t index = 0; index < frame_tmp; index++) {
				printf("No.%d it have %d ,it's %d/%d level stack is \"%s\" (%p) function.\r\n",
					   cnt, *(stack_back_trace->back_trace_count_ptr + cnt), index + 1, frame_tmp, back_trace_string_tmp[index].name_ptr, *(*trace_tmp + index));

				/*printf("No.%d it have %d it's %d/%d level stack is \"%s\" (%p) function in \"%s\" file at %d line.\r\n",
					   cnt, *(stack_back_trace->back_trace_count_ptr + cnt), index + 1, frame_tmp, back_trace_string_tmp[index].name_ptr, *(*trace_tmp + index),
					   back_trace_string_tmp[index].file_name_ptr, back_trace_string_tmp[index].file_line);*/
			}

			printf("\r\n");
		}
	}

	return 0;
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

stack_back_trace_hash_t debug_capture_stack_back_trace_get_hash(stack_back_trace_stp stack_back_trace,
																stack_back_trace_size_t index)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace.get index : hash:%d  \r\n", *(stack_back_trace->back_trace_hash_ptr + index));

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	return *(stack_back_trace->back_trace_hash_ptr + index);
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

single_back_trace_t *debug_capture_stack_back_trace_get_trace(stack_back_trace_stp stack_back_trace,
															  stack_back_trace_size_t index,
															  stack_back_trace_size_t sub_index)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(stack_back_trace);

	return *(*(stack_back_trace->back_trace_ptr + index) + sub_index);
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_copy(stack_back_trace_stp destination,
											stack_back_trace_stp source,
											stack_back_trace_size_t dst_index,
											stack_back_trace_size_t src_index)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(destination);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(source);

	for (size_t sub_index = 0; sub_index < *(source->back_trace_frames_ptr + src_index); sub_index++) {
		*(*(destination->back_trace_ptr + dst_index) + sub_index) = *(*(source->back_trace_ptr + src_index) + sub_index);
	}

	*(destination->back_trace_frames_ptr + dst_index) = *(source->back_trace_frames_ptr + src_index);
	*(destination->back_trace_hash_ptr + dst_index) = *(source->back_trace_hash_ptr + src_index);

	return 0;
}

/**
 * @brief This function will initialize a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_link_init(stack_back_trace_link_stpp link,
												 stack_back_trace_size_t count)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(link);

	if (NULL == ((*link)
				 = calloc(1, sizeof(struct stack_back_trace_link_t)))) {
		return 1;
	}

	debug_capture_stack_back_trace_init(&global_link_stack_back_trace_tmp, 1);

	debug_capture_stack_back_trace_init(&(*link)->mark_ptr, count);
	debug_capture_stack_back_trace_init(&(*link)->link_ptr, count);

	return 0;
}

/**
 * @brief This function will destroy a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_link_destroy(stack_back_trace_link_stp *link)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(link);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(*link);

	debug_capture_stack_back_trace_destroy(&(*link)->mark_ptr);
	debug_capture_stack_back_trace_destroy(&(*link)->link_ptr);

	free(*link);

	return 0;
}

/**
 * @brief This function will make a sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

errno_t debug_capture_stack_back_trace_link_mark(stack_back_trace_link_stp link,
												 stack_back_trace_size_t frames_to_skip)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(link);

	debug_capture_stack_back_trace(global_link_stack_back_trace_tmp, frames_to_skip + 1);

	stack_back_trace_size_t index = 0;

	for (stack_back_trace_size_t index_tmp = 0; index_tmp < link->mark_ptr->type_count; index_tmp++) {	/* Loop to see if it has been recored */
		stack_back_trace_hash_t hash = debug_capture_stack_back_trace_get_hash(link->mark_ptr, index_tmp);

		//debug_capture_stack_back_trace_get_trace(link->mark_ptr, index_tmp, 0);								/* Get the top level stack address only */

		if (0u != hash) {
			if (*(global_link_stack_back_trace_tmp->back_trace_hash_ptr + global_link_stack_back_trace_tmp->type_count - 1) == hash) {
				index = index_tmp;

				goto COMMON_HANDLER;
			}
		}
	}

	index = link->mark_ptr->type_count;

	if (link->mark_ptr->max_type_count <= index) {
		return 1;
	}

	debug_capture_stack_back_trace_copy(link->mark_ptr, global_link_stack_back_trace_tmp, index, 0);

	link->mark_ptr->type_count++;

COMMON_HANDLER:

	link->mark_ptr->back_trace_count_ptr[index] += 1;

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace link.mark:hash:%d  \r\n", *(link->mark_ptr->back_trace_hash_ptr + index));

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	return 0;
}

/**
 * @brief This function will set a link via the sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return the hash value of the linker
 */

errno_t debug_capture_stack_back_trace_link_link(stack_back_trace_link_stp link,
												 stack_back_trace_size_t frames_to_skip)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(link);

	debug_capture_stack_back_trace(global_link_stack_back_trace_tmp, frames_to_skip + 1);

	stack_back_trace_size_t index = 0;

	for (stack_back_trace_size_t index_tmp = 0; index_tmp < link->link_ptr->type_count; index_tmp++) {	/* Loop to see if it has been recored */
		stack_back_trace_hash_t hash = debug_capture_stack_back_trace_get_hash(link->link_ptr, index_tmp);

		if (0u != hash) {
			if (*(global_link_stack_back_trace_tmp->back_trace_hash_ptr + global_link_stack_back_trace_tmp->type_count - 1) == hash) {
				index = index_tmp;

				goto COMMON_HANDLER;
			}
		}
	}

	index = link->link_ptr->type_count;

	if (link->link_ptr->max_type_count <= index) {
		return 1;
	}

	debug_capture_stack_back_trace_copy(link->link_ptr, global_link_stack_back_trace_tmp, index, 0);

	link->link_ptr->type_count++;

COMMON_HANDLER:

	link->link_ptr->back_trace_count_ptr[index] += 1;

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace link.mark:hash:%d  \r\n", *(link->link_ptr->back_trace_hash_ptr + index));

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	return 0;
}

/**
 * @brief This function will get the trace in the link.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NULL
 */

errno_t debug_capture_stack_back_trace_link_get_trace_ptr(stack_back_trace_link_stp link,
														  stack_back_trace_stpp trace)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(link);
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(trace);

	*(trace + 0) = link->mark_ptr;
	*(trace + 1) = link->link_ptr;

	return 0;
}

/**
 * @brief This function will convert the back trace struct to the symbol description.
 *
 * @param symbol the pointer to symbol description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t capture_stack_back_trace_convert_to_symbol(stack_back_trace_string_stp string,
												   back_trace_t trace,
												   back_trace_frame_t frames)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(trace);

	HANDLE process = GetCurrentProcess();
	DWORD64 displacementSym = 0;
	DWORD64 single_back_trace = 0;

	char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
	PSYMBOL_INFO symbol_info = (PSYMBOL_INFO)buffer;

	SymInitialize(process, NULL, TRUE);

	for (back_trace_frame_t i = 0; i < frames; ++i) {
		single_back_trace = (DWORD64) * (trace + i);

		symbol_info->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol_info->MaxNameLen = MAX_SYM_NAME;

		if (SymFromAddr(process, single_back_trace, &displacementSym, symbol_info)) {
			char *name_copy = calloc(symbol_info->NameLen + 1, sizeof(char));

			if (NULL == name_copy) {
				return 1;
			}

			memcpy(name_copy, symbol_info->Name, symbol_info->NameLen);

			(*string + i)->name_ptr = name_copy;
			(*string + i)->name_len = (size_t)symbol_info->NameLen;

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t No.%d total:%d name_ptr:%s ( %lld ) \r\n",
				   frames - i, frames, symbol_info->Name, symbol_info->Address);

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
		} else {
			printf("SymFromAddr error : %d \r\n", GetLastError());
		}
	}

	return 0;
}

/**
 * @brief This function will convert the back trace struct to the line description.
 *
 * @param symbol the pointer to line description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

errno_t capture_stack_back_trace_convert_to_line(stack_back_trace_string_stp string,
												 back_trace_t trace,
												 back_trace_frame_t frames)
{
	DEBUG_ASSERT_CONTROL_POINTER_PRINTF(trace);

	HANDLE process = GetCurrentProcess();
	DWORD displacementLine = 0;
	DWORD64 single_back_trace = 0;

	IMAGEHLP_LINE64 line_info = { 0 };

	SymInitialize(process, NULL, TRUE);

	for (USHORT i = 0; i < frames; ++i) {
		single_back_trace = (DWORD64) * (trace + i);

		line_info.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		if (SymGetLineFromAddr64(process, single_back_trace, &displacementLine, &line_info)) {
			size_t name_len = strlen(line_info.FileName);
			char *name_copy = calloc(name_len + 1, sizeof(char));

			if (NULL == name_copy) {
				return 1;
			}

			memcpy(name_copy, line_info.FileName, name_len);

			(*string + i)->file_line = line_info.LineNumber;
			(*string + i)->file_name_ptr = name_copy;
			(*string + i)->file_line_len = name_len;

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t file_name_ptr: %s at line: %d \r\n",
				   line_info.FileName, line_info.LineNumber);

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
		} else {
			printf("SymFromAddr error : %d \r\n", GetLastError());
		}
	}

	return 0;
}