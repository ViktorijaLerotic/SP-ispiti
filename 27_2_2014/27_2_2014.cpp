//Napisati program koji iz datoteke èita dio teksta, rijeè po rijeè i unosi u binarno stablo pretraživanja
//(maksimalna duljina rijeèi 1024 znaka). Ispisati binarno stablo na „inorder“ naèin.
//Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve rijeèi koje poèinju samoglasnikom, a u
//drugoj sve rijeèi koje poèinju suglasnikom. Rijeèi zapisane u datotekama moraju biti sortirane po abecedi. 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node* position;
struct node{
	char word[20];
	position left;
	position right;
}_NODE;

void Print(position root);
position CreateSubTree(char* x);
position Insert(position root, char* x);
void ReadFromFile(position root, char* fileName);

int main(void){
	position root = NULL;

	ReadFromFile(root, "aaa.txt");
	Print(root);
	return 0;
}
position CreateSubTree(char* x){
	position q = (position)malloc(sizeof(_NODE));
	if(q == NULL) return NULL;
	
	strcpy(q->word,x);
	q->left = NULL;
	q->right = NULL;
	
	return q;
}
position Insert(position root, char* x){

	// 1) ako nemam nijedan element
	if(root == NULL){
	root = CreateSubTree(x);
	}
		
	// 2) ako postoji prvi clan i ako je x manji od prvog clana-ide na lijevu stranu
	else if(strcmp(x, root->word) < 0){
		
		root->left = Insert(root->left, x);
	}
	// 3) ako postoji prvi clan i ako je x veci od prvog clana-ide na desnu stranu
	else if(strcmp(x, root->word) > 0){
	
		root->right = Insert(root->right, x);
	}
	
	return root;
}

void ReadFromFile(position root, char* fileName){
	FILE* f;
	char* str;
	
	f = fopen(fileName, "r");
	if(f == NULL) { printf("Datoteka nije dobro ucitana.\n"); return;}
	
	while(!feof(f)){
		str = (char*)malloc(sizeof(char));
		fscanf(f,"%s ", str);
		root = Insert(root, str);
		
	}
//	fclose(f);
}
void Print(position root){
	if(root == NULL) printf("Prazno stablo.\n");

else{
	printf("%s", root->word);
	Print(root->left);
	
	Print(root->right);
}
	
}
