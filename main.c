#include <stdio.h>
#include <stdlib.h>
#include "longnum.h"

void main() {
	LongNumber numa = read_longnum("a.txt");
	//numa = reverse(numa);
	print_longnum(numa);

	LongNumber numb = read_longnum("b.txt");
	//numb = reverse(numb);
	print_longnum(numb);
	
	LongNumber numc = add_longnum(numa, numb);
	LongNumber numd = mul_by_digit(numc, 9);
	numc = reverse(numc);
	print_longnum(numc);
	numd = reverse(numd);
	print_longnum(numd);
	write_longnum(numd, "c.txt");
	
	LongNumber nume = mul_by_pow10(numd, 3);
	print_longnum(nume);
	numb = reverse(numb);
	LongNumber numf = mul_longnum(numa, numb);
	print_longnum(numf);

	delete_longnum(numa);
	delete_longnum(numb);
	delete_longnum(numc);
	delete_longnum(numd);
	delete_longnum(nume);
	//delete_longnum(numf);
	
}