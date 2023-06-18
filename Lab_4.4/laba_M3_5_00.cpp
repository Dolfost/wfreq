#include <iostream>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include "laba_M3_5.h"
#include "log_msg.h"
#include "laba_M2_7.h"

size_t strlen(const uint8_t* in) {
	size_t result;

	for (result = 0; *(in + result) != '\0'; result++);

	return result - 1;
}

uint32_t simple_hash_func_add_leters(const uint8_t* key)
{
	uint32_t hash = 0;
	uint32_t str_len = strlen(key);
	for (int i = str_len; i; --i, ++key) {
		hash += (*((uint8_t*)key) << (((i - 1) % 4)*8));
	}
	return hash;
}

uint32_t jenkins_one_at_a_time_hash(const char *s)
{
	uint32_t hash = 0;
	for(; *s; ++s)
	{
		hash += *s;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

char *get_file_content(char *file_path)
{
	FILE *fptr = NULL;
	fptr = fopen(file_path, "rw+");
	if(!fptr) {
		printD("Could not open \"%s\" for reading and writing.\n", file_path);
		exit(EXIT_FAILURE);
	}
	fseek(fptr, 0, SEEK_SET);

	char *file_content = NULL;
	int file_content_len = 0;
	while (!feof(fptr)) {
		char *paragraph = NULL;
		paragraph = fget_paragraph(fptr);
		if (!paragraph) {
			break;
		}
		int paragraph_len = strlen(paragraph);
		if (paragraph[paragraph_len-1] == '\n') {
			paragraph[paragraph_len-1]=' ';
		}

		file_content_len += paragraph_len;
		file_content = (char *)realloc(file_content, (file_content_len + 1) * sizeof(char));
		memset(file_content + (file_content_len - paragraph_len), 0, (paragraph_len + 1) * sizeof(char));
		strcat(file_content, paragraph);

		free(paragraph);
	}
	// printD_var(file_content, s);
	fclose(fptr);
	return file_content;
}


void do_laba_stuff_M3_5(char *fname, int sort_by_frq, int sort_by_asc)
{
	uint32_t (*hash_func_add_leters)(const char* key);
	// hash_func_add_leters = &simple_hash_func_add_leters;
	hash_func_add_leters = &jenkins_one_at_a_time_hash;

	char *file_content = get_file_content(fname);
	int file_content_len = strlen(file_content);
	printD_var(file_content, s);

	int space_counter = 1;
	for (size_t i = 0; i < file_content_len; i++) {
		if (file_content[i] == ' ') {
			++space_counter;
		}
	}

	char **words = (char **)calloc(space_counter, sizeof(char*));
	memset(words, 0, space_counter * sizeof(char*));
	int words_len = 0; // less or eq [space_counter]


	char *token = strtok(file_content, " ");
	while (token) {
		printD_var(token, s);
		words[words_len] = token;
		++words_len;
		char *prev_token = token;
		token = strtok(NULL, " ");
	}

	// for (size_t i = 0; i < words_len; i++) {printD_var(words[i], s);}


	int hash_table_len = space_counter * 2.7f;
	int *hash_table = (int *)calloc(hash_table_len, sizeof(int));
	memset(hash_table, 0, hash_table_len * sizeof(int));

	for (size_t i = 0; i < words_len; i++) {
		int hash_index = hash_func_add_leters(words[i]) % hash_table_len;
		hash_table[hash_index] = hash_table[hash_index] + 1;
	}

	// print all strings
	// for (size_t i = 0; i < words_len; i++) {
	// 	int hash_index = hash_func_add_leters(words[i]) % hash_table_len;
	// 	printD("[%10s] [%i]\n", words[i], hash_table[hash_index]);
	// }

	__new_line;
	pr_array(words, words_len, sizeof(char*), -6s);
	__new_line;
	for (size_t i = 0; i < words_len; i++) {
		for (size_t j = i + 1; j < words_len; j++) {
			if (words[i] == NULL || words[j] == NULL) {
				continue;
			}
			//let's remove all links to equivalent strings.
			if (strcmp(words[i], words[j]) == 0) {
				words[j] = NULL;
			}
		}
	}
	pr_array(words, words_len, sizeof(char*), -6s);
	__new_line;
	__new_line;

	printD_var(sort_by_asc, i);
	printD_var(sort_by_frq, i);
	__new_line;

	for (size_t i = 0; i < words_len; i++) {
		for (size_t j = i + 1; j < words_len; j++) {
			if (words[i] == NULL || words[j] == NULL) {
				continue;
			}

			// sorting words by ascending in a frq way:
			if (sort_by_frq != 0 && sort_by_asc == 0) {
				int hash_index;
				hash_index = hash_func_add_leters(words[i]) % hash_table_len;
				int word_i_num = hash_table[hash_index];
				hash_index = hash_func_add_leters(words[j]) % hash_table_len;
				int word_j_num = hash_table[hash_index];

				switch (sort_by_frq) {
					case -1: {
								 if (word_i_num < word_j_num) {
									 char *tmp = words[j];
									 words[j] = words[i];
									 words[i] = tmp;
								 }
							 }
							 break;

					case 1: {
								if (word_i_num > word_j_num) {
									char *tmp = words[j];
									words[j] = words[i];
									words[i] = tmp;
								}
							}
							break;
				}
			}

			if (strlen(words[i]) > strlen(words[j]) && sort_by_asc) {
				char *tmp = words[j];
				words[j] = words[i];
				words[i] = tmp;
			}
		}
	}

	__new_line;
	pr_array(words, words_len, sizeof(char*), -6s);
	__new_line;__new_line;

	for (size_t i = 0; i < words_len; i++) {
		if (words[i] == NULL) {
			continue;
		}
		int hash_index = hash_func_add_leters(words[i]) % hash_table_len;
		printD("[%10s] [%i]\n", words[i], hash_table[hash_index]);
	}

	// for (size_t i = 0; i < file_content_len; i++) {
	// 	if (file_content[i] == '\0') {
	// 		file_content[i] = ' ';
	// 	}
	// }
	// printD_var(file_content, s);

	free(words);
	free(file_content);
}
