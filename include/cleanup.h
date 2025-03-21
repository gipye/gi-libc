#pragma once

#include <stdlib.h>

static inline void freep(void *p)
{
	free(*(void **)p);
}
#define __cleanup_free__ __attribute__((__cleanup__(freep)))
