#include <stdio.h>
#include <stdlib.h>

void open_file(const char *fileName) {
    if (freopen(fileName, "r", stdin) == NULL) {
        perror("Error opening input file");
        exit(1);
    }
}