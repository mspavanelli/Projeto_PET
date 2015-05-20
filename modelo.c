//--------------------------------------------------------------
// NOMES: escreva o nome dos integrantes aqui
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>



// ######### ESCREVA O NROUSP DO PRIMEIRO INTEGRANTE AQUI
char* nroUSP1() {
    return("7580011");
}



// ######### ESCREVA O NROUSP DO SEGUNDO INTEGRANTE AQUI (OU DEIXE COM ZERO)
char* nroUSP2() {
    return("9065701");
}

void ordenar(char *nomearq);


// esta eh a memoria util para ordenacao
// nao declare nenhuma variavel global alem desta
// e nao use vetores ou listas adicionais
int M[100];

/* Funções Auxiliares*/
void imprimir_vetor()
{
	int i;
	for( i = 0; i < 100; i++ )
	{
		printf("%d ", M[i] );
	}
	printf("\n");
}

void gravar_arquivo( FILE * destino )
{
	int i;
	for ( i = 0; i < 100; i++ )
	{
		fprintf(destino, "%i ", M[i]);
	} 
}

/* Ordenação Interna */
void sort()
{
	int i, j;
	for ( i = 0; i < 100; i++ )
	{
		for ( j = i; j < 100; j++ )
		{
			if ( M[j] < M[i] )
			{
				int aux = M[j];
				M[j] = M[i];
				M[i] = aux;
			}
		}
	}
}

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
void ordenar(char *nomearq)
{
	FILE * arquivo = fopen( nomearq, "r" );		// arquivo ser ordenado
	FILE * saida = fopen( "saida.txt", "w" );	// arquivo ordenado
	int i;	// variável de iteração
	
	while( !feof(arquivo) )	// enquanto "houver arquivo"
	{	
		for ( i = 0; i < 100; i++ )	// percorre todo o arquivo
			fscanf(arquivo, "%i", &M[i]);	// preenche a memória com os dados
		sort();	// ordena a memória
		gravar_arquivo(saida);	// grava dados ordenados no arquivo de saída
	}

}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

	char *arqteste = "exemplo.txt";
	

	// serao realizadas chamadas como esta:
	ordenar(arqteste);


}

// por favor nao inclua nenhum código abaixo da função main()
