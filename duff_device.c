#include <stdio.h>

//duff's device
void duffs_device(const char *src, int length, char *dst) {
	int n = (length + 7) / 8;
	switch (length % 8) {
		case 0:	do {	*dst++ = *src++;
		case 7:			*dst++ = *src++;
		case 6:			*dst++ = *src++;
		case 5:			*dst++ = *src++;
		case 4:			*dst++ = *src++;
		case 3:			*dst++ = *src++;
		case 2:			*dst++ = *src++;
		case 1:			*dst++ = *src++;
				} while (--n > 0);
	}
}

int main() {
	char src[100] = "this is source! Don't copy this part.";
	char dst[100] = {};

	duffs_device(src, 15, dst);

	//verify
	printf("%s\n", dst);

	return 0;
}