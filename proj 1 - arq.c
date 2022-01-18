#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

//Funções
void cabecalho(FILE **in, FILE **out, int *linhas, int *colunas, int *lim_cinza, int opcao);
void opcaoA(FILE *in, FILE *out, int linhas, int colunas, int lim_cinza);
void opcaoB(FILE *in, FILE *out, int linhas, int colunas, int lim_cinza);
void opcaoC(FILE *in, FILE *out, int linhas, int colunas, int lim_cinza);

int main()
{
	//variaveis gerais
	FILE *in;
	FILE *out;
	
	int linhas, colunas, lim_cinza;
	
	//MENU
	
	int opcao=1;
	while(opcao != 0)
	{
		printf("Escolha uma opcao: ");
		printf("\n\n");
		
		printf("1 - limiarizacao");
		printf("\n\n");
		
		printf("2 - criar negativo");
		printf("\n\n");
		
		printf("3 - histograma da imagem");
		printf("\n\n");
		
		printf("0- finalizar programa");
		printf("\n\n");
		
		printf("opcao: ");
		scanf("%d",&opcao);
		printf("\n");
		
		if(opcao == 1)
		{
			cabecalho(&in, &out, &linhas, &colunas, &lim_cinza, opcao);
			opcaoA(in, out, linhas, colunas, lim_cinza);
			printf("limiarizacao feita");//função 1
			printf("\n\n");
		}
		else if(opcao == 2)
		{
			cabecalho(&in, &out, &linhas, &colunas, &lim_cinza, opcao);
			opcaoB(in, out, linhas, colunas, lim_cinza);
			printf("negativo feito");//função 2
			printf("\n\n");
		}
		else if(opcao == 3)
		{
			cabecalho(&in, &out, &linhas, &colunas, &lim_cinza, opcao);
			opcaoC(in, out, linhas, colunas, lim_cinza);
			printf("histograma feito");//função 3
			printf("\n\n");
		}
		else if(opcao > 3)
		{
			printf("opcao invalida");
			printf("\n\n");
		}
		else if(opcao == 0)
		{
			printf("finalizando programa...");
		}
	}
	
	fclose(in);
	fclose(out);
	return 0;
}

void cabecalho(FILE **in, FILE **out, int *linhas, int *colunas, int *lim_cinza, int opcao)
{
	char tipo_arq[10]; //string que armazena o tipo de arquivo P2
	
	*in = fopen("exemplo.pgm","rt");
	
	if(opcao == 1)
	{
		*out = fopen("limiarizacao.pgm","wt");
	}
	else if(opcao == 2)
	{
		*out = fopen("negativo.pgm","wt");
	}
	else if(opcao == 3)
	{
		*out = fopen("histograma.txt","wt");//faz .txt para o histograma
	}
	
    fgets(tipo_arq, 10, *in); //lê a primeira linha (P2)
    fprintf(*out, "%s", tipo_arq); //printa P2 no arquivo final

    fscanf(*in, "%d %d", colunas, linhas);
    fprintf(*out, "%d %d\n", *colunas, *linhas);

    fscanf(*in, "%d", lim_cinza);
    fprintf(*out, "%d\n", *lim_cinza);
    
    return;
}


void opcaoA(FILE *in, FILE *out, int linhas, int colunas, int lim_cinza)
{
	int pixel;
	int i, j;
	
	//execução
	for(i = 0; i < linhas; i++)//limiarização
	{
		for(j = 0; j < colunas; j++)
		{
			fscanf(in, " %d",&pixel);
			if(pixel > 150)
			{
				
				pixel = lim_cinza;//valor máximo
				fprintf(out, "%d ",pixel);
			}
			else
			{
				pixel = 0;//valor mínimo
				fprintf(out, "%d ",pixel);
			}
		}
	}
}

void opcaoB(FILE *in, FILE *out, int linhas, int colunas, int lim_cinza)
{	
	int pixel;
	int i, j;
	
	//execução
	for(i = 0; i < linhas; i++)//negativo
	{
		for(j = 0; j < colunas; j++)
		{
			fscanf(in, " %d",&pixel);
			
			pixel = lim_cinza - pixel;//inverte o valor
			
			fprintf(out, "%d ",pixel);
		}
	}
}

void opcaoC(FILE *in, FILE *out, int linhas, int colunas, int lim_cinza)
{
	int i, j;
	int pixel;
	int alcance_cinza = lim_cinza + 1;
	int valorPixel[alcance_cinza];
	
	for(i = 0; i < alcance_cinza; i++)//zera o contador de cada pixel
	{
		valorPixel[i] = 0;
	}
	//execução
	for(i = 0; i < linhas; i++)//histograma
	{
		for(j = 0; j < colunas; j++)
		{
			fscanf(in, " %d",&pixel);			
			valorPixel[pixel]++;
		}
	}
	
	fprintf(in, "Histograma:\n");
	
	for(i = 0; i < alcance_cinza; i++)
	{
		fprintf(out, "nº de pixel %d: %d \n",i, valorPixel[i]);
	}
}
