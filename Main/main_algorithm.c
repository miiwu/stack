#include "algorithm.h"

#include "main_cfg.h"

void main_algorithm(void)
{
	printf("\r\n ------------------------+ algorithm.substring_search demo start +------------------------\r\n");

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

	printf("algorithm.substring_search.brute_force_algorithm:%f \r\n\r\n",
		   substring_search_control(BRUTE_FORCE_ALGORITHM, substring_search_package));

	printf("algorithm.substring_search.sunday_algorithm:%f \r\n\r\n",
		   substring_search_control(SUNDAY_ALGORITHM, substring_search_package));

	printf("\r\n ------------------------+ algorithm.substring_search demo end +------------------------ \r\n");

	printf("\r\n ------------------------+ algorithm.modify_sequence demo start +------------------------\r\n");

	int
		num_lhs = 1,
		num_rhs = 2;

	modify_sequence_control_swap(&num_lhs, &num_rhs, 1);
	printf("algorithm.modify_sequence.swap: lhs:%d rhs:%d \r\n",
		   num_lhs, num_rhs);

	printf("\r\n ------------------------+ algorithm.modify_sequence demo end +------------------------ \r\n");

	return;
}