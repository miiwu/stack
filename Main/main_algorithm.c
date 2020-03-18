#include "algorithm.h"

#include "main_cfg.h"

void main_algorithm(void)
{
	char
		string[] = "substring searching algorithm",
		substring[] = "search";

	struct search_substring_package_s
		search_substring_package = {
		.str.string = string,
		.str.length = strlen(string),
		.substr.string = substring,
		.substr.length = strlen(substring)
	};

	printf("\r\n ------------------------+ algorithm demo start +------------------------\r\n");

	printf("algorithm.search_substring.brute_force_algorithm:%f \r\n\r\n",
		   search_substring_control(BRUTE_FORCE_ALGORITHM, search_substring_package));

	printf("algorithm.search_substring.sunday_algorithm:%f \r\n\r\n",
		   search_substring_control(SUNDAY_ALGORITHM, search_substring_package));

	printf("\r\n ------------------------+ algorithm demo end +------------------------ \r\n");

	return;
}