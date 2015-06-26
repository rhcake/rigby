#include <stdio.h>

#ifdef _RIGBY_DEBUG_
	#define log(...)	(printf(__VA_ARGS__), printf("\n"))
#else
	#define log(...)
#endif