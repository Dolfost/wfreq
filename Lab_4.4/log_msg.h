#include <iostream>
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
// #include <log_msg.hpp>

#ifndef __LOG_MSG_FILE__
#define __LOG_MSG_FILE__

extern int __tub;
#if defined(__WIN_DIR_SLASH__)
#define __SLASH__ '\\'
#else
#define __SLASH__ '/'
#endif

#ifndef printD
#	if 0
#		define printD(...) { \
	char *ptr = (char *)strrchr(__FILE__, __SLASH__); \
	printf("[%s:%-3i]=> %s()=> ", ((ptr) ? ptr + 1 : __FILE__), __LINE__, __func__); } \
printf(__VA_ARGS__)
#	else
#		define printD printf
#	endif //if 1
#endif //ifndef printD

#ifndef __line_info
#define __line_info printD("\n")
#endif

#ifndef printD_var
#define printf_var(var, f) printf(#var"[%"#f"]\n", var)
#define printf_vnn(var, f) printf(#var"[%"#f"]"  , var)
#define printf_vnr(var, f) printf("[%"#f"]", var)
#define printD_var(var, f) printD(#var"[%"#f"]\n", var)	

#define LOGN_val_s(var) printD_var(var, s)
#define __new_line printf("\n")
#endif

#ifndef __start_func
#define __start_func printD("[+]\n")
// #define __start_func printf("")
#endif

#ifndef __end_func
#define __end_func printD("[-]\n")
// #define __end_func printf("")
#endif

#define pr_array(ptr, len, e_size, format) \
	__asm__ __volatile__("" ::: "memory"); \
{ \
	char __format[] = #format; \
	switch (__format[strlen(__format) - 1]) { \
		case 'f': {       float   *_ptr = (float   *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
		case 'c': {       char    *_ptr = (char    *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
		case 's': {       char   **_ptr = (char   **)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
		case 'i': { \
					  switch (e_size) { \
						  case 1: { int8_t  *_ptr = (int8_t  *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
						  case 2: { int16_t *_ptr = (int16_t *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
						  case 4: { int32_t *_ptr = (int32_t *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
					  } \
				  } break; \
		case 'u': { \
					  switch (e_size) { \
						  case 1: { uint8_t  *_ptr = (uint8_t  *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
						  case 2: { uint16_t *_ptr = (uint16_t *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
						  case 4: { uint32_t *_ptr = (uint32_t *)(ptr); for (uint32_t i = len; i; --i) { printf("[%"#format"]", *_ptr++); } }; break; \
					  } \
				  } break; \
	} \
} \
__asm__ __volatile__("" ::: "memory");

// Try:
// int masi[] = {1,2,3,15,4,5,6,7,8};
// float masf[] = {1,2,3,15,4,5,6,7,8};
// uint8_t masu8[] = {1,2,3,15,4,5,6,7,8};
// pr_array(&masf[0], sizeof(masf)/sizeof(float), sizeof(masf[0]), f); printf("\n");
// pr_array(&masf[0], sizeof(masf)/sizeof(uint8_t), sizeof(char), -3u); printf("\n");
// pr_array(&masu8[0], sizeof(masu8)/sizeof(uint8_t), sizeof(char), -3u); printf("\n");
// pr_array(&masu8[0], sizeof(masu8)/sizeof(uint8_t), sizeof(char), c); printf("\n");

#endif


// compiler=g++ ; ((mkdir -p out && rm -f `find ./out -maxdepth 1 -name \*.o`; for i in $(find . -maxdepth 1 -name \*.cpp); do echo "$i:"; ccache $compiler $i -O0 -ggdb -std=^Cu++11 -o ./out/$i.o -c; done; ccache $compiler $(find ./out -maxdepth 1 -name \*.o) -o ./out/res  -lstdc++ -lm) 2>&1)
