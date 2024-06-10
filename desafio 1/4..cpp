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
        while (fgets(linha, 100, arq) != NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            viagens[totalViagens].total = 0; // Inicialize o total como zero
            totalViagens++;
        }
    }
    fclose(arq);
}

float calcularReembolso(float preco, int distancia)
{
    // Calcula o valor total do reembolso
    return (preco * distancia) / 3.0;
}

void calcularTotais()
{
    // Vari�veis para armazenar o total geral e o total de cada funcion�rio
    float totalGeral = 0;
    float totalPorFuncionario[totalViagens];
    memset(totalPorFuncionario, 0, sizeof(totalPorFuncionario)); // Inicializa o array com zero
    
    for(i = 0; i < totalViagens; i++)
    {
        // Calcula o total do reembolso para cada viagem
        viagens[i].total = calcularReembolso(viagens[i].preco, viagens[i].distancia);
        // Adiciona o total ao total geral
        totalGeral += viagens[i].total;
        // Adiciona o total ao funcion�rio correspondente
        totalPorFuncionario[i] += viagens[i].total;
    }

    // Cria o arquivo de sa�da
    FILE *relatorio = fopen("RelatorioViagens(2).md", "w");
    if (relatorio == NULL)
    {
        printf("Erro ao criar o arquivo de relat�rio\n");
        return;
    }

    // Escreve os dados no arquivo de sa�da em formato markdown
    fprintf(relatorio, "# Relat�rio de Viagens\n\n");
    fprintf(relatorio, "## Dados das Viagens\n\n");
    fprintf(relatorio, "| Matr�cula | Funcion�rio | Data | Origem | Destino | Dist�ncia | Pre�o | Total por Funcion�rio|\n");
    fprintf(relatorio, "|-----------|-------------|------|--------|---------|-----------|-------|----------------------|\n");
    for(i = 0; i < totalViagens; i++)
    {
        fprintf(relatorio, "| %d | %s | %s | %s | %s | %d | %.2f | %.2f |\n", viagens[i].matricula, viagens[i].funcionario, viagens[i].data, viagens[i].origem, viagens[i].destino, viagens[i].distancia, viagens[i].preco, totalPorFuncionario[i]);
    }

    // Escreve os totais no arquivo de sa�da
    fprintf(relatorio, "\n## Totais\n\n");
    fprintf(relatorio, "### Total Geral: %.2f\n\n", totalGeral);
    
    // Fecha o arquivo de sa�da
    fclose(relatorio);

    // Mostra mensagem de sucesso
    printf("Relat�rio criado com sucesso: RelatorioViagens(2).md\n");
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularTotais(); // Calcular os totais ap�s carregar os dados
    return 0;
}
