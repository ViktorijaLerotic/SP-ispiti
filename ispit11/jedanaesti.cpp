/*
Napisati program koji iz dvije datoteke (jedna sadrži ocjenu 1. kolokvija,a druga ocjenu 2. kolokvija) kreira
vezanu listu studenata koji su položili ispit i ta se nova vezana lista slaže po ocjenama. Naèin pretvorbe
bodova u ocjenu je dan u tablici.
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct list* position;

struct list{
	char name[20];
	char surname[20];
	int score;
	position next;
}_LIST;
position CreateHead();
position CreateNode(char* name, char* surname, int s);
void Insert(position p, position q);
void ReadFromFile(position head, char* fileName, char* fileN);
void Print(position head);

int main(void)
{
	position head = CreateHead();
	ReadFromFile(head, "prvi.txt","drugi.txt");
	Print(head);
	
	free(head);
	return 0;
}

position CreateHead(){
	position q = (position)malloc(sizeof(_LIST));
	
	if(q == NULL) return NULL;
	q->score = 0;
	q->next = NULL;
	return q;
}
position CreateNode(char* name, char* surname, int s){
	position q = (position)malloc(sizeof(_LIST));
	
	if(q == NULL) return NULL;
	
	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->score = s;
	q->next = NULL;
	return q;
}

void Insert(position p, position q){
	
	q->next = p->next;
	p->next = q;
}

void ReadFromFile(position head, char* fileName, char* fileN){
	
	FILE* f;
	FILE* p;
	f = fopen(fileName, "r");
	p = fopen(fileN, "r");
	
	if(f == NULL) return;
	if(p == NULL) return;
	int x = 0, y = 0;
	char a[20], b[20];
	
	while(!feof(f) && !feof(p)){
		
		position q = (position)malloc(sizeof(_LIST));
		
		if(q){
			fscanf(f, "%s %s %d ", q->name, q->surname, &x );
			fscanf(p, "%s %s %d ", a, b, &y);
			if(strcmp(q->name, a) == 0 && strcmp(q->surname, b) == 0)
				q->score = (int)(x + y)/2;
	
			q->next = NULL;
			Insert(head, q);
		}
	}
	
	fclose(f);
	fclose(p);
}
void Print(position head){
	position q = head->next;
	
	while(q != NULL){
		
		if(q->score >= 50 && q->score <= 59)
			printf("%s %s je dobio/la ocjenu 2(%d%%)\n", q->name, q->surname, q->score);
		else if(q->score > 59 && q->score <= 74)
			printf("%s %s je dobio/la ocjenu 3(%d%%)\n", q->name, q->surname, q->score);
	else if(q->score > 75 && q->score <= 87)
			printf("%s %s je dobio/la ocjenu 4(%d%%)\n", q->name, q->surname, q->score);
	else if(q->score > 87 && q->score <= 100)
			printf("%s %s je dobio/la ocjenu 3(%d%%)\n", q->name, q->surname, q->score);
		else if(q->score < 50)
			printf("%s %s je dobio/la ocjenu 1(%d%%)\n", q->name, q->surname, q->score);
		q = q->next;
	}
}












