#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("viagens.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq)!= NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            totalViagens++;
        }
    }
    fclose(arq);
}

void mostrarDados()
{
    printf("Viagens ACME:\n");
    printf("Matricula\tFuncionario\tData\tOrigem\tDestino\tDistância\tPreço\tTotal\n");

    float totalGeral = 0.0;
    char funcionarioAtual[50] = "";
    float totalFuncionario = 0.0;

    for(i=0; i < totalViagens; i++)
    {
        if(strcmp(viagens[i].funcionario, funcionarioAtual) != 0)
        {
            if(i > 0)
            {
                printf("Total do funcionário %s: %.2f\n", funcionarioAtual, totalFuncionario);
            }
            strcpy(funcionarioAtual, viagens[i].funcionario);
            totalFuncionario = 0.0;
        }

        printf("%d\t%s\t%s\t%s\t%s\t%d\t%.2f\t%.2f\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem,  viagens[i].destino, viagens[i].distancia, viagens[i].preco,  viagens[i].total);
        totalFuncionario += viagens[i].total;
        totalGeral += viagens[i].total;
    }

    printf("Total do funcionário %s: %.2f\n", funcionarioAtual, totalFuncionario);
    printf("Total Geral: %.2f\n", totalGeral);
}

float Reembolso(int distancia, float preco) {
    return distancia * preco / 3;
}

void calcularReembolso() {
    float totalGeral = 0.0;
    for(i=0; i < totalViagens; i++) {
        viagens[i].total = Reembolso(viagens[i].distancia, viagens[i].preco);
        totalGeral += viagens[i].total;
    }
    printf("Total geral de reembolso: %.2f\n", totalGeral);
}

int main(){
    setlocale(LC_ALL, "");
    carregaDados();
    calcularReembolso();
    mostrarDados();
    return 0;
}
