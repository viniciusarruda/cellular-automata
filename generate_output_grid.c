/*
 * Made by: Vinicius Arruda
 * E-mail: vinicius_farruda@hotmail.com
 * Blog: csvacation.wordpress.com
 */

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	int i, j, tam;               
	FILE *arquivo;
	
	if(argc < 3)
	{
		printf("Usage: ./%s OutputFileName.txt GridDimension\n", argv[0]);
		return(1);
	}


	if( (arquivo = fopen(argv[1], "w") ) == NULL)
	{
		printf("Erro ao abrir o arquivo !\n");
		return(1);
	}	
			
	tam = atoi(argv[2]);

	
	
	for(i=0; i<tam; i++)
	{
		for(j=0; j<tam; j++)
			putc('-',arquivo);
	putc('\n',arquivo);
	}
			
			
	fclose(arquivo);

	return(0);
}