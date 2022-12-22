#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]) {
    if (argv[1] == NULL) {
        return -1;
    }
    struct hostent  *hostent_;
    hostent_ = gethostbyname(argv[1]);
    int i = 0;
    while (hostent_->h_addr_list[i] != NULL) {
        struct in_addr *addr_ = (struct in_addr *) hostent_->h_addr_list[i];
        printf("%s\n", inet_ntoa(*addr_));
        i++;
    }
    return 0;
}

