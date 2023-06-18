#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <getopt.h>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "log_msg.h"
#include <stdarg.h>
#include <ctype.h>

#include "laba_M2_7.h"
//"123" === '1''2''3''\0'



char* fget_paragraph(FILE *f_ptr)
{
	char *file_line = NULL; /// returned ptr
	int   file_line_len = 0;


	const int line_piece_const_len = 10 + 1;
	char      line_piece[line_piece_const_len]; // '\0'  "123" == '1''2''3''\0'
	int       line_piece_len = 0;
	memset(line_piece, 0, line_piece_const_len);

	while (fgets(line_piece, line_piece_const_len, f_ptr)) {
		line_piece_len = strlen(line_piece);

		if ((line_piece_len == line_piece_const_len - 1) && (line_piece[line_piece_len - 1] != '\n')) {
			file_line_len += line_piece_len;
			file_line = (char *)realloc(file_line, (file_line_len + 1) * sizeof(char));
			memset(file_line + (file_line_len - line_piece_len), 0, (line_piece_len + 1) * sizeof(char));
			//*(file_line + (file_line_len - curet_piece_of_Fline)) = '\0';
			strcat(file_line, line_piece);
			// printD_var(file_line, s);
		} else {
			break;
		}
	}

	if (line_piece_len) {
		file_line_len += line_piece_len;
		file_line = (char *)realloc(file_line, (file_line_len + 1) * sizeof(char));
		memset(file_line + (file_line_len - line_piece_len), 0, (line_piece_len + 1) * sizeof(char));
		//*(file_line + (file_line_len - curet_piece_of_Fline)) = '\0';
		strcat(file_line, line_piece);
		// printD_var(file_line, s);
	}

	return file_line;
}

int do_laba_stuff_M2_7(char *file_path)
{
	// https://www.log2base2.com/C/pointer/realloc-in-c.html

	FILE *fptr = NULL;
	fptr = fopen(file_path, "rw+");
	if(!fptr) {
		printD("Could not open \"%s\" file for reading and writing.\n", file_path);
		exit(EXIT_FAILURE);
	}
	fseek(fptr, 0, SEEK_SET);

	char *file_content = NULL;//(char *)calloc(1, sizeof(char));
	int file_content_len = 0;//strlen(file_content);
	while (!feof(fptr)) {
		char *paragraph = NULL;
		paragraph = fget_paragraph(fptr);
		if (!paragraph) {
			break;
		}
		int paragraph_len = strlen(paragraph); // 1\n\0
											   // printD_var(paragraph_len, i);
		if (paragraph[paragraph_len-1] == '\n') {
			paragraph[paragraph_len-1]='\0'; // 1\0\0
		}
		printD_var(paragraph, s);
		if (paragraph[paragraph_len-1] == '\0') {
			paragraph[paragraph_len-1]='\n'; // 1\n\0
		}

		file_content_len += paragraph_len;
		file_content = (char *)realloc(file_content, (file_content_len + 1) * sizeof(char));
		memset(file_content + (file_content_len - paragraph_len), 0, (paragraph_len + 1) * sizeof(char));
		strcat(file_content, paragraph);
		// printD_var(file_content, s);

		free(paragraph);
	}
	fclose(fptr);

	printD_var(file_content, s);
	free(file_content);

	return 0;
}

