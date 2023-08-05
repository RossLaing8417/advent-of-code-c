#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "md5.h"

#define MAX_SIZE 16

void print_hash(uint8_t *p){
    for(unsigned int i = 0; i < 16; ++i){
        printf("%02x", p[i]);
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("File as first argument required\n");
        exit(-1);
    }

    const char * filename = argv[1];

    FILE * file = fopen(filename, "r");

    if (!file) {
        printf("Error reading file: %s\n", filename);
        exit(-1);
    }

    char key[MAX_SIZE];
    char message[32];

    fgets(key, sizeof(key), file);
    key[strcspn(key, "\n")] = 0;

    uint8_t result[16];
    size_t i = 0;

    while (1) {
        i++;

        sprintf(message, "%s%zu", key, i);

        md5String(message, result);

        // There is probably some bit stuff I could do...
        if (!result[0] && !result[1] && result[2] < 0x10) {
            // printf("Magic!\n");
            break;
        }
    }

    printf("Answer: %zu\n", i);

    fclose(file);
}
