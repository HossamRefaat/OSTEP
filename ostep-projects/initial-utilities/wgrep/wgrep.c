#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *searchterm = argv[1];
    FILE *fp;

    if (argc == 2) {
        fp = stdin;
    } else {
        fp = fopen(argv[2], "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
    if (fp != stdin) {
        fclose(fp);
    }

    return 0;
}