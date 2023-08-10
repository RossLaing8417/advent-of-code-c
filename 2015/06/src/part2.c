#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 34

typedef enum {
    ON = 0,
    OFF = 1,
    TOGGLE =  2
} Action;

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
    uint32_t lights[1000][1000] = { 0, };

    char act_str[MAX_SIZE];
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    Action action;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        sscanf(line, "%s", act_str);

        if (strcmp(act_str, "toggle") == 0) {
            sscanf(line, "%s %d,%d through %d,%d\n", act_str, &x0, &y0, &x1, &y1);
            action = TOGGLE;
        }
        else if (strcmp(act_str, "turn") == 0) {
            sscanf(line, "%s %s %d,%d through %d,%d\n", act_str, act_str, &x0, &y0, &x1, &y1);
            if (strcmp(act_str, "on") == 0) {
                action = ON;
            }
            else {
                action = OFF;
            }
        }
        else {
            continue;
        }

        for (int x = x0; x <= x1; x++) {
            for (int y = y0; y <= y1; y++) {
                if (action == ON) {
                    lights[x][y]++;
                }
                else if (action == OFF) {
                    if (lights[x][y] > 0) {
                        lights[x][y]--;
                    }
                }
                else {
                    lights[x][y] += 2;
                }
            }
        }
    }

    int total = 0;

    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            if (lights[x][y]) {
                total += lights[x][y];
            }
        }
    }

    printf("Total: %d\n", total);

    fclose(file);
}
