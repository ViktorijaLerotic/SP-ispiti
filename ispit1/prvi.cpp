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
int ReadFromFile(position root, char* fileName);
void pushInList(position root, positionL head, int value);
position FindElement(position root, int value);
void PrintL(positionL head);
void Print(position);
void PrintLeft(position);
void PrintRight(position);

int main(void) {
	
   position root = (position)malloc(sizeof(_NODE));
    
	root->left = NULL;
	root->right = NULL;
	root->lenght = 0;
	root->word = '\0';


		
	positionL head =(positionL)malloc(sizeof(_LIST));
	head->list_word = '\0';
	head->next = NULL;
	
	int averageLenght = ReadFromFile(root, "rijeci.txt");
	printf("%d\n", root->left->lenght);
	Print(root);

	
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

int ReadFromFile(position root, char* fileName){
	FILE* f;
	f = fopen(fileName, "r");
	
	if( f == NULL ) return -1;
	
	position q = NULL;
	int x;
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
	
	fclose(f);
return sum/numberOfWords;
}

void Print(position root){
	if(root == NULL){
	 	/*
	 		Rekurzivna je funkcija, ovo nije nuzno
	 		prazno stablo vec je i prazan child element.
	 		Ovo je potrebno provjeriti samo jednom prije ispisa
	 		(kao precondition funkcije).
	 		
			printf("Prazno stablo."); 
		*/
		return;
	}
	printf("%s\n", root->word);
		Print(root->left);	
	Print(root->right);	

}

void PrintLeft(position root){
	if(root == NULL){
		return;
	}

	printf("%s\n", root->word);
	Print(root->left);
}

void PrintRight(position root){
	if(root == NULL){
		return;
	}

	printf("%s\n", root->word);
	Print(root->right);
}
position FindElement(position root, int value){
	if(root == NULL) return NULL;
	if(root->lenght > value)
		return FindElement(root->left, value);
	else if(root->lenght < value)
	return FindElement(root->right, value);
return root;
}
void pushInList(position root, positionL head, int value){

/*
	node unosIzStablaUListu(float f, node S, pos P)
{
	if (NULL != S)
	{
		unosIzStablaUListu(f, S->left, P);
		if ((int)f < S->lenght)
		{
			pos temp = (pos)malloc(sizeof(lista));
			temp->rijec = malloc(S->lenght * sizeof(char));
			strcpy(temp->rijec, S->rijec);
			temp->next = P->next;
			P->next = temp;
		}
		unosIzStablaUListu(f, S->right, P);
	}
}
*/

}
void PrintL(positionL head){
	positionL q = head->next;

	printf("Ovo su rijeci koje su dulje od prosjecne rijeci u stablu zapisane u listi.\n");
	while(q != NULL){
		printf("%s\n", q->list_word);
		q = q->next;
	}
}
