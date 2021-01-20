#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{

	char value;
	struct node *next;
};

typedef struct node Node;

struct list{

	Node *head;
	int size;
};

typedef struct list List;

//prototypes
List *create_list();
void push(char value, List *l);
bool is_empty(List *l);
char pop(List *l);
bool is_exist(List l, char val);
int check(List *l, FILE *fh);

int main(int argc, char *argv[]){

	if(argc != 2){
		fprintf(stderr, "Usage: ./checkbrackets.c <filename>\n");
		return 0;
	}

	FILE *fh = fopen(argv[1], "r");
	if(fh == 0){

		fprintf(stderr, "cannot open specified file.\n");
		return 0;
	}

	List *l = create_list();
	int count = check(l, fh);
	if (count != 0){
		printf("%d : Mismatching brackets found. fix first few and try again!\n", count);
	}else{
		printf("0 : Mismatching brackets found\n");
	}
	return 1;
}

int check(List *l, FILE *fh){
	int line = 1;
	int count = 0;
	char c;
	while((c = fgetc(fh)) != EOF){

		char i;
		switch(c){

			case '(':
			case '[':
			case '{':
				push(c, l);
				break;

			case '\n':

				line++;
				break;

			case ')':
				i = pop(l);
				if(i == '('){
					break;
				}else{
					++count;
					printf("line %d :Extra ')' found.\n", line);
					break;
				}

			case ']':
				i = pop(l);
				if(i == '['){
					break;
				}else{
					++count;
					printf("line %d :Extra ']' found.\n", line);
					break;
				}


			case '}':
				i = pop(l);
				if(i == '{'){
					break;
				}else{
					++count;
					printf("line %d :Extra '}' found.\n", line);
					break;
				}

			default:
				break;
		}
	}
	return count;
}

bool is_exist(List l, char val){

	while(!is_empty(&l)){

		if(l.head->value == val){

			return true;
		}
		l.head = l.head->next;
	}
	return false;
}

List *create_list(){

	List *l = malloc(sizeof(List));
	if(l == NULL){

		fprintf(stderr, "could not allocate memory.");
		exit(1);
	}
	l->head = NULL;
	l->size = 0;

	return l;
}

void push(char value , List *l){

	Node *p = malloc(sizeof(Node));
	if(p == NULL){

		fprintf(stderr, "could not allocate memory");
		exit(1);
	}
	p->value = value;				
	p->next = l->head;
	l->head = p;
	l->size++;
}

bool is_empty(List *l){

	return (l->head == NULL);
}

char pop(List *l){

	if(!is_empty(l)){
		char i = l->head->value;
		Node *ptr = l->head;
		l->head = l->head->next;		
		free(ptr);
		l->size--;
		return i;
	}else{

		puts("\n");
	}
}
