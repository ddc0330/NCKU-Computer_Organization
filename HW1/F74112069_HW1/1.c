#include <stdio.h>
int main(){
	int a, b;
	FILE *input = fopen("../input/1.txt", "r");
	fscanf(input, "%d %d", &a, &b);
	fclose(input);
	asm volatile(
		"div %[a], %[a], %[b]\n\t" //main code a=a/b
		:[a] "+r"(a) //OutputOperands, "=r" write，"+r" write/read
		:[b] "r"(b) //InputOperands, read
	);
	printf("%d\n", a);
	return 0;
}


