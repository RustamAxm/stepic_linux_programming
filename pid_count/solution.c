#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int find_proc_in_pid(const pid_t pid, const char *find_proc) {
    char path[1024];
    char buffer[1024];
    sprintf(path, "/proc/%d/stat", pid);
    FILE *fd = fopen(path, "r");
    size_t size = fread(buffer, sizeof(char), sizeof(buffer), fd);
    if (size > 0 && strstr(buffer, find_proc) != NULL) {
        return 1;
    }
    return 0;
}

int main() {
    DIR * dir_;
    struct dirent * dirent_;
    char find_proc [] = "genenv";
    int counter = 0;
    if ((dir_ = opendir("/proc/")) != NULL) {
        while ((dirent_ = readdir(dir_)) != NULL) {
            pid_t pid_ = atoi(dirent_->d_name);
            if (pid_ > 0) {
                counter += find_proc_in_pid(pid_, find_proc);
            }
        }
        closedir(dir_);
    }
    printf("%d\n", counter);
    return 0;
}
