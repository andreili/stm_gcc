#include "my_func.h"

int strlen(const char* str)
{
	int len = 0;
	while (*str++)
		++len;
	return len;
}

void memcpy(char* dst, const char* src, int len)
{
	while (len--)
		*dst++ = *src++;
}
