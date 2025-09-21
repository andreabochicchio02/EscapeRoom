#ifndef UTILITY_SERVER_H
#define UTILITY_SERVER_H

#include <unistd.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <time.h>

#include "../lib/funzioni.h"

#define SERVER_PORT 4242                            /* porta del server */
#define DIM_CODA 20                                 /* dimensione coda richieste */
#define SIZE_BUFF 2048                              /* dimesione buffer */

#define NUM_SCENARI 2                               /* numero di scenari possibili per ogni stanza */

#define MAX_LOCATIONS 10                            /* dimensione vettore con tutte location */
#define MAX_OBJ 10                                  /* dimensione vettore con oggetti liberi o bloccati*/

#define MAX_OBJ_TAKEN 3                             /* massimo numero di oggetti che l'utente può prendere */
#define MAX_ERR_INDO 3                              /* nuemro massimo di errori ad indivinello */


/*--------------------------------------*/
/*------ STRUTTURA DATI DEL GIOCO ------*/
/*--------------------------------------*/

/* scenari disponibili */
enum type_scenario{ROCK, POP};

/* tipologie di enigmi usati */
enum type_enigma{MULTIPLA,                          /* domanda risposta multipla */
                INDOVINELLO,                        /* indovinello con limite tentativi */
                ORDINE };                           /* operazioni in un determinato ordine */


/* struttura per dati degli enigmi */
struct enigma_risp{
    enum type_enigma tipologia;                     
    char* text;                                     /* testo dell'enigma */
    char risposta;                                  /* lettara risposta giusta */

    char* msg_corretto;                    
    char* msg_errore;
};

/* struttura per dati degli scenari */
struct info_scenari{
    enum type_scenario scenario;                    /* nome dello scenario */
    char* nome_vinile;

    struct enigma_risp enigma_mult;                 /* enigma scelta multipla */
    struct enigma_risp enigma_ind;                  /* enigma indovinello */
};

/* struttura per dati delle location */
struct info_location{
    char* name;
    char* description;
};

/* struttura per dati oggeti liberi */
struct info_obj_free{
    char* name;
    char* description;
    char* take_description;
};

/* struttura per dati oggetti bloccati */
struct info_obj_lock{
    char* name;
    int stato;                                      /* 0 => non preso, 1 => preso */
    int usato;                                      /* 0 => non usato, 1 => usato */

    char* description;

    enum type_enigma tipologia;
    const struct enigma_risp* enigma[NUM_SCENARI];  /* puntatore all'enigma, NULL se enigma è ordine operazioni */

    char* take_lock;                                /* descrizione quando l'oggetto è ancora bloccato */
    char* take_unlock;                              /* descrizione quando l'oggeto è stato sbloccato */
};

/* struttura per dati della room */
struct room{
    char* nome[NUM_SCENARI];                        /* una stanza può avere più scenari */

    char* description;
    char* desc_vittoria;

    int tot_token;                                  /* numero token per vincere */
    int max_time;                                   /* massimo tempo che può durare partita */
    int time_help;                                  /* minuti aggiuntivi in caso di aiuto corretto */

    int num_location;                               /* numero di location*/
    struct info_location location[MAX_LOCATIONS];   /* vettore con il massimo numero location nella stanza */

    int num_obj_free;                               /* numero di oggetti liberi*/
    struct info_obj_free obj_free[MAX_OBJ];         /* vettore con il massimo numero oggetti liberi nella stanza */      

    int num_obj_lock;                               /* numero di oggetti bloccati */
    struct info_obj_lock obj_lock[MAX_OBJ];         /* vettore con il massimo numero oggetti bloccati nella stanza */
};

/*struttura per informazioni sull'utente */
struct info_user{
    int id;                                         /* id del socket di comunicazione */
    char username[LEN_CAMPI];                       /* username dell'utente, la lunghezza decisa staticamente */
    int attivo;                                     /* 1=> utente ha effettuato start in una room, 0=> altriemnti */
    int room;                                       /* id room nel quale sta giocando */
    enum type_scenario scenario;                    /* 0 => ROCK, 1=> POP*/

    /* lista degli oggetti presi */
    int num_obj_free;                               /* numero oggetti liberi presi */
    struct info_obj_free* obj_free_presi;           /* vettore dinamico con gli oggetti liberi presi */

    int num_sbloccati;                              /* numero oggetti bloccati ora sbloccati */
    struct info_obj_lock* obj_sbloccati;            /* vettore dinamico con gli oggetti bloccati presi */

    int num_err_indo;                               /* quanti errori ha fatto all'enigma di tipo indovinello */

    int num_obj_presi;                              /* numero oggetti presi */
    int token_presi;                                /* numero token presi */

    /* funzione a scelta help */
    int bonus;                                      /* si può usare il bonus una volta sola */                             
    const struct enigma_risp* enigma_help;          /* puntatore all'enigma */
    int help_user;                                  /* -1 => se nessuno ha chiesto aiuto, altriemnti id */

    time_t start_time;                              /* ora di inizio partita */ 
    int time_bonus;                                 /* tempo aggiunto quando si aiuta un altro utente */

    char notifica[256];                             /* notifiche da inviare all'utente */

    struct info_user* next;
};


/* accetta la connect effettuata da un client */
int accept_connessione(int);


/*-----------------------------------------------------------*/
/*------ FUNZIONI GESTIONE COMANDI RICEVUTI DAL CLIENT ------*/
/*-----------------------------------------------------------*/

/* analizza quale è il comando inviato dal client */
void gestione_richiesta(int, struct Formato_cmd, struct Formato_resp*);

/* gestione registrazione del client */
void comando_signup(int, struct Formato_cmd, struct Formato_resp*);

/* gestione accesso del client */
void comando_login(int, struct Formato_cmd, struct Formato_resp*);

/* gestione avvio gioco in una stanza */
void comando_start(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* gestione descrizione di location o object */
void comando_look(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* gestione take oggetto che può essere libero o bloccato da enigma */
void comando_take(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* gestione uso di oggetti presi nella stanza */
void comando_use(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* elenco degli oggetti presi */
void comando_objs(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* elimina un elemento dalla lista client attivi */
void comando_end(int sd);



/*-----------------------------------------------------------*/
/*------ FUNZIONI COMANDO HELP E COMUNICAZIONE TRA HOST -----*/
/*-----------------------------------------------------------*/

/* gestione comando help per rispondere ad un indovinello */
int funzione_help(int, char[]);

/* gestione scelta dell'utente dal quale farsi aiutare */
void gestione_user(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* gestione notifica, utente ha accetto o rifiutato di aiutare un altro giocatore */
void gestione_notifica(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* gestione risposta enigma di aiuto, tempo bonus e avviso del client richiedente */
void gestione_aiuto(struct info_user*, struct Formato_cmd, struct Formato_resp*);



/*-----------------------------------------------------------*/
/*------ FUNZIONI UTILITA' PER LA GESTIONE DEI COMANDI ------*/
/*-----------------------------------------------------------*/

/* controllo stanze disponibili da inviare al client */
void gestione_stanze(char[]);

/* funzione che gestisce la risoluzione enigma */
void gestione_enigma(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* funzione che gestisce richiesta di lasciare un oggetto */
void gestione_lascia(struct info_user*, struct Formato_cmd, struct Formato_resp*);

/* inserisco in una stringa tutti gli oggetti presi */
int elenco_oggetti(char*, struct info_user*);

/* controllo che non sia finito il tempo */
int controllo_time(struct info_user*);

/* inserisco in una stringa token raccolti, token rimanenti, secondi ramanenti */
void insert_dati(struct info_user*, char[]);

/* cerca un oggetto free in un vettore, ritorno l'indice, -1 se non esiste*/
int search_obj_free(const struct info_obj_free*, int, char*);

/* cerca un oggetto lock in un vettore, ritorno l'indice, -1 se non esiste*/
int search_obj_lock(const struct info_obj_lock*, int, char*);

/* aggiungo un utente alla lista degli utenti attivi */
struct info_user* new_user(int);

/* controllo se l'utente è ancora attivo */
struct info_user* search_user(int);

/* controllo se l'username è già attivo */
struct info_user* duplicato(int, char[]);

/* restituisce numero di utenti attivi */
int utenti_attivi();

#endif