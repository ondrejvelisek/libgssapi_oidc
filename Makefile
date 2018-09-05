default: gss_server gss_client

gss_client: src/client_main.c src/gss_oidc_client.c
	clang $^ -o $@

gss_server: src/server_main.c src/gss_oidc_server.c
	clang $^ -lgss_oidc -L. -o $@

install:
	cp libgss_oidc.so /lib/