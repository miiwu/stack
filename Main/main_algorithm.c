#include "algorithm.h"

#include "main_cfg.h"

void main_algorithm(void)
{
	printf("\r\n ------------------------+ algorithm.substring_search demo start +------------------------\r\n");

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

	printf("algorithm.search_substring.brute_force_algorithm:%f \r\n\r\n",
		   search_substring_control(BRUTE_FORCE_ALGORITHM, search_substring_package));

	printf("algorithm.search_substring.sunday_algorithm:%f \r\n\r\n",
		   search_substring_control(SUNDAY_ALGORITHM, search_substring_package));

	printf("\r\n ------------------------+ algorithm.substring_search demo end +------------------------ \r\n");

	printf("\r\n ------------------------+ algorithm.modify_sequence demo start +------------------------\r\n");

	int
		num_lhs = 1,
		num_rhs = 2;

	modify_sequence_control_swap(&num_lhs, &num_rhs, 1);
	printf("algorithm.modify_sequence.swap: lhs:%d rhs:%d \r\n",
		   num_lhs, num_rhs);

	printf("\r\n ------------------------+ algorithm.modify_sequence demo end +------------------------ \r\n");

	printf("\r\n ------------------------+ algorithm.sort demo start +------------------------\r\n");

	char
		string_lhs[] = "string_lhs",
		string_rhs[] = "string_rhs";

	char
		*sort_object[] = {
		string_lhs,
		string_rhs
	};

	struct sort_package_s
		sort_package = {
		.count = 2,
		.mem_len = sizeof(char*),
		.mem_len_key = sizeof(string_lhs),
		.object_ptr = sort_object,
		.compare_ptr = compare_control_lesser,
	};

	sort_control(STABLE_SORT, sort_package);
	printf("algorithm.modify_sequence.swap: lhs:\"%s\" rhs:\"%s\" \r\n",
		   sort_object[0], sort_object[1]);

	printf("\r\n ------------------------+ algorithm.sort demo end +------------------------ \r\n");

	return;
}