#include <string.h>

size_t strlen(const char *str)
{
	register char * i;

	for (i = str; *i; i++);
	return i - str;
}
