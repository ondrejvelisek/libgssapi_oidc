cmake_minimum_required(VERSION 3.5)
project(gss_oidc C)

set(CMAKE_C_STANDARD 99)

add_executable(gss_oidc_server src/server_main.c)
add_executable(gss_oidc_client src/client_main.c)
add_library(gss_oidc SHARED src/gss_oidc.c)