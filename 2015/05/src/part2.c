/**
 * I suck and I ended up googling the answers :)
 * Apparently the C code I got didn't work, I didn't try understand it though
 * I used used the below as it was quite elegant:
 * cat input |  grep "\(..\).*\1" | grep "\(.\).\1" | wc -l
 */

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

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
    int pattern_1 = 0,
        pattern_2 = 0;
    int pairs['z'-'a'+1]['z'-'a'+1];
    int *first_pair;

    memset(pairs, -1, sizeof(pairs));

    int i = 0;
    line++;
    while (*line)
    {
        first_pair = &pairs[*(line-1) - 'a'][*line - 'a'];

        if (*first_pair == -1)
        {
            *first_pair = i;
        }
        else if (*first_pair != -1 && *first_pair < (i-1))
        {
            pattern_2 = 1;
        }

        if (i >= 2 && *(line-2) == *line)
        {
            pattern_1 = 1;
        }

        line++;
        i++;
    }

    return (pattern_1 && pattern_2);
}
