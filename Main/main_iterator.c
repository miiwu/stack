#include "iterator.h"

#define MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN							1
#define MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN								0
#define MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN							1

void main_access_iterator(void);
void main_input_iterator(void);
void main_output_iterator(void);

void main(void)
{
	printf("\r\n------------------------+ iterator demo start +------------------------\r\n");

#if MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

	main_access_iterator();

#endif // MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

#if MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN

	main_input_iterator();

#endif // #define MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN

#if MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN

	main_output_iterator();

#endif // MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN

	printf("\r\n------------------------+ iterator demo end +------------------------\r\n");

	return;
}

void *string_element_access_at(char string[],
							   size_t position);
void *string_element_access_data(char string[]);
bool string_capacity_empty(char string[]);
size_t string_capacity_max_size(char string[]);
size_t string_capacity_size(char string[]);
size_t string_capacity_element_size(char string[]);
void *string_modifiers_modify(char string[],
							  size_t index,
							  void *source);

char string[30] = "this is a iterator test.";

struct access_iterator_object_control_s
	object_control = {
	.element_access.at = string_element_access_at,
	.element_access.data = string_element_access_data,

	.capacity.empty = string_capacity_empty,
	.capacity.max_size = string_capacity_max_size,
	.capacity.size = string_capacity_size,
	.capacity.element_size = string_capacity_element_size,

	.modifiers.modify = string_modifiers_modify,
};

struct access_iterator_object_unit_s
	access_iterator_object_unit = {
	.object_ptr = string,
	.control_ptr = &object_control,
};

char *element = NULL;

struct access_iterator_s *begin_iterator = NULL;
struct access_iterator_s *end_iterator = NULL;

#if MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

#define MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN					1
#define MAIN_ACCESS_ITERATOR_CFG_BIDIRECTIONAL_ITERATOR_EN				0
#define MAIN_ACCESS_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN				0
#define MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN					1

struct access_iterator_s *access_iterator = NULL;
struct access_iterator_s *access_iterator_another = NULL;
errno_t main_access_iterator_construct(void);

void main_forward_iterator(void);
void main_bidirectional_iterator(void);
void main_random_access_iterator(void);
void main_continuous_iterator(void);

void main_access_iterator(void)
{
	printf("\r\n------------------------+ access iterator demo start +------------------------\r\n");

	printf("\r\naccess_iterator.construct access iterator start \r\n");
	main_access_iterator_construct();

#if MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN

	main_forward_iterator();

#endif // MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN

#if MAIN_ACCESS_ITERATOR_CFG_BIDIRECTIONAL_ITERATOR_EN

	main_bidirectional_iterator();

#endif // MAIN_ACCESS_ITERATOR_CFG_BIDIRECTIONAL_ITERATOR_EN

#if MAIN_ACCESS_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN

	main_random_access_iterator();

#endif // MAIN_ACCESS_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN

#if MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN

	main_continuous_iterator();

#endif // MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN

	printf("\r\n------------------------+ access iterator demo end +------------------------\r\n");

	return;
}

#if MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN

void main_forward_iterator(void)
{
	printf("\r\n------------------------+ forward iterator demo start +------------------------\r\n");

	printf("\r\nforward_iterator.element_access.advance start \r\n");
	printf("forward_iterator.element_access.advance:%p \r\n",
		   access_iterator_control.element_access.advance(access_iterator,
														  forward_iterator.advance,
														  0));

	printf("\r\nforward_iterator.element_access.distance start \r\n");
	printf("forward_iterator.element_access.distance:%d \r\n",
		   access_iterator_control.element_access.distance(access_iterator,
														   access_iterator_another));

	printf("\r\nforward_iterator.element_access.front start \r\n");
	printf("forward_iterator.element_access.front:%p \r\n",
		   access_iterator_control.element_access.front(access_iterator,
														forward_iterator.front));

	printf("\r\nforward_iterator.element_access.back start \r\n");
	printf("forward_iterator.element_access.back:%p \r\n",
		   access_iterator_control.element_access.back(access_iterator,
													   forward_iterator.back));

	printf("\r\nforward_iterator.range_access.empty start \r\n");
	printf("forward_iterator.range_access.empty:%d \r\n",
		   access_iterator_control.range_access.empty(access_iterator));

	printf("\r\nforward_iterator.range_access.size start \r\n");
	printf("forward_iterator.range_access.size:%d \r\n",
		   access_iterator_control.range_access.size(access_iterator));

	printf("\r\nforward_iterator.range_access.max_size start \r\n");
	printf("forward_iterator.range_access.max_size:%d \r\n",
		   access_iterator_control.range_access.max_size(access_iterator));

	printf("\r\nforward_iterator.range_access.data start \r\n");
	printf("forward_iterator.range_access.data:%p \r\n",
		   access_iterator_control.range_access.data(access_iterator));

	printf("\r\n------------------------+ forward iterator demo end +------------------------\r\n");

	return;
}

#endif // MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN

#if MAIN_ACCESS_ITERATOR_CFG_BIDIRECTIONAL_ITERATOR_EN

void main_bidirectional_iterator(void)
{
}

#endif // MAIN_ACCESS_ITERATOR_CFG_BIDIRECTIONAL_ITERATOR_EN

#if MAIN_ACCESS_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN

void main_random_access_iterator(void)
{
}

#endif // MAIN_ACCESS_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN

#if MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN

void main_continuous_iterator(void)
{
	printf("\r\n------------------------+ continuous iterator demo start +------------------------\r\n");

	printf("\r\ncontinuous_iterator.element_access.advance start \r\n");
	printf("continuous_iterator.element_access.advance:%p \r\n",
		   access_iterator_control.element_access.advance(access_iterator,
														  continuous_iterator.advance,
														  0));

	printf("\r\n------------------------+ continuous iterator demo end +------------------------\r\n");

	return;
}

#endif // MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN

#include "access_iterator_pte_def.h"

errno_t main_access_iterator_construct(void)
{
	unify_struct_control_construct(&access_iterator,
								   CONCEPT_ALLOCATOR,
								   100);
	access_iterator->object_unit_ptr = &access_iterator_object_unit;

	unify_struct_control_construct(&access_iterator_another,
								   CONCEPT_ALLOCATOR,
								   100);
	access_iterator_another->object_unit_ptr = &access_iterator_object_unit;
	access_iterator_another->privite.position = 24;

	return DEBUG_ERROR_CONTROL_ERROR();
}

#endif // MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

#if MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN

struct iterator_s *input_iterator = NULL;

void main_input_iterator(void)
{
	printf("\r\n ------------------------+ input_iterator demo start +------------------------\r\n");

	printf("\r\ninput_iterator.configuration.init start\r\n");
	if (input_iterator_control.configuration.init(&input_iterator, object_unit)) {
		return;
	}

	printf("\r\ninput_iterator.element_access.advance start\r\n");
	element = input_iterator_control.element_access.advance(input_iterator, -2);
	printf("input_iterator.element_access.advance:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\ninput_iterator.iterator_operations.next start\r\n");
	element = input_iterator_control.iterator_operations.next(input_iterator);
	printf("input_iterator.iterator_operations.next:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\ninput_iterator.range_access.size start\r\n");
	element = (char *)input_iterator_control.range_access.size(input_iterator);
	printf("input_iterator.range_access.size:%d \r\n"
		   , (NULL == element) ? '?' : (size_t)element);

	printf("\r\ninput_iterator.range_access.data start\r\n");
	element = input_iterator_control.range_access.data(input_iterator);
	printf("input_iterator.range_access.data:%p \r\n"
		   , (NULL == element) ? NULL : element);

	printf("\r\ninput_iterator.configuration.destroy start\r\n");
	if (input_iterator_control.configuration.destroy(&input_iterator)) {
		return;
	}

	printf("\r\n ------------------------+ input_iterator demo end +------------------------ \r\n");
}

#endif // MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN

#if MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN

struct iterator_s *input_iterator = NULL;
output_iterator_stp output_iterator = NULL;

void main_output_iterator(void)
{
	printf("\r\n ------------------------+ output_iterator demo start +------------------------\r\n");

	printf("\r\noutput_iterator.configuration.init start\r\n");
	output_iterator_control.configuration.init(&output_iterator, access_iterator_object_unit);

	printf("\r\noutput_iterator.iterator_operations.begin start\r\n");
	begin_iterator = output_iterator_control.iterator_operations.begin(output_iterator);

	printf("\r\noutput_iterator.access start\r\n");
	printf("output_iterator.access:\"%s\"\r\n",
		   (char *)output_iterator_control.access(begin_iterator, random_access_iterator.at, 0));

	printf("\r\noutput_iterator.modify start\r\n");
	printf("output_iterator.modify:\"%s\"\r\n",
		   (char *)output_iterator_control.modify(begin_iterator, "*", random_access_iterator.at, 1));

	printf("\r\noutput_iterator.iterator_operations.dereferance start\r\n");
	output_iterator_control.iterator_operations.dereferance(output_iterator,
														   &begin_iterator);

	printf("\r\noutput_iterator.configuration.destroy start\r\n");
	output_iterator_control.configuration.destroy(&output_iterator);

	printf("\r\n ------------------------+ output_iterator demo end +------------------------ \r\n");

	return;
}

#endif // MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN

void *string_element_access_at(char string[],
							   size_t position)
{
	return &string[position];
}

void *string_element_access_data(char string[])
{
	return string;
}

bool string_capacity_empty(char string[])
{
	return !strlen(string);
}

size_t string_capacity_max_size(char string[])
{
	return 30;
}

size_t string_capacity_size(char string[])
{
	return strlen(string);
}

size_t string_capacity_element_size(char string[])
{
	return sizeof(char);
}

void *string_modifiers_modify(char string[],
							  size_t index,
							  void *source)
{
	char *result = memcpy(&string[index], source, 1);

	return result;
}