#include<stdio.h>
#include <math.h>
#include <stdbool.h>
//#include "Fermat.h"
#include <time.h>
#include <string.h>
#include "sys/times.h"
#include "sys/vtimes.h"



//        Variables Globales

long list[3] = { 0 };
clock_t begin, end;
clock_t beginTotal, endTotal;
double time_spent;



// Funciones utilitarias
void printArray(long entrada) {
	long i = 0;

	printf("\n%ld: ", entrada);
	while (i < 3) {

		if(list[i]!=0)
		{printf("%ld ", list[i]);}
		i++;
	}
	printf("\n");
}

double memoryUsage() {
	static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys,
			lastTotalIdle;
	double percent;
	FILE* file;
	unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;
	file = fopen("/proc/stat", "r");
	fscanf(file, "cpu %Ld %Ld %Ld %Ld", &totalUser, &totalUserLow, &totalSys,
			&totalIdle);
	fclose(file);
	total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow)
			+ (totalSys - lastTotalSys);
	percent = total;
	total += (totalIdle - lastTotalIdle);
	percent /= total;
	percent *= 100;
	return percent;

}

void insertSort() {
	long k = 0;
	long j, aux;
	while (k < 3) {
		for (j = k; j > 0 && list[j - 1] < list[j]; j--) {
			aux = list[j];
			list[j] = list[j - 1];
			list[j - 1] = aux;
		}
		k++;
	}

}

//   Funciones Propias del Algoritmos de Solucion
long biggestTriangular(long n) {
	double result = (sqrt(8 * n + 1) - 1) / 2;
	//printf("result: %f\n ",floor(result));
	return floor(result);
}

bool isTriangular(double n) {
	double result;
	result = (sqrt(8 * n + 1) - 1) / 2;
	//printf("result: %f\n ",result);
	if (fmod(result, 1) == 0) {

		return true;
	}
	return false;

}


long triangular(long n) {
	return (n * (n + 1)) / 2;
}



bool metodoUno(long n)
{
	begin=clock();
	double result= sqrt(n);

	if(floor(result)==result)
	{
		list[0]= triangular(result);
		list[1]=triangular(result-1);
		list[2]=0;
		end=clock();
		printf("calculado metodo 1");
		return true;

	}
	end=clock();
	return false;
}

bool metodoDos(long n) {
	long a = biggestTriangular(n);
	long b, k, j;
	long triangularJ, triangularK, triangularNJK;
	begin = clock();
	for (j = 0; j < a; j++) {
		triangularJ = triangular(j);
		b = biggestTriangular(n - triangularJ);
		for (k = j; k < b; k++) {
			triangularK = triangular(k);
			if (triangularK + triangularJ > n)
			{

			}
			else
			{
				triangularNJK = n - triangularJ - triangularK;
				if (isTriangular(triangularNJK)
						&& (triangularNJK) >= triangularK) //tercer sumando
				{

					list[0] = triangularJ;
					list[1] = triangularK;
					list[2] = triangularNJK;
					end = clock();
					printf("calculada metodo 2");
					return true;
				}
			}
		}
	}
	end = clock();
	return false;
}

void resetList()
{
	list[0]=0;
	list[1]=0;
	list[2]=0;

}

void printInfo(long n, bool opcion)
{
	if(opcion)
	{
		insertSort(n);
		printArray(n);
		printf("time spent by %ld: %f", n,
				(double) (end - begin) / CLOCKS_PER_SEC);
		printf("\nCPU currently used: %f%\n", memoryUsage());
		begin = 0;
		end = 0;
	}
}

bool evaluateSingleNumber(long n, bool opcion)
{
	if(isTriangular(n))
	{	begin=clock();
		list[0]=n;
		list[1]=0;
		list[2]=0;
		end=clock();
		printInfo(n,opcion);
		return true;
	}
	else
	{
		if(metodoUno(n))
		{	printInfo(n,opcion);
			return true;
		}
		else{
			metodoDos(n);
			printInfo(n,opcion);
			return true;
		}
	}
   return false;
}
void evaluateConjeture()
{
	long i = 0;
	beginTotal = clock();
	long maximun = pow(10, 9);
	while (i < maximun) {
		printf("\n%ld", i);
		evaluateSingleNumber(i, false);
		resetList();
		i++;
	}
	endTotal = clock();
	if (i == pow(10, i)) {
		printf("1\n");
	}
	else{printf("0\n");}

	printf("time spent to prove the entire conjecture: %f",
			(double) (endTotal - beginTotal) / CLOCKS_PER_SEC);
	printf("\nCPU currently used: %f %\n", memoryUsage());

}

// Metodo principal
void main()
{
	long n;
	printf("Enter a number: ");
	scanf("%ld", &n);
	while (n != -1)
	{
		if (n == 0)
		{
		  evaluateConjeture();
		}
		else
		{
		  evaluateSingleNumber(n, true);
		}
		printf("Enter a number: ");
		scanf("%ld", &n);
	}

}

