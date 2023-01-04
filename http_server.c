#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFLEN 1024
#define BACKLOG 5

int main(void) {
  char resp_buff[BUFLEN];
  char http_header[2 * BUFLEN] = "hhtp/1.1 200 OK\r\n\n";

  FILE *html_data = fopen("index.html", "r");
  fgets(resp_buff, sizeof(resp_buff), html_data);
  strcat(http_header, resp_buff);
  fclose(html_data);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8001);
  server_address.sin_addr.s_addr = INADDR_ANY;

  int serv_sock = socket(AF_INET, SOCK_STREAM, 0);

  int status = bind(serv_sock, (struct sockaddr*) &server_address, sizeof(server_address));

  listen(serv_sock, BACKLOG);

  int client_sock;

  while (1) {
      client_sock = accept(serv_sock, NULL, NULL);
      send(client_sock, http_header, sizeof(http_header), 0);
      close(client_sock);
  }
  return 0;
}
