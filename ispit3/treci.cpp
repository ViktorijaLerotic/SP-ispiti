/*
Napisati program koji iz datoteke èita dio teksta, rijeè po rijeè i unosi u binarno stablo pretraživanja
(maksimalna duljina rijeèi 1024 znaka). Ispisati binarno stablo na „inorder“ naèin.
Iz binarnog stabla kreirati dvije datoteke, u prvoj se nalaze sve rijeèi koje poèinju samoglasnikom, a u
drugoj sve rijeèi koje poèinju suglasnikom. Rijeèi zapisane u datotekama moraju biti sortirane po abecedi
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

typedef struct node* position;
struct node{
	char* word;
	position left;
	position right;
}_NODE;

position Insert(position root, position ele);
position ReadFromFile(position root);
void Print(position root);
void PrintInFile(position root, char*, char*);

int main(void){
	position root = NULL;

	root = ReadFromFile(root);
	
	Print(root);
	
	PrintInFile(root, "samo.txt", "sugl.txt");
	
	
	return 0;
}

position Insert(position root, position ele){
	if(root == NULL){
		root =(position)malloc(sizeof(_NODE));
		if(root)
		{
		root->word =(char*)malloc(sizeof(char));
		root->word = ele->word;
		root->right = NULL;
		root->left = NULL;
		}
		
	}
		
		
	if(strcmpi(ele->word, root->word) <0)
		root->left = Insert(root->left, ele);
		
	else if(strcmpi(ele->word, root->word) > 0)
		root->right = Insert(root->right, ele);
		
	return root;
}
position ReadFromFile(position root){
	FILE* f;
	f = fopen("rijeci.txt", "r");
	
	if(f == NULL) printf("Ne.");
	
	while(!feof(f)){
		position q = (position)malloc(sizeof(_NODE));
		
		if(q){
			q->word =(char*)malloc(sizeof(char)*24);
			q->word[23] = '\0';
			fscanf(f, "%s ", q->word, 23);
			q->left = NULL;
			q->right = NULL;
			
			root = Insert(root, q);
		}
	}
	fclose(f);
	
	return root;
}
void Print(position root){

		if(root!=NULL){
	Print(root->left);	
	printf("%s\n", root->word);
	Print(root->right);		
	}


}
void PrintInFile(position root, char* f, char* p){

	FILE* a;
	FILE* b;
	a = fopen(f, "a");
	b = fopen(p, "a");
	if(root != NULL){
		
		PrintInFile(root->left, f, p);
		
		if(root->word[0] == 'a' || root->word[0] == 'e' || root->word[0] == 'i' || root->word[0] == 'o' || root->word[0] == 'u')
			fprintf(a, "%s\n", root->word);
		else
			fprintf(b, "%s\n", root->word);	

		PrintInFile(root->right, f, p);
	}
	
}


