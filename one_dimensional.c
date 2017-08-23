/*
 * Made by: Vinicius Arruda
 * E-mail: vinicius_farruda@hotmail.com
 * Blog: csvacation.wordpress.com
 */

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void itobin(int r, int* rbin);
int meupow(int n, int e);
void itera(char* aux);
int op(char viz[4]);
void next_gen(char* gen, int* r, char* next);

int
main(int argc, char* argv[])
{
	int i;
	if (argc != 3)
	{
		printf("Usage: ./space-time rule numberOfGenerations\n");
		return 1;
	}
	
	int rule[8];
	itobin(atoi(argv[1]), rule);
	
	char g[91];
	
	for(i = 0; i < 90;i++)
		g[i] = ' ';
	g[90] = '\0';
	
	g[44] = 'o';
	
	char n[91];
	
	
	/* Print the diagram */
	printf("\n  # |          SPACE-TIME DIAGRAM    CELLULAR AUTOMATA    RULE %d    FOR %d GENERATIONS\n", atoi(argv[1]), atoi(argv[2]));
	
	printf("----+-------------------------------------------------------------------------------------------\n");
	
	printf(" %2d | %s\n", 0, g); 
	for (i = 0; i < atoi(argv[2]); i++)
	{
		next_gen(g, rule, n);
		strcpy(g, n);
		printf(" %2d | %s\n", i+1, g); 
	}
	printf("\n");
	
	return 0;
}

void
next_gen(char* gen, int* r, char next[])
{
	int i;
	char var[4];
	for (i = 0; i < 90; i++) 
	{	
		if (i == 0)
		{
			var[0] = gen[89];
			var[1] = gen[i];
			var[2] = gen[1];
			var[3] = '\0';
			next[i] = (char) r[op(var)];
		}
		else if (i == 89)
		{	
			var[0] = gen[88];
			var[1] = gen[i];
			var[2] = gen[0];
			var[3] = '\0';
			next[i] = (char) r[op(var)];
		}
		else
		{
			var[0] = gen[i-1];
			var[1] = gen[i];
			var[2] = gen[i+1];
			var[3] = '\0';
			next[i] = (char) r[op(var)];
		}
	}
	next[90] = '\0';
}

int
op(char viz[4])	
{
	int i;
	char aux[4] = "   ";
	
	if (!strcmp(viz, aux))
			return 0;
	
	for (i = 0; i < 7; i++)
	{
		itera(&aux[2]); 
		if (!strcmp(viz, aux))
			return (i + 1);
	}
			
	return 99; /* Error flag */
}



void
itera(char* aux)
{	
	if (*aux == ' ')
		*aux = 'o';
	else 
	{
		*aux = ' ';
		itera(&*(aux - 1));
	}
}

void 
itobin(int r, int* rbin)
{
	int i;
	for (i = 7; i >= 0; i--)
	{
		*(rbin + i) = r / meupow(2,i);
		r %= meupow(2,i);
	}
	
	for (i = 0; i < 8; i++)
		if (rbin[i] == 0)
			rbin[i] = 32; /* Code of ' ' from ascii table */
		else
			rbin[i] = 111; /* Code of 'o' from ascii table */
}

int 
meupow(int n, int e)
{
	int i, num = 1;
	for (i = 0; i < e; i++)
		num *= n;

	return num;
}