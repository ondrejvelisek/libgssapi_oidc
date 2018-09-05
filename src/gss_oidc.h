#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <syslog.h>

#include <gssapi/gssapi_generic.h>
#include "constants.h"


#ifndef GSSAPI_OIDC_H
#define GSSAPI_OIDC_H

typedef struct int_array {
    int* array;
} *int_array;
struct gss_ctx_id_struct {
    char* id;
};
struct gss_cred_id_struct {
    char* id;
};
struct gss_name_struct {
    char* name;
};

#endif