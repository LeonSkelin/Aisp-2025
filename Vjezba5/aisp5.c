#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct SortedList;
typedef struct SortedList List;
typedef List* Position;
struct SortedList
{
	int number;
	Position Next;
};

void DeleteAll(Position);
int ReadFromFile(char*, Position);
int ListUnity(Position, Position, Position);
int ListIntersection(Position, Position, Position);
void Print(Position);
int PushFront(Position);
int SortedInsert(Position, int);
int main()
{
	List first, second, setIntersection, setUnity;
	char filename1[32] = "\0";
	char filename2[32] = "\0";
	int result = 0;
	first.Next = NULL;
	second.Next = NULL;
	setIntersection.Next = NULL;
	setUnity.Next = NULL;
	printf("Write the name of the first list file: \n");
	scanf(" %s", filename1);
	result = ReadFromFile(filename1, &first);
	if (result != 0)
	{
		printf("Error reading first file!\n");
		DeleteAll(&first);
		return -1;
	}
	printf("Write the name of the second list file: \n");
	scanf(" %s", filename2);
	result = ReadFromFile(filename2, &second);
	if (result != 0)
	{
		printf("Error reading second file!\n");
		DeleteAll(&first);
		DeleteAll(&second);
		return -1;
	}
	result = ListUnity(&setUnity, first.Next, second.Next);
	if (result != 0)
	{
		printf("Error uniting 2 lists!\n");
		DeleteAll(&first);
		DeleteAll(&second);
		DeleteAll(&setUnity);
		return -1;
	}
	result = ListIntersection(&setIntersection, first.Next, second.Next);
	if (result != 0)
	{
		printf("Error intersecting 2 lists!\n");
		DeleteAll(&first);
		DeleteAll(&second);
		DeleteAll(&setIntersection);
		return -1;
	}
	DeleteAll(&first);
	DeleteAll(&second);
	DeleteAll(&setUnity);
	DeleteAll(&setIntersection);
	return 0;
}

int SortedInsert(Position P, int value)
{
	Position prev = P;
	Position current = P->Next;

	while (current != NULL && current->number < value)
	{
		prev = current;
		current = current->Next;
	}

	if (current != NULL && current->number == value)
		return 0;

	Position newNumber = (Position)malloc(sizeof(List));
	if (newNumber == NULL)
	{
		printf("Error with allocation!\n");
		return -1;
	}

	newNumber->number = value;
	newNumber->Next = current;
	prev->Next = newNumber;

	return 0;
}
int ReadFromFile(char* filename, Position head)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		printf("Nema datoteke!\n");
		return -1;
	}

	int value;
	while (fscanf(fp, "%d", &value) == 1)
	{
		if (SortedInsert(head, value) != 0)
		{
			fclose(fp);
			return -1;
		}
	}

	fclose(fp);
	return 0;
}

int ListUnity(Position unity, Position first, Position second)
{
	while (first != NULL && second != NULL)
	{
		if (first->number < second->number)
		{
			SortedInsert(unity, first->number);
			first = first->Next;
		}
		else if (first->number > second->number)
		{
			SortedInsert(unity, second->number);
			second = second->Next;
		}
		else
		{
			SortedInsert(unity, first->number);
			first = first->Next;
			second = second->Next;
		}
	}

	while (first != NULL)
	{
		SortedInsert(unity, first->number);
		first = first->Next;
	}

	while (second != NULL)
	{
		SortedInsert(unity, second->number);
		second = second->Next;
	}

	Print(unity);
	return 0;
}


int ListIntersection(Position intersection, Position first, Position second)
{
	while (first != NULL && second != NULL)
	{
		if (first->number < second->number)
			first = first->Next;
		else if (first->number > second->number)
			second = second->Next;
		else
		{
			SortedInsert(intersection, first->number);
			first = first->Next;
			second = second->Next;
		}
	}

	Print(intersection);
	return 0;
}


void Print(Position target)
{
	target = target->Next;
	while (target != NULL)
	{
		printf("-%d\n", target->number);
		target = target->Next;
	}
	printf("\n");
}
void DeleteAll(Position P)
{
	Position target;
	while (P->Next != NULL)
	{
		target = P->Next;
		P->Next = target->Next;
		free(target);
	}
}
