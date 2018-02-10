//Napisati program koji iz datoteke èita dio teksta, rijeè po rijeè i unosi ih u red s prioritetom (maksimalna
//duljina rijeèi 1024 znaka, prioritet=1 => rijeè poèinje samoglasnikom, prioritet=2 => rijeè poèinje
//suglasnikom;). Rijeèi u redu moraju biti sortirane po prioritetu.
//Iz tako kreiranog reda kreirati dvije datoteke, u prvoj æe se nalaziti rijeèi sa prioritetom=1, a u drugoj rijeèi
//s prioritetom=2; s tim da su te rijeèi u datoteci zapisane sortirane po abecedi.

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
typedef struct node* position;
struct node{
	char* word;
	int priority;
	position next;
}_NODE;
void Insert(position p, position q);
void AddAtEnd(position head, position element);
void ReadFromFile(char* name, position head);
void Print(position head);
position CreateHead();
void AddAtOrder(position head, position element);
void PrintInFile(position head);
int main(void){
	position head = CreateHead();
	
	ReadFromFile("rijeci.txt", head);
	Print(head);
	PrintInFile(head);
		return 0;
}
position CreateHead(){
	position q = (position)malloc(sizeof(_NODE));
	if(q == NULL) return NULL;
	
//	strcpy(q->word, '\0');
	q->priority = 0;
	q->next = NULL;
	
	return q;
}
void Insert(position p, position q){
	q->next = p->next;
	p->next = q;
}
void AddAtEnd(position head, position element){
	position last = head;
	
		while(last->next != NULL)
			last = last->next;
			
	Insert(last, element);
}
void AddAtOrder(position head, position element){
	
	if(head->next == NULL)
		{
			Insert(head, element);
			return;
		}
		
		position p = head;
		position q = p->next;
		while(p->next != NULL && p->next->priority < 2)
				p = p->next;
	
				Insert(p, element);
			return;
		
		
			
		
			
			
Insert(head, element);
}
void ReadFromFile(char* name, position head){
	FILE* f;
	f = fopen(name, "r");
	if(f == NULL) return;
	
	while(!feof(f)){
		position q = (position)malloc(sizeof(_NODE));
		
		if(q){
			q->word = (char*)malloc(sizeof(char)*1024);
			q->word[1023] = '\0';
			fscanf(f, "%s ", q->word, 1023);
			if(q->word[0] == 'a' || q->word[0] == 'e' || q->word[0] == 'i' || q->word[0] == 'o' || q->word[0] == 'u')
				q->priority = 1;
			else
			q->priority = 2;
			
			q->next = NULL;
			AddAtOrder(head, q);
		}
	}
	fclose(f);
}
void Print(position head){
	position p = head->next;
	if(p == NULL) printf("Lista je prazna!\n");
	
	while(p != NULL){
		printf("%s\n", p->word);
		p = p->next;
	}
}
void PrintInFile(position head){
	FILE* f;
	FILE* p;
	f = fopen("samoglasnici.txt", "w");
	p = fopen("suglasnici.txt", "w");
	
	if(f == NULL) return;
	if(p == NULL) return;
	position q = head->next;
	while( q != NULL){
			if(q->priority == 1)
			fprintf(f, "%s ", q->word);
			else
			fprintf(p, "%s ", q->word);
		q = q->next;
	}
fclose(f);
fclose(p);
}
