#include "algorithm.h"

#include "main_cfg.h"

void main_algorithm(void)
{
	char
		string[] = "substring searcing algorithm",
		substring[] = "search";

	printf("\r\n ------------------------+ algorithm demo start +------------------------\r\n");

	printf("algorithm.substring_search.brute_force_algorithm:%f \r\n",
		   substring_search_control_brute_force_algorithm(string,
														  strlen(string),
														  substring,
														  strlen(substring)));

	printf("algorithm.substring_search.sunday_algorithm:%f \r\n",
		   substring_search_control_sunday_algorithm(string,
													 strlen(string),
													 substring,
													 strlen(substring)));

	printf("\r\n ------------------------+ algorithm demo end +------------------------ \r\n");

	return;
}