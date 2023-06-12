#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_SIZE 7500

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

    char line[MAX_LINE_SIZE];
    int floor = 0;
    int position = 0;

    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; i < MAX_LINE_SIZE && line[i] != '\0'; i++) {
            switch(line[i]) {
                case '(': floor++; break;
                case ')': floor--; break;
            }
            if (!position && floor < 0)
                position = i + 1;
        }
    }

    printf("Position: %d\n", position);

    fclose(file);
}
