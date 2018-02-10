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

int main(void){
	
	return 0;
}

int GenerateRadom(int lower_bound, int higher_bound){

	return rand()%(higher_bound - lower_bound + 1) + lower_bound+1;
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
void AddAtOrder(position head, position element){
}
void Generate10Numbers(position head){
	int i = 0;
	position q = NULL;
	for(i = 0; i < 20; i++){
		//stavit uvjet ako se poavlja da ponovno generira broj
		q = CreateNode(GenerateRadom(100,150), i);
			q->index = i;
		AddAtOrder(head, q);
	
	}
		
}
