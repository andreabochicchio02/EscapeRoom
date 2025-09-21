#ifndef UTILITY_CLIENT_H
#define UTILITY_CLIENT_H

#include <unistd.h>
#include <netinet/in.h>

#include "../lib/funzioni.h"


#define SERVER_PORT 4242                        /* porta del server */
#define SIZE_BUFF 2048                          /* grandezza buffer */  


/* gestione username e pass per signup */
void signup(struct Formato_cmd*);

/* gestione username e pass per login */
void login(struct Formato_cmd*);

/* stampa a video l'elenco dei comandi con una breve guida */
void print_comandi();

/* pulisce lo standard input fino al carattere '\n' */
void pulisci_buf();

#endif