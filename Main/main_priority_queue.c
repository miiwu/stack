#include "main_cfg.h"

#define MAIN_PRIORITY_QUEUE_CFG_ADAPT_VECTOR_EN				0u

#define MAIN_PRIORITY_QUEUE_CFG_ADAPT_FORWARD_LIST_EN		1u

#if (MAIN_PRIORITY_QUEUE_CFG_ADAPT_VECTOR_EN)

#define MAIN_PRIORITY_QUEUE_CONTAINER	VECTOR

#define MAIN_PRIORITY_QUEUE_CONTAINER_CONTROL	vector_ctrl

vector_tp priority_queue_container = NULL;

#endif // (MAIN_PRIORITY_QUEUE_CFG_ADAPT_VECTOR_EN)

#if (MAIN_PRIORITY_QUEUE_CFG_ADAPT_FORWARD_LIST_EN)

#define MAIN_PRIORITY_QUEUE_CONTAINER	FORWARD_LIST

#define MAIN_PRIORITY_QUEUE_CONTAINER_CONTROL	forward_list_ctrl

forward_list_stp priority_queue_container = NULL;

#endif // (MAIN_PRIORITY_QUEUE_CFG_ADAPT_FORWARD_LIST_EN)

void main_priority_priority_queue(void)
{
	//priority_queue_stp
	//	priority_queue = NULL,
	//	priority_queue_attach = NULL,
	//	priority_queue_copy = NULL;

	//char
	//	**string = calloc(1, sizeof(char **)),
	//	*string_start = "####",
	//	string_moudle[] = "priority_queue";

	//printf("\r\n ------------------------+ priority_queue demo start +------------------------ \r\n");

	//printf("priority_queue.init start\r\n");
	//priority_queue_ctrl.configuration.init(&priority_queue, MAIN_PRIORITY_QUEUE_CONTAINER, sizeof(string_moudle), NULL, NULL);		/* Initialize priority_queue,char[sizeof(string_moudle)] type */
	//MAIN_PRIORITY_QUEUE_CONTAINER_CONTROL.configuration.init(&priority_queue_container, sizeof(string_moudle), NULL, NULL);		/* Initialize priority_queue_container,char[sizeof(string_moudle)] type */
	//priority_queue_ctrl.configuration.attach(&priority_queue_attach, MAIN_PRIORITY_QUEUE_CONTAINER, priority_queue_container);

	//printf("\r\npriority_queue.max_size start\r\n");
	//printf("max size : %d \r\n    ", priority_queue_ctrl.capacity.max_size(priority_queue));

	//printf("\r\npriority_queue_attach.max_size start\r\n");
	//printf("max size : %d \r\n    ", priority_queue_ctrl.capacity.max_size(priority_queue_attach));

	//printf("\r\npriority_queue.push start\r\n");
	//for (size_t cnt = 0; cnt < 10; cnt++) {
	//	printf("push no.%d : \"%s\" \r\n", cnt, string_moudle);

	//	priority_queue_ctrl.modifiers.push(priority_queue, string_moudle);

	//	string_moudle[0] += 1;
	//}

	//printf("\r\npriority_queue.front start\r\n");
	//printf("front : \"%s\" \r\n", (char *)priority_queue_ctrl.element_access.front(priority_queue));

	//printf("\r\npriority_queue.back start\r\n");
	//printf("back : \"%s\" \r\n", (char *)priority_queue_ctrl.element_access.back(priority_queue));

	//printf("\r\npriority_queue & priority_queue_attach.copy priority_queue start\r\n");
	//priority_queue_ctrl.modifiers.copy(&priority_queue_attach, priority_queue);

	//printf("\r\npriority_queue_attach.pop start\r\n");
	//for (size_t cnt = 0; cnt < 10; cnt++) {
	//	printf("front no.%d : \"%s\" \r\n", cnt, (char *)priority_queue_ctrl.element_access.front(priority_queue_attach));
	//	priority_queue_ctrl.modifiers.pop(priority_queue_attach);
	//}

	//printf("\r\npriority_queue.destroy start\r\n");
	//priority_queue_ctrl.configuration.destroy(&priority_queue);

	//printf("\r\npriority_queue_attach.destroy start\r\n");
	//priority_queue_ctrl.configuration.destroy(&priority_queue_attach);

	//printf("\r\n ------------------------+ priority_queue demo end +------------------------\r\n");

	//return;
}