#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct node;
typedef struct node* Position;
struct node {
	int coefiecient;
	int exponent;
	Position next;
};
int readPolynom(Position);
int sumaPolynom(Position, Position, Position);
int MulPolynom(Position, Position, Position);
int printList(Position);
int deleteAll(Position);
int main()
{
	struct node head1;
	struct node head2;
	struct node headSuma;
	struct node headMultiple;
	int result = 0;
	head1.next = NULL;
	head2.next = NULL;
	headSuma.next = NULL;
	headMultiple.next = NULL;
	result = readPolynom(&head1);
	if (result == 1)
	{
		printf("Datoteka nije otvorena!\n");
		return 0;
	}
	else if (result == -1) 
	{
		printf("Greska pri alokaciji memorije!\n");
		deleteAll(&head1);
		return 0;
	}
	else 
	{
		printf("Sve je proslo u redu!\n");
	}
	result = readPolynom(&head2);
	if (result == 1)
	{
		printf("Datoteka nije otvorena!\n");
		return 0;
	}
	else if (result == -1)
	{
		printf("Greska pri alokaciji memorije!\n");
		deleteAll(&head2);
		return 0;
	}
	else 
	{
		printf("Sve je proslo u redu!\n");
	}
	printf("Prvi polinom:\t");
	printList(head1.next);
	printf("Drugi polinom:\t");
	printList(head2.next);
	result = sumaPolynom(head1.next, head2.next, &headSuma);
	if (result == -1)
	{
		printf("Greska pri alokaciji memorije!\n");
		deleteAll(&head1);
		deleteAll(&head2);
		deleteAll(&headSuma);
		return 0;
	}
	else 
	{
		printf("\nSve je proslo u redu!\n");
	}
	printf("Suma polinoma:\t");
	printList(headSuma.next);
	result = MulPolynom(head1.next, head2.next, &headMultiple);
	if (result == -1)
	{
		printf("Greska pri alokaciji memorije!\n");
		deleteAll(&head1);
		deleteAll(&head2);
		deleteAll(&headMultiple);
		return 0;
	}
	else 
	{
		printf("Sve je proslo u redu!\n");
	}
	printf("Produkt polinoma:");
	printList(headMultiple.next);

	deleteAll(&head1);
	deleteAll(&head2);
	deleteAll(&headSuma);
	deleteAll(&headMultiple);
	printList(headMultiple.next);
	printList(headSuma.next);
	printList(head1.next);
	printList(head2.next);
	return 0;
}
int readPolynom(Position P)
{
	FILE* fp = NULL;
	char fileName[128] = "\0";
	Position q = NULL;

	printf("Upisi ime datoteke:\n");
	scanf(" %s", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("Datoteka nije otvorena!\n");
		return 1;
	}
	int koef, eksp;
	while (fscanf(fp, "%d %d", &koef, &eksp) == 2) 
	{
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL)
		{
			printf("Gre ka pri alokaciji memorije!\n");
			fclose(fp);
			return -1;
		}

		// Postavljanje vrednosti 
		q->coefiecient = koef;
		q->exponent = eksp;

		// Umetanje elementa u sortiranu listu
		while (P->next != NULL && P->next->exponent > q->exponent) 
		{
			P = P->next;
		}

		q->next = P->next;
		P->next = q;
	}
	fclose(fp);
	return 0;
}
int sumaPolynom(Position P1, Position P2, Position Suma) 
{
	Position q = NULL;
	while (P1 != NULL || P2 != NULL)
	{
		q = (Position)malloc(sizeof(struct node));
		if (q == NULL) {
			printf("Greska pri alokaciji memorije!\n");
			return -1;
		}

		if (P1 == NULL) {  // Ako je prvi polinom prazan, preuzmi element iz drugog polinoma
			q->exponent = P2->exponent;
			q->coefiecient = P2->coefiecient;
			P2 = P2->next;
		}
		else if (P2 == NULL) {
			q->exponent = P1->exponent;
			q->coefiecient = P1->coefiecient;
			P1 = P1->next;
		}
		else if (P1->exponent > P2->exponent) 
		{   // Ako je eksponent iz prvog polinoma veci, dodaj taj element u sumu
			q->exponent = P1->exponent;
			q->coefiecient = P1->coefiecient;
			P1 = P1->next;
		}
		else if (P1->exponent < P2->exponent)
		{
			q->exponent = P2->exponent;
			q->coefiecient = P2->coefiecient;
			P2 = P2->next;
		}
		else 
		{   // Ako su eksponenti jednaki, zbroji koeficijente
			q->exponent = P1->exponent;
			q->coefiecient = P1->coefiecient + P2->coefiecient;
			P1 = P1->next;
			P2 = P2->next;
		}

		q->next = Suma->next;
		Suma->next = q;
		Suma = q;  // Pokazivac Suma pomakni na kraj nove liste

	}

	return 0;
}
int MulPolynom(Position P1, Position P2, Position multiple) {
	Position q = NULL, i = NULL, j = NULL, tmp = NULL;
	int eksp = 0;
	int koef = 0;

	for (i = P1; i != NULL; i = i->next)
	{
		for (j = P2; j != NULL; j = j->next)
		{
			eksp = i->exponent + j->exponent;
			koef = i->coefiecient * j->coefiecient;

			tmp = multiple;
			while (tmp->next != NULL && tmp->next->exponent > eksp) {
				tmp = tmp->next;
			}
			// Ako je eksponent vec  prisutan u rezultatu, samo zbrojimo koeficijente
			if (tmp->next != NULL && tmp->next->exponent == eksp) {
				tmp->next->coefiecient += koef;
			}
			else 
			{
				// Ako eksponent nije prisutan, stvaramo novi cvor
				q = (Position)malloc(sizeof(struct node));
				if (q == NULL)
				{
					printf("Greska pri alokaciji memorije!\n");
					return -1;
				}
				q->exponent = eksp;
				q->coefiecient = koef;
				q->next = tmp->next;
				tmp->next = q;
			}
		}
	}
	return 0;
}
int printList(Position P)
{
	if (P == NULL)
	{
		printf("Prazna lista\n");
		return 0;
	}
	while (P != NULL) 
	{

		if (P->coefiecient > 0)
		{
			printf("+%dx^%d ", P->coefiecient, P->exponent);
		}
		else
		{
			printf("%dx^%d ", P->coefiecient, P->exponent);
		}
		P = P->next;
	}
	printf("\n");
	return 0;
}
int deleteAll(Position P)
{
	Position temp = NULL;

	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

	return 0;
}
