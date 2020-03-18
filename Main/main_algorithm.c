#include "algorithm.h"

#include "main_cfg.h"

void main_algorithm(void)
{
	char
		string[] = "substring searching algorithm",
		substring[] = "search";

	struct substring_search_package_s
		substring_search_package = {
		.str.string = string,
		.str.length = strlen(string),
		.substr.string = substring,
		.substr.length = strlen(substring)
	};

	printf("\r\n ------------------------+ algorithm demo start +------------------------\r\n");

	printf("algorithm.substring_search.brute_force_algorithm:%f \r\n\r\n",
		   substring_search_control(BRUTE_FORCE_ALGORITHM, substring_search_package));

	printf("algorithm.substring_search.sunday_algorithm:%f \r\n\r\n",
		   substring_search_control(SUNDAY_ALGORITHM, substring_search_package));

	printf("\r\n ------------------------+ algorithm demo end +------------------------ \r\n");

	return;
}