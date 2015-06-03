//--------------------------------------------------------------
// NOMES: 
// Primeiro Integrante: Matheus Santos Pavanelli
// Segundo Integrante: Décio de Souza Oliveira Júnior 
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
// #include <malloc.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1

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

/* Ordenação da memória: Selection Sort */
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

/* Funções Auxiliares de Escrita */

/* Copia conteúdo de arquivo binário para arquivo texto */
void binToTxt(FILE * origem, FILE *destino){
	fseek( origem, 0, SEEK_SET ); // joga o 'cursor' para o início do arquivo
	int caractere;
	// Enquanto ouver entrada, copia para a saída
	while ( 1 == (fread(&caractere, sizeof(int), 1, origem)) )
		fprintf(destino, "%i ", caractere);
}

/* Clona um arquivo binário */
void binToBin( FILE * source, FILE * target )
{
	fseek(source, 0, SEEK_SET); // joga o 'cursor' para o início do arquivo de entrada
	fseek(target, 0, SEEK_SET); // joga o 'cursor' para o início do arquivo de saída
	int aux;
	// Enquanto ouver entrada, copia para a saída
	while( fread( &aux, sizeof(int), 1, source) == 1 )
		fwrite( &aux, sizeof(int), 1, target );
}

/* Copia os dados da memória para um arquivo temporário.
	A variável limite serve para indicar o tamanho da corrida
*/
void gravar_arquivo_tmp( FILE * destino, int limite )
{
	fseek(destino, 0, SEEK_SET); // joga o 'cursor' para o início do arquivo
	int i;
	// Lê a memória e grava no arquivo temporário
	for ( i = 0; i < limite; i++ )
		fwrite( &M[i], sizeof(int), 1, destino); 
}

/* Intercalação de arquivos utilizando o princípio do Merge Sort
	- Arquivo f1 e f2: Arquivos de entrada
	- Arquivo f3: Resultado da intercalação de f1 com f2
*/
void merge( FILE * f1, FILE * f2, FILE * f3 )
{
	fseek(f1, 0, SEEK_SET); 		// joga o 'cursor' para o início do arquivo
	fseek(f2, 0, SEEK_SET); 		// joga o 'cursor' para o início do arquivo
	int lidof1, lidof2;				// valores lidos dos arquivos de entrada
	int controle_f1, controle_f2;	// determina se o arquivo acabou
	int memoria;					// último item escrito no arquivo final
	while( TRUE )
	{
		// Lê os arquivos de entrada
		controle_f1 = fread(&lidof1, sizeof(int), 1, f1);
		controle_f2 = fread(&lidof2, sizeof(int), 1, f2);
		// se algum dos arquivos acabou, sai do laço
		if( controle_f1 !=1 || controle_f2 !=1 ) break;
		
		// Caso 1: item de f1 menor que f2
		if( lidof1 < lidof2 )
		{	
			if( lidof1 != memoria )	 // controle de repetição
			{
				fwrite( &lidof1, sizeof(int), 1, f3 );
				memoria = lidof1;
			}
			fseek(f2, - sizeof(int), SEEK_CUR);	 // corrige cursor para próxima leitura
		}
		// Caso 2: item de f2 menor que f1
		else if( lidof1 > lidof2 )
		{	
			if( lidof2 != memoria ) // controle de repetição
			{
				fwrite( &lidof2, sizeof(int), 1, f3 );
				memoria = lidof2;
			}
			fseek(f1, - sizeof(int), SEEK_CUR); // corrige cursor para próxima leitura
		}
		// Caso 3: item de f1 igual ao de f2
		else if ( lidof1 == lidof2 )
		{	
			if( lidof1 != memoria ) // controle de repetição
			{
				fwrite( &lidof1, sizeof(int), 1, f3);
				memoria = lidof1;
			}
		}
	}

	// Caso o arquivo 2 chegue ao fim antes do arquivo 1, copia restante do arquivo 1
	if ( controle_f1 == 1 )
	{
		if( lidof1 != memoria ) // controle de repetição
		{
			fwrite( &lidof1, sizeof(int), 1, f3);
			memoria= lidof1;
		}
		while( fread(&lidof1, sizeof(int), 1, f1) == 1 )
		{
			if( lidof1 != memoria ) // controle de repetição
			{
				fwrite( &lidof1, sizeof(int), 1, f3);
				memoria = lidof1;
			}
		}	
	} 
	// Caso o arquivo 1 chegue ao fim antes do arquivo 2, copia restante do arquivo 2
	else if ( controle_f2 == 1 )
	{
		if( lidof2 != memoria ) // controle de repetição
		{
			fwrite( &lidof2, sizeof(int), 1, f3);
			memoria = lidof2;
		}
		while( fread(&lidof2, sizeof(int), 1, f2) == 1 )
		{
			if( lidof2 != memoria ) // controle de repetição
			{
				fwrite( &lidof2, sizeof(int), 1, f3);
				memoria = lidof2;
			}
		}
	}
}

/* A lógica usada foi ordenar e já intercalar a cada corrida realizada */
void ordenar(char *nomearq)
{
	// Arquivos de auxilío para a intercalação
	FILE * temp1;
	FILE * temp2;

	FILE * arquivo = fopen( nomearq, "r" );		// arquivo ser ordenado
	FILE * final = fopen( "final.tmp", "w+b" );	// arquivo ordenado em binário
	int i;				// iterador para a memória
	int contador = 0;	// Quantidade ocupada na memória a cada corrida
	int corrida = 0;	// Marca a quantidade de corridas
	
	while( !feof(arquivo) )	// enquanto arquivo de entrada não chegar ao fim
	{	
		temp1 = fopen( "temp1.tmp", "w+b" );	// cria temp1 binário para escrita e leitura	
		binToBin(final, temp1);					// copia as corridas já ordenadas para o temp1
		fclose(final);							// fecha e 
		remove("final.tmp");					// exclui o arquivo

		corrida++;								// contabiliza o número da corrida atual 

		/* Percorre o arquivo (corrida) */
		for ( i = 0; i < 100 ; i++ )
		{
			if ( ! (fscanf(arquivo, "%i", &M[i] ) == 1) )	// preenche a memória com os dados
				break;		// para quando não tiver mais leitura
			contador++;		// quantidade de dados lidos
		}
		sort(contador);	// ordena dados na memória
		
		temp2 = fopen( "temp2.tmp", "w+b" );	// cria temp2 binário para escrita e leitura 
		gravar_arquivo_tmp(temp2, contador);	// grava os itens ordenados da memória no temp2 
		
		/* CASO ESPECIAL: Primeira Corrida
		 * Condição executada quando não há nenhuma corrida ordenada previamente
		 */
		if(corrida == 1)
		{
			fclose(temp1);
			remove("temp1.tmp");
			temp1 = fopen( "temp1.tmp", "w+b" );
			binToBin(temp2, temp1);
		}
		/* ------------- */

		final = fopen( "final.tmp", "w+b" );	// cria arquivo final
		
		merge(temp1, temp2, final);				// junta os arquivos no arquivo final
		
		// Fecha e exclui os arquivos temporários
		fclose(temp1);				
		fclose(temp2);
		remove("temp1.tmp");
		remove("temp2.tmp");

		contador = 0;							// Zera o contador indicando uma nova corrida
	}

	FILE * saida = fopen( "saida.txt", "w" );	// cria arquivo de saída tipo texto
	binToTxt(final, saida);						// copia o resultado final da intercalação na saída
	
	// Fecha e exclui o arquivo temporário
	fclose(final);
	remove("final.tmp");

	// Fecha os arquivo de entrada e saída
	fclose(arquivo);
	fclose(saida);
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main()
{
	char *arqteste = "exemplo.txt";
	ordenar(arqteste);
}

// por favor nao inclua nenhum código abaixo da função main()