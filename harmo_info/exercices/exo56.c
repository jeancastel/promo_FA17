#include <stdio.h>
#include <stdlib.h>

void find_div(int val) {
	int i;
	int j = 0;
	int tab_div[100];
	
	int val_moit = val/2;

	for(i=0;i<val_moit;i++) {
		printf("debug : %d", i);
		if(val%i == 0) tab_div[j] = i;
		j++;
	}

	printf("Diviseurs de %d : ", val);
	for(i=0;i<val;i++) {
		printf(" %d", tab_div[i]);
	}

}

int main() {

int value;

printf("valeur : ");
scanf("%d", &value);

printf("\ndebug");
find_div(value);

return 0;
}
