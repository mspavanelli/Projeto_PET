//--------------------------------------------------------------
// NOMES: 
// Primeiro Integrante: Matheus Santos Pavanelli
// Segundo Integrante: Décio de Souza Oliveira Júnior 
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
// #include <conio.h> Biblioteca exclusiva Windows
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
	int i;
	for ( i = 0; i < limite; i++ )
		fprintf(destino, "%i ", M[i]); 
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

void txtToTxt( FILE * source, FILE * target )
{
	int aux;
	while(!feof(source)){
		fscanf(source, "%i", &aux);
		fprintf(target, "%i ", aux);
	}
}


void merge( FILE * f1, FILE * f2, FILE * f3 )
{
	fseek(f2, 0, SEEK_SET); // joga o 'cursor' para o início do arquivo
	fseek(f1, 0, SEEK_SET);
	int lidof1,lidof2;
	while( fread(&lidof2, sizeof(int), 1, f2) == 1 )	// enquanto houver 
	{
		if(!(fread(&lidof2, sizeof(int), 1, f2) == 1)){
			fwrite( &lidof2, sizeof(int), 1, f3 );
			break;
		}else fseek(f2, - sizeof(int), SEEK_CUR);

		printf("LIDO F2 %i\n", lidof2);
		fread(&lidof1, sizeof(int), 1, f1);
		if(lidof1<lidof2) {
			
			fwrite( &lidof1, sizeof(int), 1, f3 );
			fseek(f2, - sizeof(int), SEEK_CUR);
		}
		else if(lidof1>lidof2) {
			fwrite( &lidof2, sizeof(int), 1, f3 );
			fseek(f1, - sizeof(int), SEEK_CUR);
		}

		else if (lidof1==lidof2){
			fwrite( &lidof1, sizeof(int), 1, f3);
		}
	}
	
	while( fread(&lidof1, sizeof(int), 1, f1) == 1 ) // termina de copiar arquivo 
	{
		fwrite( &lidof1, sizeof(int), 1, f3);
	}
	
	
}

void mergeTXT( FILE * f1, FILE * f2, FILE * f3 )
{
	int lidof1,lidof2, cont = 0;
	fscanf(f1, "%i", &lidof1);
	fscanf(f2, "%i", &lidof2);

	while(!(feof(f2)) && !(feof(f1)))	// enquanto houver 
	{
		// printf("cheguei aqui f1: %i\n", lidof1);
		// printf("cheguei aqui f2: %i\n", lidof2);
		if(lidof1>lidof2){
			fprintf(f3, "%i ",lidof2);
			fscanf(f2, "%i", &lidof2);			
		} else if(lidof1<lidof2){
			fprintf(f3, "%i ",lidof1);
			fscanf(f1, "%i", &lidof1);
		}else if (lidof1==lidof2){
			fprintf(f3, "%i ",lidof1);
			fscanf(f1, "%i", &lidof1);
			fscanf(f2, "%i", &lidof2);
		}
		// cont++;
	}
	
	// printf("lido1: %i\n", lidof1);
	// printf("lido2: %i\n", lidof2);

	while(!feof(f1)) // termina de copiar arquivo 
	{
		// printf("cheguei aqui só f1: %i\n", lidof1);
		
		fprintf(f3, "%i ",lidof1);
		fscanf(f1, "%i", &lidof1);
	}

	while(!feof(f2)) // termina de copiar arquivo 
	{
		fprintf(f3, "%i ",lidof2);
		fscanf(f2, "%i", &lidof2);
	}
	
	
}

void merge2(FILE * f1, FILE * f3){
	int lidof1;
	while( fread(&lidof1, sizeof(int), 1, f1) == 1 )
	{
		fwrite( &lidof1, sizeof(int), 1, f3);
	}
}

void binToTxt(FILE * origem, FILE *destino){
	fseek( origem, 0, SEEK_SET );
	int pavanelli;
	while ( 1 == (fread(&pavanelli, sizeof(int), 1, origem)) )
	{
		fprintf(destino, "%i ", pavanelli);
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
	//FILE * final = fopen( "final.tmp", "w" );	// arquivo ordenado em binário
	//fclose(final);
	FILE *final;
	int i, contador = 0, corrida = 0;

	//int numero;
	while( !feof(arquivo) )	// enquanto "houver arquivo"
	//while (fscanf(arquivo,"%i",&M[0]) == 1)	
	{	
		corrida++;
		printf("CORRIDA: %i\n", corrida);




		if(corrida ==1){
			for ( i = 0; i < 100 ; i++ )	// percorre todo o arquivo
			{
				if ( ! (fscanf(arquivo, "%i", &M[i] ) == 1) )	// preenche a memória com os dados
					break;		// para quando não tiver mais leitura
				contador++;		// quantidade de dados lidos
			}
			sort(contador);	// ordena a memória
			
			temp2 = fopen( "temp2.tmp", "w" );
			temp1 = fopen( "temp1.tmp", "w" );
			gravar_arquivo_tmp(temp2, contador);
			gravar_arquivo_tmp(temp1, contador);
			
			fclose(temp2);
			fclose(temp1);
			
			final = fopen( "final.tmp", "w" );
			
			
			temp2 = fopen( "temp2.tmp", "r" );
			temp1 = fopen( "temp1.tmp", "r" );

			mergeTXT(temp1, temp2, final);
			
			fclose(temp1);
			fclose(temp2);
			fclose(final);
			remove("temp1.tmp");
			remove("temp2.tmp");
			
			contador=0;	
		}





		else{

			temp1 = fopen( "temp1.tmp", "w" );
			final = fopen( "final.tmp", "r" );
			//contador++;
			txtToTxt(final, temp1);
			fclose(final);
			remove("final.tmp");
			
			
			for ( i = 0; i < 100 ; i++ )	// percorre todo o arquivo
			{
				if ( ! (fscanf(arquivo, "%i", &M[i] ) == 1) )	// preenche a memória com os dados
					break;		// para quando não tiver mais leitura
				contador++;		// quantidade de dados lidos
			}
			sort(contador);	// ordena a memória
			
			temp2 = fopen( "temp2.tmp", "w" );
			gravar_arquivo_tmp(temp2, contador);
			
			
			final = fopen( "final.tmp", "w" );
			
			
			fclose(temp1);
			fclose(temp2);
			temp2 = fopen( "temp2.tmp", "r" );
			temp1 = fopen( "temp1.tmp", "r" );

			mergeTXT(temp1, temp2, final);
			
			fclose(temp1);
			fclose(temp2);
			remove("temp1.tmp");
			remove("temp2.tmp");
			
			contador=0;

		}
	}

	//return;
	fclose(final);
	final = fopen( "final.tmp", "r" );
	FILE * saida = fopen( "saida.txt", "w" );
	txtToTxt(final, saida);
	
	fclose(final);
	remove("final.tmp");

	fclose(arquivo);
	//fclose(temp1);
	//fclose(temp2);
	//fclose(final);
	fclose(saida);
}





//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

	// FILE *arq1 = fopen("arq1.txt", "r");
	// FILE *arq2 = fopen("arq2.txt", "r");
	// FILE *arq3 = fopen("arq3.txt", "w");
	// mergeTXT(arq1, arq2, arq3);
	// return;

	char *arqteste = "exemplo.txt";
	

	// serao realizadas chamadas como esta:
	ordenar(arqteste);


}

// por favor nao inclua nenhum código abaixo da função main()
