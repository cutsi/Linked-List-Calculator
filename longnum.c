#include <stdio.h>
#include <stdlib.h>
#include "longnum.h"

LongNumber read_longnum(char* fname) {
	FILE *file;
	file = fopen(fname, "rt");
	int a;
	if (file == NULL) {
		printf("Error\n");
		exit(0);
	}
	fscanf(file, "%d,", &a);
	fclose(file);

	LongNumber LN = (LongNumber)malloc(sizeof(LongNumber));

	LN->next = NULL;
	LN->z = 0;
	Digit *s = LN;
	LN->next = s;
	Digit* d = (Digit*)malloc(sizeof(Digit));
	d->z = a % 10;
	a = a / 10;
	s->next = d;
	s = s->next;
	while (a > 0) {
		Digit* dig = (Digit*)malloc(sizeof(Digit));
		dig->z = a % 10;	
		a = a / 10;
		s->next = dig;	
		s = s->next;
		
	}
	s->next = NULL;

	return LN;	
}
void write_longnum(LongNumber num, char* fname) {
	FILE *file;
	file = fopen(fname, "w");
	if (file == NULL) {
		printf("Error\n");
		exit(0);
	}
	Digit *s = num->next;
	while (s != NULL) {
		fprintf(file, "%d", s->z);
		s = s->next;
	}
	fclose(file);

}

void print_longnum(LongNumber num) {
	//num = reverse(num);
	Digit *s = num->next;
	while (s  != NULL) {
		printf("%d", s->z);
		s = s->next;
	}
	printf("\n\n");
}


LongNumber add_longnum(LongNumber a, LongNumber b) {
	int ost=0;
	LongNumber rez = (LongNumber)malloc(sizeof(LongNumber));
	Digit* resDigit = (Digit*)malloc(sizeof(Digit));
	resDigit->z = 0;
	resDigit->next = rez->next;
	rez->next = resDigit;
	//rez->next = NULL;
	//rez->z = 0;
	Digit *s = a->next;
	Digit *q = b->next;
	Digit *w = rez;
	while (s != NULL || q != NULL) {
		if (a == NULL) {
			while (b != NULL) {
				Digit* resDigit = (Digit*)malloc(sizeof(Digit));
				resDigit->z = q->z;
				resDigit->next = rez->next;
				rez->next = resDigit;
			}
		}
		else if (b == NULL) {
			while (a != NULL) {
				Digit* resDigit = (Digit*)malloc(sizeof(Digit));
				resDigit->z = s->z;
				resDigit->next = rez->next;
				rez->next = resDigit;
			}
		}
		else {
			Digit *l = (Digit*)malloc(sizeof(Digit));
			l->z = (s->z + q->z + ost);
			if (s->next == NULL || b->next == NULL) {
				if (l->z > 9) {
					l->z = l->z % 10;
					Digit *p = (Digit*)malloc(sizeof(Digit));
					p->z = 1;
					w->next = l;
					w = w->next;
					w->next = p;
					p->next = NULL;

					break;
				}
				l->next = NULL;
				w->next = l;
				w = w->next;
				break;
			}
			ost = 0;
			if (l->z > 9) {
				l->z = l->z % 10;
				ost = 1;
			}
			w->next = l;
			w = w->next;
			s = s->next;
			q = q->next;
		}
	}

	return rez;
}

LongNumber reverse(LongNumber num) {
	Digit* pret = NULL;
	Digit* curr = num->next;
	//printf("current %d", current);
	Digit* next = NULL;
	while (curr != NULL)
	{
		next = curr->next; 
		curr->next = pret;

		pret = curr;
		curr = next;
	}
	//pret->next = NULL;
	num->next = pret;

	return num;
}
LongNumber mul_by_digit(LongNumber num, int z) {
	int ost = 0;
	LongNumber rez = (LongNumber)malloc(sizeof(LongNumber));
	rez->next = NULL;
	rez->z = 0;
	Digit *s = num->next;
	Digit *w = rez;
	while (s != NULL) {
		Digit *l = (Digit*)malloc(sizeof(Digit));
		l->z = (s->z * z + ost);
		if (s->next == NULL) {
			if (l->z > 9) {
				l->z = l->z % 10;
				Digit *p = (Digit*)malloc(sizeof(Digit));
				p->z = 1;
				w->next = l;
				w = w->next;
				w->next = p;
				p->next = NULL;
				break;
			}
			l->next = NULL;
			w->next = l;
			w = w->next;
			break;
		}
		ost = 0;
		if (l->z > 9) {
			ost = l->z - (l->z % 10);
			ost = ost / 10;
			l->z = l->z % 10;
		}
		w->next = l;
		w = w->next;
		s = s->next;
	}
	return rez;
}
void delete_longnum(LongNumber num) {
	Digit *a = num->next;
	while (a != NULL) {
		Digit *b = a;
		a = a->next;
		//free(b->z);
		free(b);
	}
	free(num);
}

// pomocna funkcija koja mnozi broj sa potencijom od 10 (odnosno dodaje nule na pocetak broja)
// Gradi se potpuno nova lista (broj) kao rezultat.

LongNumber mul_by_pow10(LongNumber num, int pow) {
	//LongNumber rez = (LongNumber)malloc(sizeof(LongNumber));
	Digit *s = num->next;
	while (s->next != NULL) {
		s = s->next;
	}
	while (pow > 0) {
		Digit *p = (Digit*)malloc(sizeof(Digit));
		p->z = 0;
		s->next = p;
		p->next = NULL;
		s = s->next;
		pow--;
	}
	return num;
}
// mnozi dva broja oslanjanjuci se na prethodne funkcije. Primjer:
// 123 x 235
// ---------
//   123 * 10^0 * 5
//   123 * 10^1 * 3
// + 123 * 10^2 * 2
// --------
//  28905 
// Gradi se potpuno nova lista (broj) kao rezultat.

LongNumber mul_longnum(LongNumber a, LongNumber b) {
	LongNumber result = (LongNumber*)malloc(sizeof(LongNumber));
	result->next = NULL;
	
	LongNumber sA = a;
	LongNumber sB= b->next;
	//sB = reverse(sB);
	LongNumber temp = (LongNumber*)malloc(sizeof(LongNumber));
	temp->next = NULL;
	int i = 0;
	while (sB != NULL) {
		temp = mul_by_digit(mul_by_pow10(sA, i), sB->z);
		print_longnum(temp);
		//printf(" rez= %d", temp->z);
		result = add_longnum(result, temp);
		//printf("%d asas", result->z);
		delete_longnum(temp);
		//free(temp);
		i++;
		sB = sB->next;
	}
	
	return result;
}








/*LongNumber mul_longnum2(LongNumber a, LongNumber b)
{
	LongNumber result = create();
	Digit* resDigit = (Digit*)malloc(sizeof(Digit));
	resDigit->next = NULL;
	resDigit->z = 0;
	addFirst(result, resDigit);

	LongNumber temp = (Digit*)malloc(sizeof(Digit));
	temp->next = NULL;
	LongNumber sA = a;
	Digit* sB = reverse(b);
	sB = sB->next;
	int i = 0;

	while (sB != NULL)
	{
		temp = mul_by_digit(mul_by_pow10(sA, i), sB->z);
		result = add_longnum(result, temp);
		delete_longnum(temp);
		i++;
		sB = sB->next;
	}

	return result;
}*/

/*void dodaj(LongNumber lst, Digit* n) {
	n->next = lst->next;
	lst->next = n;
}*/