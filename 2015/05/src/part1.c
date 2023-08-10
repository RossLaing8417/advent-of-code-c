#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 32

int isValid(char * line);

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

    char line[MAX_SIZE];
    int total = 0;

    while (fgets(line, sizeof(line), file)) {
        if (isValid(line)) {
            total++;
        }
    }

    printf("Total: %d\n", total);

    fclose(file);
}

int isValid(char * line) {
    int numV = 0, dbl = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        if (line[i] == '\n') {
            break;
        }
        switch (line[i]) {
            case 'a':
                if (line[i+1] == 'b')
                    return 0;
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                numV++;
                break;
            case 'c':
            case 'p':
            case 'x':
                if (line[i+1] == line[i] + 1)
                    return 0;
        }
        if (line[i] == line[i+1]) {
            dbl++;
        }
    }

    return (numV >= 3 && dbl);
}
