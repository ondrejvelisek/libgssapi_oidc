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


int start_gss_server();