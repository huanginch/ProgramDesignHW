#include <stdio.h>
#include <string.h>

void toUpper(char str[]);//to upper case
void toLower(char str[]);//to lower case
void toWave(char str[]);//to wave case(upper -> lower -> upper)

int main(void){
	char input[100000]; //the input string
	int funcNum; //the function number user called

	scanf("%s", input);
	scanf("%d", &funcNum);

	if(funcNum == 1){
		toUpper(input);
	}
	else if(funcNum == 2){
		toLower(input);
	}
	else if(funcNum == 3){
		toWave(input);
	}
	
}

void toUpper(char str[]){
	int i;
	for(i = 0; i < strlen(str); i++){
		if(str[i] >= 97){
			str[i] = str[i] - 32;
		}

		printf("%c", str[i]);
	}

}

void toLower(char str[]){

	int i;
	for(i = 0; i < strlen(str); i++){
		if(str[i] <= 90){
			str[i] = str[i] + 32;
		}

		printf("%c", str[i]);
	}
}

void toWave(char str[]){

	int i;
	for(i = 0; i < strlen(str); i++){

		if((i%2 == 0) && (str[i] >= 97)){//the even is lower case
			str[i] = str[i] - 32;
		}
		
		if((i%2 !=0) && (str[i]) <= 90){//the odd is upper case
			str[i] = str[i] + 32;
		}

		printf("%c", str[i]);
	}

}
