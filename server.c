#include "lib/funzioni.h"
#include "dir_server/utility_server.h"


int main(int argc, char* argv[]){
    int listener;                           /* socket di ascolto */
    int newfd;                              /* socket di comunicazione */

    fd_set master;                          /* set descrittori principale */
    fd_set read_fds;                        /* set descrittori di lettura */
    int fdmax;

    struct sockaddr_in my_addr;             /* indirizzo server */

    int in_porta;                           /* numero porta in ingresso */

    char buff[SIZE_BUFF];                   /* buffer */

    struct Formato_cmd richiesta;           /* struttura messaggio dal client */
    struct Formato_resp risposta;           /* struttura risposta al client */

    int i;                                  /* usato nelle iterazioni */
    int ret;                                /* usato per analizzare il ritorno di funzione */


    /* variabili per analizzare input da stdin */
    char cmd[LEN_CMD];                      /* i comandi al server */
    int arg_in = 0;                         /* il numero di porta */ 


    /* uso l'argomenti di input per inizializzare la porta */
    if(argc == 2)
		in_porta = atoi(argv[1]);
	else 
        in_porta = SERVER_PORT;

    system("clear");
    printf("***************************** SERVER STARTED *********************************\n");
    printf("Digita un comando:\n");
    printf("1) start <port>\t  -->    avvia il server di gioco\n");
    printf("2) stop\t\t  -->    termina il server\n");
    printf("******************************************************************************\n");
    printf("\n> ");

    while(1){
        fgets(buff, SIZE_BUFF, stdin);

        /* analizzo input utente */
        ret = sscanf(buff, "%s %d", cmd, &arg_in);
        if (ret == 2 && !strcmp(cmd, "start")) {
            printf("Avviato server di gioco con successo alla porta %d...\n\n> ", arg_in);
            in_porta = arg_in;
            break;
        } else if(ret == 1 && !strcmp(buff, "start\n") && arg_in == 0){
            printf("Avviato server di gioco con successo...\n\n> ");
            break;
        } else if(ret == 1 && !strcmp(buff, "stop\n")){     
            printf("Server ancora non avviato\n\n> ");
            continue;
        }  

        printf("Comando non valido\n");
        printf("\n> ");
    }
    fflush(stdout);

    /* creazione socket di ascolto */
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener == -1) {
        perror("Errore creazione socket");
        exit(1);
    }

    /* inizializzo struttura my_addr */
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(in_porta);

    /* associo socket al my_addr */
    ret = bind(listener, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if(ret == -1){
        perror("Error bind");
		exit(1);
    }

    /* inzio ad ascoltare richieste con code di dimensione DIM_CODA */
    ret = listen(listener, DIM_CODA);
    if(ret == -1){
        perror("Error listen");
        exit(1);
    }

    /* pulisco set di descrittori */
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    /* aggiungo i primi descittori al master */
    FD_SET(STDIN_FILENO, &master);                               
    FD_SET(listener, &master); 
    fdmax = listener; 

    while(1){
        read_fds = master;                              /* Copia che modificherò */

        /* In attesa di descrittori pronti */
        ret = select(fdmax+1, &read_fds, NULL, NULL, NULL);
        if(ret == -1){                              
            perror("Error select");                 
            exit(1);                                
        }

        for(i=0; i<=fdmax; i++){

            if(FD_ISSET(i, &read_fds)){

                /*-------------------------*/
                /*---- INPUT AL SERVER ----*/
                /*-------------------------*/
                if(i == STDIN_FILENO){
                    fgets(buff, SIZE_BUFF, stdin);
                    
                    if(!strcmp(buff, "stop\n")){
                        /* controllare che non ci siano utenti attivi */
                        if(utenti_attivi() != 0){
                            printf("Errore chiusura server, ci sono giocatori attivi!\n\n> ");
                            fflush(stdout);
                            continue;
                        }
                        close(listener);
                        printf("Server spento!\n");
                        exit(0);
                    }else{
                        printf("Comando non valido\n\n> ");
                    }
                    fflush(stdout);
                }
                /*-------------------------------------*/
                /*---- NUOVA RICHIESTA CONNESSIONE ----*/
                /*-------------------------------------*/
                else if(i == listener){                         
                    newfd = accept_connessione(listener);
                    
                    /* aggiungo il descrittore ai socket monitorati */
                    FD_SET(newfd, &master);

                    /* aggiorno contatore massimo descrittori */
                    if(newfd > fdmax){
                        fdmax = newfd; 
                    }

                }
                /*-------------------------------------*/
                /*---- COMUNICAZIONE CON IL CLIENT ----*/
                /*-------------------------------------*/       
                else{     
                    ret = receive_data(i, buff);
                    if(!ret){                                   /* rilevata chiusa client */
                        comando_end(i);
                        printf("Client %d chiuso.\n\n> ", i);
                        fflush(stdout);
                        close(i);
                        FD_CLR(i, &master);
                        continue;
                    }


                    cmd_parsing(buff, &richiesta);

                    /* STAMPO IN MANIERA VERBOSA COSA RICEVO DAL CLIENT */
                    printf("RICHIESTA DA %d\tComando: %s\n\n> ", i, richiesta.cmd);
                    fflush(stdout);

                    /* GESTIONE RICHIESTA DEL CLIENTS */
                    gestione_richiesta(i, richiesta, &risposta);

                    resp_to_string(risposta, buff);

                    /* STAMPO IN MANIERA VERBOSA COSA INVIO AL CLIENT */
                    printf("RISPOSTA A %d\tComando: %s\tEsito: %d\n\n> ", i, risposta.richiesta, risposta.bool_ret);
                    fflush(stdout);

                    send_data(i, buff);
                }
            }
        }
    }

}