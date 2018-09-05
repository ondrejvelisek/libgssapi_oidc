#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "constants.h"
#include "gss_oidc.h"



int make_request(int server_socket, char* request, char* response) {
    write(server_socket, request, strlen(request) + 1);
    read(server_socket, response, BUFFER_SIZE);
    return 0;
}

int body(int server_socket) {

    printf("FFF");

    char* request = malloc(BUFFER_SIZE);;
    char* response = malloc(BUFFER_SIZE);;

    for(int i = 0; i < 10; i++)
    {
        printf("BBB");

        fgets(request, BUFFER_SIZE, stdin);

        printf("DDD%s", request);


        if (strcmp(request, "exit") == 0)
            break;

        make_request(server_socket, request, response);

        printf("%s", response);

        bzero(request, BUFFER_SIZE);
        bzero(response, BUFFER_SIZE);
    }
    return 0;
}

int start_gss_client() {
    printf("Starting client...\n");

    int server_socket;
    struct sockaddr_in server_address;

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT_NUMBER);

    inet_pton(AF_INET, "127.0.0.1", &(server_address.sin_addr));

    connect(server_socket,(struct sockaddr *)&server_address,sizeof(server_address));

    printf("Client connected\n");

    body(server_socket);

    printf("Client disconnected\n");
    return 0;
}