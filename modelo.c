//--------------------------------------------------------------
// NOMES: 
// Primeiro Integrante: Matheus Santos Pavanelli
// Segundo Integrante: Décio de Souza Oliveira Júnior 
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


void binToTxt(FILE * origem, FILE *destino){
	fseek( origem, 0, SEEK_SET );
	int pavanelli;
	while ( 1 == (fread(&pavanelli, sizeof(int), 1, origem)) )
	{
		fprintf(destino, "%i ", pavanelli);
	}
}

void txtToBin(FILE * origem, FILE *destino){
	fseek( destino, 0, SEEK_SET );
	int pavanelli;
	while ( 1 == (fscanf(origem, "%i", &pavanelli ) ))
	{
		fprintf(destino, "%i ", pavanelli);
	}
}


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

void gravar_arquivo_tmp( FILE * destino, int limite )
{
	fseek(destino, 0, SEEK_SET);
	int i;
	for ( i = 0; i < limite; i++ )
		fwrite( &M[i], sizeof(int), 1, destino); 
}

void binToBin( FILE * source, FILE * target )
{
	fseek(source, 0, SEEK_SET);	// joga o 'cursor' para o início do arquivo
	fseek(target, 0, SEEK_SET);
	int aux;
	while( fread( &aux, sizeof(int), 1, source) == 1 ){
		fwrite( &aux, sizeof(int), 1, target );
	}
}

void merge( FILE * f1, FILE * f2, FILE * f3 )
{
	fseek(f2, 0, SEEK_SET); // joga o 'cursor' para o início do arquivo
	fseek(f1, 0, SEEK_SET);
	int lidof1,lidof2,a,b,memoria;
	while(1==1)	// enquanto houver 
	{
		b = fread(&lidof2, sizeof(int), 1, f2);
		a = fread(&lidof1, sizeof(int), 1, f1);
		if(a!=1 || b!=1) break;
		
		if(lidof1<lidof2) {
			
			if(lidof1 != memoria){
			
				fwrite( &lidof1, sizeof(int), 1, f3 );
				memoria = lidof1;
			}
			fseek(f2, - sizeof(int), SEEK_CUR);
		}
		else if(lidof1>lidof2) {
			
			if(lidof2 != memoria){
			
				fwrite( &lidof2, sizeof(int), 1, f3 );
				memoria = lidof2;
			}
			fseek(f1, - sizeof(int), SEEK_CUR);
		}

		else if (lidof1==lidof2){
			
			if(lidof1 != memoria){
				fwrite( &lidof1, sizeof(int), 1, f3);
				memoria = lidof1;
			}
		}
	}
	
	if(a==1){
		if(lidof1 != memoria) {
			fwrite( &lidof1, sizeof(int), 1, f3);
			memoria= lidof1;
		}
		while( fread(&lidof1, sizeof(int), 1, f1) == 1 )
		{
			if(lidof1 != memoria){
				fwrite( &lidof1, sizeof(int), 1, f3);
				memoria=lidof1;
			}
		}
		
	} else if (b==1){
		if(lidof2 != memoria) {
			fwrite( &lidof2, sizeof(int), 1, f3);
			memoria = lidof2;
		}
		while( fread(&lidof2, sizeof(int), 1, f2) == 1 )
		{
			if(lidof2 != memoria) {
				fwrite( &lidof2, sizeof(int), 1, f3);
				memoria = lidof2;
			}
		}
	}
	
	
}



void merge2(FILE * f1, FILE * f3){
	int lidof1;
	while( fread(&lidof1, sizeof(int), 1, f1) == 1 )
	{
		fwrite( &lidof1, sizeof(int), 1, f3);
	}
}


//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------
void ordenar(char *nomearq) {

	
	// seu codigo AQUI
	FILE *temp1;
	FILE *temp2;
	FILE * arquivo = fopen( nomearq, "r" );		// arquivo ser ordenado
	FILE * final = fopen( "final.tmp", "w+b" );	// arquivo ordenado em binário
	int i, contador = 0, corrida = 0;

	
	while( !feof(arquivo) )	// enquanto "houver arquivo"

	{	
		temp1 = fopen( "temp1.tmp", "w+b" );
		
		
		binToBin(final, temp1);
		
		fclose(final);
		remove("final.tmp");
		
		
		corrida++;
		for ( i = 0; i < 100 ; i++ )	// percorre todo o arquivo
		{
			if ( ! (fscanf(arquivo, "%i", &M[i] ) == 1) )	// preenche a memória com os dados
				break;		// para quando não tiver mais leitura
			contador++;		// quantidade de dados lidos
		}
		sort(contador);	// ordena a memória
		
		temp2 = fopen( "temp2.tmp", "w+b" );
		gravar_arquivo_tmp(temp2, contador);
		
		if(corrida == 1){
			fclose(temp1);
			remove("temp1.tmp");
			temp1 = fopen( "temp1.tmp", "w+b" );
			binToBin(temp2, temp1);
		}
		
		final = fopen( "final.tmp", "w+b" );
		
		
		
		merge(temp1, temp2, final);
		
		fclose(temp1);
		fclose(temp2);
		remove("temp1.tmp");
		remove("temp2.tmp");
		
		contador=0;
	}

	FILE * saida = fopen( "saida.txt", "w" );
	binToTxt(final, saida);
	
	fclose(final);
	remove("final.tmp");

	fclose(arquivo);

	fclose(saida);
	
	

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