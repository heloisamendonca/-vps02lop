#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char data[12];
    char hora[6];
    int maquina;
    int quantidade;
} Producao;

Producao producoes[50];
int totalProducoes = 0, i;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("producao.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq)!= NULL)
        {
            sscanf(linha, "%[^;];%[^;];%d", producoes[totalProducoes].data, producoes[totalProducoes].hora, &producoes[totalProducoes].maquina);
            producoes[totalProducoes].quantidade = 1;
            totalProducoes++;
        }
    }
    fclose(arq);
}

void mostrarDados()
{
    int totalMaquina[10] = {0};

    for(i=0; i < totalProducoes; i++)
    {
        totalMaquina[producoes[i].maquina - 1]++;
    }

    printf("Quantidade de explosivos produzidos por máquina:\n");
    for(i=0; i < 10; i++)
    {
        printf("Máquina %d: %d\n", i+1, totalMaquina[i]);
    }
}

int main(){
    setlocale(LC_ALL, "");
    carregaDados();
    mostrarDados();
    return 0;
}
