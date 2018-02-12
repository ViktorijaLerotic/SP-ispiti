//Napisati program koji �ita iz datoteke dio teksta, te kreira binarno stablo pretra�ivanja. Binarno stablo se
//kreira na na�in da se u njega upisuju sve razli�ite rije�i iz teksta koji je zapisan u datoteci s pripadaju�im
//duljinama unesene rije�i.
//struct _Cvor{char *rijec; int length; struct _Cvor *Left; struct _Cvor *Right;};
//Potrebno je izra�unati prosje�nu duljinu svake rije�i zapisane u binarnom stablu.
//Napisati program koji iz tako kreiranog binarnog stabla u vezanu listu puni samo one rije�i koje su dulje
//od prosje�ne duljine svih rije�i, te ispisati tu vezanu listu.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef struct node* position;
struct node{
	char* word;
	int lenght;
	position left;
	position right;
}_NODE;

typedef struct list* positionL;
struct list{
	char* list_word;
	positionL next;
}_LIST;

position CreateNode(char* word, int lenght);
position Insert(position root, char* word);
position ReadFromFile(position root, char* fileName, int& y);
void pushInL(position, positionL head, int);
position FindElement(position root, int value);
void PrintL(positionL head);
void Print(position);
int GetAverageLength();
void InsertL(positionL p, positionL q);
int main(void) {
	
   position root = NULL;
   positionL head =(positionL)malloc(sizeof(_LIST));
	head->list_word = '\0';
	head->next = NULL;
	
	int x = 0;
	root = ReadFromFile(root, "rijeci.txt", x);
	Print(root);
	//printf("%d   ", x);
	pushInL(root,head, x);
	
	PrintL(head);

	return 0;
}

position Insert(position root, position q){
	//1) ako nemam root
	
	if( root == NULL){
		root = (position)malloc(sizeof(_NODE));
		root->left = NULL;
		root->right = NULL;
		root->lenght = 0;
		root->word = '\0';
		root = q;	
	}
		
		
	else if(root != NULL && q->lenght > root->lenght)
		root->right = Insert(root->right, q);
		
	else if(q->lenght < root->lenght)
		 root->left = Insert(root->left, q);
		 else if(q->lenght == root->lenght)
		 	printf("Ista velicina!");
	
	return root;
}

position ReadFromFile(position root, char* fileName, int& y){
	FILE* f;
	f = fopen(fileName, "r");
	
	if( f == NULL ) printf("Nije dobro ucitana datoteka!\n");
	
	position q = NULL;
	int x = 0;
	int sum = 0;
	int numberOfWords = 0;
	while(!feof(f)){
		
		q = (position)malloc(sizeof(_NODE));
		
		if(q){
			
			q->word = (char*)malloc(sizeof(char)*25);
			q->word[24] = '\0';
			fscanf(f, " %s", q->word, 24);
			x = strlen(q->word);
		//	printf("%d  ", x);
			sum += x;
			numberOfWords ++;
			q->lenght = x;
			q->left = NULL;
			q->right = NULL;
			
			//Debug:
			//printf("%s ", q->word);
		 	root = Insert(root, q);	
		}
		
	
	}
	printf("Prosjecna duljina rijeci u binarnom stablu je: %d", sum/numberOfWords);
	printf("\n");
	
	y = sum/numberOfWords;
	
	fclose(f);
return root;
}
int GetAverageLength(){
	
	
}

void Print(position root){
	if(root == NULL){
		return;
	}
	printf("%s %d\n", root->word, root->lenght);
	Print(root->left);	
	Print(root->right);	


}
void pushInL(position root, positionL head, int value){
	//bez toha nece radit!!!
	if(root == NULL){
		return;
	}
	positionL t = (positionL)malloc(sizeof(_LIST));

	pushInL(root->left,head, value);	
	pushInL(root->right,head, value);	
	
	if(root->lenght > value){
		//printf("%s %d\n", root->word, root->lenght);
		t->list_word = root->word;
		t->next = NULL;
	//	printf("%s ", t->list_word);
		InsertL(head, t);
	}
	

}

position FindElement(position root, int value){
	if(root == NULL) return NULL;
	
	if(root->lenght > value)
		return FindElement(root->left, value);
		
	else if(root->lenght < value)
	return FindElement(root->right, value);
	
return root;
}
void InsertL(positionL p, positionL q){
	q->next = p->next;
	p->next = q;
}

void PrintL(positionL head){
	positionL q = head->next;

	printf("Ovo su rijeci koje su dulje od prosjecne rijeci u stablu zapisane u listi.\n");
	while(q != NULL){
		printf("%s\n", q->list_word);
		q = q->next;
	}
}
