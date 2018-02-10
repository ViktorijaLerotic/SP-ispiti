/*
Napisati program koji generira 20 sluèajnih brojeva iz opsega 100 – 150 i njih spremiti u vezanu listu i
svakom od njih dodijeliti redni broj od 0-19.

*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* position;

struct node{
	int number;
	int index;
	position next;
}_NODE;

int GenerateRadom(int lower_bound, int higher_bound);
position CreateHead();
position CreateNode(int x, int i);
void Generate20Numbers(position head);
void Print(position head);
void AddAtEnd(position head, position element);
void FindTheIndexes(position head);
position Find(position head, int x);
void Delete(position head, position element);
position FindPrev(position head, position element);
int main(void){
	
	position head = CreateHead();
	Generate20Numbers(head);
	Print(head);
	
	printf("Nakon zamjene.\n");
	
	FindTheIndexes(head);
	Print(head);
	
	return 0;
}

int GenerateRadom(int lower_bound, int higher_bound){

	return rand()%(higher_bound - lower_bound + 1) + lower_bound+1;
}

position CreateHead(){
	
	position q = (position)malloc(sizeof(_NODE));
	if(q == NULL) return NULL;
	
	q->index = 0;
	q->next = NULL;
	
	return q;
}

position CreateNode(int x, int i){
	position q = (position)malloc(sizeof(_NODE));
	if(q == NULL) return NULL;
	
	q->number = x;
	q->index = i;
	q->next = NULL;
	
	return q;
}

void Insert(position Prev, position Next){
	
	Next->next = Prev->next;
	Prev->next = Next;
}
void AddAtEnd(position head, position element){
	
	position last = head;
	while(last->next != NULL)
		last = last->next;
		
		Insert(last, element);
}
void Generate20Numbers(position head){
	int i = 0;
	position q = NULL;
	for(i = 0; i < 20; i++){
		q = CreateNode(GenerateRadom(100,150), i);
			q->index = i;
		AddAtEnd(head, q);
	
	}
		
}

void Print(position head){
	position q = head->next;
	if(q == NULL) printf("Lista je prazna!\n");
	while( q != NULL){
		printf("%d na %d. indexu\n", q->number, q->index);
		
		q = q->next;
	}
}
// trazim po indexu
position Find(position head, int x){
	
	position q = head->next;
	while(q != NULL && q->index < x)
		q = q->next;
		
	return q;	
}
position FindPrev(position head, position element){
	position q = head;
	position p = head->next;
	
	while(p != NULL && p->index < element->index){
		q = p;
		p = p->next;
	}
	
	return q;
}
void Delete(position head, position element){
	position q = Find(head, element->index);
	position p = FindPrev(head, element);
	
	p->next = q->next;
	free(q);
}
void FindTheIndexes(position head){
	int i = 0;
	int x = 0;
	position q = NULL;
	position neww = CreateHead();
	for(i = 0; i < 5; i++){
		x =	GenerateRadom(0,19);
		q = Find(head, x);
		AddAtEnd(neww, CreateNode(q->number, x));
		Delete(head, q);
	}

	position n = neww->next;
	
	while(n != NULL)
	{
		Insert(head,CreateNode(n->number, n->index));
		n = n->next;
	}
	
	
}








