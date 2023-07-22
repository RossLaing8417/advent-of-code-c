#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 512

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

    int grid[MAX_SIZE][MAX_SIZE] = { 0 };
    int total = 0;

    char c;
    int x = MAX_SIZE / 2;
    int y = x;

    grid[x][y]++;

    while ((c = fgetc(file)) != EOF) {
        switch (c) {
            case '^': y++; break;
            case 'v': y--; break;
            case '>': x++; break;
            case '<': x--; break;
        }
        grid[x][y]++;
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (grid[i][j] > 0) {
                total++;
            }
        }
    }

    printf("Total: %d\n", total);

    fclose(file);
}
