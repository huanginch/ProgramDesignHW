#include <stdio.h>

int main(void){
	int input; //the input number
	int i;
	scanf("%d", &input);
	for(i = 2; i <= input; i++){
		while(input%i == 0){
			printf("%d ", i);
			input = input/i;
		}
	}
}
