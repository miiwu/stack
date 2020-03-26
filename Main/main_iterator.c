#include "iterator.h"

#include "main_cfg.h"

void *string_element_access_at(char string[],
							   size_t position);
bool string_capacity_empty(char string[]);
size_t string_capacity_max_size(char string[]);
size_t string_capacity_size(char string[]);

void main_iterator(void)
{
	printf("\r\n ------------------------+ iterator demo start +------------------------\r\n");

	char string[] = "this is a iterator test\r\n";

	struct iterator_object_control_s
		object_control = {
		.element_access.at = string_element_access_at,

		.capacity.empty = string_capacity_empty,
		.capacity.max_size = string_capacity_max_size,
		.capacity.size = string_capacity_size,
	};

	struct iterator_object_unit_s
		object_unit = {
		.object_ptr = string,
		.control_ptr = &object_control,
	};

	iterator_stp iterator = NULL;
	char *element = NULL;

	printf("\r\n ------------------------+ iterator.configuration.init start +------------------------\r\n");
	if (iterator_control.configuration.init(&iterator, object_unit)) {
		return;
	}

	printf("\r\niterator.iterator_operations.prev start\r\n");
	element = iterator_control.iterator_operations.prev(iterator);
	printf("iterator.iterator_operations.prev:\"%c\" \r\n"
		   , (NULL == element) ? '\0' : *element);

	printf("\r\niterator.iterator_operations.next start\r\n");
	element = iterator_control.iterator_operations.next(iterator);
	printf("iterator.iterator_operations.next:\"%c\" \r\n"
		   , (NULL == element) ? '\0' : *element);

	printf("\r\n ------------------------+ iterator demo end +------------------------ \r\n");

	return;
}

void *string_element_access_at(char string[],
							   size_t position)
{
	return &string[position];
}

bool string_capacity_empty(char string[])
{
	return sizeof(string);
}

size_t string_capacity_max_size(char string[])
{
	return sizeof(string);
}

size_t string_capacity_size(char string[])
{
	return sizeof(string);
}