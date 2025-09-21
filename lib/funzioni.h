#ifndef FUNZIONE_H
#define FUNZIONE_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define LEN_CMD 8                   /* max lunghezza comandi server e client */
#define LEN_CAMPI 32                /* max lunghezza massima info inviati da client a server */
#define LEN_MSG 1024                /* max lunghezza massaggio principale inviato da server a client */
#define LEN_INFO 256                /* max lunghezza informazioni aggiuntive inviare da server a client */


/* Formato messaggio da client al server */
struct Formato_cmd {
    char cmd[LEN_CMD];              /* comando */
    char campo1[LEN_CAMPI];         /* paramentro 1 */
    char campo2[LEN_CAMPI];         /* parametro 2*/
};

/* Formato messaggio da server a client */
struct Formato_resp {
    char richiesta[LEN_CMD];        /* indico a quale comando sto rispondendo */
    int bool_ret;                   /* 0=>errore, 1=>successo */
    char notice[LEN_INFO];          /* ci sono eventuali notifiche */
    char info[LEN_INFO];            /* informazioni sui token raccolti, mancanti e tempo rimanente */
    char msg[LEN_MSG];              /* messaggio principale*/
    char info_next[LEN_INFO];       /* informazioni sul fasi successive gioco */
};

/* inizializza la struttura con il carattere nullo */
void inizializza_formato(struct Formato_cmd*);

/* text-protocols: da struttura Formato_cmd a stringa */
void cmd_to_string(struct Formato_cmd, char[]);

/* text-protocols: da struttura Formato_resp a stringa */
void resp_to_string(struct Formato_resp, char[]);

/* text-protocols: da stringa a struttura Formato_cmd */
int cmd_parsing(char[], struct Formato_cmd*);

/* text-protocols: da stringa a struttura Formato_resp */
void resp_parsing(char[], struct Formato_resp*);

/* ricezione dati tramite socket di comunicazione */
int receive_data(int, char[]);

/* invio dati tramite socket di comunicazione */
int send_data(int, char[]);


#endif