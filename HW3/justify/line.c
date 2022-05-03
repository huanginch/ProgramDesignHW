#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line.h"
#define MAX_LINE_LEN 60
#define MAX_WORD_LEN 20
 
//char line[MAX_LINE_LEN+1];

struct word{
	char content[MAX_WORD_LEN + 1];
	struct word *next;
};

struct word *line = NULL; //the head of the line
int line_len = 0;
int num_words = 0;
 
void clear_line(void)
{
  	line_len = 0;
  	num_words = 0;

	if(line != NULL){
		//free the list
		struct word *current = line;
		struct word *next = line->next;
		while(next != NULL){
			free(current);
			current = next;
			next = current->next;
		}

		line = NULL;
	}	

}

void add_word(const char *word)
{
	//create new word
	struct word *new_word = malloc(sizeof(struct word));
	strncpy(new_word->content, word, strlen(word));
	new_word->content[strlen(word)] = '\0';
	new_word->next = NULL;

	if(line == NULL){
		//the list is empty
		line = new_word;
	}
	else{
		//find the last word
		struct word *current = line;
		while(current->next != NULL){
			//find the end of the list
			current = current->next;
		}

		current->next = new_word;
		
		//including the space
		line_len++;
	}

	line_len += strlen(word);
	num_words++;
}
 
int space_remaining(void)
{
  return MAX_LINE_LEN - line_len;
}

void write_line(void)
{
  	int extra_spaces, spaces_to_insert, i;
 
  	extra_spaces = MAX_LINE_LEN - line_len;

	struct word *current = line;

	while(current != NULL){
		//ptint word
		printf("%s", current->content);
		
		//print extra space
		if(current->next != NULL){
      		spaces_to_insert = extra_spaces / (num_words - 1);
			for(i = 1; i <= spaces_to_insert + 1; i++)
				putchar(' ');
			extra_spaces -= spaces_to_insert;
		}
		num_words--;
		current = current->next;
	}
	printf("\n");

}
 
void flush_line(void)
{
  if (line_len > 0){
	//print the line
	struct word *current = line;

	while(current->next != NULL){
		printf("%s ", current->content);
		current = current->next;
	}
	
	printf("%s\n", current->content);
	
  }
}
