#include <stdio.h>

int main(int argc, char **argv) {
	char buf[4096];
	int cb = read(0, buf, sizeof(buf));
	buf[cb] = 0;
	strrev(buf);
	printf("200 OK\r\n");
	printf("Content-Type: text/plain\r\n");
	printf("Content-Length: %d\r\n", cb);
	printf("\r\n");
	printf(buf);
	return 0;
}
