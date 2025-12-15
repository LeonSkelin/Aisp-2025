#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_LEN 50

#define PUSHFRONTCHOICE 1
#define PRINTLISTCHOICE 2
#define	PUSHBACKCHOICE 3
#define SEARCHLISTCHOICE 4
#define DELETELISTCHOICE 5
#define PUSHAFTERCHOICE 6
#define	PUSHBEFORECHOICE 7
#define PUSHSORTEDCHOICE 8
#define	WRITEINFILECHOICE 9
#define	READFROMFILECHOICE 10
#define DELETEALLCHOICE 11

struct _Person;
typedef struct _Person Person;
typedef Person* Position;

struct _Person
{
	char name[NAME_LEN];
	char surname[NAME_LEN];
	int dateOfBirth;
	Position Next;

};

int PushFront(Position);
int PrintList(Position);
int PushBack(Position);
int SearchList(Position, char[]);
Position FindPrevious(Position, char[]);
int DeleteList(Position, char[]);
int PushBefore(Position, char[]);
int PushAfter(Position, char[]);
int PushSorted(Position);
int WriteInFile(Position);
int ReadFromFile(Position);
int PushFrontFile(Position, char[], char[], int);
int DeleteAll(Position);


int main()
{
	int isAppRunning = 1;
	int choice = 0;
	int result = 0;
	char target[NAME_LEN] = { 0 };
	Person head;			 //prazna lista
	head.Next = NULL;		//head stavit u null(uzemljenje)

	do {
		printf("Odaberi:\n\n");
		printf("1 - Dodaj novi element na pocetku liste\n\n");
		printf("2 - Ispisi listu\n\n");
		printf("3 - Dodaj novi element na kraj liste\n\n");
		printf("4 - Nadi element u listi po prezimenu\n\n");
		printf("5 - Izbrisi trazeni element u listi\n\n");
		printf("6 - Dodaj novi element nakon odredenog mjesta u listi\n\n");
		printf("7 - Dodaj novi element prije odredenog mjesta u listi\n\n");
		printf("8 - Dodaj sortirano osobu\n\n");
		printf("9 - Upisi listu u datoteku\n\n");
		printf("10 - Procitaj listu iz datoteke\n\n");
		printf("11 - Brisi sve\n\n");
		printf("Upisi bilo sta za prekid\n\n");


		scanf(" %d", &choice);

		switch (choice)
		{
		case PUSHFRONTCHOICE:
			result = PushFront(&head);
			if (result != 0)
			{
				printf("Greska u dodavanju elementa.\n");
				return -2;
			}
			break;
		case PRINTLISTCHOICE:
			result = PrintList(head.Next);
			if (result != 0)
			{
				printf("Greska u ispisu.\n");
				return -2;
			}
			break;
		case PUSHBACKCHOICE:
			result = PushBack(&head);
			if (result != 0)
			{
				printf("Greska u dodavanju elementa.\n");
				return -2;
			}
			break;
		case SEARCHLISTCHOICE:
			printf("Upisi prezime trazenog elementa:\n");
			scanf(" %s", target);
			result = SearchList(&head, target);
			if (result != 0)
			{
				printf("Greska u trazenju elementa.\n");
				return -2;
			}
			break;
		case DELETELISTCHOICE:
			printf("Upisi prezime elementa kojeg zelis izbrisat:\n");
			scanf(" %s", &target);
			result = DeleteList(&head, target);
			if (result != 0)
			{
				printf("Greska u brisanju elementa.\n");
				return -2;
			}
			break;
		case PUSHAFTERCHOICE:
			printf("Upisi prezime trazenog elementa:\n");
			scanf(" %s", &target);
			result = PushAfter(&head, target);
			if (result != 0)
			{
				printf("Greska!\n");
				return -1;
			}
			break;
		case PUSHBEFORECHOICE:
			printf("Upisi prezime trazenog elementa:\n");
			scanf(" %s", &target);
			result = PushBefore(&head, target);
			if (result != 0)
			{
				printf("Greska!\n");
				return -1;
			}
			break;
		case PUSHSORTEDCHOICE:
			result = PushSorted(&head);
			if (result != 0)
			{
				printf("Greska!\n");
				return -1;
			}
			break;
		case WRITEINFILECHOICE:
			result = WriteInFile(&head);
			if (result != 0)
			{
				printf("Greska!\n");
				return -1;
			}
			break;
		case READFROMFILECHOICE:
			result = ReadFromFile(&head);
			if (result != 0)
			{
				printf("Greska!\n");
				return -1;
			}
			break;
		case DELETEALLCHOICE:
			result = DeleteAll(&head);
			if (result != 0)
			{
				printf("Greska!\n");
				return -1;
			}
			break;
		default:
			isAppRunning = 0;
			break;
		}
	} while (isAppRunning);

	DeleteAll(&head);
	return 0;
}


int PushFront(Position head) //uvijek se dodaje nakon heada.
{
	Position newElement = (Position)malloc(sizeof(Person));
	if (newElement == NULL)
	{
		printf("Greska u alokaciji.\n");
		return -1;
	}
	printf("Upisi ime, prezime i godina rodenja.\n");
	scanf(" %s %s %d", newElement->name, newElement->surname, &newElement->dateOfBirth);

	newElement->Next = head->Next;
	head->Next = newElement;

	return 0;
}
int PrintList(Position head) //head je head.Next
{
	if (head == NULL)
	{
		printf("Lista je prazna.\n");
		return 1;
	}
	while (head != NULL)
	{
		printf(" %s %s %d\n", head->name, head->surname, head->dateOfBirth);
		head = head->Next;
	}
	return 0;
}
int PushBack(Position head)
{
	while (head->Next != NULL)
	{
		head = head->Next;
	}
	return PushFront(head);
}

int SearchList(Position head, char target[]) //target je trazeni elemenat
{

	while (head != NULL && _strcmpi(head->surname, target) != 0)
	{
		head = head->Next;
	}
	if (head == 0)
	{
		printf("Nema elemenata u listi.\n");
		return 0;
	}
	else
	{
		printf("Trazeni element je naden: %s %s %d\n", head->name, head->surname, head->dateOfBirth);
		return 0;
	}
}
Position FindPrevious(Position head, char target[])
{
	if (head->Next == NULL)
	{
		printf("Lista je prazna.\n");
	}


	while (head->Next != NULL && _strcmpi(head->Next->surname, target) != 0) //trazi prezime prijasnjeg elementa
	{
		head = head->Next;
	}

	if (head == NULL)
	{
		printf("Element nije naden u listi.\n");
		return 1;
	}
	else
		return head;
}
int	DeleteList(Position head, char x[])
{
	head = FindPrevious(head, x);
	if (head->Next == NULL)
	{
		return 1;
	}
	Position target = head->Next;
	head->Next = target->Next;
	free(target);
	return 0;
}
int PushAfter(Position P, char target[])
{
	P = FindPrevious(P, target);
	/*if (P == 0)
	{
		return -2;
	}*/
	P = P->Next; //ovo se ne pise ako stavljamo isprid odredenog elementa
	return PushFront(P);
}
int PushBefore(Position P, char target[])
{
	P = FindPrevious(P, target);
	/*if (P == 0)
	{
		return -2;
	}*/
	return PushFront(P);
}
int ReadFromFile(Position P)
{
	int result = 0;
	char name[NAME_LEN];
	char surname[NAME_LEN];
	int dateOfBirth = 0;
	char filename[NAME_LEN];
	printf("Napisi ime filea\n");
	scanf(" %s", &filename);
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Datoteka nije pronadena\n");
		return 1;
	}
	while ((fscanf(fp, "%s %s %d", name, surname, &dateOfBirth) > 0) && (!feof(fp))) {
		result = PushFrontFile(P, name, surname, dateOfBirth);
		if (result != 0) {
			fclose(fp);
			return result;
		}
	}

	fclose(fp);
	PrintList(P->Next);
	return 0;
}
int PushFrontFile(Position p, char name[], char surname[], int dateOfBirth) {
	Position ne = (Position)malloc(sizeof(Person));
	if (ne == NULL) {
		printf("Alokacija nije uspjela\n");
		return -1;
	}
	strcpy(ne->name, name);
	strcpy(ne->surname, surname);
	ne->dateOfBirth = dateOfBirth;
	ne->Next = p->Next;
	p->Next = ne;
	return 0;
}
int PushSorted(Position P)
{
	Position newPerson = (Position)malloc(sizeof(Person));
	if (newPerson == NULL)
	{
		printf("Alokacija nije uspjela!\n");
		return -1;
	}
	printf("Napisi ime, prezime i godinu rodenja osobe:\n");
	scanf(" %s %s %d", newPerson->name, newPerson->surname, &newPerson->dateOfBirth);
	while (P->Next != NULL && _strcmpi(P->Next->surname, newPerson->surname) < 0)
	{
		P = P->Next;
	}
	newPerson->Next = P->Next;
	P->Next = newPerson;
	return 0;
}
int WriteInFile(Position P)
{
	char filename[NAME_LEN] = { '\0' };
	printf("Napisi naziv filea\n");
	scanf(" %s", &filename);
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		return -2;
	}
	while (P->Next != NULL)
	{
		fprintf(fp, " %s %s %d\n", P->Next->name, P->Next->surname, P->Next->dateOfBirth);
		P->Next = P->Next->Next;
	}
	fclose(fp);
	return 0;
}
int DeleteAll(Position P) //P je head
{
	while (P->Next != NULL)
	{
		Position t = P->Next;
		P->Next = t->Next;
		free(t);
	}
	return 0;
}
