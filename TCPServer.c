#include <linux/in.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/endian.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CONNECTION_BACKLOG 5
#define BUFLEN 256

int main() {
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9002);
  server_address.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY = 0.0.0.0

  int net_sock = socket(AF_INET, SOCK_STREAM, 0);
  int bind_status = bind(net_sock, (struct sockaddr *)&server_address,
                         sizeof(server_address));

  if (bind_status == -1) {
    printf("error while binding to the remote socket\n");
  }

  listen(net_sock, CONNECTION_BACKLOG);
  int client_sock = accept(net_sock, NULL, NULL);

  char serv_buffer[] = "you reached the server\n";

  send(client_sock, &serv_buffer, sizeof(serv_buffer), 0);

  close(net_sock);
  return 0;
}
