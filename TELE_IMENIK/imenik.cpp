/*
Napraviti telefonski imenik na sljedeci nacin:
Podaci korisnika(ime prezime, adresa) citaju se iz datoteke te se spremaju u binarno stablo za pretrazivanje, sortirano po prezimenu.
Svako prvo slovo prezimena sprema se u vezanu listu, ali bez ponavljanja.
Tako svaki element vezane liste pokazuje na root stabla u kojem se nalaze osobe sa istim pocetnim slovom prezimena.
Telefosnki broj se generira, raspon od 400 000 do 600 000 bez ponavljanja!!
Omofuciti pretragu po prezimenu!
*/

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct tree* positionT;
struct tree{
	char name[20];
	char surname[20];
	char street[20];
	int number;
	positionT left;
	positionT right;
}_TREE;

typedef struct list* positionL;

struct list{
	char firstLetter;
	positionL next;
	positionT myRoot;
}_LIST;

positionT InsertInTree(positionT root, positionT element);
positionT CreateEmptyTreeNode();
positionT Find(positionT root, char* surname);

positionL CreateEmptyListNode();


void InsertL(positionL p, positionL q);
void AddAtOrder(positionL head, positionL element, positionT q);
void ReadFromFile(positionL head);
void PrintList(positionL head);
void PrintTree(positionT root);

int FindBySurname(positionL head, char firstLetter);
int GenerateRandom(int lb, int ub);

int main(void){
	
	positionL head = CreateEmptyListNode();
	ReadFromFile(head);
	printf("PREZIME IME ULICA BROJ\n");
	PrintList(head);
	
	printf("Unesite pocetno slovo prezimena koje zelite pretraziti.\n");
	char a;
	scanf("%c", &a);
	int numb = FindBySurname(head, a);
	printf("Trazeni broje je %d.\n", numb);
	return 0;
}

positionT InsertInTree(positionT root, positionT element){
	if(root == NULL){
		root = (positionT)malloc(sizeof(_TREE));
		strcpy(root->name, element->name);
		strcpy(root->surname, element->surname);
		strcpy(root->street, element->street);
		root->number = element->number;
		root->left = NULL;
		root->right = NULL;
	}
	else if(strcmp(root->surname, element->surname) > 0)
		root->left = InsertInTree(root->left, element);
		
	else if(strcmp(root->surname, element->surname) < 0)
		root->right = InsertInTree(root->right, element);
return root;
}

positionT CreateEmptyTreeNode(){
	positionT q = (positionT)malloc(sizeof(_TREE));
	strcpy(q->name, '\0');
	strcpy(q->surname, '\0');
	strcpy(q->street, '\0');
	q->number = 0;
	q->left = NULL;
	q->right = NULL;
return q;
}
positionL CreateEmptyListNode(){
	positionL q = (positionL)malloc(sizeof(_LIST));
	q->firstLetter = '\0';
	q->myRoot = NULL;
	q->next = NULL;
	return q;
	
}
void InsertL(positionL p, positionL q){
	
	q->next = p->next;
	p->next = q;
}
void AddAtOrder(positionL head, positionL element, positionT q){
	if( head->next == NULL){
		
		InsertL(head, element);
		
		return;
	}
	char a, b;
	b = element->firstLetter;
	positionL p = head;
	while(p->next != NULL && p->next->firstLetter < element->firstLetter)
		p = p->next;
	a = p->firstLetter;
	
	if(p->next != NULL && p->next->firstLetter == element->firstLetter)
		{
			p->next->myRoot = InsertInTree(p->next->myRoot, q);
			return;
		}
	else if(a < b){
		InsertL(p, element);
		// isto ide za one cvorove koji su prvi u stablu!!!!!!!!!!!!
		p->next->myRoot = InsertInTree(p->next->myRoot, q);
		return;
	}
		
	InsertL(head, element);
	
}
int GenerateRandom(int lb, int ub){
	return rand()%(ub - lb + 1) + lb;
}

void ReadFromFile(positionL head){
	
	FILE* f = NULL;
	f = fopen("podaci.txt", "r");
	if(f == NULL) return;
	
	while(!feof(f)){
		
		//nece da radi ovako!!!
		/*positionT tree_node = CreateEmptyTreeNode();
		positionL list_node = CreateEmptyListNode();*/
		
		positionT tree_node = (positionT)malloc(sizeof(_TREE));
		positionL list_node = (positionL)malloc(sizeof(_LIST));
		
		list_node->myRoot = NULL;
		
			
		if(tree_node && list_node){
			
			tree_node->left = NULL;
			tree_node->right = NULL;
			list_node->next = NULL;
			
			fscanf(f, "%s %s %s", tree_node->surname, tree_node->name, tree_node->street);
			tree_node->number = GenerateRandom(500000, 600000);
			
			list_node->firstLetter = tree_node->surname[0];
			
			AddAtOrder(head, list_node, tree_node);
			
		}
	}
fclose(f);
}

void PrintTree(positionT root){
	if(root != NULL){
		PrintTree(root->left);
		int x = root->number%10;
		int y = root->number/10%10;
		int z = root->number/100%10;
		printf("%s %s %s %d-%d%d%d\n", root->name, root->surname, root->street, root->number/1000, z,y,x);
		PrintTree(root->right);
	}
}

void PrintList(positionL head){
	positionL p = head->next;
	while(p!= NULL){
		printf("%c\n", p->firstLetter);
		PrintTree(p->myRoot);
		printf("\n");
		p = p->next;
	}
}
positionT Find(positionT root, char* surname){
	if(root == NULL)
	return NULL;
	else if(strcmp(root->surname,surname) == 0)
		return root;
	else if(strcmp(root->surname,surname) > 0)
		return Find(root->left,surname);
else if(strcmp(root->surname,surname) < 0)
		return Find(root->right,surname);
}

int FindBySurname(positionL head, char firstLetter){
	positionL p = head->next;
	while(p != NULL && p->firstLetter != firstLetter)
		p = p->next;
		
	PrintTree(p->myRoot);
	printf("Unesite prezime:\n");
	char lastName[20];
	scanf("%s", lastName);
		
	positionT f = (positionT)malloc(sizeof(_TREE));
	
	f =	Find(p->myRoot, lastName);

	
	return f->number;
}



