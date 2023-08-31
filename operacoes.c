#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Game busca(FILE *arquivo, char *key, Game *game) {
    int size;
    long int offset;
    char buffer[256];
    
    fseek(arquivo, 4, SEEK_SET);

    while(fread(&size, sizeof(short int), 1, arquivo) != 0) {
        offset = ftell(arquivo) - 2;

        fread(buffer, sizeof(char), size, arquivo);

        strtok(buffer, "|");

        if (strcmp(buffer, key) == 0) {
            char *id = buffer;

            char *name = strtok(NULL, "|");

            char *year = strtok(NULL, "|");

            char *genre = strtok(NULL, "|");

            char *creator = strtok(NULL, "|");

            char *platform = strtok(NULL, "|");

            construct(game, id, offset, size, name, year, genre, creator, platform);

            return *game;
        }
    }
    printf("Erro: registro não encontrado\n");
    exit(EXIT_FAILURE);
}

void remocao(FILE *arquivo, char *key, Game game) 
{
    char buffer[1] = "*";
    int led_pos = search_led_position(arquivo, game);    

    fseek(arquivo, game.offset + 2, SEEK_SET);
    fwrite(buffer, sizeof(char), 1, arquivo);
    fwrite(&led_pos, sizeof(int), 4, arquivo);
}

void insercao(FILE *arquivo, char *registry)
{
    fseek(arquivo, 0, SEEK_END);
    short int size = strlen(registry);

    fwrite(&size, sizeof(short int), 1, arquivo);
    fwrite(registry, sizeof(char), strlen(registry), arquivo);
}