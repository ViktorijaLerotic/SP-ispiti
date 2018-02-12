/*
Napisati program koji generira sluèajne brojeve u opsegu od 50-80. Ukoliko je generirani broj paran
sprema se u vezanu listu parnih brojeva i to u padajuæem redoslijedu (od najveæeg prema najmanjem).
Ukoliko je broj neparan sprema se u vezanu listu neparnih brojeva, takoðer u padajuæem redoslijedu. Niti
jedna vezana lista ne smije sadržavati dva ista elementa. Unos traje sve dok obje liste ne sadrže 10
elemenata. Treba ispisivati koji se broj generira i na kraju ispisati obje liste.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct node* position;
struct node{
	int number;
	position next;
}_NODE;

int GenerateRadom(int lower_bound, int higher_bound);
position CreateHead();
position CreateNode(int x);
void Generate10Numbers(position head);
position Find(position head, int x);
void Insert(position p, position q);
void Print(position head);
void AddAtOrder(position head, position element);
void Divide(position head1, position head2, position head3);

int main(void){
	
	position head = CreateHead();
	position head2 = CreateHead();
	position head3 = CreateHead();
	
	Generate10Numbers(head);
	printf("Svih 20 slucajnih brojevi u rasponu od 50 do 80 bez ponavljanja su:\n");
	Print(head);
	Divide(head, head2, head3);
	printf("Parni brojevi su:\n");
	Print(head2);
	printf("Nearni brojevi su:\n");
	Print(head3);

	free(head);
	
	return 0;
}

int GenerateRadom(int lower_bound, int higher_bound){

	return rand()%(higher_bound - lower_bound + 1) + lower_bound;
}

position CreateHead(){
	
	position q = (position)malloc(sizeof(_NODE));
	if(q == NULL) return NULL;
	
	q->next = NULL;
	
	return q;
}

position CreateNode(int x){
	position q = (position)malloc(sizeof(_NODE));
	if(q == NULL) return NULL;
	
	q->number = x;
	q->next = NULL;
	
	return q;
}
void Insert(position p, position q){
	
	q->next = p->next;
	p->next = q;
}
void AddAtOrder(position head, position element){
	if(head->next == NULL){
		Insert(head, element);
		return;
	}	
			

	position p = head;
	while(p->next != NULL && p->next->number < element->number)
		p = p->next;
			
		Insert(p, element);
		return;
		
		
		
	Insert(head, element);

}
position Find(position head, int x){
	position p = head->next;
	
	while(p != NULL && p->number != x)
		p = p->next;
		
return p;
}
void Generate10Numbers(position head){
	int i = 0;
	position q = NULL;

	int x = 0;
	
	for(i = 0; i < 20; i++){
		position t = (position)malloc(sizeof(_NODE));
	
		x = GenerateRadom(50,30);
		t = Find(head, x);
	
		//stavit uvjet ako se poavlja da ponovno generira broj
		int i = 20;
		while(i){
			if(t!= NULL && t->number == x)
			x = GenerateRadom(50,80);
			i--;
		}	
			
		q = CreateNode(x);
		q->next = NULL;
		AddAtOrder(head, q);
	
	}
		
}

void Print(position head){
	position p = head->next;
	
	while(p != NULL){
		printf("%d\n",  p->number);
		p = p->next;
	}
}
void Divide(position head1, position head2, position head3){
	position p = head1->next;

	while(p != NULL){
	position t = (position)malloc(sizeof(_NODE));		
		if(p->number%2 == 0){
		//	printf("p %d\n", p->number);
		t->number = p->number;
		t->next = NULL;
			Insert(head2, t);
		}
			
		else{
		//	printf("n %d\n", p->number);
			t->number = p->number;
		t->next = NULL;
		Insert(head3, t);
		}
		
		p = p->next;
	}
}
