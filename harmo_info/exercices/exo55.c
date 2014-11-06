#include <stdio.h>
#include <stdlib.h>

void print_line(int val, int nb_spaces) {
	int i;
		
	for(i=0;i<nb_spaces;i++) {
		printf("  ");
	}
	for(i=1;i<val;i++) {
		printf("%d ", i);
	}
	for(i=val;i>=1;i--) {
		printf("%d ", i);
	}
}

int main() {
	int nb_lines = 10;
	int i;

	for(i=1;i<nb_lines;i++) {
		print_line(i, nb_lines-i);
		print_line(i, nb_lines-i);
		printf("\n");
	}

return 0;
}
