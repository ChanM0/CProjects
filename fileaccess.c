#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main (argc, argv)  int argc; char *argv[];
{
	int errors, k;
	struct stat buf;
	errors = 0;
	for (k=1; k < argc; k++) {
		if (stat(argv[k], &buf) == (-1)) {
			fprintf(stderr, "%s: cannot access %s\n", argv[0], argv[k]);
			errors++;
			continue;
		}
		
		if (buf.st_mode & 0400)
			printf("read");
		else
			printf("no read");
	}
	if (errors)
		exit(1);
	else
		exit(0);
}