#include "iterator.h"

#define MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN							1
#define MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN								0
#define MAIN_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN						0
#define MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN							0

void main_access_iterator(void);
void main_input_iterator(void);
void main_output_iterator(void);

void main(void)
{
#if MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

	main_access_iterator();

#endif // MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

#if MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN

	main_input_iterator();

#endif // #define MAIN_ITERATOR_CFG_INPUT_ITERATOR_EN

#if MAIN_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN

	main_random_access_iterator();

#endif // MAIN_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN

#if MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN

	main_output_iterator();

#endif // MAIN_ITERATOR_CFG_OUTPUT_ITERATOR_EN

	return;
}

void *string_element_access_at(char string[],
							   size_t position);
void *string_element_access_data(char string[]);
bool string_capacity_empty(char string[]);
size_t string_capacity_max_size(char string[]);
size_t string_capacity_size(char string[]);
void *string_modifiers_modify(char string[],
							  size_t index,
							  void *source);

char string[] = "this is a iterator test.";

struct access_iterator_object_control_s
	object_control = {
	.element_access.at = string_element_access_at,
	.element_access.data = string_element_access_data,

	.capacity.empty = string_capacity_empty,
	.capacity.max_size = string_capacity_max_size,
	.capacity.size = string_capacity_size,

	.modifiers.modify = string_modifiers_modify,
};
//
//struct iterator_object_unit_s
//	object_unit = {
//	.object_ptr = string,
//	.control_ptr = &object_control,
//};
//
//char *element = NULL;

#if MAIN_ITERATOR_CFG_ACCESS_ITERATOR_EN

#define MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN					1
#define MAIN_ACCESS_ITERATOR_CFG_BIDIRECTIONAL_ITERATOR_EN				0
#define MAIN_ACCESS_ITERATOR_CFG_RANDOM_ACCESS_ITERATOR_EN				0
#define MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN					0

void main_forward_iterator(void);
void main_bidirectional_iterator(void);
void main_random_access_iterator(void);
void main_continuous_iterator(void);

void main_access_iterator(void)
{
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

	return;
}

#if MAIN_ACCESS_ITERATOR_CFG_FORWARD_ITERATOR_EN

void main_forward_iterator(void)
{
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
}

#endif // MAIN_ACCESS_ITERATOR_CFG_CONTINUOUS_ITERATOR_EN

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

	printf("\r\ninput_iterator.iterator_operations.advance start\r\n");
	element = input_iterator_control.iterator_operations.advance(input_iterator, -2);
	printf("input_iterator.iterator_operations.advance:\"%c\" \r\n"
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
	if (output_iterator_control.configuration.init(&output_iterator, 0, object_unit)) {
		return;
	}

	printf("\r\noutput_iterator.configuration.adapt_exist start\r\n");
	input_iterator_control.configuration.init(&input_iterator, object_unit);
	output_iterator_control.configuration.adapt_exist(&output_iterator, input_iterator);

	printf("\r\noutput_iterator.iterator_operation.advance start\r\n");
	element = output_iterator_control.iterator_operations.advance(output_iterator, 2);
	printf("output_iterator.iterator_operations.advance:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\noutput_iterator.modify start\r\n");
	element = output_iterator_control.modify(output_iterator, 1, "*");
	element = output_iterator_control.iterator_operations.advance(output_iterator, 0);
	printf("output_iterator.iterator_operations.advance:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\noutput_iterator.range_access.size start\r\n");
	element = (char *)output_iterator_control.range_access.size(output_iterator);
	printf("output_iterator.range_access.size:%d \r\n"
		   , (NULL == element) ? '?' : (size_t)element);

	printf("\r\noutput_iterator.range_access.data start\r\n");
	element = output_iterator_control.range_access.data(output_iterator);
	printf("output_iterator.range_access.data:\"%s\" \r\n"
		   , element);

	printf("\r\noutput_iterator.configuration.destroy start\r\n");
	output_iterator_control.configuration.destroy(&output_iterator);
	input_iterator_control.configuration.destroy(&input_iterator);

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
	return strlen(string);
}

size_t string_capacity_size(char string[])
{
	return strlen(string);
}

void *string_modifiers_modify(char string[],
							  size_t index,
							  void *source)
{
	char *result = memcpy(&string[index], source, 1);

	return result;
}