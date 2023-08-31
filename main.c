#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.c"
#include "led.c"
#include "operacoes.c"

void executa_operacoes(char *nome_arquivo) {
    FILE *arquivo;
    FILE *dados;
    char linha[100];
    Game game;

    arquivo = fopen(nome_arquivo, "r");
    
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
        exit(EXIT_FAILURE);
    }

    dados = fopen("dados.dat", "rb+");

    if (dados == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo dados.dat\n");
        exit(EXIT_FAILURE);
    }

    fseek(dados, 4, SEEK_SET);

    while (fgets(linha, 100, arquivo) != NULL) {
        char operation = linha[0];
        char *check_new_line = strchr(linha, '\n');

        if (check_new_line != NULL) {
            linha[strlen(linha) - 1] = '\0';
        }

        switch(operation) {
            case 'i':
                printf("Inserção de registro\n");
                insercao(dados, linha + 2);
                printf("Registro inserido! (%ld bytes)\n", strlen(linha + 2));
                printf("Local: fim do arquivo\n\n");
                break;
            case 'r':
                printf("Remoção do registro de chave: %s ", linha + 2);
                game = busca(dados, linha + 2, &game);
                remocao(dados, linha + 2, game);
                printf("Registro removido! (%d bytes) \n", game.size);
                printf("Local: offset = %ld bytes (%p)\n\n", game.offset, &game.offset);
                break;
            case 'b':
                printf("Busca pelo registro de chave: %s\n", linha + 2);
                game = busca(dados, linha + 2, &game);
                imprime_game(game);
                break;
            default:
                fprintf(stderr, "Operação invalida!\n");
                exit(EXIT_FAILURE);
        }
    }

    fclose(dados);
    fclose(arquivo);
}


int main(int argc, char *argv[]) {

    if (argc == 3 && strcmp(argv[1], "-e") == 0) {

        printf("Modo de execucao de operacoes ativado ... nome do arquivo = %s\n", argv[2]);
        executa_operacoes(argv[2]);

    } else if (argc == 2 && strcmp(argv[1], "-p") == 0) {
        FILE* dados;
        dados = fopen("dados.dat", "rb+");
        printf("Modo de impressao da LED ativado ...\n");
        imprime_led(dados);
        fclose(dados);
    } else {
        fprintf(stderr, "Argumentos incorretos!\n");
        fprintf(stderr, "Modo de uso:\n");
        fprintf(stderr, "$ %s -e nome_arquivo\n", argv[0]);
        fprintf(stderr, "$ %s -p\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    return 0;
}