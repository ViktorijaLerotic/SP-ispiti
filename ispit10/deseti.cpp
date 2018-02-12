#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>

typedef struct tree* positionT;
struct tree{
	char word[50];
	int number;
	positionT left;
	positionT right;
}_TREE_NODE;

typedef struct list* positionL;
struct list{
	
	int number;
	positionL next;
}_LIST_NODE;

void Print(positionT root);
void PrintL(positionL head);
positionT InsertInTree(positionT root, positionT element);
int GenerateRandomNumber(int lb, int ub);
void InsertInList(positionL Prev, positionL Next);
positionT Find(positionT root, int ele);
positionT ReadFromFile(positionL head, positionT root);
positionL CreateHead();
void Smth(positionT root, int br);
int main(void){
	
	positionT root = NULL;
	positionL head = CreateHead();
	
	root = ReadFromFile(head, root);
	
	Print(root);
	printf("\n");
	
	PrintL(head);
	return 0;
}
positionL CreateHead(){
		positionL p = (positionL)malloc(sizeof(_LIST_NODE));
		if(p == NULL) return NULL;
		
		p->next = NULL;
		p->number = 0;
		
	return p;
	
}
positionT InsertInTree(positionT root, positionT element){
	
	if(root == NULL){
		root = (positionT)malloc(sizeof(_TREE_NODE));
		strcpy(root->word, element->word);
		root->number = element->number;
		root->left = NULL;
		root->right = NULL;
		
	}
	
	else if(root->number > element->number)
	root->left = InsertInTree(root->left, element);
	
	else if(root->number < element->number)
		root->right = InsertInTree(root->right, element);
	
	
	return root;
}

int GenerateRandomNumber(int lb, int ub){
	
	return rand()%(ub - lb + 1) + lb;
}
void InsertInList(positionL Prev, positionL Next){
	
	Next->next = Prev->next;
	Prev->next = Next;
}

positionT Find(positionT root, int ele){
	
	if(root == NULL) return NULL;
	
	else if(root->number > ele)
		return Find(root->left, ele);
		
	else if (root->number < ele)
		return Find(root->right, ele);
	
return root;
	
}
positionT ReadFromFile(positionL head, positionT root){
	
	FILE* f;
	int numb;
	f = fopen("rijeci.txt", "r");
	
	if(f == NULL) printf("Datoteka nije dobro ucitana!\n");
	
	int br = 0;
	
	while(!feof(f)){
		
		positionT q = (positionT)malloc(sizeof(_TREE_NODE));
		positionT fo = (positionT)malloc(sizeof(_TREE_NODE));
		positionL p = (positionL)malloc(sizeof(_LIST_NODE));
		
		if(q && p){
			
			fscanf(f, "%s ", q->word);
			
			q->left = NULL;
			q->right = NULL;
			
			numb = GenerateRandomNumber(10, 500);
			
			fo = Find(root, numb);
		
			
			if( fo != NULL && fo->number == numb ){
			//	printf("Ponovljeni broj je: %d\n", numb);
				p->number = numb;
				p->next = NULL;
				InsertInList(head,p);
				//stavila sam gornju granicu 500 umjesto 1010 jer kad je 1010 ne ponavljaju mi se brojevi pa zad nema smisla
				numb = GenerateRandomNumber(10, 500);
				q->number = numb;
				
			}
			
			else
				q->number = numb;
				
			
			br++;
			
			root = InsertInTree(root, q);
			
		}
	}
	
	Smth(root, br);
		
		fclose(f);
return root;
}
void Smth(positionT root, int br){
	positionT s = (positionT)malloc(sizeof(_TREE_NODE));
	int j = 0;
	int i = 0;
	printf("Slucajni brojevi su:\n");
	for(i = 0; i < 20; i++){
	//	printf("%d. broj je %d\n", i+1, GenerateRandomNumber(1, br));
	j = GenerateRandomNumber(1, br);
	s = Find(root, j);
	if( s!= NULL)
	printf("Rijec s tim brojem je : %s\n", s->word);
	}
}
void Print(positionT root){
	
	if(root !=NULL){
		
		Print(root->left);
		printf("%s %d \n", root->word, root->number);
		Print(root->right);
	}
}

void PrintL(positionL head){
	positionL p = head->next;

	while(p != NULL){
		printf("%d \n", p->number);
		p = p->next;
		
	}

}


