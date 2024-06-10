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
    int totalDia[31] = {0};
    char dataAtual[12];

    for(i=0; i < totalProducoes; i++)
    {
        totalMaquina[producoes[i].maquina - 1]++;
        if(strcmp(producoes[i].data, dataAtual)!= 0)
        {
            strcpy(dataAtual, producoes[i].data);
            totalDia[atoi(strtok(producoes[i].data, "/")) - 1]++;
        }
    }

    FILE *arq;
    arq = fopen("explosivos.md", "w");
    if (arq == NULL)
    {
        printf("Erro ao criar o arquivo de relatório\n");
    }
    else
    {
        fprintf(arq, "# Quantidade de explosivos produzidos por dia e por máquina\n");
        fprintf(arq, "|Dia|Máquina 1|Máquina 2|Máquina 3|Máquina 4|Total|\n");
        fprintf(arq, "|-|-|-|-|-|-:|\n");

        for(i=0; i < 31; i++)
        {
            fprintf(arq, "|%d|%d|%d|%d|%d|%d|\n", i+1, totalMaquina[0], totalMaquina[1], totalMaquina[2], totalMaquina[3], totalDia[i]);
        }
    }
    fclose(arq);
    
     // Mostra mensagem de sucesso
    printf("Relatório criado com sucesso: explosivos.md\n");
}

int main(){
    setlocale(LC_ALL, "");
    carregaDados();
    mostrarDados();
    return 0;
}
