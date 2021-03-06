#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
typedef struct list* position;
typedef struct tree* positionT;

struct tree{
	char word[50];
	int counterT ;
	positionT left;
	positionT right;
}_TREE;

struct list{
	char firstLetter;
	int counter;
	position next;
	positionT myRoot;
}_LIST;
positionT Insert(positionT root, positionT ele);
void Print(positionT root);
void ReadFromFile(position head);
void PrintL(position head);
void InsertL(position q, position p);
void AddAtOrder(position head, position element, positionT q);
position CreateHead();
bool isDuplicate(position head, position element);
void DeleteElement(position head, position ele);
positionT Find(positionT root, char* word);
void CountDuplicate(position head);
void FindDuplicate(positionT root);
int main(void){
	

	position head = CreateHead();
	 ReadFromFile(head);
	

	 PrintL(head);
	 
	 position p = head->next;
	 
	 while(p != NULL){
	 	printf("Stablo:\n");
	 	Print(p->myRoot);
	 	printf("\n");
	 	p = p->next;
	 }
	
	printf("Broj rijeci %d\n", head->counter);
	return 0;
}
position CreateHead(){
	position q = (position)malloc(sizeof(_LIST));
	q->firstLetter = '\0';
	q->counter = 0;

	q->next = NULL;
	
	return q;
}
positionT Insert(positionT root, positionT ele){
	
	if(root == NULL){
		root = (positionT)malloc(sizeof(_TREE));
		strcpy(root->word, ele->word);
		root->counterT = ele->counterT;
	//	printf("%d\n", root->counterT);
		root->left = NULL;
		root->right = NULL;
	}
	else if(strcmp(ele->word, root->word) < 0)
		root->left = Insert(root->left, ele);
		
	else if(strcmp(ele->word, root->word) > 0)	
		root->right = Insert(root->right, ele);
		
	return root;
}
void InsertL(position q, position p){
	p->next = q->next;
	q->next = p;
}
void DeleteElement(position head, position ele){
	
	position q = head;
	position p = head->next;
	char a, b;
	a = p->firstLetter;
	b = ele->firstLetter;
	while(p != NULL && a != b ){
		p = p->next;
		a = p->firstLetter;
	}
	
	position found = p;
	
	while(p != NULL && a != b){
		
		q = p;
		p = p->next;
		a = p->firstLetter;
	}
	position prev = q;
	
	prev->next = found->next;
	
	free(found);
	
	
}
positionT Find(positionT root, char* word){
	
	if(root == NULL) return NULL;
	
	else if(strcmp(root->word, word) > 0)
		return Find(root->left, word);
		
	else if (strcmp(root->word, word) < 0)
		return Find(root->right, word);
	
return root;
	
}
void AddAtOrder(position head, position element, positionT q){
	
	if(head->next == NULL){
		InsertL(head, element);
			q->counterT++;
			head->next->myRoot = Insert(head->next->myRoot, q);
		return;
	}
	
	position p = head;
	char a,b;
	b = element->firstLetter;

	while(p->next != NULL && element->firstLetter > p->next->firstLetter)
		p = p->next;
		
		a = p->firstLetter; 
		
//u ovom if-u ovako prepoznaje charove a ne kao a i b
		 if( p->next != NULL && element->firstLetter == p->next->firstLetter)
		 {			positionT f = (positionT)malloc(sizeof(_TREE));
					f = Find(p->next->myRoot, q->word);
					
					if( f != NULL){
					f->counterT++;
					return;
					}
			 else{
			 	q->counterT++;
			 	p->next->myRoot = Insert(p->next->myRoot, q);
		 		return;
			 	}
		 
		 }
// u ovom ifu ne prepoznaje charove kao pokazivace struktura nego kao a i b	
	else if(a < b){
				q->counterT++;
				InsertL(p, element);
				p->next->myRoot = Insert(p->next->myRoot, q);
				return;
				}
	
	InsertL(head, element);

}


void ReadFromFile(position head){
	FILE* f;
	
	f = fopen("rijeci.txt", "r");
	
	if(f == NULL) printf("Nije dobro ucitana datoteka.\n");
	
	
	int br = 0, brUpp=0;
	
	while(!feof(f)){
		
		positionT q =(positionT)malloc(sizeof(_TREE));
		position p =(position)malloc(sizeof(_LIST));
		q->counterT = 0;
		p->myRoot = NULL;
		q->left = NULL;
		q->right = NULL;
			if(q && p){
			br++;
			//kreiram zasebni cvor stabla koji mora pronaci svoje odgovarajuce stablo i mjesto u njemu
			fscanf(f, "%s ", q->word);
			//kreiram zasebni cvor liste koji cu kasnije ubaciti prema abecedi u listu
			p->firstLetter = q->word[0];
			p->next = NULL;
		
			//s ovom funkcijom osim sto po abecedi upisujem pocetna slova takoder gradim stablo ukoliko mi se pocetno slovo ponavlja
			AddAtOrder(head, p, q);
			
			//brojanje pocetnih rijeci
			if((int)isupper(q->word[0]))
			brUpp++;
		}
	head->counter = br;
	}

	printf("Broj rijeci koje zapocinju pocetnim slovom je %d\n", brUpp);
//	CountDuplicate(head);
	fclose(f);
	
}


void Print(positionT root){
	
	if(root !=NULL){
		
		Print(root->left);
		printf("%s %d(br ponovljenih rijeci) \n", root->word, root->counterT);
		Print(root->right);
	}
}


void PrintL(position head){
	position p = head->next;

	while(p != NULL){
		printf("%c \n", p->firstLetter);
		p = p->next;
		
	}

}
