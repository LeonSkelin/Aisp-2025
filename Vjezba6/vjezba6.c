#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct _List;
typedef struct _List List;
typedef List* Position;
struct _List
{
	int number;
	Position Next;
};

int Enqueue(Position);
int Pop(Position);
int Dequeue(Position);
int Push(Position);
int DeleteAll(Position);

int main()
{
	int isAppRunning = 1;
	int choice = 0;
	int result = 0;
	List Queue, Stack;
	Queue.Next = NULL;
	Stack.Next = NULL;
	do
	{
		printf("Choose one of the options:\n");
		printf("1 - Push new element to the beginning of the stack\n");
		printf("2 - Pop the element in stack\n");
		printf("3 - Enqueue new element to the end of the queue\n");
		printf("4 - Dequeue the element in queue\n");
		scanf(" %d", &choice);
		switch (choice)
		{
		case 1:
			result = Push(&Stack);
			if (result != 0)
			{
				printf("ERROR!\n");
				DeleteAll(&Stack);
				DeleteAll(&Queue);
				return -1;
			}
			break;
		case 2:
			result = Pop(&Stack);
			if (result != 0)
			{
				printf("ERROR!\n");
				DeleteAll(&Stack);
				DeleteAll(&Queue);
				return -1;
			}
			break;
		case 3:
			result = Enqueue(&Queue);
			if (result != 0)
			{
				printf("ERROR!\n");
				DeleteAll(&Stack);
				DeleteAll(&Queue);
				return -1;
			}
			break;
		case 4:
			result = Dequeue(&Queue);
			if (result != 0)
			{
				printf("ERROR!\n");
				DeleteAll(&Stack);
				DeleteAll(&Queue);
				return -1;
			}
			break;
		default:
			isAppRunning = 0;
			break;
		}
	} while (isAppRunning);
	DeleteAll(&Stack);
	DeleteAll(&Queue);
	return 0;
}


int Push(Position p)
{
	Position ne = (Position)malloc(sizeof(List));
	if (ne == NULL)
	{
		printf("Alokacija neuspjela\n");
		return -1;
	}
	ne->number = rand() % (100 + 1 - 10) + 10;
	ne->Next = p->Next;
	p->Next = ne;

	return 0;
}

int Enqueue(Position p)
{
	Position ne = (Position)malloc(sizeof(List));
	if (ne == NULL)
	{
		printf("Alokacija neuspjela\n");
		return -1;
	}
	while (p->Next != NULL)
	{
		p = p->Next;
	}
	ne->number = rand() % (100 + 1 - 10) + 10;
	ne->Next = p->Next;
	p->Next = ne;
	return 0;
}
int Pop(Position P)
{

	if (P->Next == NULL) {
		printf("\n\nqueue is empty! \n\n");
		return 0;
	}

	if (P->Next->Next == NULL) 
	{
		Position target = P->Next;
		printf("\n%d \n\n", target->number);
		P->Next = NULL;
		free(target);

		return 0;
	}

	while (P->Next->Next != NULL)
	{
		P = P->Next;

	}

	if (P != NULL)
	{
		Position target = P->Next;
		P->Next = target->Next;
		printf("\n%d \n\n", target->number);
		free(target);
	}
	
	return 0;
}

int Dequeue(Position P)
{

	if (P->Next == NULL) {
		printf("\n\nqueue is empty! \n\n");
		return 0;
	}
	Position target = P->Next;
	P->Next = target->Next;
	printf("\n%d \n\n", target->number);
	free(target);
	

	return 0;
}

int DeleteAll(Position P)
{
	while (P->Next != NULL)
	{
		Position t = P->Next;
		P->Next = t->Next;
		free(t);
	}
	return 0;
}
