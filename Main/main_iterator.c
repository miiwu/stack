#include "main_cfg.h"

#if MAIN_ITERATOR_EN

void *string_element_access_at(char string[],
							   size_t position);
void *string_element_access_data(char string[]);
bool string_capacity_empty(char string[]);
size_t string_capacity_max_size(char string[]);
size_t string_capacity_size(char string[]);
errno_t string_modifiers_modify(char string[],
								size_t index,
								void *source);

void main_input_iterator(void);
void main_random_access_iterator(void);

char string[] = "this is a iterator test.";

struct iterator_object_control_s
	object_control = {
	.element_access.at = string_element_access_at,
	.element_access.data = string_element_access_data,

	.capacity.empty = string_capacity_empty,
	.capacity.max_size = string_capacity_max_size,
	.capacity.size = string_capacity_size,

	.modifiers.modify = string_modifiers_modify,
};

struct iterator_object_unit_s
	object_unit = {
	.object_ptr = string,
	.control_ptr = &object_control,
};

struct iterator_s *input_iterator = NULL;
struct iterator_s *random_access_iterator = NULL;
char *element = NULL;

void main_iterator(void)
{
	main_input_iterator();
	main_random_access_iterator();

	return;
}

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

void main_random_access_iterator(void)
{
	printf("\r\n ------------------------+ random_access_iterator demo start +------------------------\r\n");

	printf("\r\nrandom_access_iterator.configuration.init start\r\n");
	if (random_access_iterator_control.configuration.init(&random_access_iterator, object_unit)) {
		return;
	}

	printf("\r\nrandom_access_iterator.iterator_operations.prev start\r\n");
	element = random_access_iterator_control.iterator_operations.prev(random_access_iterator);
	printf("random_access_iterator.iterator_operations.prev:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\nrandom_access_iterator.iterator_operations.next start\r\n");
	element = random_access_iterator_control.iterator_operations.next(random_access_iterator);
	printf("random_access_iterator.iterator_operations.next:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\nrandom_access_iterator.iterator_operations.at start\r\n");
	element = random_access_iterator_control.iterator_operations.at(random_access_iterator, 23);
	printf("random_access_iterator.iterator_operations.at:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\nrandom_access_iterator.iterator_operations.modify start\r\n");
	element = (char *)random_access_iterator_control.iterator_operations.modify(random_access_iterator, "!");
	printf("random_access_iterator.iterator_operations.modify:%d \r\n"
		   , (size_t)element);

	printf("\r\nrandom_access_iterator.iterator_operations.advance start\r\n");
	element = random_access_iterator_control.iterator_operations.advance(random_access_iterator, -2);
	printf("random_access_iterator.iterator_operations.advance:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\nrandom_access_iterator.range_access.begin start\r\n");
	element = random_access_iterator_control.range_access.begin(random_access_iterator);
	printf("random_access_iterator.range_access.begin:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\nrandom_access_iterator.range_access.end start\r\n");
	element = random_access_iterator_control.range_access.end(random_access_iterator);
	printf("random_access_iterator.range_access.end:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\nrandom_access_iterator.range_access.size start\r\n");
	element = (char *)random_access_iterator_control.range_access.size(random_access_iterator);
	printf("random_access_iterator.range_access.size:%d \r\n"
		   , (size_t)element);

	printf("\r\nrandom_access_iterator.range_access.data start\r\n");
	element = random_access_iterator_control.range_access.data(random_access_iterator);
	printf("random_access_iterator.range_access.data:%p \r\n"
		   , (NULL == element) ? NULL : element);

	printf("\r\nrandom_access_iterator.configuration.destroy start\r\n");
	if (random_access_iterator_control.configuration.destroy(&random_access_iterator)) {
		return;
	}

	printf("\r\n ------------------------+ random_access_iterator demo end +------------------------ \r\n");
}

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

errno_t string_modifiers_modify(char string[],
								size_t index,
								void *source)
{
	return !memcpy(&string[index], source, 1);
}

#endif // MAIN_ITERATOR_EN