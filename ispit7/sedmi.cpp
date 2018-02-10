/*Napisati program koji za tri razlièita predmeta èita ime i prezime studenta te njegovu ocjenu. Podaci o
svakom predmetu se nalaze u odvojenoj datoteci i iz svake datoteke je potrebno kreirati vezanu listu i
ispisati je.
a) Nakon toga potrebno je kreirati novu listu koja sadrži imena studenata koji su položili sva tri
predmeta.
b) Nadopuniti zadatak pod a) tako da se ispiše nova vezana lista koja osim što sadrži imena
studenata, sadrži i njihovu prosjeènu ocjenu iz ta tri predmeta.
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
typedef struct person* position;
struct person{
	char name[20];
	char surname[20];
	int number;
	position next;
}_PERSON;

position CreateHeadNode();
position CreateNode(char* name, char* surname, int number);
void ReadFromFile(char* nameFile, position head);
void Insert(position prev, position next);
void PrintElementsOfList(position head);
position IsPassed(position head, position head2, position head3);

int main(void){
	position head1 = CreateHeadNode();
	position head2 = CreateHeadNode();
	position head3 = CreateHeadNode();
	position head4 = CreateHeadNode();
	position head5 = CreateHeadNode();
	
//	ReadFromFile("povijest.txt", head1);
	ReadFromFile("matematika.txt", head2);
	ReadFromFile("fizika.txt", head3);
	ReadFromFile("kemija.txt", head4);
	
//	PrintElementsOfList(head1);
	printf("Ocijene iz matematike:\n");
	PrintElementsOfList(head2);
	printf("\n");
	printf("Ocijene iz fizike:\n");
	PrintElementsOfList(head3);
	printf("\n");
	printf("Ocijene iz kemije:\n");
	PrintElementsOfList(head4);
	printf("\n");
	

	
	head5 = IsPassed(head2, head3, head4);
	PrintElementsOfList(head5);
	free(head1);
	free(head2);
	free(head3);
	free(head4);
	free(head5);
	return 0;
}

position CreateHeadNode(){
	position q = (position)malloc(sizeof(_PERSON));
	if(q == NULL) return NULL;
	
	q->next = NULL;
	return q;
}
position CreateNode(char* name, char* surname, int number){
	position q = (position)malloc(sizeof(_PERSON));
	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->number = number;
	q->next = NULL;
	return q;
}
void Insert(position prev, position next){
	next->next = prev->next;
	prev->next = next;
}



void ReadFromFile(char* nameFile, position head){
	FILE* f;
	f = fopen(nameFile, "r");
	if(f == NULL) printf("Nije dobro otvorena datoteka");
	char name[20], surname[20];
	int numb;
	while(!feof(f)){
		fscanf(f,"%s %s %d", name, surname, &numb);
		Insert(head,CreateNode(name, surname, numb));
	}
	fclose(f);
	
}

void PrintElementsOfList(position head){
	
	//obavezno ispisivat od 1.pravog clana a ne heada jer ostane neko "smece"
	position elements=head->next; //!!!!!!!!!!
	if(elements==NULL){
		printf("Vezana lista je prazna!");
		return;
	}
	while(elements!=NULL){
		printf("%s %s %d\n", elements->name, elements->surname, elements->number);
		//prebaciti na novi element obavezno!!
		elements=elements->next;
	}
}
position IsPassed(position head, position head2, position head3){
	
	position p = head->next;
	position q = head2->next;
	position s = head3->next;
	
	position neww = CreateHeadNode();
	position t = NULL;
	while(p != NULL && q != NULL && s != NULL){
		
		if(p->number >= 50 && q->number >= 50 && s->number >=50)
				{
					t = CreateNode(p->name, p->surname, (p->number+q->number+s->number)/3);
					Insert(neww, t);
				}
			
		p = p->next;
		q = q->next;
		s = s->next;
	}
	
	return neww;
}








