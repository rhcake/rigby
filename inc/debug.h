#include <stdio.h>

#ifdef _RIGBY_DEBUG_
	#define logln(...)	(printf(__VA_ARGS__), printf("\n"))
#else
	#define logln(...)
#endif