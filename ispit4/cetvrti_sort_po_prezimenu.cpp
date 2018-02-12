/*
Napisati program koji iz datoteke èita podatke o broju bodova koje je jedan student dobio na ispitu
(struct _student{char ime[128];char prezime[128];int broj_bodova; int relativni_broj_bodova;struct
_student *left; ;struct _student right;}) i sprema ih u binarno stablo pretraživanja. (Napomena : 0 <
broj_bodova <= 100). Ispisati binarno stablo na „inorder“ naèin.
U tako kreiranom binarnom stablu potrebno je za svakog od studenata izraèunati i relativan broj bodova
po formuli: relativan_broj_bodova=( broj_bodova / MAX(broj_bodova) ). Ispisati binarno stablo na
„preorder“ naèin.
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct student* position;
struct student{
	char name[128];
	char surname[128];
	int score;
	float relative;
	position left;
	position right;
}_STUDENT;

position Insert(position root, position ele);
position ReadFromFile(position root, int& v);
void Print(position root);
void PrintPost(position root, int v);
int maxScore(position root);
int main(void){
	
	position root = NULL;
	int v = 0;
	root = ReadFromFile(root, v);
	
	Print(root);

	printf("\n");
	
	PrintPost(root, v);
	
	return 0;
}
position Insert(position root, position ele){
	if(root == NULL){
		root = (position)malloc(sizeof(_STUDENT));
		strcpy(root->name, ele->name);
		strcpy(root->surname, ele->surname);
		root->score = ele->score;
		root->relative = ele->relative;
		root->right = NULL;
		root->left = NULL;
	}
	
	else if(strcmp(root->surname, ele->surname) > 0 ) 
		root->left = Insert(root->left, ele);
		
	else if(strcmp(root->surname, ele->surname) < 0) 
			root->right = Insert(root->right, ele);
	return root;
}
position ReadFromFile(position root, int& v){
	FILE* f;
	f = fopen("studenti.txt", "r");
	if(f == NULL) printf("lose.");
	int br = 0;
	while(!feof(f)){
		
		position q =(position)malloc(sizeof(_STUDENT));
		
		if(q){
			fscanf(f, "%s %s %d", q->name, q->surname, &q->score);
			q->relative = 0;
			q->left = NULL;
			q->right = NULL;
			root = Insert(root,q);	
			
			if( q->score > br)
				br = q->score;
			}
	}
	v = br;
	fclose(f);
	return root;
}
void Print(position root){
	if(root != NULL){
		Print(root->left);
		printf("%s %s %d\n", root->name, root->surname, root->score);	

		Print(root->right);
	}
}
int maxScore(position root){
	while(root->right != NULL)
		root = root->right;
		
	return root->score;
}
void PrintPost(position root, int v){
		if(root != NULL){
			root->relative = (float)root->score/v*100;
		printf("%s %s %d%% %.2lf%%\n", root->name, root->surname, root->score, root->relative);
				PrintPost(root->left,v);
	
				PrintPost(root->right,v);

	}
}
