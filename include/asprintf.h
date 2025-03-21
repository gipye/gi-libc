#pragma once

#include <stdlib.h>
#include <stdarg.h>

int vasprintf(char **restrict strp, const char *restrict fmt, va_list ap);
int asprintf(char **restrict strp, const char *restrict fmt, ...);

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
