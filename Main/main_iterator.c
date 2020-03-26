#include "iterator.h"

#include "main_cfg.h"

void *string_element_access_at(char string[],
							   size_t position);
void *string_element_access_data(char string[]);
bool string_capacity_empty(char string[]);
size_t string_capacity_max_size(char string[]);
size_t string_capacity_size(char string[]);

void main_iterator(void)
{
	printf("\r\n ------------------------+ iterator demo start +------------------------\r\n");

	char string[] = "this is a iterator test.";

	struct iterator_object_control_s
		object_control = {
		.element_access.at = string_element_access_at,
		.element_access.data = string_element_access_data,

		.capacity.empty = string_capacity_empty,
		.capacity.max_size = string_capacity_max_size,
		.capacity.size = string_capacity_size,
	};

	struct iterator_object_unit_s
		object_unit = {
		.object_ptr = string,
		.control_ptr = &object_control,
	};

	struct iterator_s *iterator = NULL;
	char *element = NULL;

	printf("\r\n ------------------------+ iterator.configuration.init start +------------------------\r\n");
	if (random_access_iterator_control.configuration.init(&iterator, object_unit)) {
		return;
	}

	printf("\r\niterator.iterator_operations.prev start\r\n");
	element = random_access_iterator_control.iterator_operations.prev(iterator);
	printf("iterator.iterator_operations.prev:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\niterator.iterator_operations.next start\r\n");
	element = random_access_iterator_control.iterator_operations.next(iterator);
	printf("iterator.iterator_operations.next:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\niterator.iterator_operations.at start\r\n");
	element = random_access_iterator_control.iterator_operations.at(iterator, 8);
	printf("iterator.iterator_operations.at:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\niterator.iterator_operations.advance start\r\n");
	element = random_access_iterator_control.iterator_operations.advance(iterator, -2);
	printf("iterator.iterator_operations.advance:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\niterator.range_access.begin start\r\n");
	element = random_access_iterator_control.range_access.begin(iterator);
	printf("iterator.range_access.begin:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\niterator.range_access.end start\r\n");
	element = random_access_iterator_control.range_access.end(iterator);
	printf("iterator.range_access.end:\"%c\" \r\n"
		   , (NULL == element) ? '?' : *element);

	printf("\r\niterator.range_access.size start\r\n");
	element = (char *)random_access_iterator_control.range_access.size(iterator);
	printf("iterator.range_access.size:%d \r\n"
		   , (NULL == element) ? '?' : (size_t )element);

	printf("\r\niterator.range_access.data start\r\n");
	element = random_access_iterator_control.range_access.data(iterator);
	printf("iterator.range_access.data:%p \r\n"
		   , (NULL == element) ? NULL : element);

	printf("\r\n ------------------------+ iterator.configuration.destroy start +------------------------\r\n");
	if (random_access_iterator_control.configuration.destroy(&iterator)) {
		return;
	}

	printf("\r\n ------------------------+ iterator demo end +------------------------ \r\n");

	return;
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