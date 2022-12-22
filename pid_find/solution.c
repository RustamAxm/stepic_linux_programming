#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // getpid
#include <string.h>  // strtok

int main() {

pid_t pid = getpid();
pid_t ppid;
char path[100];
char buffer[1024];
sprintf(path, "/proc/%d/stat", pid);
FILE *fd = fopen(path, "r");

size_t size = fread(buffer, sizeof(char), sizeof(buffer), fd);
    if (size > 0) {
        int counter = 0;
        char *pch = strtok(buffer, " ");
        while (counter != 2) {
            pch = strtok(NULL, " ");
            counter++;
        }
        ppid = atoi(strtok(NULL, " "));
    }

    fclose(fd);
    printf("%d\n", ppid);

return 0;
}
