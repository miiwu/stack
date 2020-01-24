/*
************************************************************************************************************************
*                                  DEBUG COMPONENT OF CAPATURE STACK BACK TRACE FUNCTIONS
*
* File    : DEBUG_CAPATURE_STACK_BACK_TRACE.C
* By      : lqq
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

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define TRACE_MAX_DEPTH	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH
#define TRACE_SIZE_TYPE	DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE

#define GET_ADDRESS_VIA_PTR(pointer,mem_type,index)	(void*)((size_t)(pointer) + index * mem_type)

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
 * @brief This struct is the stack back trace stack_back_trace module
 */

struct stack_back_trace_t {
	/* @brief This variables will record the max types.					                */
	DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE max_type_count;

	/* @brief This variables will record how many types is recorded.					                */
	DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE type_count;

	/* @brief This variables will record the amount of back trace.					                    */
	DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE *back_trace_count;

	/* @brief This variables will record the back trace.					                            */
	back_trace_pt back_trace;

	/* @brief This variables will record the back trace frames.											*/
	back_trace_frame_pt back_trace_frames;

	/* @brief This variables will record the hash value of back trace.					                */
	back_trace_hash_pt back_trace_hash;
};

/**
 * @brief This struct is the stack back trace link module
 */

struct stack_back_trace_link_t {
	/* @brief This variables will record the trace value of the both stack.					            */
	struct stack_back_trace_t *mark_ptr;

	/* @brief This variables will record the hash value of the both stack.					            */
	struct stack_back_trace_t *link_ptr;
};

/**
 * @brief This struct is the stack back trace symbol module
 */

struct stack_back_trace_string_t {
	/* @brief This variables will record the max types.													*/
	size_t name_len;

	/* @brief This variables will record how many types is recorded.					                */
	char *name;

	/* @brief This variables will record the trace value of the both stack.					            */
	size_t file_line;

	/* @brief This variables will record the trace value of the both stack.					            */
	size_t file_line_len;

	/* @brief This variables will record the hash value of the both stack.					            */
	char *file_name;
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

DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE
g_pre_single_trace_len = sizeof(single_back_trace_t),
g_pre_trace_len = sizeof(single_back_trace_t) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH,
g_pre_frame_len = sizeof(back_trace_frame_t);

STACK_BACK_TRACE_TYPEDEF_PTR global_link_stack_back_trace_tmp = NULL;

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

bool debug_capture_stack_back_trace_empty_callback(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace);

/**
 * @brief This function will convert the back trace struct to the symbol description.
 *
 * @param symbol the pointer to symbol description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

void capture_stack_back_trace_convert_to_symbol(STACK_BACK_TRACE_STRING_TYPEDEF_PTR string,
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

void capture_stack_back_trace_convert_to_line(STACK_BACK_TRACE_STRING_TYPEDEF_PTR string,
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

void debug_capture_stack_back_trace_init(STACK_BACK_TRACE_TYPEDEF_PTR *stack_back_trace,
										 DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE count)
{
	struct stack_back_trace_t
		*strcuture_allocated = calloc(1, sizeof(struct stack_back_trace_t));

	TRACE_SIZE_TYPE
		*count_allocated = calloc(count, sizeof(TRACE_SIZE_TYPE));

	back_trace_pt
		trace_allocated = calloc(count, sizeof(single_back_trace_t) * TRACE_MAX_DEPTH);

	back_trace_frame_pt
		frames_allocated = calloc(count, sizeof(back_trace_frame_t));

	back_trace_hash_pt
		hash_allocated = calloc(count, sizeof(back_trace_hash_t));

	if (NULL == strcuture_allocated ||
		NULL == count_allocated ||
		NULL == trace_allocated ||
		NULL == frames_allocated ||
		NULL == hash_allocated) {
		return;
	}

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("trace:%p frames:%p hash:%p capture stack back trace.init:block \r\n",
		   *trace_allocated, frames_allocated, hash_allocated);

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	strcuture_allocated->max_type_count = count;
	strcuture_allocated->type_count = 0u;
	strcuture_allocated->back_trace_count = count_allocated;
	strcuture_allocated->back_trace = trace_allocated;
	strcuture_allocated->back_trace_frames = frames_allocated;
	strcuture_allocated->back_trace_hash = hash_allocated;

	*stack_back_trace = strcuture_allocated;
}

/**
 * @brief This function will destroy the capture stack back trace struct.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_destroy(STACK_BACK_TRACE_TYPEDEF_PTR *strcuture)
{
	assert(strcuture);

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("trace:%p frames:%p hash:%p capture stack back trace.destroy:block \r\n",
		   *(*strcuture)->back_trace, (*strcuture)->back_trace_frames, (*strcuture)->back_trace_hash);

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	free(*(*strcuture)->back_trace);
	free((*strcuture)->back_trace_frames);
	free((*strcuture)->back_trace_hash);
	free((*strcuture)->back_trace_count);

	(*strcuture)->type_count = 0u;

	free((*strcuture));
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

void debug_capture_stack_back_trace(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace,
									DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE frames_to_skip)
{
	void *back_trace_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	ULONG back_trace_hash_tmp = 0;
	SYMBOL_INFO back_trace_symbol_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	IMAGEHLP_LINE64 back_trace_line_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };

	back_trace_frame_t back_trace_frames_tmp = CaptureStackBackTrace(frames_to_skip + 1
																	 , DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH
																	 , back_trace_tmp
																	 , &back_trace_hash_tmp) - 7;	/* the stack of main() is start from the level 7 */

	if (stack_back_trace->max_type_count <= stack_back_trace->type_count &&
		10 > (stack_back_trace->type_count / stack_back_trace->max_type_count) &&		/* Exclude it have been reduced to a negative number. */
		false == debug_capture_stack_back_trace_empty_callback(stack_back_trace)) {	
		return;
	}

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		back_trace_hash_t
			hash = *(stack_back_trace->back_trace_hash + cnt);

		if (hash == back_trace_hash_tmp) {
			stack_back_trace->back_trace_count[cnt] += 1;

			return;
		}
	}

	for (DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index = 0; index < DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH; index++) {
		*(*(stack_back_trace->back_trace + stack_back_trace->type_count) + index) = back_trace_tmp[index];
	}

	memcpy((void *)(stack_back_trace->back_trace_frames + stack_back_trace->type_count),
		(void *)&back_trace_frames_tmp, sizeof(back_trace_frame_t));

	memcpy((void *)(stack_back_trace->back_trace_hash + stack_back_trace->type_count),
		(void *)&back_trace_hash_tmp, sizeof(back_trace_hash_t));

	stack_back_trace->back_trace_count[stack_back_trace->type_count] = 1;

	stack_back_trace->type_count++;
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

bool debug_capture_stack_back_trace_empty_callback(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace)
{
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

void debug_capture_stack_back_trace_reduce_count(STACK_BACK_TRACE_TYPEDEF_PTR strcuture,
												 back_trace_hash_t hash)
{
	assert(strcuture);

	if (0u == hash) {
		#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		printf("capture stack back trace.reduce count:NULL_HASH\r\n");

		#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		return;
	}

	for (size_t cnt = 0; cnt < strcuture->type_count; cnt++) {
		if (hash == *(strcuture->back_trace_hash + cnt)) {
			if (0u < *(strcuture->back_trace_count + cnt)) {
				*(strcuture->back_trace_count + cnt) -= 1;
			}

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("capture stack back trace.reduce count:No.%d reduce to %d \r\n", cnt, *(strcuture->back_trace_count + cnt));

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			return;
		}
	}

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace.reduce count:NULL_TRACE_HASH_MATCH\r\n");

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_convert_to_string(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace)
{
	assert(stack_back_trace);

	STACK_BACK_TRACE_STRING_TYPEDEF back_trace_string_tmp = { 0 };
	back_trace_frame_t frame_tmp = 0;
	back_trace_pt trace_tmp = 0;

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		if (0u < *(stack_back_trace->back_trace_count + cnt)) {
			trace_tmp = (stack_back_trace->back_trace + cnt);
			frame_tmp = *(stack_back_trace->back_trace_frames + cnt);

			capture_stack_back_trace_convert_to_symbol(&back_trace_string_tmp,
													   *trace_tmp,
													   frame_tmp);

			capture_stack_back_trace_convert_to_line(&back_trace_string_tmp,
													 *trace_tmp,
													 frame_tmp);

			for (size_t index = 0; index < frame_tmp; index++) {
				printf("No.%d it have %d ,it's %d/%d level stack is \"%s\" (%p) function.\r\n",
					   cnt, *(stack_back_trace->back_trace_count + cnt), index + 1, frame_tmp, back_trace_string_tmp[index].name, *(*trace_tmp + index));

				/*printf("No.%d it have %d it's %d/%d level stack is \"%s\" (%p) function in \"%s\" file at %d line.\r\n",
					   cnt, *(stack_back_trace->back_trace_count + cnt), index + 1, frame_tmp, back_trace_string_tmp[index].name, *(*trace_tmp + index),
					   back_trace_string_tmp[index].file_name, back_trace_string_tmp[index].file_line);*/
			}

			printf("\r\n");
		}
	}
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

back_trace_hash_t debug_capture_stack_back_trace_get_hash(STACK_BACK_TRACE_TYPEDEF_PTR strcuture,
														  DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index)
{
	assert(strcuture);

	return *(strcuture->back_trace_hash + index);

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace.get index : hash:%d  \r\n", *(strcuture->back_trace_hash + index));

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

single_back_trace_t *debug_capture_stack_back_trace_get_trace(STACK_BACK_TRACE_TYPEDEF_PTR strcuture,
															  DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index,
															  DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE sub_index)
{
	assert(strcuture);

	return *(*(strcuture->back_trace + index) + sub_index);
}

/**
 * @brief This function will return the specified hash.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 * @param hash the hash of the capture stack back trace
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_copy(STACK_BACK_TRACE_TYPEDEF_PTR destination,
										 STACK_BACK_TRACE_TYPEDEF_PTR source,
										 DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE dst_index,
										 DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE src_index)
{
	assert(destination);
	assert(source);

	for (size_t sub_index = 0; sub_index < *(source->back_trace_frames + src_index); sub_index++) {
		*(*(destination->back_trace + dst_index) + sub_index) = *(*(source->back_trace + src_index) + sub_index);
	}

	*(destination->back_trace_frames + dst_index) = *(source->back_trace_frames + src_index);
	*(destination->back_trace_hash + dst_index) = *(source->back_trace_hash + src_index);
}

/**
 * @brief This function will initialize a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_link_init(STACK_BACK_TRACE_LINK_TYPEDEF_PTR *link,
											  DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE count)
{
	assert(link);

	STACK_BACK_TRACE_LINK_TYPEDEF_PTR
		link_allocated = calloc(1, sizeof(struct stack_back_trace_link_t));

	if (NULL == link_allocated) {
		return;
	}

	debug_capture_stack_back_trace_init(&global_link_stack_back_trace_tmp, 1);

	debug_capture_stack_back_trace_init(&link_allocated->mark_ptr, count);
	debug_capture_stack_back_trace_init(&link_allocated->link_ptr, count);

	*link = link_allocated;
}

/**
 * @brief This function will destroy a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_link_destroy(STACK_BACK_TRACE_LINK_TYPEDEF_PTR *link)
{
	assert(link);

	if (NULL == *link) {
		return;
	}

	debug_capture_stack_back_trace_destroy(&(*link)->mark_ptr);
	debug_capture_stack_back_trace_destroy(&(*link)->link_ptr);

	free(*link);
}

/**
 * @brief This function will make a sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_link_mark(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
											  DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE frames_to_skip)
{
	assert(link);

	debug_capture_stack_back_trace(global_link_stack_back_trace_tmp, frames_to_skip + 1);

	DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index = 0;

	for (DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index_tmp = 0; index_tmp < link->mark_ptr->type_count; index_tmp++) {	/* Loop to see if it has been recored */
		back_trace_hash_t hash = debug_capture_stack_back_trace_get_hash(link->mark_ptr, index_tmp);

		//debug_capture_stack_back_trace_get_trace(link->mark_ptr, index_tmp, 0);								/* Get the top level stack address only */

		if (0u != hash) {
			if (*(global_link_stack_back_trace_tmp->back_trace_hash + global_link_stack_back_trace_tmp->type_count - 1) == hash) {
				index = index_tmp;

				goto COMMON_HANDLER;
			}
		}
	}

	index = link->mark_ptr->type_count;

	if (link->mark_ptr->max_type_count <= index) {
		return;
	}

	debug_capture_stack_back_trace_copy(link->mark_ptr, global_link_stack_back_trace_tmp, index, 0);

	link->mark_ptr->type_count++;

COMMON_HANDLER:

	link->mark_ptr->back_trace_count[index] += 1;

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace link.mark:hash:%d  \r\n", *(link->mark_ptr->back_trace_hash + index));

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
}

/**
 * @brief This function will set a link via the sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return the hash value of the linker
 */

void debug_capture_stack_back_trace_link_link(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
											  DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE frames_to_skip)
{
	assert(link);

	debug_capture_stack_back_trace(global_link_stack_back_trace_tmp, frames_to_skip + 1);

	DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index = 0;

	for (DEBUG_COMPONENT_GLOBAL_CFG_SIZE_TYPE index_tmp = 0; index_tmp < link->link_ptr->type_count; index_tmp++) {	/* Loop to see if it has been recored */
		back_trace_hash_t hash = debug_capture_stack_back_trace_get_hash(link->link_ptr, index_tmp);

		if (0u != hash) {
			if (*(global_link_stack_back_trace_tmp->back_trace_hash + global_link_stack_back_trace_tmp->type_count - 1) == hash) {
				index = index_tmp;

				goto COMMON_HANDLER;
			}
		}
	}

	index = link->link_ptr->type_count;

	if (link->link_ptr->max_type_count <= index) {
		return;
	}

	debug_capture_stack_back_trace_copy(link->link_ptr, global_link_stack_back_trace_tmp, index, 0);

	link->link_ptr->type_count++;

COMMON_HANDLER:

	link->link_ptr->back_trace_count[index] += 1;

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("capture stack back trace link.mark:hash:%d  \r\n", *(link->link_ptr->back_trace_hash + index));

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
}

/**
 * @brief This function will get the trace in the link.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NULL
 */

void debug_capture_stack_back_trace_link_get_trace_ptr(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
													   STACK_BACK_TRACE_TYPEDEF_PPTR trace)
{
	assert(link);
	assert(trace);

	*(trace + 0) = link->mark_ptr;
	*(trace + 1) = link->link_ptr;
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

void capture_stack_back_trace_convert_to_symbol(STACK_BACK_TRACE_STRING_TYPEDEF_PTR string,
												back_trace_t trace,
												back_trace_frame_t frames)
{
	assert(trace);

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
				return;
			}

			memcpy(name_copy, symbol_info->Name, symbol_info->NameLen);

			(*string + i)->name = name_copy;
			(*string + i)->name_len = (size_t)symbol_info->NameLen;

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t No.%d total:%d name:%s ( %lld ) \r\n",
				   frames - i, frames, symbol_info->Name, symbol_info->Address);

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
		} else {
			printf("SymFromAddr error : %d \r\n", GetLastError());
		}
	}
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

void capture_stack_back_trace_convert_to_line(STACK_BACK_TRACE_STRING_TYPEDEF_PTR string,
											  back_trace_t trace,
											  back_trace_frame_t frames)
{
	assert(trace);

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
				return;
			}

			memcpy(name_copy, line_info.FileName, name_len);

			(*string + i)->file_line = line_info.LineNumber;
			(*string + i)->file_name = name_copy;
			(*string + i)->file_line_len = name_len;

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t file_name: %s at line: %d \r\n",
				   line_info.FileName, line_info.LineNumber);

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
		} else {
			printf("SymFromAddr error : %d \r\n", GetLastError());
		}
	}
}