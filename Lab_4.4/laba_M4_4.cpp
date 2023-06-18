#include <iostream>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include "laba_M4_4.h"
#include "laba_M3_5.h"
#include "log_msg.h"


int main_laba_M4_4(int argc, char *argv[])
{
	///\ MAIN GOAL:
	///\ is to print time like "YY/MM/DD HH:MN:SC"
	///\ HINT: strlen("YY_MM_DD HH:MN:SC") + 1 = 18

	int time_compute_var = 0, sort_by_frq = 0, sort_by_asc = 0;
	int opt_rez = 0;
	int maxres = INT_MAX;
	char *fname = NULL;
	while ((opt_rez = getopt(argc, argv, "?hf:s:am:")) != -1) { 
		switch (opt_rez) {
			case '?': {
						  fprintf(stderr, "Unknown option: '%c'\n", opt_rez);
						  exit(EXIT_FAILURE);
					  }
					  break;

			case 'v': {
						  time_compute_var = 1;
					  }break;

			case 's': {
						  sort_by_frq = atoi(optarg); //1 in order -1 otherwise 0
						  if (sort_by_frq > 1 || sort_by_frq < -1) {
							  sort_by_frq = 0;
						  }
					  }break;

			case 'a': {
						  sort_by_asc = 1;
					  }break;

			case 'm': {
						  maxres = atoi(optarg);
					  }break;

			case 'f': {
						  fname = (char *)calloc(strlen(optarg) + 1, sizeof(char));
						  if (!fname) {
							  printD("Could not allocate memory.\n");
							  exit(EXIT_FAILURE);
						  }
						  strcat(fname, optarg);
					  }
					  break;

			case 'h': {
						  printf("This is a help. You won't find any useful info here.\n"
								  "But you can play some games\n"
								  "\n"
								  "Example:\n"
								  "./out -f file_path -c 5 -r 5\n");
						  exit(EXIT_SUCCESS);
					  }
					  break;
		}
	}

	time_t start;
	if (time_compute_var) {
		start = time(NULL);
	}

	do_laba_stuff_M4_4(fname, sort_by_frq, sort_by_asc, maxres);
	free(fname);

	if (time_compute_var) {
		printD("%li [sec]\n", time(NULL) - start);
	}

	return 0;
}

// mkdir -p out; rm -rf ./out/*; for i in $(find . -name \*.cpp); do g++ -O0 -ggdb -o out/$i.o -c ./$i; done; g++ $(find . -name *.o) -o ./out/res -lpthread -pthread -lstdc++ -lm
