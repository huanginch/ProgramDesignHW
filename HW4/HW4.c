#include <stdio.h>

unsigned short swap_bytes(unsigned short i);//swap function

int main(void){
	unsigned short input; //user input
	scanf("%hx", &input);

	input = swap_bytes(input);
	printf("%hx\n", input);
}

unsigned short swap_bytes(unsigned short i){

	return ((i << 8) & 0xff00 | (i >> 8) & 0x00ff);
}
