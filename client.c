#include "lib/funzioni.h"
#include "dir_client/utility_client.h"                         


int main(int argc, char* argv[]){
    int sd;                                     /* socket */

    struct sockaddr_in server_addr;             /* indirizzo server */

    char buff[SIZE_BUFF];                       /* buffer */

    struct Formato_cmd richiesta;               /* struttura messaggio inviato al server */
    struct Formato_resp risposta;               /* struttura risposta ricevuta dal server */

    int ret;                                    /* usato per analizzare il ritorno di funzione */
    char* pun;                                  /* puntatore utilità per stringhe */

    /* creazione socket */
    sd = socket(AF_INET, SOCK_STREAM, 0);   
    if(sd == -1){
        perror("Errore creazione socket:");
        exit(1);
    }    

    /* creazione indirizzo server */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    /* connessione al server */
    do{
        ret = connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if(ret == -1){
            perror("Error connect:");
            sleep(2);                           /* richieste connessione al server ogni 1 sec*/
        }
    }while(ret == -1);
    
    

    /*------ GESTIONE COMANDO SIGNUP o LOGIN -------*/
    system("clear");
    printf("****************************** AUTENTICAZIONE **********************************\n");
    printf("Digita un comando:\n");
    printf("1) login\t-->    accedi al tuo account\n");
    printf("2) signup\t-->    crea un nuovo account\n");
    printf("********************************************************************************\n");
    printf("\n> ");

    while(1){
        fgets(buff, SIZE_BUFF, stdin);

        if(!strcmp(buff, "login\n")){
            login(&richiesta);                  /* input per effettuare login */

            /* converto da struttura a stinga e invio al server */
            cmd_to_string(richiesta, buff);     
            send_data(sd, buff);
        } 
        else if(!strcmp(buff, "signup\n")){
            signup(&richiesta);                 /* input per effettuare signup */

            /* converto da struttura a stinga e invio al server */
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        } else {
            printf("Comando non valido\n");
            printf("\n> ");
            continue;
        }
    

        /* ricevo dati dal server e converto da stringa a struttura */
        ret = receive_data(sd, buff);
        if(!ret){
            printf("Chiusura connessione con il server\n");
            close(sd);
            exit(0);
        }
        resp_parsing(buff, &risposta);

        if(risposta.bool_ret == 1){             /* auteticazione affettuata con successo */
            break;
        }else{                                  /* errore durante l'autenticazione */
            printf("%s, inserisci un comando per l'autenticazione. \n", risposta.msg);
            printf("\n> ");
        }
    }


    /* stampo e video elenco dei comandi e room disponibili */
    system("clear");
    printf("*********************************** WELCOME! ***********************************\n");
    print_comandi();
    printf("********************************************************************************\n\n");
    printf("Avvia la stanza usando il suo codice:\n");
    printf("%s", risposta.info_next);                       /* stampo le room che ha inviato il server */
    printf("\n> ");


    /*------ GESTIONE COMANDO START ------*/
    while(1){
        /* input per avviare una stanza */
        fgets(buff, SIZE_BUFF, stdin);

        /* converto da stringa a struttura */
        ret = cmd_parsing(buff, &richiesta);

        /* controllo che il comando sia stato inserito correttamente */
        if (ret != 2 || strcmp(richiesta.cmd, "start") != 0) {
            printf("Devi scegliere lo scenario. Ad esempio 'start 1'.\n\n> ");
            continue;
        }
        
        /* invio al server la room */
        cmd_to_string(richiesta, buff);
        send_data(sd, buff);

        /* ricevo dati dal server */
        ret = receive_data(sd, buff);
        if(!ret){
            printf("Chiusura connessione con il server\n");
            close(sd);
            exit(0);
        }
        resp_parsing(buff, &risposta);


        if(risposta.bool_ret == 1){     /* avvio room effettuato con successo */
            break;
        } else{                         /* errore durante l'avvio della room */
            printf("%s\n\n> ", risposta.msg);
        }
    }

    
    /* stampo dei comandi per la fase successiva */
    system("clear");
    print_comandi();
    printf("\n%s\n\n> ", risposta.msg);

    /*---------------------------------------------*/
    /*---- GESTIONE COMANDI DURANTE LA PARTITA ----*/
    /*---------------------------------------------*/
    while(1){
        fgets(buff, SIZE_BUFF, stdin);
        
        /* CASI PARTICOLARI: oltre all'input devo inserire altre informazioni per il server*/
        if(!strcmp(risposta.richiesta, "e_mult") ||                                                                       
            !strcmp(risposta.richiesta, "e_indo") || 
            !strcmp(risposta.richiesta, "lascia") ||                                     
            !strcmp(risposta.richiesta, "aiuto")){                                     
                pun = (char*)malloc(strlen(buff) + strlen(risposta.richiesta) + 2);         /* lunghezza + 2 per lo spazio e '\0' */
                
                /* invio al server anche l'operazione che voglio fare */
                sprintf(pun, "%s %s", risposta.richiesta, buff);
                strcpy(buff, pun);
                free(pun);
        }

        /* converto da stringa a struttura */
        ret = cmd_parsing(buff, &richiesta);  

        /* prima ancora di inviare al server faccio già un controllo validità input */
        if ((ret == 2 || ret == 1) && !strcmp(richiesta.cmd, "look")) {         /* COMANDO LOOK */
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        }else if(ret == 2 && !strcmp(richiesta.cmd, "take")){                   /* COMANDO TAKE */
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        } else if((ret == 2 || ret == 3) && !strcmp(richiesta.cmd, "use")){     /* COMANDO USE */   
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        }else if(ret == 1 && !strcmp(richiesta.cmd, "objs")){                   /* COMANDO OBJS */
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        } else if(ret == 1 && !strcmp(richiesta.cmd, "end")){                   /* COMANDO END */
            printf("Hai abbandonato l'escape room musicale.\n");
            /* non è necessario inviare il comando*/
            /* chiudendo il socket, lui riceverà 0 dalla primitiva recv*/
            close(sd);          
            exit(0);
        } else if(ret == 1 && (!strcmp(richiesta.cmd, "yes") ||                 /* GESTIONE RISPOSTA NOTIFICA */
            !strcmp(richiesta.cmd, "no"))){
                send_data(sd, buff);
        } else if(ret == 2 && !strcmp(richiesta.cmd, "aiuto")){                 /* GESTIONE AIUTO ALTRO GIOCATORE */
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        } else if(ret == 2 && (!strcmp(richiesta.cmd, "e_mult") ||              /* RISPOSTA ENIGMA */
            !strcmp(richiesta.cmd, "e_indo"))){
                cmd_to_string(richiesta, buff);
                send_data(sd, buff);    
        } else if(ret == 2 && !strcmp(richiesta.cmd, "lascia")){                /* LASCIO UN OGGETTO PRESO */
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        } else if(ret == 2 && !strcmp(richiesta.cmd, "user") &&                 /* SCELTA GIOCATORE A CUI CHIEDERE AIUTO */
            /* comando valido solo se ho ricevuto lista utenti attivi */
            !strcmp(risposta.richiesta, "list")){                               
            
            cmd_to_string(richiesta, buff);
            send_data(sd, buff);
        } else {                                                                /* COMANDO NON VALIDO */
            /* pulisco quello che mi aveva inviato il server */
            strcpy(risposta.richiesta, "_");

            /* dico che il comando non è valido */
            printf("\nIngresso non valido\n\n> ");
            continue;
        }

        /* ricevo risposta dal server e converto da stringa a struttura */
        ret = receive_data(sd, buff);
        if(!ret){
            printf("Chiusura connessione con il server\n");
            close(sd);
            exit(0);
        }
        resp_parsing(buff, &risposta);

        system("clear");                                        /* pulisco la schermata */


        /* 3 casi di terminazione partita */
        if(!strcmp(risposta.richiesta, "tempo") ||              /* tempo scaduto */
            !strcmp(risposta.richiesta, "max_err") ||           /* superati massimo tentivi indovinello */
            !strcmp(risposta.richiesta, "win")){                /* vittoria (raccolti tutti i token) */
                printf("%s\n", risposta.msg);
                close(sd);
                exit(0);
        }


        /* stampo sempre l'elenco dei comandi per facilitare gioco */
        print_comandi();

        /* stampo le notifiche (se ci sono) */
        if(risposta.notice[0] != '_'){
            printf("\nNOTIFICA: %s\n", risposta.notice);
        }

        /* stampo informazioni arrivate dal server */
        printf("\n%s\n\n%s\n", risposta.info, risposta.msg);

        /*in alcuni casi ci sono informazioni anche in info_next */
        if(!strcmp(risposta.richiesta, "e_mult") ||                                 /* enigma a risposta multipla*/
                !strcmp(risposta.richiesta, "e_indo") ||                            /* enigma ad indovinello */
                !strcmp(risposta.richiesta, "lascia") ||                            /* raggiunto massimo oggeti che si possono prendere */        
                (!strcmp(risposta.richiesta, "use") && risposta.bool_ret) ||        /* ho usato oggetti */
                !strcmp(risposta.richiesta, "errore") ||                            /* errore ad indovinello */
                !strcmp(risposta.richiesta, "aiuto")){                              /* indovinello per aiuto ad un altro giocatore */              
            printf("%s\n", risposta.info_next);
        }

        printf("\n> ");
    }

}
