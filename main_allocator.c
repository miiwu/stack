#include "main_cfg.h"

void main_allocator(void)
{
	ALLOCATOR_TYPEDEF_PTR
		allocator = { NULL };

	printf("\r\n ------------------------+ allocator demo start +------------------------\r\n");

	printf("\r\nallocator.init start\r\n");
	allocator_ctrl.configration.init(&allocator, NULL);

	printf("\r\nallocator.allocate start\r\n");
	allocator_ctrl.allocate(allocator, 1, 1);

	printf("\r\nallocator.destroy start\r\n");
	allocator_ctrl.configration.destroy(&allocator);

	printf("\r\n ------------------------+ allocator demo end +------------------------\r\n");

	return;
}