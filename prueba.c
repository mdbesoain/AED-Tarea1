/*
 * prueba.c
 *
 *  Created on: Apr 15, 2014
 *      Author: mdbesoain
 */
#include <math.h>
#include <stdio.h>
#include "Fermat.h"
#include <stdbool.h>

void runTest()
{	int i=0;
	while(i<10)
	{
		evaluateSingleNumber(pow(10,i), true);
		i++;
	}
}

int principal(void)
{	int opcion;
	printf("Enter an opcion");
	scanf("%d",&opcion);
	if(opcion==1)
	{
		runTest();
	}

}
