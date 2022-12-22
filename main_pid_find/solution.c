#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>


void split_stat(char * buffer_in, char * arr[]) {
    char * pch = strtok (buffer_in," ");

    int i = 0;
    while (pch != NULL) {
        strcpy(arr[i], pch);
        pch = strtok (NULL, " ");
        i++;
    }
}

int get_parent_pid(const pid_t pid_) {
    pid_t ppid = pid_;
    char path[1024];
    char buffer[1024];
    sprintf(path, "/proc/%d/stat", pid_);
    FILE *fd = fopen(path, "r");

    if (fd == NULL) {
        perror("fd");
        fprintf(stderr,"Error path: %s\n", path);
        exit(1);
    }
    size_t size = fread(buffer, sizeof(char), sizeof(buffer), fd);
    if (size > 0) {
        char * arr[64];
        int i = 0;
        for(; i < 64; i++) {
            arr[i]= malloc(sizeof(char) * 64);
        }
        split_stat(buffer, arr);
        ppid = atoi(arr[3]);
    }
    fclose(fd);
    return ppid;
}

int main(int argc, char * argv[]) {
    pid_t pid_ = atoi(argv[1]);
    printf("%d\n", pid_);
    while (pid_ != 1) {
        pid_ = get_parent_pid(pid_);
        printf("%d\n", pid_);
    }
    return 0;
}

