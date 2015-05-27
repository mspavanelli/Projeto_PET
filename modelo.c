//--------------------------------------------------------------
// NOMES: 
// Primeiro Integrante: Matheus Santos Pavanelli
// Segundo Integrante: Décio Oliveira Júnior 
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
		printf("%d ", M[i] );
	printf("\n");
}

void gravar_arquivo( FILE * destino, int limite )
{
	int i;
	for ( i = 0; i < limite; i++ )
		fprintf(destino, "%i ", M[i]); 
}

void gravar_arquivo_tmp( FILE * destino, int limite )
{
	int i;
	for ( i = 0; i < limite; i++ )
		fwrite( &M[i], sizeof(int), 1, destino); 
}

/* Ordenação Interna usando SelectionSort */
void sort( int limite )
{
	int i, j;
	for ( i = 0; i < limite; i++ )
	{
		for ( j = i; j < limite; j++ )
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
/* Copia conteúdo de um arquivo binário para outro */
void binToBin( FILE * source, FILE * target )
{
	fseek(source, 0, SEEK_SET);	// joga o 'cursor' para o início do arquivo
	int aux;
	while( fread( &aux, sizeof(int), 1, source) )
		fwrite(  &aux, sizeof(int), 1, target );
}

void binToTxt(){}

/* Junta conteúdo de f1 e f2 em f3 em ordem crescente */
void merge( FILE * f1, FILE * f2, FILE * f3 )
{
	/*
	- f1: acumulador
	- f2: corrida atual
	- f3: merge de (f1,f2)
	*/
	fseek(f2, 0, SEEK_SET); // joga o 'cursor' para o início do arquivo
	fseek(f1, 0, SEEK_SET);
	int lidof1,lidof2, contadorf2=0, contadorf1=-1, memoria =0;
	while( fread(&lidof2, sizeof(int), 1, f2) == 1 )	// enquanto houver 
	{
		contadorf2++;
		fread(&lidof1, sizeof(int), 1, f1);
		contadorf1++;
		if(lidof1<lidof2 && lidof1!= memoria) {
			
			fwrite( &lidof1, sizeof(int), 1, f3 );
			memoria = lidof1;
			fseek(f2, - sizeof(int), SEEK_CUR);
			// printf("contadorf1\n");
		}
		else if(lidof1>lidof2 && lidof2!= memoria) {
			fwrite( &lidof2, sizeof(int), 1, f3 );
			memoria = lidof2;
			fseek(f1, - sizeof(int), SEEK_CUR);
			// printf("contadorf1\n");
		}

		else if (lidof1==lidof2 && lidof1!= memoria){
			fwrite( &lidof1, sizeof(int), 1, f3);
			memoria = lidof1;
			printf("Lido %i %i\n", lidof1, lidof2);
			printf("contadorfx\n");
		}
		// printf("Lido %i %i\n", lidof1, lidof2);
		// printf("Contador f2: %i\n", contadorf2);
	}

	while( fread(&lidof1, sizeof(int), 1, f2) == 1 )
	{
		fwrite( &lidof1, sizeof(int), 1, f3);
	}
}

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
void ordenar(char *nomearq)
{
	FILE * arquivo = fopen( nomearq, "r" );		// arquivo ser ordenado
	FILE * saida = fopen( "saida.txt", "w" );	// arquivo ordenado
	FILE * temp1 = fopen( "temp1.tmp", "wb+" );	// temporário auxiliar 1
	FILE * temp2 = fopen( "temp2.tmp", "wb+" );	// temporário auxiliar 2
	FILE * final = fopen( "final.tmp", "wb+" );	// arquivo ordenado em binário
	int i, contador = 0, corrida = 0;

	while( !feof(arquivo) )	// enquanto "houver arquivo"
	{	
		binToBin(final, temp1);
		corrida++;
		printf("Corrida: %i\n", corrida);
		for ( i = 0; i < 100 ; i++ )	// percorre todo o arquivo
		{
			if ( ! (fscanf(arquivo, "%i", &M[i] ) == 1) )	// preenche a memória com os dados
				break;		// para quando não tiver mais leitura
			contador++;		// quantidade de dados lidos
		}
		sort( contador );	// ordena a memória
		gravar_arquivo_tmp(temp2, contador);
		
		if(corrida == 1){
			binToBin(temp2, temp1);
			//contador=0;
			//continue;
			merge(temp2, temp1, final);
			break;
		}

		printf("Merge\n");
		merge(temp1, temp2, final);
		contador = 0;
	}

	fseek( final, 0, SEEK_SET );
	int pavanelli;
	while ( 1 == (fread(&pavanelli, sizeof(int), 1, final)) )
	{
		fprintf(saida, "%i ", pavanelli);
		// printf("Imprimindo\n");
	}


	//binToTxt()
	//fwrite( &M[0], sizeof(int), 100, temp1 );	// escreve o conteúdo da memória no arquivo temporário
	// if ((fread( &M[0], sizeof(int), 1 ,temp1) == 1));
	// gravar_arquivo( saida, 100 );

	//binToBin( temp1, temp2 );

	 //merge( temp1, temp2, final );

	/*	Próximos Passos
	 *
	 * - Testar acesso dos arquivos binários com o SEEK
	 * - Algorítmo de junção (merge)
	 * 
	 *  IMPORTANTE
	 * 
	 *  - fread(bloco de mem, tamanho de cada elemento, qtde_de_elementos, arquivo)
	 * 	 
	 */
}


// ---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// ---------------------------------------------------------
int main()
{
	char *arqteste = "exemplo.txt";
	ordenar(arqteste);
}

// por favor nao inclua nenhum código abaixo da função main()
