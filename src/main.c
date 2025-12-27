#include <stdio.h>
#include <string.h>
#include "../includes/open.h"
#include "../includes/keywords.h"

int main(int argc, char *argv[]) {
    // check if  a file has .redstone extension
    if (argc > 1 && strstr(argv[1], ".redstone") != NULL) {
        char *fileName = argv[1];
        open_file(fileName);
        process_file(fileName);
    } else {
        printf("No input file provided or invalid file type.\n");
    }
    
    return 0;
}