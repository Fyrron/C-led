#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char id[10];
    long int offset;
    int size;
    char name[50];
    char year[50];
    char genre[50];
    char creator[50];
    char platform[50];
} Game;

void set_id(Game *game, char *id) {
    strcpy(game->id, id);
}

void set_offset(Game *game, long int offset) {
    game->offset = offset;
}

void set_size(Game *game, int size) {
    game->size = size;
}

void set_name(Game *game, char *name) {
    strcpy(game->name, name);
}

void set_year(Game *game, char *year) {
    strcpy(game->year, year);
}

void set_genre(Game *game, char *genre) {
    strcpy(game->genre, genre);
}

void set_creator(Game *game, char *creator) {
    strcpy(game->creator, creator);
}

void set_platform(Game *game, char *platform) {
    strcpy(game->platform, platform);
}

void imprime_game(Game game) {
    printf("%s|%s|%s|%s|%s|%s (%d bytes)\nLocal: offset = %ld bytes (%p)\n\n", game.id, game.name, game.year, game.genre, game.creator, game.platform, game.size, game.offset, &game.offset);
}

void construct(Game *game, char *id, long int offset, int size, char *name, char *year, char *genre, char *creator, char *platform) {
    set_id(game, id);
    set_offset(game, offset);
    set_size(game, size);
    set_name(game, name);
    set_year(game, year);
    set_genre(game, genre);
    set_creator(game, creator);
    set_platform(game, platform);
}

