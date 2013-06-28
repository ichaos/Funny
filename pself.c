#include <stdio.h>
char b = 0x22;char n = 0xa;char *c="#include <stdio.h>%cchar b = 0x22;char n = 0xa;char *c=%c%s%c;void main(){printf(c, n, b, c, b);}";void main(){printf(c, n, b, c, b);}

/*
 * print message: 
#include <stdio.h>
char b = 0x22;char n = 0xa;char *c="#include <stdio.h>%cchar b = 0x22;char n = 0xa;char *c=%c%s%c;void main(){printf(c, n, b, c, b);}";void main(){printf(c, n, b, c, b);}
 */
