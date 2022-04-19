#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 49

//course
struct course{
	char name[NAME_LENGTH + 1];
	struct course *next;
	struct course *prior;
};

//use to record the id
struct map{
	int id;
	struct course *course_ptr;
	struct map *next;
};

void create_list(struct course **first); //create the linked list
void add_course(struct course **first, struct map **mapFirst, struct map **mapEnd, int course_id, int next_id, int prior_id, char name[]);//add course to the linked list
void check_course(struct map **mapFirst, struct map **mapEnd, struct course **current, int course_id, char name[]);//check the the course is already exist or not
void find_next(struct map **mapFirst, struct map **mapEnd, struct course **next_course, int next_id);//find the next course
void find_prior(struct map **mapFirst, struct map **mapEnd, struct course **prior_course, int pr_id);//find the prior course
void remove_null_course(struct course **first, int courseNum);//remove the node which is not exist
void read_input(struct course **first);//handle the input and search the course

int main(void){
	
	struct course *head = NULL;
	create_list(&head);
	read_input(&head);

	return 0;
}

void create_list(struct course **first){
	int i = 0;//use for the loop
	int courseNum = 0; //the number of the courses
	scanf("%d\n", &courseNum);
	
	struct map *maphead = NULL;//the head of the map
	struct map *map_end = NULL;//the end of the map

	//create the linked list
	for(i = 0; i < courseNum; i++){
		int course_id = 0;//id of the course
		int next = 0; //next course
		int prior = 0; //prior course
		char name[NAME_LENGTH + 1];//name of the course

		scanf("%d %d %d %s\n", &course_id, &next, &prior, name);
		add_course(first, &maphead, &map_end, course_id, next, prior, name);	
	}

	remove_null_course(first, courseNum);
}

void add_course(struct course **first, struct map **mapFirst, struct map **mapEnd, int course_id, int next_id, int pr_id, char name[]){

	struct course *current = malloc(sizeof(struct course)); //point to the current node
	check_course(mapFirst, mapEnd, &current, course_id, name);//check if the node is alreay exist
	struct course *new_course = current;

	if(new_course == NULL){

		//create new course node
		new_course = malloc(sizeof(struct course));
		strncpy(new_course->name, name, strlen(name));
		new_course->next = NULL;
		new_course->prior = NULL;

		//create new map node
		struct map *new_node = malloc(sizeof(struct map));
		new_node->id = course_id;
		new_node->course_ptr = new_course;

		if(*mapFirst == NULL){
			*mapFirst = new_node;
			*mapEnd = *mapFirst;
		}
		else{
			(*mapEnd)->next = new_node;
			*mapEnd = (*mapEnd)->next;
		}
	}

	if(*first == NULL){// if there is no node in the list
		//printf("the list is empty\n");
		*first = new_course;
		//printf("first course name: %s\n", (*first)->name);
	}
	

	//link the node
	if(next_id != -1){
		struct course *next_course = malloc(sizeof(struct course));
		find_next(mapFirst, mapEnd, &next_course, next_id);
		new_course->next = next_course;
	}
	if(pr_id != -1){
		struct course *prior_course = malloc(sizeof(struct course));
		find_prior(mapFirst, mapEnd, &prior_course, pr_id);
		new_course->prior = prior_course;
	}
}

void check_course(struct map **mapFirst, struct map **mapEnd, struct course **current, int course_id, char name[]){
	
	struct map *mapCurrent;

	if(*mapFirst == NULL){
		*current = NULL;
		return;
	}
	else{
		mapCurrent = *mapFirst;
	}

	while(mapCurrent->id != course_id){
		if(mapCurrent->id == (*mapEnd)->id){//not found
			*current = NULL;
			return;
		}
		else{
			mapCurrent = mapCurrent->next;
		}
	}

	*current = mapCurrent->course_ptr;
	strncpy(((*current)->name), name, strlen(name));
}

void find_next(struct map **mapFirst, struct map **mapEnd, struct course **next_course, int next_id){
	struct map *mapCurrent = *mapFirst;

	while((mapCurrent->id) != next_id){
		if(mapCurrent->id == (*mapEnd)->id){//next node do not exist

			//create a new course node
			struct course *new_course = malloc(sizeof(struct course));
			strcpy(new_course->name, "");
			new_course->next = NULL;
			new_course->prior = NULL;

			//add a new node to map and point the node to the new course
			struct map *new_node = malloc(sizeof(struct course));
			new_node->id = next_id;
			new_node->course_ptr = new_course;
			new_node->next = NULL;
			mapCurrent->next = new_node;
			*mapEnd = mapCurrent->next;//move the end pointer to the end
			mapCurrent = mapCurrent->next;

			//free the node
			new_node = NULL;
			new_course = NULL;
			break;

		}
		else{
			mapCurrent = mapCurrent->next;//check next node
		}
	}

	//point current to the next course node
	*next_course = mapCurrent->course_ptr;
}

void find_prior(struct map **mapFirst, struct map **mapEnd,  struct course **prior_course, int pr_id){
	struct map *mapCurrent = *mapFirst;

	while(mapCurrent->id != pr_id){
		if(mapCurrent->id == (*mapEnd)->id){//prior node do not exist

			//create new course node
			struct course *new_course = malloc(sizeof(struct course));
			strcpy(new_course->name, "");
			new_course->next = NULL;
			new_course->prior = NULL;
			
			//add a new node to map and point the node to the new course
			struct map *new_node = malloc(sizeof(struct course));
			new_node->id = pr_id;
			new_node->course_ptr = new_course;
			mapCurrent->next = new_node;
			*mapEnd = mapCurrent->next;//move the end pointer to the end
			mapCurrent = mapCurrent->next;
			
			//free the node
			new_node = NULL;
			new_course = NULL;
			break;
		}
		else{
			mapCurrent = mapCurrent->next;
		}
	}
	
	//point current to the next course node
	*prior_course = mapCurrent->course_ptr;
}

void remove_null_course(struct course **first, int courseNum){
	struct course *current = *first;
	int i = 0;
	for(i = 0; i < courseNum; i++){
		struct course *next_course = current->next;
		if(next_course == NULL)
			break; //the end of the list
		if(!strcmp(next_course->name, "")){//if the next course do not exist
			current->next = NULL;
			break;
		}

		current = current->next;
	}

	for(i = 0; i < courseNum; i++){
		struct course *prior_course = current->prior;
		if(prior_course == NULL)
			break; //the head of the list
		if(!strcmp(prior_course->name, "")){//if the prior course do not exist
			current->prior = NULL;
			break;
		}

		current = current->prior;
	}
}

void read_input(struct course **first){
	struct course *current = *first;//the current course
	char input; //the command user input
	
	for(;;){
		printf("Current Course: %s\n", current->name);
		printf("[n] Next course. [p] Prior course [q] Quit:");
		scanf("%c\n", &input);

		if(input == 'n'){
			if(current->next == NULL){
				printf("There is no next course.\n");
			}
			else{
				current = current->next;
			}
		}
		else if(input == 'p'){

			if(current->prior == NULL){
				printf("There is no previous course.\n");
			}
			else{
				current = current->prior;
			}
		}
		else if(input == 'q'){
			break;
		}
		else{
			fprintf(stderr, "Invalid input\n");
		}
	}
}
