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
		corrida++;
		for ( i = 0; i < 100 ; i++ )	// percorre todo o arquivo
		{
			if ( ! (fscanf(arquivo, "%i", &M[i] ) == 1) )	// preenche a memória com os dados
				break;		// para quando não tiver mais leitura
			contador++;		// quantidade de dados lidos
		}
		sort( contador );	// ordena a memória
		contador = 0;
	}
	fwrite( &M[0], sizeof(int), 10, temp1 );	// escreve o conteúdo da memória no arquivo temporário
	if ((fread( &M[0], sizeof(int), 1 ,temp1) == 1));
	gravar_arquivo( saida, 100 );

	binToBin( temp1, temp2 );

	/*	Próximos Passos
	 *
	 * - Testar acesso dos arquivos binários com o SEEK
	 * - 
	 * - Algorítmo de junção (merge)
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
