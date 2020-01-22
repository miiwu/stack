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

#include "debug_capture_stack_back_trace.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define TRACE_MAX_DEPTH	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH
#define TRACE_SIZE_TYPE	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE

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
 * @brief This struct is the capture stack back trace stack_back_trace module
 */

struct stack_back_trace_t {
	/* @brief This variables will record the max types.					                */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE max_type_count;

	/* @brief This variables will record how many types is recorded.					                */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE type_count;

	/* @brief This variables will record the amount of back trace.					                    */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE *back_trace_count;

	/* @brief This variables will record the back trace.					                            */
	back_trace_t *back_trace;

	/* @brief This variables will record the back trace frames.											*/
	back_trace_frame_t *back_trace_frames;

	/* @brief This variables will record the hash value of back trace.					                */
	back_trace_hash_t *back_trace_hash;
};

typedef back_trace_hash_t link_hash_table_t[2], (*link_hash_table_pt)[2];

/**
 * @brief This struct is the capture stack back trace link stack_back_trace module
 */

struct stack_back_trace_link_t {
	/* @brief This variables will record the max types.					                */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE max_index_count;

	/* @brief This variables will record how many types is recorded.					                */
	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index_count;

	link_hash_table_pt hash_table_ptr;

	/* @brief This variables will record the trace value of the both stack.					            */
	struct stack_back_trace_t sign;

	/* @brief This variables will record the hash value of the both stack.					            */
	struct stack_back_trace_t link;
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

DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE
g_pre_single_trace_len = sizeof(single_back_trace_t),
g_pre_trace_len = sizeof(single_back_trace_t) * DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH,
g_pre_frame_len = sizeof(back_trace_frame_t);

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

bool debug_capture_stack_back_trace_empty_callback(void);

/**
 * @brief This function will convert the back trace struct to the symbol description.
 *
 * @param symbol the pointer to symbol description buffer
 * @param trace the pointer to the trace of stack back trace captured
 * @param frames the amount of captured
 *
 * @return NONE
 */

void capture_stack_back_trace_convert_to_symbol(PSYMBOL_INFO symbol,
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

void capture_stack_back_trace_convert_to_line(PIMAGEHLP_LINE64 line,
											  back_trace_t trace,
											  USHORT frames);

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
										 DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE count)
{
	struct stack_back_trace_t
		*strcuture_allocated = calloc(1, sizeof(struct stack_back_trace_t));

	TRACE_SIZE_TYPE
		*count_allocated = calloc(count, sizeof(TRACE_SIZE_TYPE));

	back_trace_t
		*trace_allocated = calloc(1, sizeof(back_trace_t));

	back_trace_frame_t
		*frames_allocated = calloc(count, sizeof(back_trace_frame_t));

	back_trace_hash_t
		*hash_allocated = calloc(count, sizeof(back_trace_hash_t));

	back_trace_t
		trace_element_allocated = calloc(TRACE_MAX_DEPTH, sizeof(back_trace_t) * TRACE_MAX_DEPTH);

	if (NULL == strcuture_allocated ||
		NULL == count_allocated ||
		NULL == trace_allocated ||
		NULL == frames_allocated ||
		NULL == hash_allocated ||
		NULL == trace_element_allocated) {
		return;
	}

	*trace_allocated = trace_element_allocated;

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
	free((*strcuture)->back_trace);
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
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip,
									DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_capture)
{
	void *back_trace_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	ULONG back_trace_hash_tmp = 0;
	SYMBOL_INFO back_trace_symbol_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	IMAGEHLP_LINE64 back_trace_line_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };

	back_trace_frame_t back_trace_frames_tmp = CaptureStackBackTrace(frames_to_skip + 1
																	 , frames_to_capture
																	 , back_trace_tmp
																	 , &back_trace_hash_tmp) - 7;	/* the stack of main() is start from the level 7 */

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		back_trace_hash_t
			hash = *(stack_back_trace->back_trace_hash + cnt);

		if (hash == back_trace_hash_tmp) {
			stack_back_trace->back_trace_count[cnt] += 1;

			return;
		}
	}

	if (stack_back_trace->max_type_count <= stack_back_trace->type_count &&
		false == debug_capture_stack_back_trace_empty_callback()) {
		return;
	}

	memcpy((void *)((size_t)*stack_back_trace->back_trace + stack_back_trace->type_count * g_pre_trace_len),
		(void *)&back_trace_tmp, g_pre_trace_len);

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

bool debug_capture_stack_back_trace_empty_callback(void)
{
	printf("stack back trace buffer is empty. \r\n");

	return false;
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

		printf("NULL_HASH capture stack back trace.reduce count \r\n");

		#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

		return;
	}

	for (size_t cnt = 0; cnt < strcuture->type_count; cnt++) {
		if (hash == *(strcuture->back_trace_hash + cnt)) {
			if (0u < *(strcuture->back_trace_count + cnt)) {
				*(strcuture->back_trace_count + cnt) -= 1;
			}

			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("No.%d reduce to %d capture stack back trace.reduce count \r\n", cnt, *(strcuture->back_trace_count + cnt));

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			return;
		}
	}

	#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

	printf("END capture stack back trace.reduce count \r\n");

	#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
}

/**
 * @brief This function will reduce the count of the capture stack back trace type.
 *
 * @param stack_back_trace the pointer to the capture stack back trace struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_convert_to_symbol(STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace)
{
	assert(stack_back_trace);

	SYMBOL_INFO back_trace_symbol_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };

	for (size_t cnt = 0; cnt < stack_back_trace->type_count; cnt++) {
		if (0u < *(stack_back_trace->back_trace_count + cnt)) {
			capture_stack_back_trace_convert_to_symbol(back_trace_symbol_tmp,
				(back_trace_t)((size_t)*stack_back_trace->back_trace + cnt * g_pre_trace_len),
													   *(stack_back_trace->back_trace_frames + cnt));

		//	printf("No.%d it's last level is \"%s\" \r\n", cnt, back_trace_symbol_tmp[0].Name);
		}
	}

	return;
}

/**
 * @brief This function will initialize a link struct.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

void debug_capture_stack_back_trace_link_init(STACK_BACK_TRACE_LINK_TYPEDEF_PTR *link,
											  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE count)
{
	assert(link);

	STACK_BACK_TRACE_LINK_TYPEDEF_PTR
		link_allocated = calloc(1, sizeof(struct stack_back_trace_link_t));

	link_hash_table_pt
		hash_table_ptr_allocated = calloc(count, sizeof(link_hash_table_t));

	if (NULL == link_allocated ||
		NULL == hash_table_ptr_allocated) {
		return;
	}

	link_allocated->max_index_count = count;
	link_allocated->index_count = 0;
	link_allocated->hash_table_ptr = hash_table_ptr_allocated;

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

	free((*link)->hash_table_ptr);
	free(*link);
}

/**
 * @brief This function will make a sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return NONE
 */

DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE debug_capture_stack_back_trace_link_mark(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
																					  STACK_BACK_TRACE_TYPEDEF_PTR stack_back_trace,
																					  DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip)
{
	assert(link);
	assert(stack_back_trace);

	debug_capture_stack_back_trace(stack_back_trace, frames_to_skip + 1, 64);

	DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index = 0;

	for (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE i = 0; i < link->index_count; i++) {	/* Loop to see if it has been recored */
		back_trace_hash_t hash = *(*(link->hash_table_ptr + i) + 0);
		if (0u != hash) {
			if (*(stack_back_trace->back_trace_hash + stack_back_trace->type_count - 1) == hash) {
				index = i;

				goto COMMON_HANDLER;
			}
		}
	}

	index = link->index_count;

	if (link->max_index_count <= link->index_count) {
		return 0xffff;
	}

	link->index_count++;

COMMON_HANDLER:

	*(*(link->hash_table_ptr + index) + 0) = *(stack_back_trace->back_trace_hash + stack_back_trace->type_count - 1);

	printf("index:%d index_count:%d hash:%d capture stack back trace.link mark \r\n", index, link->index_count, *(*(link->hash_table_ptr + index) + 0));

	return index;
}

/**
 * @brief This function will set a link via the sign.
 *
 * @param link the pointer to the stack back trace link struct
 *
 * @return the hash value of the linker
 */

back_trace_hash_t debug_capture_stack_back_trace_link_link(STACK_BACK_TRACE_LINK_TYPEDEF_PTR link,
														   DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE index,
														   DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_SIZE_TYPE frames_to_skip)
{
	assert(link);

	PVOID back_trace_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };
	ULONG back_trace_hash_tmp = 0;
	IMAGEHLP_LINE64 back_trace_line_tmp[DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH] = { 0 };

	const USHORT farmes = CaptureStackBackTrace(frames_to_skip + 1
												, DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_STACK_MAX_DEPTH
												, back_trace_tmp
												, &back_trace_hash_tmp) - 7;

	if (link->max_index_count <= index) {
		return 0u;
	}

	if ((0u != *(*(link->hash_table_ptr + index) + 1)) &&
		(*(*(link->hash_table_ptr + index) + 1) != back_trace_hash_tmp)) {
		return 0u;
	}

	if (0u == *(*(link->hash_table_ptr + index) + 1)) {
		*(*(link->hash_table_ptr + index) + 1) = back_trace_hash_tmp;
	}

	return *(*(link->hash_table_ptr + index) + 0);
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

void capture_stack_back_trace_convert_to_symbol(PSYMBOL_INFO symbol,
												back_trace_t trace,
												back_trace_frame_t frames)
{
	assert(trace);

	HANDLE process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	for (back_trace_frame_t i = 0; i < frames; ++i) {
		DWORD64 back_trace_address = (DWORD64) * (trace + i);
		DWORD64 displacementSym = 0;

		(symbol + i)->SizeOfStruct = sizeof(SYMBOL_INFO);
		(symbol + i)->MaxNameLen = MAX_SYM_NAME;

		if (SymFromAddr(process, back_trace_address, &displacementSym, (symbol + i))) {
			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t No.%d name:%s ( %lld ) \r\n",
				   frames - i, (symbol + i)->Name, (symbol + i)->Address);

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

void capture_stack_back_trace_convert_to_line(PIMAGEHLP_LINE64 line,
											  back_trace_t trace,
											  USHORT frames)
{
	assert(trace);

	HANDLE process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	for (USHORT i = 0; i < frames; ++i) {
		DWORD64 back_trace_address = (DWORD64)trace[i];
		DWORD displacementLine = 0;

		(line + i)->SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		if (SymGetLineFromAddr64(process, back_trace_address, &displacementLine, (line + i))) {
			#if (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)

			printf("\t file_name: %s at line: %d \r\n",
				(line + i)->FileName, (line + i)->LineNumber);

			#endif // (DEBUG_CAPTURE_STACK_BACK_TRACE_CFG_DEBUG_MODE_EN)
		} else {
			printf("SymFromAddr error : %d \r\n", GetLastError());
		}
	}
}