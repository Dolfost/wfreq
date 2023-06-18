#include <iostream>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <unordered_map>

#include "laba_M4_4.h"
#include "laba_M3_5.h"
#include "laba_M2_7.h"
#include "log_msg.h"

void do_laba_stuff_M4_4(char *fname, int sort_by_frq, int sort_by_asc, int maxres)
{

	char *ptr = get_file_content(fname);
	std::string file_content(ptr);
	free(ptr);

	/*  створимо хештаблицю слів:  */
	std::unordered_map<std::string, int> hash_table;

	/*  створимо масив вказівників на слова:  */
	//char* file_content_char = strdup(file_content.c_str());
	char *token = strtok((char*)file_content.c_str(), " \t\n,.?!\"';@#$%^&*()-+={}[]\\/`~");
	while (token) {
		hash_table[std::string(token)]++; //words.push_back(token); // printD_var(words.back(), -6s);
		token = strtok(NULL, " ,\t\n.?!\":;@#$%^&*()-+={}[]\\/`~");
	}

	file_content.clear(); // про всяк випадок

	std::vector<std::pair<std::string, int>> hash_table_vec(hash_table.begin(), hash_table.end());

	for (std::vector<std::pair<std::string, int>>::iterator i = hash_table_vec.begin(); i != hash_table_vec.end(); i++) {
		for (std::vector<std::pair<std::string, int>>::iterator j = hash_table_vec.begin(); j != hash_table_vec.end(); j++) {
			switch (sort_by_frq) {
				case -1: {
							 if (i->second < j->second) {
								 std::swap(j->first, i->first);
								 std::swap(j->second, i->second);
							 }
						 } continue;

				case 1: {
							if (i->second > j->second) {
								std::swap(j->first, i->first);
								std::swap(j->second, i->second);
							}
						} continue;
			}

			if (sort_by_asc && strlen(i->first.c_str()) > strlen(j->first.c_str())) {
				std::swap(j->first, i->first);
				std::swap(j->second, i->second);
			}
		}
	}

	/** Друкуємо  хэштейбл (сортований): */
	int i = 0;
	for (auto it = hash_table_vec.cbegin(); it != hash_table_vec.cend() && i < maxres; ++it, i++) {
		printf("%s %i\n", it->first.c_str(), it->second);
	}
}
