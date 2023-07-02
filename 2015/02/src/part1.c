#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_SIZE 16

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
    int l, w, h, s_area, min, total = 0;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%dx%dx%d", &l, &w, &h);

        s_area = (2 * l * w) + (2 * w * h) + (2 * h * l);

        min = l * w;
        min = (min > w * h ? w * h : min);
        min = (min > h * l ? h * l : min);

        s_area += min;
        total += s_area;
    }

    printf("Total: %d\n", total);

    fclose(file);
}
