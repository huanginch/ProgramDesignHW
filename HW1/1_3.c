#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define wordLEN 100
#define wordNum_max 100

void cmpPrefix(char str1[], char str2[], char LCP[]); //compare two string's longest prefix
void toLower(char str[wordNum_max][wordLEN + 1], int row); //change 2D array to lower case

int main(void){
	int i, j;//use for the loop
	int caseNum = 0, wordNum = 0; //caseNum-> case 1 or case 2, wordNum-> the number of input words
	//char tmp_LCP[wordLEN]; // the temp LCP to save the cmpared result of two string 
	char LCP[wordLEN];//the array to save longest common prefix

	// read the case number and word number	
	scanf("%d\n", &caseNum);
	scanf("%d\n", &wordNum);
	
	char words[wordNum_max][wordLEN + 1];// the input words

	//init the array
	for(i = 0; i < wordLEN; i++){
		
		LCP[i] = '\0';

		for(j = 0; j < wordNum_max; j++){
			words[i][j] = '\0';
		}
	}
	
	//read the words
	for(i = 0; i < wordNum; i++){
		
		scanf("%s[^\n]", words[i]);
	}

	//change to lower case
	if(caseNum == 2){
		toLower(words, wordNum);
	}

	//find the Longest Common Prefix
	
	cmpPrefix(words[0], words[1], LCP);

	for(i = 2; i < wordNum; i++){
		cmpPrefix(words[i], LCP, LCP);
		//use the last result to compare with the next word
	}
	if(strcmp(LCP, "\0")){
		printf("%s\n", LCP);
	}
	else{
		printf("No longest common prefix\n");
	}
}


void cmpPrefix(char str1[], char str2[], char LCP[]){
	
	int i = 0, count = 0;// count use for record the LCP's location
	int cmpLEN = 0;// the max length of these two string
	char tmp_LCP[wordLEN];

	for(i = 0; i < wordLEN; i++){
		tmp_LCP[i] = '\0';
	}

	if(strlen(str1) > strlen(str2)){
		cmpLEN = strlen(str2);
	}
	else{
		cmpLEN = strlen(str1);
	}

	for(i = 0; i < cmpLEN; i++){

		if( str1[i] == str2[i] ){
			tmp_LCP[i] = str1[i];
			count++;
		}
		else{
			tmp_LCP[i] = '\0';
			break;
		}

	}

	strcpy(LCP, tmp_LCP);
}

void toLower(char str[wordNum_max][wordLEN + 1], int row){
	
	int i, j;

	for(i = 0; i < row; i++){
		for(j = 0; j < strlen(str[i]); j++){
			str[i][j] = tolower(str[i][j]);
		}
	}
}
