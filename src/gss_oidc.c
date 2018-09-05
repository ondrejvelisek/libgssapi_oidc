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
#include "gss_oidc.h"
#include "constants.h"


OM_uint32
gss_acquire_cred (
        OM_uint32 *minor_status,
        const gss_name_t desired_name,
        OM_uint32 time_req,
        const gss_OID_set desired_mechs,
        gss_cred_usage_t cred_usage,
        gss_cred_id_t *output_cred_handle,
        gss_OID_set *actual_mechs,
        OM_uint32 *time_rec
) {
    openlog ("gss_acquire_cred", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    setlogmask (LOG_UPTO (LOG_NOTICE));

    // INPUT
    syslog(LOG_AUTH, "\n=== gss_acquire_cred --- INPUT ===\n");
    syslog(LOG_AUTH, "desired_name %s\n", desired_name->name);
    syslog(LOG_AUTH, "time_req %d\n", time_req);
    syslog(LOG_AUTH, "desired_mechs count %d\n", (int) desired_mechs->count);
    syslog(LOG_AUTH, "desired_mechs elem %d\n", ((int*) desired_mechs->elements->elements)[0]);
    syslog(LOG_AUTH, "cred_usage %d\n", cred_usage);


    // OUTPUT
    *minor_status = MINOR_STATUS_OK;
    (*output_cred_handle)->id = "TOKEN_CREDS";
    int mechs[1];
    mechs[0] = OIDC_MECHANISM;
    gss_OID elements = malloc(sizeof(elements));
    elements->elements = mechs;
    (*actual_mechs)->elements = elements;
    (*actual_mechs)->count = 5;
    (*actual_mechs)->elements = malloc(sizeof(*(*actual_mechs)->elements));
    (*actual_mechs)->elements->length = 6;
    int* actual_mechs_elements = malloc(sizeof(int));
    actual_mechs_elements[0] = OIDC_MECHANISM;
    (*actual_mechs)->elements->elements = actual_mechs_elements;
    *time_rec = 15*60;

    closelog ();
    return GSS_S_COMPLETE;
}

OM_uint32
gss_init_sec_context (
        OM_uint32 * minor_status,
        const gss_cred_id_t initiator_cred_handle,
        gss_ctx_id_t * context_handle,
        const gss_name_t target_name,
        const gss_OID mech_type,
        OM_uint32 req_flags,
        OM_uint32 time_req,
        const gss_channel_bindings_t input_chan_bindings,
        const gss_buffer_t input_token,
        gss_OID * actual_mech_type,
        gss_buffer_t output_token,
        OM_uint32 * ret_flags,
        OM_uint32 * time_rec
) {
    // INPUT
    printf("\n=== gss_init_sec_context --- INPUT ===\n");
    printf("initiator_cred_handle %s\n", initiator_cred_handle->id);
    printf("context_handle %s\n", (*context_handle)->id);
    printf("target_name %s\n", target_name->name);
    printf("mech_type %d\n", ((int*) mech_type->elements)[0]);
    printf("req_flags %x\n", (int) req_flags);
    printf("time_req %d\n", (int) time_req);
    printf("input_chan_bindings initiator_address %s\n", (char*)input_chan_bindings->initiator_address.value);
    printf("input_chan_bindings acceptor_address %s\n", (char*)input_chan_bindings->acceptor_address.value);
    printf("input_chan_bindings application_data %s\n", (char*)input_chan_bindings->application_data.value);
    printf("input_token %s\n", (char*)input_token->value);

    // OUTPUT
    *minor_status = MINOR_STATUS_OK;
    (*context_handle)->id = "Contex 0123";
    int actual_mech_elemets[1];
    actual_mech_elemets[0] = OIDC_MECHANISM;
    (*actual_mech_type)->elements = actual_mech_elemets;
    output_token->value = "TOKEN 1234";
    *ret_flags = 0;
    *time_rec = 15*60;

    return GSS_S_COMPLETE;

}

OM_uint32
gss_accept_sec_context (
        OM_uint32 * minor_status,
        gss_ctx_id_t * context_handle,
        const gss_cred_id_t acceptor_cred_handle,
        const gss_buffer_t input_token_buffer,
        const gss_channel_bindings_t input_chan_bindings,
        gss_name_t * src_name,
        gss_OID * mech_type,
        gss_buffer_t output_token,
        OM_uint32 * ret_flags,
        OM_uint32 * time_rec,
        gss_cred_id_t * delegated_cred_handle
) {
    // INPUT
    printf("\n=== gss_accept_sec_context --- INPUT ===\n");
    printf("acceptor_cred_handle %s\n", acceptor_cred_handle->id);
    printf("input_chan_bindings initiator_address %s\n", (char*)input_chan_bindings->initiator_address.value);
    printf("input_chan_bindings acceptor_address %s\n", (char*)input_chan_bindings->acceptor_address.value);
    printf("input_chan_bindings application_data %s\n", (char*)input_chan_bindings->application_data.value);
    printf("input_token %s\n", (char*)input_token_buffer->value);

    // OUTPUT
    *minor_status = MINOR_STATUS_OK;
    (*src_name)->name = "ondrej velisek gss_accept_sec_context";
    int mech_elemets[1];
    mech_elemets[0] = OIDC_MECHANISM;
    (*mech_type)->elements = mech_elemets;
    (*context_handle)->id = "Contex gss_accept_sec_context";
    *ret_flags = 0;
    *time_rec = 15*60;
    (*delegated_cred_handle)->id = "CRED gss_accept_sec_context";
    output_token->value = "TOKEN gss_accept_sec_context";

    return GSS_S_COMPLETE;
}
