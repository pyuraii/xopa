#include <stdio.h>
#include <stdlib.h>

void error(const char *string) {
	fprintf(stderr, "%s\n", string);
	exit(-1);
}

int main(int argc, char *argv[]) {
	int count = 99;

	if (argc == 2) count = atoi(argv[1]);
	else if (argc > 2) error("Too many arguments!");

	while (count > 1) {
		printf("%d bottles of beer on the wall, "
		       "%d bottles of beer.\n", count, count);

		printf("Take one down, pass it around, "
		       "%d bottles of beer on the wall.\n\n", count, count, --count);
	}
	
	printf("1 bottle of beer on the wall, "
	       "1 bottle of beer.\n"
	       "Take one down and pass it around, "
	       "no more bottles of beer on the wall.\n\n"

	       "No more bottles of beer on the wall, "
	       "no more bottles of beer.\n"
	       "Go to the store and buy some more, "
	       "99 bottles of beer on the wall.\n\n"
	);

	return 0;
}
