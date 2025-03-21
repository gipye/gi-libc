#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int vasprintf(char **restrict strp, const char *restrict fmt, va_list ap)
{
	va_list args_copy;
	char *new_buffer;
	int size;

	va_copy(args_copy, ap);
	size = vsnprintf(NULL, 0, fmt, args_copy);
	va_end(args_copy);
	if (size < 0)
		return -1;

	new_buffer = malloc(size + 1);
	if (new_buffer == NULL)
		return -1;

	if (vsnprintf(new_buffer, size + 1, fmt, ap) != size)
		return -1;

	*strp = new_buffer;

	return size;
}

int asprintf(char **restrict strp, const char *restrict fmt, ...)
{
	va_list ap;
	int ret;

	va_start(ap, fmt);
	ret = vasprintf(strp, fmt, ap);
	va_end(ap);

	return ret;
}
