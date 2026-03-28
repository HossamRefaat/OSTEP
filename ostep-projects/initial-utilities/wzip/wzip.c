#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }

        int count = 1;
        char prev_char = fgetc(fp);
        if (prev_char == EOF) {
            fclose(fp);
            continue;
        }

        char curr_char;
        while ((curr_char = fgetc(fp)) != EOF) {
            if (curr_char == prev_char) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&prev_char, sizeof(char), 1, stdout);
                count = 1;
                prev_char = curr_char;
            }
        }

        // Write the last run
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev_char, sizeof(char), 1, stdout);

        fclose(fp);
    }

    return 0;
}