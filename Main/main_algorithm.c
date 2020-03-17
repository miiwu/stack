#include "algorithm.h"

#include "main_cfg.h"

void main_algorithm(void)
{
	char
		string[] = "substring searching algorithm",
		substring[] = "search";

	printf("\r\n ------------------------+ algorithm demo start +------------------------\r\n");

	printf("algorithm.substring_search:%f \r\n", substring_search_control_sunday_algorithm(string,
																						   strlen(string),
																						   substring,
																						   strlen(substring)));

	printf("\r\n ------------------------+ algorithm demo end +------------------------ \r\n");

	return;
}