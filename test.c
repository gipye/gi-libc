#include <stdio.h>
#include "asprintf.h"
#include "cleanup.h"

int main(void)
{
	__cleanup_free__ char *buf = NULL;
	char *dev = "/dev/ttyUSB0";

	astrcatf(&buf, "/sys/class/tty/%s/ccc", dev);
	fprintf(stdout, "buf: %s\n", buf);

	astrcatf(&buf, "/ccc");
	fprintf(stdout, "buf: %s\n", buf);
}
