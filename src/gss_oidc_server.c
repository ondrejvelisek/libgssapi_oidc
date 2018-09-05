#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <gssapi/gssapi_generic.h>
#include "constants.h"
#include "gss_oidc.h"


int handle_request(char* request, char* response) {
    printf("received: %s", request);

    // input
    gss_name_t desired_name = malloc(sizeof(*desired_name));
    desired_name->name = "rootoo";
    OM_uint32 time_req = 0;
    gss_OID_set desired_mechs = malloc(sizeof(*desired_mechs));
    desired_mechs->count = 1;
    desired_mechs->elements = malloc(sizeof(*desired_mechs->elements));
    desired_mechs->elements->length = 1;
    int* desired_mechs_elements = malloc(sizeof(int));
    desired_mechs_elements[0] = OIDC_MECHANISM;
    desired_mechs->elements->elements = desired_mechs_elements;
    gss_cred_usage_t cred_usage = GSS_C_BOTH;

    // output
    OM_uint32 minor_status;
    gss_cred_id_t output_cred_handle = malloc(sizeof(*output_cred_handle));
    gss_OID_set actual_mechs = malloc(sizeof(*actual_mechs));
    OM_uint32 time_rec;

    printf("\n=== about to call acquire ===\n");

    int status = gss_acquire_cred(
            &minor_status,
            desired_name,
            time_req,
            desired_mechs,
            cred_usage,
            &output_cred_handle,
            &actual_mechs,
            &time_rec
    );

    printf("\n=== OUTPUT ===\n");
    printf("status %d\n", status);
    printf("minor_status %d\n", minor_status);
    printf("output_cred_handle %s\n", output_cred_handle->id);
    printf("actual_mechs count %d\n", (int) actual_mechs->count);
    printf("actual_mechs elem %d\n", ((int*) actual_mechs->elements->elements)[0]);
    printf("time_rec %d\n", time_rec);

    sprintf(response, "your request has %zu characters\n", strlen(request)-1);
    return 0;
}

int start_gss_server() {
    printf("Starting server...\n");

    int server_socket, client_socket;

    struct sockaddr_in server_address;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0)
        exit(-1);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);
    server_address.sin_port = htons(PORT_NUMBER);

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
        exit(-1);

    if (listen(server_socket, MAX_CONNECTIONS) < 0)
        exit(-1);

    printf("Server started\n");

    char request[BUFFER_SIZE];
    char response[STRINGS_SIZE];
    while(1) {

        if ((client_socket = accept(server_socket, (struct sockaddr*) NULL, NULL)) < 0)
            break;

        printf("Connection accepted\n");

        while(read(client_socket, request, BUFFER_SIZE) > 0)
        {
            handle_request(request, response);

            write(client_socket, response, strlen(response)+1);
            bzero(request, BUFFER_SIZE);
            bzero(response, BUFFER_SIZE);
        }

        printf("Connection closed\n");
    }
    return 0;
}