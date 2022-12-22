#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>


int count_children(char * buffer_in) {
    char * pch = strtok (buffer_in," "); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)
    int i = 1;
    while (pch != NULL) {
        pch = strtok (NULL, " ");
        i++;
    }
    return i;
}

int get_children_pid_count(const pid_t pid_) {
    pid_t ppid = pid_;
    char path[1024];
    char buffer[1024];
    sprintf(path, "/proc/%d/task/%d/children", pid_, pid_);
    FILE *fd = fopen(path, "r");

    if (fd == NULL) {
        perror("fd");
        fprintf(stderr,"Error path: %s\n", path);
        exit(1);
    }
    size_t size = fread(buffer, sizeof(char), sizeof(buffer), fd);
    int count = 0;
    if (size > 0) {
        count = count_children(buffer);
    }
    fclose(fd);
    return count;
}

int main(int argc, char * argv[]) {
    pid_t pid_ = atoi(argv[1]);
    printf("%i\n", get_children_pid_count(pid_));
    return 0;
}

