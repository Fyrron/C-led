#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int head_offset;
    int prev_offset;
    int prev_prev_offset;
    int cur_offset;
    int cur_size;
} Led;

Led check_led_head(FILE *arquivo) {
    Led led;
    fseek(arquivo, 0, SEEK_SET);
    fread(&led.head_offset, sizeof(int), 1, arquivo);
    return led;
}

void set_led_head(FILE *arquivo, Led led)
{
    fseek(arquivo, 0, SEEK_SET);
    fwrite(&led.head_offset, sizeof(int), 1, arquivo);
}

long int search_led_position(FILE *arquivo, Game game)
{
    Led led = check_led_head(arquivo);

    if(led.head_offset == -1) {
        led.head_offset = game.offset;
        set_led_head(arquivo, led);
        return -1;
    }

    fseek(arquivo, led.head_offset, SEEK_SET);
    fread(&led.cur_size, sizeof(short int), 1, arquivo);
    if(led.cur_size < game.size) {
        long int return_to_led_value = led.head_offset;
        led.head_offset = game.offset;
        set_led_head(arquivo, led);
        return return_to_led_value;
    }

    while(led.cur_size > game.size) {
        fseek(arquivo, -2, SEEK_CUR);
        led.prev_prev_offset = ftell(arquivo);
        fseek(arquivo, 3, SEEK_CUR);
        fread(&led.cur_offset, sizeof(int), 1, arquivo);
        
        if(led.cur_offset == -1) {
            fseek(arquivo, led.prev_prev_offset + 3, SEEK_SET);
            fwrite(&game.offset, sizeof(int), 1, arquivo);
            return -1;
        }
        fseek(arquivo, led.cur_offset, SEEK_SET);
        fread(&led.cur_size, sizeof(short int), 1, arquivo);
        led.prev_offset = led.cur_offset;
    }

    fseek(arquivo, led.prev_prev_offset + 3, SEEK_SET);
    fwrite(&game.offset, sizeof(int), 1, arquivo);
    return led.cur_offset;
}


void imprime_led(FILE *arquivo) {
    Led led = check_led_head(arquivo);
    
    if(led.head_offset == -1) {
        printf("Led vazia\n");
        return;
    }

    printf("LED -> ");
    fseek(arquivo, led.head_offset, SEEK_SET);
    fread(&led.cur_size, sizeof(short int), 1, arquivo);
    fseek(arquivo, 1, SEEK_CUR);
    fread(&led.cur_offset, sizeof(int), 1, arquivo);

    while(led.cur_offset != -1) {
        printf(" [offset: %d, tam: %d] ->", led.cur_offset, led.cur_size);
        fseek(arquivo, led.cur_offset, SEEK_SET);
        fread(&led.cur_size, sizeof(short int), 1, arquivo);
        fseek(arquivo, 1, SEEK_CUR);
        fread(&led.cur_offset, sizeof(int), 1, arquivo);
    }

    printf(" [offset: -1, tam: %d]\n", led.cur_size);
}