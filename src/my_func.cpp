#include "my_func.h"

int strlen(const char* str)
{
	int len = 0;
	while (*str++ != '\0')
		++len;
	return len;
}

void memcpy(char* dst, const char* src, int len)
{
	for (int i=0 ; i<len ; ++i)
		*dst++ = *src++;
}
