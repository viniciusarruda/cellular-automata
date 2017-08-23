/*
 * Made by: Vinicius Arruda
 * E-mail: vinicius_farruda@hotmail.com
 * Blog: csvacation.wordpress.com
 */

#include<stdio.h>
#include<stdlib.h>

#ifdef _WIN32
	#define CLEAR "cls"
#else
	#define CLEAR "clear"
#endif

int TAM;

/* Prints the grid */
void imprime(char** board)
{
	int i, j;
	for(i=0;i<TAM;i++)
	{
		printf("\n");
		for(j=0;j<TAM;j++)
		{
			printf(" %c", board[i][j]); 
		}
	}
	printf("\n\n");
}


int limite(int x, int b)
{
	if(b)
		if(x==(TAM-1))
			return 0;
		else
			return x+1;
	else
		if(x==0)
			return (TAM-1);
		else
			return x-1;
}


int conta_vivo(char** board, int i, int j)
{
	int vivo = 0;

	if(board[limite(i,0)][limite(j,0)] == '0' || board[limite(i,0)][limite(j,0)] == '2') 
		vivo++;
	if(board[limite(i,0)][j] == '0' || board[limite(i,0)][j] == '2')
		vivo++;
	if(board[limite(i,0)][limite(j,1)] == '0' || board[limite(i,0)][limite(j,1)] == '2')
		vivo++;
	if(board[i][limite(j,0)] == '0' || board[i][limite(j,0)] == '2')
		vivo++;
	if(board[i][limite(j,1)] == '0' || board[i][limite(j,1)] == '2')
		vivo++;
	if(board[limite(i,1)][limite(j,0)] == '0' || board[limite(i,1)][limite(j,0)] == '2')
		vivo++;
	if(board[limite(i,1)][j] == '0' || board[limite(i,1)][j] == '2')
		vivo++;
	if(board[limite(i,1)][limite(j,1)] == '0' || board[limite(i,1)][limite(j,1)] == '2')
		vivo++;
	
	return vivo;
}


void nasce(char** board, int i, int j, int *f)
{
	if(conta_vivo(board, i, j) == 3)
	{
		board[i][j] = '3';
		*f = 1;
	}
}


void morre(char** board, int i, int j, int *f)
{
	if(conta_vivo(board, i, j)<2 || conta_vivo(board, i, j)>3)
	{
		board[i][j] = '2';
		*f = 1;	
	}
}


void atualiza(char** board)
{
	int i, j;
	for(i=0; i<TAM; i++)
		for(j=0;j<TAM;j++)
		{
			if(board[i][j] == '2')
				board[i][j] = '-';      
			if(board[i][j] == '3')
				board[i][j] = '0';
		}
}


void pausa(void)
{
	int i;
	for(i=0;i<100000000;i++);

}


int arquivo(char** board, char *file)
{
	int i, j;
	FILE *arquiv;
			
	if( (arquiv = fopen(file, "r") ) == NULL)
	{
		printf("Error opening the file !\n");
		return(1);
	}
	
	
	for(i=0; i<TAM; i++)                 
	{
		for(j=0; j<TAM; j++)
			board[i][j] = (char) getc(arquiv);
		getc(arquiv);
	}
	
	fclose(arquiv);
	return 0;
}



int main(int argc, char **argv)
{
	int i, j, flag;
	char** board;
	
	if(argc < 3)
	{
		printf("Usage: ./%s NameOfFileStartGrid.txt GridDimension.\n", argv[0]);
		return(1);
	}
	
	TAM = atoi(argv[2]);
	
	board = malloc((unsigned int) TAM * sizeof(char*));
	for(i = 0; i < TAM; i++)
		board[i] = malloc((unsigned int) TAM * sizeof(char));
	
	arquivo(board, argv[1]);

	flag = 1; 

	while(flag==1)
	{
		pausa();		
		
		system(CLEAR);
			
		imprime(board);

		flag = 0;
	
		for(i=0; i<TAM; i++)
			for(j=0;j<TAM;j++)
			{
				if(board[i][j] == '-') 
					nasce(board, i, j, &flag);		
				else if(board[i][j] == '0')
					morre(board, i, j, &flag);
			}
		atualiza(board);
	}
	free(board);
	
	return 0;
}