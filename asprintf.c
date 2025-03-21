#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "cleanup.h"

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

#define astrcatf(out, fmt, ...)						\
({									\
        char *tmp = *(out);						\
        int ret;							\
        ret = asprintf((out), "%s" fmt, tmp ?: "", ## __VA_ARGS__);	\
        if (ret < 0) {							\
        	tmp = NULL;						\
	}								\
        free(tmp);							\
        ret;								\
})

static inline int astrcat(char **out, const char *add)
{
        char *tmp = *out;
        int ret;

        ret = asprintf(out, "%s%s", tmp ?: "", add);
        if (ret < 0)
        	return ret;

        free(tmp);
        return ret;
}

int main(void)
{
	__cleanup_free__ char *buf = NULL;
	char *dev = "/dev/ttyUSB0";

	astrcatf(&buf, "/sys/class/tty/%s/ccc", dev);
	fprintf(stdout, "buf: %s\n", buf);

	astrcatf(&buf, "/ccc");
	fprintf(stdout, "buf: %s\n", buf);
}
