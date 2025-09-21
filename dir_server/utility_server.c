#include "utility_server.h"

/*-----------------------------------------------------------*/
/*------ INIZIALIZZZAZIONE STRUTTURE DATI DEL GIOCO ---------*/
/*-----------------------------------------------------------*/

/* informazioni scenari */
const struct info_scenari dati_scenari[] = {
    {
        .scenario = ROCK,
        .nome_vinile = "The Wall dei Pink Floyd.",
        .enigma_mult = {
            .tipologia = MULTIPLA,
            .text = "Chi è considerato il re del rock mondiale? (inserisci la lettera)\n"
                        "a) Jim Morrison\n"
                        "b) Mick Jagger\n"
                        "c) Elvis Presley\n"
                        "d) Vasco Rossi",
            .risposta = 'c', 
            .msg_corretto = "Complimenti hai vinto il token: RITMI NOSTALGICI!\n" 
                        "Hai sbloccato l'oggetto **vinile**. Adesso puoi raccogliere l'oggetto.",
            .msg_errore = "Risposta errata!. Puoi raccogliere nuovamente l'oggetto **vinile** ora o in seguito e " 
                          "riprovare a rispondere correttamente all'enigma."
        },
        .enigma_ind = {
            .tipologia = INDOVINELLO,
            .text = "Quante corde ha il basso?",
            .risposta = '4', 
            .msg_corretto = "Complimenti hai vinto il token: MUSICISTA!\n"
                        "Hai sbloccato l'oggetto **chitarra**. Adesso puoi raccogliere l'oggetto.",
            .msg_errore = "Risposta errata!. Puoi raccogliere nuovamente l'oggetto **chitarra** ora o in seguito e " 
                            "riprovare a rispondere correttamente all'enigma."
        }

    },
    {
        .scenario = POP,
        .nome_vinile = "Like a Virgin di Madonna.",
        .enigma_mult = {
            .tipologia = MULTIPLA,
            .text = "Chi è considerato il re del pop mondiale? (inserisci la lettera)\n"
                        "a) Michael Jackson\n"
                        "b) Madonna\n"
                        "c) Katy Perry\n"
                        "d) Britney Spears", 
            .risposta = 'a', 
            .msg_corretto = "Complimenti hai vinto il token: RITMI NOSTALGICI!\n" 
                        "Hai sbloccato l'oggetto **vinile**. Adesso puoi raccogliere l'oggetto.",
            .msg_errore = "Risposta errata!. Puoi raccogliere nuovamente l'oggetto **vinile** ora o in seguito e " 
                            "riprovare a rispondere correttamente all'enigma."
        },
        .enigma_ind = {
            .tipologia = INDOVINELLO,
            .text = "Quante corde ha la chitarra acustica?",
            .risposta = '6', 
            .msg_corretto = "Complimenti hai vinto il token: MUSICISTA!\n"
                        "Hai sbloccato l'oggetto **chitarra**. Adesso puoi raccogliere l'oggetto.",
            .msg_errore = "Risposta errata!. Puoi raccogliere nuovamente l'oggetto **chitarra** ora o in seguito e " 
                            "riprovare a rispondere correttamente all'enigma."
        }
    }
};


/* informazione room */
const struct room stanze[] = {
    {
        .nome = {
                "STANZA ROCK",
                "STANZA POP"
            },
        .description = "Sei in una stanza molto coinvolgente. Le pareti sono decorate " 
                        "con pentagrammi e testi di famose canzoni.\nDi fronte a te, " 
                        "sul ++tavolo++, c'è un **giradischi** collegato ad una **chiave** di violino "
                        "tramite un sistema elettronico.\n"
                        "Accanto al ++tavolo++, c'è una **chitarra** con uno **spartito** musicale appoggiato su di essa.\n"
                        "Alla tua destra c'è una ++armadietto++ prova a vedere cosa c'è dentro!",
        .desc_vittoria = "Hai sbloccato tutti i token: RITMI NOSTALGICI, MUSICISTA e CHIAVE DI VIOLINO, " 
                        "questo ti permette di uscire dalla stanza!\nHAI VINTO!",
        .tot_token = 3,
        .max_time = 600,
        .time_help = 3,
        .num_location = 2,
        .location = {
            {
                .name = "tavolo",
                .description = "Il ++tavolo++ è fatto di legno massiccio con venature naturali, dallo stile rustico. " 
                                "Su di esso è appoggiato un **giradischi** vintage ben curato collegato ad una "
                                "**chiave** di violino tramite un sistema elettronico.\n"
                                "Accanto al ++tavolo++, c'è una moderna **chitarra** acustica con uno **spartito** "
                                "musicale appoggiato su di essa.",
            },
            {
                .name = "armadietto",
                .description = "L'++armadietto++ è costruito in legno scuro, dalle linee pulite e rifiniture d'oro. "
                                "Custodisce al suo interno una collezione di CD musicali, "
                                "ma c'è anche un bellissimo **vinile**: "                                                   /*in base allo scenario ci sarà la canzone*/
            }
        }, 
        .num_obj_free = 2,
        .obj_free = {
            {
                .name = "giradischi",
                .description = "Il **giradischi** ha una base scura e rifiniture metalliche. Il piatto girevole è in vetro "
                                "trasparente infine il braccio aggiunge un'eleganza vintage.", 
                .take_description = "HAI PRESO IL **giradischi**! Ora puoi usarlo per ascoltare il **vinile**.",        
            },
            {
                .name = "spartito",
                .description = "Lo **spartito** è sgualcito, ma è visibile la partituta della chitarra della canzone ",     /*in base allo scenario ci sarà la canzone*/
                .take_description = "HAI PRESO LO **spartito**! Ora puoi usarlo per suonare con la **chitarra**.",       
            }
        }, 
        .num_obj_lock = 3,
        .obj_lock = {
            {
                .name = "vinile",
                .stato = 0, 
                .usato = 0,
                .description = "Il **vinile** è formato 33 giri. La copertina in cortoncino " 
                                "mostra segni del tempo trascorso, con angoli sbiaditi e piccole pieghe.", 
                .tipologia = MULTIPLA,
                .enigma = {
                    &dati_scenari[ROCK].enigma_mult,
                    &dati_scenari[POP].enigma_mult,
                },
                .take_lock = "L'oggetto **vinile** è bloccato. Devi dimostrare che sei "
                                "appassionato di musica per poterlo prendere.", 
                .take_unlock = "HAI PRESO IL **vinile**! Ora puoi usarlo per ascoltare musica.", 
            }, 
            {
                .name = "chitarra",
                .stato = 0,
                .usato = 0, 
                .description = "La **chitarra** acustica è in legno di mogano, tastiera in acero. Il manico è sottile e il design "
                                "è elegante ma allo stesso tempo moderno.", 
                .tipologia = INDOVINELLO,
                .enigma = {
                    &dati_scenari[ROCK].enigma_ind,
                    &dati_scenari[POP].enigma_ind,
                },
                .take_lock = "L'oggetto **chitarra** è bloccato. Devi dimostrare che sai suonarla per poterla prendere.\n",
                .take_unlock = "HAI PRESO LA **chitarra**! Ora puoi suonarla.",  
            },
            {
                .name = "chiave",
                .stato = 0,
                .usato = 0, 
                .description = "La **chiave** di violino è a forma di S con una testa ovale. "
                                "Sicuramente riesce ad aprire una particolare serratura per uscire. ",
                .tipologia = ORDINE,
                .enigma = {
                    NULL,
                    NULL
                },
                .take_lock = "L'oggetto **chiave* è bloccato. Essa è collegata tramite un sistema elettronico al **giradischi**. "
                                "Prova ad usarlo per sbloccare la **chiave**.",
            }
        }
    }
};


/* lista di tutti gli utenti attivi */
struct info_user* lista_users = NULL;



/*-----------------------------------------------------------*/
/*------ FUNZIONE PER ACCETTARE CONNESSIONE DAL CLIENT ------*/
/*-----------------------------------------------------------*/
int accept_connessione(int listener){
    struct sockaddr_in client_addr;         /* indirizzo cliente */
    socklen_t client_len = sizeof(client_addr);

    int newfd = accept(listener, (struct sockaddr*) &client_addr, &client_len);
    if(newfd == -1){
        perror("Error accept");
        exit(1);
    }  

    return newfd;
}






/*-----------------------------------------------------------*/
/*------ FUNZIONI GESTIONE COMANDI RICEVUTI DAL CLIENT ------*/
/*-----------------------------------------------------------*/

/* analizza quale è il comando inviato dal client */
void gestione_richiesta(int client, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    struct info_user* utente = NULL;

    /* pulisco alcuni dati della struttura dati usata per invio dati al client */
    strcpy(risposta->info, "_");
    strcpy(risposta->notice, "_");
    strcpy(risposta->info_next, "_");

    /*---- GESTIONE COMANDI LOGIN E SIGNUP ----*/
    if(!strcmp(richiesta.cmd, "login")){                        /* login */
        comando_login(client, richiesta, risposta);
        return;
    }else if(!strcmp(richiesta.cmd, "signup")){                 /* signup */
        comando_signup(client, richiesta, risposta);
        return;
    }

    /* se sono arrivato qui allora l'utente ha effettuato autenticazione */
    /* dal socket trovo le informazioni sul giocatore */
    utente = search_user(client);


    /*---- GESTIONE COMANDO START ----*/
    if(!strcmp(richiesta.cmd, "start")){                        /* start */
        comando_start(utente, richiesta, risposta);
        return;
    }


    /* da questo momento controllo il timer */
    if(controllo_time(utente) <= 0){
        strcpy(risposta->richiesta, "tempo");
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Tempo scaduto.\nHAI PERSO!");
        return;
    }


    /*----GESTIONE DEI COMANDI RIMANENTI----*/
    if(!strcmp(richiesta.cmd, "look"))                          /*-- look --*/
        comando_look(utente, richiesta, risposta);    
    else if(!strcmp(richiesta.cmd, "take"))                     /*-- take --*/
        comando_take(utente, richiesta, risposta);    
    else if(!strcmp(richiesta.cmd, "use"))                      /*-- use --*/
        comando_use(utente, richiesta, risposta);  
    else if(!strcmp(richiesta.cmd, "objs"))                     /*-- objs --*/
        comando_objs(utente, richiesta, risposta);  
    else if(!strcmp(richiesta.cmd, "e_mult")                    /* gestione enigma */
            || !strcmp(richiesta.cmd, "e_indo"))             
        gestione_enigma(utente, richiesta, risposta);  
    else if(!strcmp(richiesta.cmd, "lascia"))                   /* gestione rilascio oggetto */
        gestione_lascia(utente, richiesta, risposta); 

    /*-- FUNZIONE A SCELTA --*/ 
    else if(!strcmp(richiesta.cmd, "user"))                     /* scleta giocatore a cui chiedere aiuto */
        gestione_user(utente, richiesta, risposta);
    else if(!strcmp(richiesta.cmd, "yes")                       /* gestione risposta notifica */
        || !strcmp(richiesta.cmd, "no"))
            gestione_notifica(utente, richiesta, risposta);
    else if(!strcmp(richiesta.cmd, "aiuto"))                    /* gestione aiuto altro giocatore */
        gestione_aiuto(utente, richiesta, risposta);
    else{
        strcpy(risposta->richiesta, richiesta.cmd);
        risposta->bool_ret = 0;
        strcat(risposta->msg, "Comando non valido.");
    }

    /* inserisco token raccolti, token rimanenti, secondi ramanenti */
    insert_dati(utente, risposta->info);

    /* invio le notifiche al client */
    strcpy(risposta->notice, utente->notifica);
}



/*---- SIGNUP ----*/
/* gestione registrazione del client */
void comando_signup(int client, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    FILE* db_utenti;
    char user[LEN_CAMPI];
    char pass[LEN_CAMPI];
    struct info_user* utente = NULL;                                        /* struttura con dati utente */

    /* inserisco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);                             /* inserisco a quale comando rispondo */
    
    /* controllo che ci sono i parametri giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] == '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }

    db_utenti = fopen("db_utenti.txt", "a+");                               /* apro il file in lettura e append */
    if(db_utenti == NULL){
        printf("Errore connessione all'elenco utenti\n");
        exit(1);
    }

    /* analizzo db_utenti.txt fino fino a fine file */
    while(fscanf(db_utenti, "%s %s", user, pass) != EOF){
        /*controllo se esiste già un utente con lo stesso nome*/    
        if(strcmp(user, richiesta.campo1) == 0){
            /* gestisto messaggio errore per il client */
            risposta->bool_ret = 0;
            strcpy(risposta->msg, "Username già esiste");

            fflush(db_utenti);
            fclose(db_utenti);
            return;
        }
    }
    
    /* inserirsco user e pass in db_utenti.txt */
    fprintf(db_utenti, "%s %s\n", richiesta.campo1, richiesta.campo2);
    fclose(db_utenti);

    /* inserisco l'utente tra quelli che si sono autenticati */
    utente = new_user(client);                                  
    /* segno che ha fatto autenticazione ma non ha avviato partita*/
    utente->attivo = 0;  
    /* inserisco l'username */
    strcpy(utente->username, richiesta.campo1); 


    /* gestisto messaggio per il client */
    risposta->bool_ret = 1;
    strcpy(risposta->msg, "Signup effettuato con successo");    
    gestione_stanze(risposta->info_next);                                   /* inserisco stanze disponibili da inviare al client */
}



/*---- LOGIN ----*/
/* gestione accesso del client */
void comando_login(int client, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    FILE* db_utenti;
    char user[LEN_CAMPI];
    char pass[LEN_CAMPI];
    struct info_user* utente = NULL;                                        /* struttura con dati utente */

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);                             /* inserisco a quale comando rispondo */

    /* controllo che ci sono i parametri giusti per il comando */
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] == '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }

    db_utenti = fopen("db_utenti.txt", "r");                                /* apro il file in lettura */
    if(db_utenti == NULL){
        printf("Errore connessione all'elenco utenti\n");
        exit(1);
    }

    /* analizzo db_utenti.txt fino fino a fine file */
    while(fscanf(db_utenti, "%s %s", user, pass) != EOF){

        /*controllo se esiste già un utente con lo stesso nome e con password corretta */    
        if(strcmp(user, richiesta.campo1) == 0
            && strcmp(pass, richiesta.campo2) == 0){

            /* controllo che l'utente non sia già attivo */
            utente = duplicato(client, richiesta.campo1);
            if(utente != NULL){                         
                /* gestisto messaggio errore per il client */
                risposta->bool_ret = 0;
                strcpy(risposta->msg, "Utente già attivo");
                return;
            } else {
                /* inserisco l'utente tra quelli che si sono autenticati */
                utente = new_user(client);
                /* segno che ha fatto autenticazione ma non ha avviato partita*/
                utente->attivo = 0;
                /* inserisco l'username */
                strcpy(utente->username, richiesta.campo1);
            }    
 
            /* controllo stanze disponibili da inviare al client */
            gestione_stanze(risposta->info_next);


            /* gestisto messaggio per il client */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, "Login effettuato con successo");

            fclose(db_utenti);
            return;
        }
    }
    fclose(db_utenti);

    /* gestisto messaggio errore per il client */
    risposta->bool_ret = 0;
    strcpy(risposta->msg, "Username o passoword errate");    
}



/*---- START ----*/
/* gestione avvio gioco in una stanza */
void comando_start(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int idx;                                                /* indice nel vettore stanze */
    int len_room = sizeof(stanze)/sizeof(stanze[0]);        /* numero stanze disponibili */
    int max_stanze = len_room * NUM_SCENARI;                /* numero stanze disponibili */


    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);             /* inserisco a quale comando rispondo */

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }

    /* controllo che il codice della stanza sia valido */
    if(atoi(richiesta.campo1)<=0 || atoi(richiesta.campo1) > max_stanze){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Codice room errato. Prova a digitare nuovamente il comando.");

        return;
    }

    /* inserisco informazioni nella struttura dati dell'utente attivo */
    utente->room = atoi(richiesta.campo1);                                      /* codice della room inizata */
    utente->scenario = (atoi(richiesta.campo1)-1) % NUM_SCENARI;                /* per utente enumarate da 1*/
    time(&utente->start_time);                                                  /* inserisco l'ora attuale */

    /* ad ogni stanza appartengono NUM_SCENARI e il vettore room indicizzazione da 0 */
    idx = (utente->room-1)/NUM_SCENARI;

    /* oltre al login, segno che l'utente ha avviato partita */
    utente->attivo = 1;

    /* informazioni da inviare al client */
    risposta->bool_ret = 1;
    sprintf(risposta->msg, "Hai avviato la %s\nHai %d minuti per raccogliere %d token. Buona fortuna!", 
            stanze[idx].nome[utente->scenario], (stanze[idx].max_time/60), stanze[idx].tot_token);
    return;
}



/*---- LOOK ----*/
/* gestione descrizione di location o object */
void comando_look(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int idx;                                                    /* indice vettore stanze */
    int i;                                                      /* per iterazione */

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);                 /* inserisco a quale comando rispondo */

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }

    /* Ad ogni stanza appartengono NUM_SCENARI e il vettore room indicizzazione da 0 */
    idx = (utente->room-1)/NUM_SCENARI;          

    /* il client richiede descrizione stanza, quindi nessun paramentro */
    if(richiesta.campo1[0] == '\0'){
        risposta->bool_ret = 1;
        strcpy(risposta->msg, stanze[idx].description);
        return;
    }



    /* controllo se parametro utente è stato una LOCATION*/
    for(i=0; i < stanze[idx].num_location; i++){
        if(!strcmp(richiesta.campo1, stanze[idx].location[i].name)){            /* controllo se campo1 è una location */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, stanze[idx].location[i].description);

            /*aggiungo altre informazioni che dipendono dallo SCENARIO */
            if(!strcmp(richiesta.campo1, "armadietto")){
                strcat(risposta->msg, dati_scenari[utente->scenario].nome_vinile);
            }       

            return;
        }
    }



    /* controllo se parametro utente è stato un OGGETTO LIBERO */
    i = search_obj_free(stanze[idx].obj_free, stanze[idx].num_obj_free, richiesta.campo1);
    
    if(i != -1){        /* se il ritorno è diverso da -1 allora è stato trovato un elemento */
        risposta->bool_ret = 1;
        strcpy(risposta->msg, stanze[idx].obj_free[i].description);

        /*aggiungo altre informazioni che dipendono dal tipo di scenario */
        if(strcmp(richiesta.campo1, "spartito") == 0){                         
            strcat(risposta->msg, dati_scenari[utente->scenario].nome_vinile);
        } 
        return;
    }



    /* controllo se parametro utente è stato un OGGETTO BLOCCATO */
    i = search_obj_lock(stanze[idx].obj_lock, stanze[idx].num_obj_lock, richiesta.campo1);
    
    if(i != -1){        /* se il ritorno è diverso da -1 allora è stato trovato un elemento */
        risposta->bool_ret = 1;
        strcpy(risposta->msg, stanze[idx].obj_lock[i].description);
        return;
    }
    

    /* arrivo qui se in ingresso non c'è né location né oggetto*/
    risposta->bool_ret = 0;
    strcpy(risposta->msg, "Location o Oggetto inserito non fa parte della stanza.");
}



/*---- TAKE ----*/
/* gestione take oggetto che può essere libero o bloccato da enigma */
void comando_take(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int idx;                                                    /* indice vettore stanze */
    int i;                                                      /* per iterazione */
    char* objs;                                                 /* stringa dinamica con elenco oggetti presi */

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);                 /* inserisco a quale comando rispondo */

    /* Ad ogni stanza appartengono NUM_SCENARI e il vettore room indicizzazione da 0 */
    idx = (utente->room-1)/NUM_SCENARI;          


    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }

    /* controllo che non si SUPERA il MAX DI OGGETTI PRENDIBILI */
    if(utente->num_obj_presi + 1 > MAX_OBJ_TAKEN){
        /* alloco memoria dinamica per inserire stringa elenco oggetti presi */
        objs = (char *)calloc(LEN_INFO * sizeof(char), sizeof(char));          /*calloc alloca memoria dinamica e pulisco */
        if(objs == NULL){
            printf("Errore allocazione memoria");
            exit(1);
        }

        /* funzione che si occupa di inserire in objs la stringa degli oggetti presi */
        elenco_oggetti(objs, utente);

        /* insersco dati per la risposta*/
        strcpy(risposta->richiesta, "lascia");              /* dico all'utente che l'operazione che deve fare è lasciare oggetto*/
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Hai raggiunto il limite degli oggetti che puoi prendere.\n" 
                                "Scrivi il nome dell'oggetto che vuoi lasciare:"); 
        strcpy(risposta->info_next, objs); 
        free(objs);
        return;
    }



    /* parametro utente è stato un OGGETTO LIBERO */
    i = search_obj_free(stanze[idx].obj_free, stanze[idx].num_obj_free, richiesta.campo1);      /* indice elemento nell'array */
    
    /* se il ritorno è diverso da -1 allora è stato trovato un elemento */
    if(i != -1){
            /* controllo che l'oggetto non sia tra gli oggetti presi */
            if(search_obj_free(utente->obj_free_presi, utente->num_obj_free, stanze[idx].obj_free[i].name) != -1){
                risposta->bool_ret = 0;
                strcpy(risposta->msg, "Già hai preso questo oggetto."); 
                return;
            }
            
            /* incremento numero di oggetti presi dal client */
            utente->num_obj_presi++;

            /* alloco un nuovo elemento nella lista dinamica degli oggetti presi */
            utente->num_obj_free++;
            utente->obj_free_presi = (struct info_obj_free*)realloc(utente->obj_free_presi, sizeof(struct info_obj_free)*utente->num_obj_free);
            if(utente->obj_free_presi == NULL){
                printf("Errore allocazione memoria");
                exit(1);
            }
            utente->obj_free_presi[utente->num_obj_free-1] = stanze[idx].obj_free[i];

            /* insersco dati per la risposta*/
            risposta->bool_ret = 1;
            strcpy(risposta->msg, stanze[idx].obj_free[i].take_description); 

            return;
    }



    /* parametro utente è OGGETTO BLOCCATO CON ENIGMA RISOLTO */
    /* se ho risolto l'enigma lo posso prendere */
    i = search_obj_lock(utente->obj_sbloccati, utente->num_sbloccati, richiesta.campo1);
    /* se il ritorno è diverso da -1 allora è stato trovato un elemento */
    if(i != -1){

        /* controllo che l'oggetto non sia tra gli oggetti presi */
        if(utente->obj_sbloccati[i].stato == 1){
            risposta->bool_ret = 0;
            strcpy(risposta->msg, "Già hai preso questo oggetto."); 
            return;
        }

        /* incremento numero di oggetti presi dal client */
        utente->num_obj_presi++;

        /* indico che è stato preso */
        utente->obj_sbloccati[i].stato = 1;

        /*---- GESTIONE VITTORIA ----*/
        /* la chiave è sbloccata e la sto prendendo */
        if(!strcmp(richiesta.campo1, "chiave")){
                    /* gestione token, incremento token presi */
                    utente->token_presi++;

                    strcpy(risposta->richiesta, "win");                 /* dico all'utente che ha vinto */
                    risposta->bool_ret = 1;
                    strcpy(risposta->msg, stanze[idx].desc_vittoria);
                    return;
        }

        /* insersco dati per la risposta */
        risposta->bool_ret = 1;
        strcpy(risposta->msg, utente->obj_sbloccati[i].take_unlock);  

        return;
    }



    /* controllo tra gli OGGETTI BLOCCATI E CHE NON HO ANCORA RISOLTO ENIGMA */
    i = search_obj_lock(stanze[idx].obj_lock, stanze[idx].num_obj_lock, richiesta.campo1);      /* indice elemento nell'array */
    /* se il ritorno è diverso da -1 allora è stato trovato un elemento */
    if(i != -1){

        if(stanze[idx].obj_lock[i].tipologia == ORDINE){                        /* l'enigma è seguire ordine di azioni predefinite */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, stanze[idx].obj_lock[i].take_lock);
            return;

        /* devo inviare ENIGMA all'utente */
        } else {
            
            /* insersco dati per la risposta */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, stanze[idx].obj_lock[i].take_lock);

            if(stanze[idx].obj_lock[i].tipologia == MULTIPLA){                  /* al client invio un enigma a risposta multipla */
                strcpy(risposta->richiesta, "e_mult");  

            } else if(stanze[idx].obj_lock[i].tipologia == INDOVINELLO) {       /* al client invio un enigma ad indovinello */
                strcpy(risposta->richiesta, "e_indo");    

                /* invio al client l'informazione che può chiedere aiuto ad un altro giocatore */ 
                if(utente->bonus == 0){         
                    strcat(risposta->msg, "\nSe vuoi chiedere aiuto ad un altro giocatore digita help.\n"
                                        "Ricorda puoi utilizzare questo bonus una sola volta.\n");
                }

                /* invio al client numero tentativi rimanenti, uso info_next come vettore appoggio */
                sprintf(risposta->info_next, "%s %d\n", "Numero di tentativi rimanenti:",       /* uso info->next come vettore d'appoggio */
                    (MAX_ERR_INDO-utente->num_err_indo));
                strcat(risposta->msg, risposta->info_next);
                strcpy(risposta->info_next, "_");

            }

            /* qui insersico l'enigma per il client */
            strcpy(risposta->info_next, stanze[idx].obj_lock[i].enigma[utente->scenario]->text);
            return;
        }
    }
    
    /* se sono arrivato qui significa che non ho trovato nessun oggetto */
    risposta->bool_ret = 0;
    strcpy(risposta->msg, "L'oggetto non fa parte della stanza.");
}



/*---- USE ----*/
/* gestione uso di oggetti presi nella stanza */
void comando_use(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int idx;                                                        /* indice vettore stanze */
    int i_free;                                                     /* per iterazione per oggetto liberi*/
    int i_lock;                                                     /* per iterazione per oggetto bloccati */

    /* uso questi due indici per vedere se posso usare la chiave */
    int i_chitarra;
    int i_vinile;

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");

        return;
    }

    /* Ad ogni stanza appartengono NUM_SCENARI e il vettore room indicizzazione da 0 */
    idx = (utente->room-1)/NUM_SCENARI; 

    /* controllo che il primo paramentro sia stato raccolto*/
    i_free = search_obj_free(utente->obj_free_presi, utente->num_obj_free, richiesta.campo1);
    i_lock = search_obj_lock(utente->obj_sbloccati, utente->num_sbloccati, richiesta.campo1);
    if(i_free == -1 && (i_lock == -1 || !utente->obj_sbloccati[i_lock].stato)){
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "L'oggetto 1 non è stato preso.");
        return;
    }

    /* gestisco use vinile giradischi */
    if((!strcmp(richiesta.campo1, "vinile") && !strcmp(richiesta.campo2, "giradischi"))){

            /* insersco dati per la risposta */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, "Hai correttamente usato gli oggetti.\n");

            /* indico che l'oggetto chitarra è stato usato */
            utente->obj_sbloccati[i_lock].usato = 1;

            /* cerco indice oggetto chitarra */
            i_chitarra = search_obj_lock(utente->obj_sbloccati, utente->num_sbloccati, "chitarra");

            /* controllo se ho fatto passi per sbloccare CHIAVE: usato chitarra e vinile quindi sbloccato 2 token */
            if(utente->token_presi == 2 && i_chitarra != -1 && utente->obj_sbloccati[i_chitarra].usato){

                /* posso sbloccare chiave */
                utente->num_sbloccati++;
                utente->obj_sbloccati = (struct info_obj_lock*)realloc(utente->obj_sbloccati, sizeof(struct info_obj_lock)*utente->num_sbloccati);
                if(utente->obj_sbloccati == NULL){
                    printf("Errore allocazione memoria");
                    exit(0);
                }

                /* cerco le informazione dell'oggetto chiave */
                i_lock = search_obj_lock(stanze[idx].obj_lock, stanze[idx].num_obj_lock, "chiave");

                /* le inserisco tra gli oggetti sbloccati */
                utente->obj_sbloccati[utente->num_sbloccati-1] = stanze[idx].obj_lock[i_lock];
                
                /* indico che è statp sbloccato ma non preso */
                utente->obj_sbloccati[utente->num_sbloccati-1].stato = 0;
                
                /* insersco dati per la risposta */
                strcpy(risposta->info_next, "Il sistema elettronico ha ascoltato la musica del **giradischi** e **chitarra**.\n"
                                        "Si è sbloccata la **chiave** di violino, prova a prenderla.");
            } else {
                strcpy(risposta->info_next, "C'è un problema, la melodia del **vinile** non basta, " 
                                        "c'è bisogno della melodia di uno strumento musicale "
                                        "per sbloccare la **chiave** di violino e per poter uscire.");
            }

            return;
    }

    /* gestisco use chiatarra spartito */
    if(!strcmp(richiesta.campo1, "chitarra") && !strcmp(richiesta.campo2, "spartito")){
            
            /* insersco dati per la risposta */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, "Hai correttamente usato gli oggetti.\n");

            /* indico che l'oggetto chitarra è stato usato */
            utente->obj_sbloccati[i_lock].usato = 1;

            /* cerco indice oggetto chitarra */
            i_vinile = search_obj_lock(utente->obj_sbloccati, utente->num_sbloccati, "vinile");

            /* controllo se ho fatto passi per sbloccare CHIAVE: usato chitarra e vinile quindi sbloccato 2 token */
            if(utente->token_presi == 2 && utente->obj_sbloccati[i_vinile].usato){
                
                /* posso sbloccare chiave */
                utente->num_sbloccati++;
                utente->obj_sbloccati = (struct info_obj_lock*)realloc(utente->obj_sbloccati, sizeof(struct info_obj_lock)*utente->num_sbloccati);
                if(utente->obj_sbloccati == NULL){
                    printf("Errore allocazione memoria");
                    exit(0);
                }

                /* cerco le informazione dell'oggetto chiave */
                i_lock = search_obj_lock(stanze[idx].obj_lock, stanze[idx].num_obj_lock, "chiave");

                /* le inserisco tra gli oggetti sbloccati */
                utente->obj_sbloccati[utente->num_sbloccati-1] = stanze[idx].obj_lock[i_lock];

                /* indico che è stato sbloccato, ma non preso */
                utente->obj_sbloccati[utente->num_sbloccati-1].stato = 0;
                
                /* insersco dati per la risposta */
                strcpy(risposta->info_next, "Il sistema elettronico ha ascoltato la musica del **giradischi** e **chitarra**.\n"
                                        "Si è sbloccata la **chiave** di violino, prova a prenderla.");
            } else {
                strcpy(risposta->info_next, "C'è un problema, la melodia della **chitarra** non basta, "
                                            "c'è bisogno di avere una melodia completa "
                                        "per sbloccare la **chiave** di violino e per poter uscire.");
            }
            return;
    }

    /* il coamndo use è stato inserito in maniera scorretta */
    risposta->bool_ret = 0;
    if(richiesta.campo2[0] == '\0'){ 
        strcpy(risposta->msg, "Non è il modo corretto per usare l'oggetto, "
                        "trova un altro oggetto da usare insieme.");
        return;
    } else {
        strcpy(risposta->msg, "Non è il modo corretto per usare gli oggetti.");
        return;
    }
}



/*---- OBJS ----*/
/* elenco degli oggetti presi */
void comando_objs(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int counter;                                        /* usato per vedere num oggetti presi */                               
    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, richiesta.cmd);

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] != '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");

        return;
    }

    /* insersco dati per la risposta */
    risposta->bool_ret = 1;
    strcpy(risposta->msg, "Elenco degli oggetti raccolti:\n");
    counter = elenco_oggetti(risposta->msg, utente);

    /* se il ritorno è 0 non sono stati presi oggetti */
    if(!counter){
        strcat(risposta->msg, "Non hai raccolto ancora nessun oggetto");
    }
}



/*---- END ----*/
/* elimina un elemento dalla lista client attivi */
void comando_end(int sd){
    struct info_user* utente = lista_users;
    struct info_user* prec = NULL; 

    while (utente != NULL && utente->id != sd) {
        prec = utente;
        utente = utente->next;
    }

    if(utente != NULL){
        if (prec != NULL) {
            prec->next = utente->next;
        } else {
            lista_users = utente->next;
        }

        /* utente->obj_free_presi è già stato deallocato */
        free(utente->obj_sbloccati);
        free(utente);
    }
}






/*-----------------------------------------------------------*/
/*------ FUNZIONI COMANDO HELP E COMUNICAZIONE TRA HOST -----*/
/*-----------------------------------------------------------*/

/* gestione comando help per rispondere ad un indovinello */
int funzione_help(int utente, char msg[]){
    char tmp[64];                                       /* stringa di appoggio */
    struct info_user* current = lista_users;            /* lista degli utenti attivi*/
    int stato = 0;                                      /* serve a ritornare 0 se non ci sono altri utenti*/

    strcpy(msg, "Digita il comando user seguito dal campo id del giocatore che hai scelto.\nEsempio: user 5\n\n"
                "Ecco l'elenco dei giocatori attivi:\n");

    /* creo elenco utenti attivi eccetto il client corrente */
    while (current != NULL) {
        if (current->id != utente && current->attivo){ 
            sprintf(tmp, "id: %d\t  username: %s\n", current->id, current->username);
            strcat(msg, tmp);
            stato = 1;
        }
        current = current->next;
    }

    return stato;    /* 0 => nessun altro utente */
}


/* gestione scelta dell'utente dal quale farsi aiutare */
void gestione_user(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    struct info_user* destinatario = NULL;
    /* insersco alcuni dati per la risposta */
    strcpy(risposta->richiesta, richiesta.cmd);

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }

    /* controlle se l'utente destinatario si è scollegato*/
    destinatario = search_user(atoi(richiesta.campo1));
    if(destinatario == NULL){
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "L'utente non esiste o si è scollegato.");
        return;
    }

    /* l'utente ha inserito il suo id */
    if(destinatario->id == utente->id){
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Paramentro id non valido.");
        return;
    }


    /* già un altro utente ha chiesto l'aiuto di questo giocatore */
    if(destinatario->help_user != -1){
        risposta->bool_ret = 1;
        strcpy(risposta->msg, "Il destinatario dell'aiuto è già occupato con un altro utente.");
        return;
    }

    /* il bonus 'help' si può usare una sola volta */
    utente->bonus = 1;

    /* inserisco informazione nella struttura dati destinatario */
    destinatario->enigma_help = &dati_scenari[utente->scenario].enigma_ind;                 /* inserisco l'enigma */
    destinatario->help_user =  utente->id;                                                  /* inserisco utente richiedente */
    
    /* inserisco notifica struttura dati destinatatio */
    sprintf(destinatario->notifica, "Vuoi aiutare un altro utente a rispondere ad un indovinello?\n"
            "Se suggerisci una risposta corretta riceverai %d minuti bonus.\n"
            "Digita il comando 'yes' per rispondere all'indovinello. Altrimenti digita 'no'", 
            stanze[(utente->room-1)/NUM_SCENARI].time_help);

    /* insersco dati per la risposta */
    risposta->bool_ret = 1;
    strcpy(risposta->msg, "Richiesta di aiuto effettuata con successo. Continua a giocare, "
                            "se l'altro giocatore deciderà di aiutarti riceverai una notifica.");
}


/* gestione notifica, utente ha accetto o rifiutato di aiutare un altro giocatore */
void gestione_notifica(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    struct info_user* richiedente;

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, "risp");

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] != '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");

        return;
    }

    /* controllo effettivamente se un giocatore gli ha chiesto aiuto */
    if(utente->help_user == -1){
        risposta->bool_ret = 0;
        strcpy(risposta->richiesta, "risp");
        strcpy(risposta->msg, "Non hai nessuna richiesta di aiuto. Comando non valido.");
        return;
    }

    /* insersco dati per la risposta */
    risposta->bool_ret = 1;
    strcpy(utente->notifica, "_");

    
    if(!strcmp(richiesta.cmd, "no")){           /* l'utente ha deciso di non aiutare */      

        /* cerco utente che ha chiesto aiuto, per inviare la risposta */
        richiedente = search_user(utente->help_user);

        /* insersco nella notifica del richiedente l'aiuto*/
        sprintf(richiedente->notifica, "L'utente %d ha deciso di non aiutarti a risolvere l'indovinello.", utente->id);
        /* l'utente può chiedere aiuto ad un altro giocatore */
        richiedente->bonus = 0;

        /* pulisco strutture dati */
        utente->help_user = -1;
        utente->enigma_help = NULL;

        /* insersco dati per la risposta */
        strcpy(risposta->msg, "Gestione corretta della notifica!");
        strcpy(risposta->info_next, "Continua a giocare!");
        strcpy(utente->notifica, "_");
    } else {                                    /* l'utente ha deciso di aiutare */
        /* insersco dati per la risposta*/
        strcpy(risposta->richiesta, "aiuto");
        sprintf(risposta->msg, "L'utente %d ti ha chiesto aiuto per questo indovinello.", utente->help_user);
        /* inserisco l'enigma da risolvere */
        strcpy(risposta->info_next, utente->enigma_help->text);
    }
}


/* gestione risposta enigma di aiuto, tempo bonus e avviso del client richiedente */
void gestione_aiuto(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    struct info_user* richiedente;

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, "risp");                    /* dico al client che ho gestito la sua risposta all'enigma */

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }
    
    /* controllo che qualcuno abbia chiesto aiuto */
    if(utente->help_user == -1){
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Non hai nessuna richiesta di aiuto");
        return;
    }
    
    /* cerco utente che ha chiesto aiuto, per inviare la risposta */
    richiedente = search_user(utente->help_user);

    /* insersco nella notifica del richiedente l'aiuto*/
    sprintf(richiedente->notifica, "L'utente %d ti ha suggerito la risposta all'indovinello: %s", utente->id, richiesta.campo1);

    /* insersco dati per la risposta */
    risposta->bool_ret = 1;

    /* aggiungo tempo bonus se risposta giusta altrimenti invio errore */
    if(utente->enigma_help->risposta == richiesta.campo1[0]){
        utente->time_bonus += stanze[(utente->room-1)/NUM_SCENARI].time_help*60;
        strcpy(risposta->msg, "Complimenti hai risposto correttamente. Hai 3 minuti bonus. Continua a giocare...");
    } else {
        strcpy(risposta->msg, "La risposta non è corretta. Continua a giocare...");
    }

    /* pulisco strutture dati*/
    utente->help_user = -1;
    utente->enigma_help = NULL;
}






/*-----------------------------------------------------------*/
/*------ FUNZIONI UTILITA' PER LA GESTIONE DEI COMANDI ------*/
/*-----------------------------------------------------------*/

/* controllo stanze disponibili da inviare al client */
void gestione_stanze(char info[]){
    char tmp[64];
    int len_room = sizeof(stanze)/sizeof(stanze[0]);
    int i = 0;                      /* utile per la concatenazione stringhe */         

    info[0] = '\0';                 /* pulisco info */

    /* controllo tutte le stanze disponibili, inserisco codice e nome in un buff */
    for (i = 0; i < len_room; i++) {
        /*stanza i, scenario 1*/
        sprintf(tmp, "Cod. %d\t %s\n", 2*i + 1, stanze[i].nome[0]);
        strcat(info, tmp);

        /*stanza i, scenario 2*/
        sprintf(tmp, "Cod. %d\t %s\n", 2*i + 2, stanze[i].nome[1]);
        strcat(info, tmp);
    }
}


/* funzione che gestisce la risoluzione enigma */
void gestione_enigma(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int idx;                    /* indice vettore stanze */
    int i;                      /* per iterazione */

    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, "risp");                    /* dico al client che ho gestito la sua risposta all'enigma */

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");
        return;
    }


    /* GESTIONE FUNZIONALITA' HELP*/
    if(!strcmp(richiesta.campo1, "help") && !strcmp(richiesta.cmd, "e_indo")){

        /* se l'utente ha usato il bonus non lo può usare nuovamente */
        if(utente->bonus == 1){
            risposta->bool_ret = 0;
            strcpy(risposta->msg, "Già hai usato questo bonus.");
            return;
        }


        risposta->bool_ret = 1;

        /* insersco dati per la risposta */
        strcpy(utente->notifica, "_");
        strcpy(risposta->richiesta, "list");                    /* dico al client cosa sto inviando */
        if(!funzione_help(utente->id, risposta->msg)){          /* inserisco elenco utenti attivi */
            strcat(risposta->msg, "Non ci sono utenti attivi a cui chiedere.");
        }
        return;
    }

    /* Ad ogni stanza appartengono NUM_SCENARI e il vettore room indicizzazione da 0 */
    idx = (utente->room-1)/NUM_SCENARI;



    /* La risposta è per un enigma a RISPOSTA MULTIPLA */ 
    if(!strcmp(richiesta.cmd, "e_mult")){
        /* risposta esatta */
        if(dati_scenari[utente->scenario].enigma_mult.risposta == richiesta.campo1[0]){

            /* aggiungo un elemento alla lista degli oggetti sbloccati */
            utente->num_sbloccati++;
            utente->obj_sbloccati = (struct info_obj_lock*)realloc(utente->obj_sbloccati, sizeof(struct info_obj_lock)*utente->num_sbloccati);
            if(utente->obj_sbloccati == NULL){
                printf("Errore allocazione memoria");
                exit(0);
            }

            /* cerco l'oggetto associato a questo enigma */
            for(i=0; i<stanze[idx].num_obj_lock; i++){
                if(!strcmp(stanze[idx].obj_lock[i].enigma[utente->scenario]->text, dati_scenari[utente->scenario].enigma_mult.text)){
                    utente->obj_sbloccati[utente->num_sbloccati-1] = stanze[idx].obj_lock[i];
                    break;
                }
            }

            /* indico che adesso è un oggetto sbloccato, ma non preso */
            utente->obj_sbloccati[utente->num_sbloccati-1].stato = 0;

            /* gestione token, incremento token presi */
            utente->token_presi++;

            /* insersco dati per la risposta */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, dati_scenari[utente->scenario].enigma_mult.msg_corretto);
            return;
        }else {         /* risposta errata */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, dati_scenari[utente->scenario].enigma_mult.msg_errore);
            return;
        }
    }



    /* La risposta è per un enigma di INDOVINELLO */ 
    if(!strcmp(richiesta.cmd, "e_indo")){

        /* se la risposta la sta dando dopo aver chiesto un aiuto posso togliere notifica */
        if(utente->bonus){
            strcpy(utente->notifica, "_");
        }

        /* risposta corretta */
        if(dati_scenari[utente->scenario].enigma_ind.risposta == richiesta.campo1[0]){

            /* aggiungo un elemento alla lista degli oggetti sbloccati */
            utente->num_sbloccati++;
            utente->obj_sbloccati = (struct info_obj_lock*)realloc(utente->obj_sbloccati, sizeof(struct info_obj_lock)*utente->num_sbloccati);
            if(utente->obj_sbloccati == NULL){
                printf("Errore allocazione memoria");
                exit(0);
            }

            /* cerco l'oggetto associato a questo enigma */
            for(i=0; i<stanze[idx].num_obj_lock; i++){
                if(!strcmp(stanze[idx].obj_lock[i].enigma[utente->scenario]->text, dati_scenari[utente->scenario].enigma_ind.text)){
                    utente->obj_sbloccati[utente->num_sbloccati-1] = stanze[idx].obj_lock[i];
                    break;
                }
            }

            /* indico che adesso è un oggetto sbloccato, ma non preso */
            utente->obj_sbloccati[utente->num_sbloccati-1].stato = 0;

            /* gestione token, incremento token presi */
            utente->token_presi++;

            /* insersco dati per la risposta */
            risposta->bool_ret = 1;
            strcpy(risposta->msg, dati_scenari[utente->scenario].enigma_ind.msg_corretto);
            return;
        }
        
        else {     /* risposta errata */
            /* incremento numero errori per indovinello */
            utente->num_err_indo++;

            /* controllo se utente ha raggiunto massimo numero di errori all'indovinello */
            if(utente->num_err_indo >= MAX_ERR_INDO){
                strcpy(risposta->richiesta, "max_err");
                risposta->bool_ret = 0;
                strcpy(risposta->msg, "Hai raggiunto massimo errori.\nHAI PERSO!");
                return;
            }

            /* insersco dati per la risposta */
            strcpy(risposta->richiesta, "errore");
            risposta->bool_ret = 1;
            strcpy(risposta->msg, dati_scenari[utente->scenario].enigma_ind.msg_errore);
            sprintf(risposta->info_next, "%s %d", "Numero di tentativi rimanenti:", (MAX_ERR_INDO-utente->num_err_indo));
            return;
        }
    }
}


/* funzione che gestisce richiesta di lasciare un oggetto */
void gestione_lascia(struct info_user* utente, struct Formato_cmd richiesta, struct Formato_resp* risposta){
    int i;                                                      /* per iterazione */
    struct info_obj_free* temp_free;


    /* insersco alcuni dati per la risposta*/
    strcpy(risposta->richiesta, "risp");

    /* controllo che ci sono i parametri siano giusti per il comando*/
    if(richiesta.campo1[0] == '\0' || richiesta.campo2[0] != '\0'){
        /* gestisto messaggio errore per il client */
        risposta->bool_ret = 0;
        strcpy(risposta->msg, "Numero parametri ingresso errati");

        return;
    }

    /* controllo che L'oggetto la lasciare è tra quelli LIBERI */
    i = search_obj_free(utente->obj_free_presi, utente->num_obj_free, richiesta.campo1);
    
    if(i != -1){            /* se il ritorno è diverso da -1 allora è stato trovato un elemento */
        
        /* inserisco ultimo elemento liberato da oggetto lasciato */
        utente->num_obj_free--;

        /* controllo se ci sono altri oggetti liberi */
        if(utente->num_obj_free > 0){
            utente->obj_free_presi[i] = utente->obj_free_presi[utente->num_obj_free];

            /* ridimensiona l'array */
            temp_free = (struct info_obj_free*)realloc(utente->obj_free_presi, (utente->num_obj_free) * sizeof(struct info_obj_free));
            if (temp_free == NULL) {
                printf("Errore allocazione memoria");
                exit(0);
            }

            /* N.B. La realloca si occupa anche di liberare lo spazio precedente occupato */

            /* assegna il nuovo puntatore */
            utente->obj_free_presi = temp_free;
        } 
        else {          /* non ci sono più oggetti liberi */
            /* c'era un solo elemento */
            free(utente->obj_free_presi);
        }

        /* diminuisco contatore generale di oggetti presi */
        utente->num_obj_presi--;

        /* insersco dati per la risposta */
        risposta->bool_ret = 1;
        strcpy(risposta->msg, "Operazione effettuato con successo. Ora puoi prendere l'oggetto " 
                        "che cercavi inizialmente."); 
        return;
    }

    /*controllo che sia negli oggetti bloccati */
    i = search_obj_lock(utente->obj_sbloccati, utente->num_sbloccati, richiesta.campo1);
    if(i != -1 && utente->obj_sbloccati[i].stato == 1){                /* esiste e deve essere preso ovvero sbloccato */
        
        /* diminuisco contatore generale di oggetti presi */
        utente->num_obj_presi--;

        /* se l'oggetto era bloccato non lo elimino dalla lista, cambio solo lo stato */
        /* perchè l'enigma è risolto quindi è comunque sbloccato, ma non preso */
        utente->obj_sbloccati[i].stato = 0;

        /* insersco dati per la risposta */
        risposta->bool_ret = 1;
        strcpy(risposta->msg, "Hai lasciato correttamente l'oggetto."); 
        return;
    }

    /* se arrivo qui significa che l'oggetto non esiste */
    risposta->bool_ret = 0;
    strcpy(risposta->msg, "L'oggetto in ingresso non è corretto."); 
}


/* inserisco in una stringa tutti gli oggetti presi */
int elenco_oggetti(char* objs, struct info_user* utente){
    int i;                                                      /* interatore */
    int counter = 0;
    
    char* tmp = (char *)malloc(LEN_INFO * sizeof(char));             /* di supporto per concatenare */

    /*Inserisco oggetto bloccati */
    for (i = 0; i < utente->num_sbloccati; i++) {
        if(utente->obj_sbloccati[i].stato == 1){
            counter++;
            sprintf(tmp, "%s\n", utente->obj_sbloccati[i].name);
            strcat(objs, tmp);
        }
    }

    /*Inserisco oggetto free*/
    for (i = 0; i < utente->num_obj_free; i++) {
        counter++;
        if(i == utente->num_obj_free-1)
            sprintf(tmp, "%s", utente->obj_free_presi[i].name);
        else 
            sprintf(tmp, "%s\n", utente->obj_free_presi[i].name);
        strcat(objs, tmp);
    }

    free(tmp);

    /* ritorno numero di oggetti presi */
    return counter;
}


/* controllo che non sia finito il tempo */
int controllo_time(struct info_user* utente){
    /* secondo alla termine */
    int tempo_rimanente;
    /* tempo correte */
    time_t corrente;
    /* limite tempo nella stanza */
    int max_time = stanze[(utente->room-1)/NUM_SCENARI].max_time;

    /*inserisco ora corrente */
    time(&corrente);

    /* faccio la differenza */
    tempo_rimanente = difftime(utente->start_time + utente->time_bonus + max_time , corrente);
    
    /* ritorno il tempo rimanente */
    return tempo_rimanente;
}


/* inserisco in una stringa token raccolti, token rimanenti, secondi ramanenti */
void insert_dati(struct info_user* utente, char msg[]){
    int rimanenti = controllo_time(utente);
    int minuti = rimanenti/60;
    int secondi = rimanenti%60;
    sprintf(msg, "Token raccolti: %d\tToken mancanti: %d\tTempo rimanente: %d min e %d sec",
                utente->token_presi, stanze[(utente->room-1)/NUM_SCENARI].tot_token - utente->token_presi, minuti, secondi);
}


/* cerca un oggetto free in un vettore, ritorno l'indice, -1 se non esiste*/
int search_obj_free(const struct info_obj_free* vect, int dim, char nome[]){
    int i;
    for(i=0; i < dim; i++){
        if(!strcmp(nome, vect[i].name)){
            return i;
        }
    }
    return -1;
}

/* cerca un oggetto lock in un vettore, ritorno l'indice, -1 se non esiste*/
int search_obj_lock(const struct info_obj_lock* vect, int dim, char nome[]){
    int i;
    for(i=0; i < dim; i++){
        if(!strcmp(nome, vect[i].name)){
            return i;
        }
    }
    return -1;
}


/* aggiungo un utente alla lista degli utenti attivi */
struct info_user* new_user(int sd){
    struct info_user* client = malloc(sizeof(struct info_user));        /* alloco dinamicamente*/
    client->id = sd;                                                    /* identifico con il socket*/
    client->attivo = 0;                                                 /* dopo aver fatto start diventa attivo */
    client->room = 0; 
    client->num_obj_free = 0;                                                  
    client->obj_free_presi = NULL;
    client->num_sbloccati = 0; 
    client->obj_sbloccati = NULL;

    client->num_err_indo = 0;

    client->num_obj_presi = 0;
    client->token_presi = 0;

    strcpy(client->notifica, "_");                                          /* per indicare che non c'è niente */

    /* funzione a scelta */
    client->bonus = 0;
    client->enigma_help = NULL;
    client->help_user = -1;

    client->time_bonus = 0;

    /* inserimento in testa nella lista degli utenti */
    client->next = lista_users;
    lista_users = client;

    return client;
}


/* controllo se l'utente è ancora attivo */
struct info_user* search_user(int sd){
    struct info_user* current = lista_users;          /* lista degli utenti attivi*/

    while (current != NULL) {
        if (current->id == sd)
            return current;
        current = current->next;
    }

    return NULL;    /* elemento non trovato */
}


/* controllo se l'username è già attivo */
struct info_user* duplicato(int sd, char name[]){
    struct info_user* current = lista_users;          /* lista degli utenti attivi*/

    while (current != NULL) {
        if (current->id == sd || strcmp(current->username, name) == 0)
            return current;
        current = current->next;
    }

    return NULL;    /* elemento non trovato */
}


/* restituisce numero di utenti attivi */
int utenti_attivi(){
    int count = 0;
    struct info_user* current = lista_users;          /* lista degli utenti attivi*/

    while (current != NULL) {
        if(current->attivo){
            count++;
        }
        current = current->next;
    }
    return count;    /* elemento non trovato */
}