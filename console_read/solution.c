//
// Created by rustam on 14.12.22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *join(const char *s1, const char *s2) {
    char * buffer;
    int len = strlen(s1) + strlen(s2) + 1;
    buffer = malloc(len);
    strcpy(buffer, s1);
    strcat(buffer, " ");
    strcat(buffer, s2);

    return buffer;
}

int main(int argc, char *argv[]) {
    char * command = join(argv[1], argv[2]);

    FILE *file;
    file = popen(command, "r");
    char c = ' ';
    int counter = 0;
    while (c != EOF) {
        c = fgetc(file);
        if (c == '0') {
            counter++;
        }
    }
    pclose(file);
    printf("%d\n", counter);

    return 0;
}