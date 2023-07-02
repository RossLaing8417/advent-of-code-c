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
    int l, w, h, min, total = 0;
    int ll, ww, hh;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%dx%dx%d", &l, &w, &h);

        ll = l * 2;
        ww = w * 2;
        hh = h * 2;

        min = ll + ww;
        min = (min > ww + hh ? ww + hh : min);
        min = (min > hh + ll ? hh + ll : min);

        total += min + (l * w * h);
    }

    printf("Total: %d\n", total);

    fclose(file);
}
