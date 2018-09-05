default: gss_server gss_client libgss_oidc.so

libgss_oidc.so: gss_oidc.o
	clang -shared -o $@ $^

gss_oidc.o: src/gss_oidc.c src/gss_oidc.h
	clang -c -fPIC src/gss_oidc.c -o $@

gss_client: src/client_main.c src/gss_oidc_client.c
	clang $^ -o $@

gss_server: src/server_main.c src/gss_oidc_server.c
	clang $^ -lgss_oidc -L. -o $@

install:
	cp libgss_oidc.so /lib/