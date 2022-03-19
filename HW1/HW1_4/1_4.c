#include <stdio.h>
#include <string.h>

#define MAXWORD 100000 // max word number in a sentence
#define MAXWORDLEN 50 //max length of a word

int wordcmp(char sentence[MAXWORD][MAXWORDLEN], char word[]); // to compare the word and sentence
void initArr(char arr[]); // init the array
void init2DArr(char arr[MAXWORD][MAXWORDLEN]); // init the 2D array

int main(void){
	char inputWord[MAXWORDLEN], chara;//the inputWord and the character of the input article
	char sentence[MAXWORD][MAXWORDLEN]; //the input sentence
	int i = 0, j = 0;
	
	initArr(inputWord);
	init2DArr(sentence);
	
	//read the sentence
	while( (chara = getchar()) != '\n' ){
		
		if(chara != ' '){ 
			sentence[i][j] = chara;
			j++;
		}
		else{ //meet the end of the word
			sentence[i][j] = '\0';
			i++;
			j = 0;
		}
	}

	sentence[i][j] = '\0'; //put \0 to the end of the last word
	

	scanf("%s", inputWord);
	printf("%s\n", inputWord);
	
	int SpecNum = 0; //the number of specific word
	SpecNum = wordcmp(sentence, inputWord);

	printf("%d\n", SpecNum);

}

int wordcmp(char sentence[MAXWORD][MAXWORDLEN], char word[]){

	int i, j;
	int count = 0; //count the number of specific word

	for(i = 0; i < MAXWORD; i++){

		if(strlen(sentence[i]) != strlen(word)){
			continue;
		}
		
		for(j = 0; j < strlen(word); j++){
			if(sentence[i][j] != word[j]){
				break;
			}
			
			if(j == strlen(sentence[i]) - 1){
				count++;
			}
		}
	}

	return count;
}

void initArr(char arr[]){
	int i;
	for(i = 0; i < strlen(arr); i++){
		arr[i] = '\0';
	}
}

void init2DArr(char arr[MAXWORD][MAXWORDLEN]){
	int i, j;

	for(i = 0; i < MAXWORD; i++){
		for(j = 0; j < MAXWORDLEN; j++){
			arr[i][j] = '\0';
		}
	}
}
