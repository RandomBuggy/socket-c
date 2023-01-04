#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/endian.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFLEN 1024

int main(int argc, char **argv) {
    char *addr = argv[1];

    struct sockaddr_in remote_addr;
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(8001);
    inet_aton(addr, &remote_addr.sin_addr.s_addr);

    int client_sock = socket(AF_INET, SOCK_STREAM, 0);

    connect(client_sock, (struct sockaddr*) &remote_addr, sizeof(remote_addr));

    char *request = "GET / HTTP1.1\r\n\n";
    char response[4*BUFLEN];

    send(client_sock, request, sizeof(request), 0);
    recv(client_sock &response, sizeof(response), 0);

    printf("response from server %s\n", response);
    close(client_sock);

    return 0;
}
