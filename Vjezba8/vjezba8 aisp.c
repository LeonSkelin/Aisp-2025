#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _Stack;
typedef struct _Stack Stack;
typedef Stack* Position;
struct _Stack
{
	int number;
	Position Next;
};

int DeleteAll(Position);
int ReadFromFile(char*, Position);
int Push(Position, int);
int Pop(Position);
int Provjera(char);
int Operacije(Position, char);

int main()
{
	Stack head;
	char filename[32] = { 0 };
	head.Next = NULL;
	printf("Type the name of the file: \t");
	scanf(" %s", filename);
	printf("Converting and summing up...\n");
	ReadFromFile(filename, &head);
	printf("Sum of postfix is = %d", head.Next->number);
	DeleteAll(&head);
	return 0;
}

int ReadFromFile(char* filename, Position P)
{
	char result = 0;
	int x = 0;
	int brojac = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Nema datoteke!\n");
		return -1;
	}
	while ((fscanf(fp, " %c", &result) > 0))
	{
		x = Provjera(result);
		if (x == 1)
		{
			Push(P, result);
		}
		else if (x == 2)
		{
			Operacije(P, result);
		}
		else
		{
			printf("Error!\n");
			fclose(fp);
			return -1;
		}
	}
	fclose(fp);
	return 0;
}

int Provjera(char result)
{
	if (result == '+' || result == '-' || result == '*' || result == '/')
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

int Operacije(Position P, char znak)
{
	int a, b, sum;
	/*if (P->Next == NULL)
	{
		printf("Not enough numbers on Stack!\n");
		return -1;
	}
	if (P->Next->Next == NULL)
	{
		printf("Not enough numbers on Stack!\n");
		return -1;
	}*/
	b = Pop(P);
	a = Pop(P);
	switch (znak)
	{
	case '+':
		sum = a + b;
		break;
	case '-':
		sum = a - b;
		break;
	case '*':
		sum = a * b;
		break;
	case '/':
		sum = a / b;
		break;
	default:
		break;
	}
	Push(P, sum);
	return 0;
}

int Push(Position p, int number)
{
	Position ne = (Position)malloc(sizeof(Stack));
	if (ne == NULL)
	{
		printf("Alokacija neuspjela\n");
		return -1;
	}
	ne->number = number;
	ne->Next = p->Next;
	p->Next = ne;
	return 0;
}

int Pop(Position P)
{
	Position target = P->Next;
	if (target == NULL)
	{
		return -1;
	}
	int val = target->number;
	P->Next = target->Next;
	free(target);
	return val;
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
