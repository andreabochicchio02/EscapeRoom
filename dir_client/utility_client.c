#include "utility_client.h"

/* gestione username e pass per signup */
void signup(struct Formato_cmd* signup){
    inizializza_formato(signup);

    strcpy(signup->cmd, "signup");

    printf("Username: ");
    fgets(signup->campo1, LEN_CAMPI, stdin);
    /*se non c'è il carattere '\n' nella stringa allora utente ha inserito più di 32 caratteri */
    if (strchr(signup->campo1, '\n') == NULL)
        pulisci_buf();
    else
        signup->campo1[strcspn(signup->campo1, "\n")] = '\0';           /* tolgo carattere inutile */


    printf("Password: ");
    fgets(signup->campo2, LEN_CAMPI, stdin);
    /*se non c'è il carattere '\n' nella stringa allora utente ha inserito più di 32 caratteri */
    if (strchr(signup->campo2, '\n') == NULL)
        pulisci_buf();
    else
        signup->campo2[strcspn(signup->campo2, "\n")] = '\0';           /* tolgo carattere inutile */
}


/* gestione username e pass per login */
void login(struct Formato_cmd* login){
    inizializza_formato(login);

    strcpy(login->cmd, "login");

    printf("Username: ");
    fgets(login->campo1, LEN_CAMPI, stdin);
    /*se non c'è il carattere '\n' nella stringa allora utente ha inserito più di 32 caratteri */
    if (strchr(login->campo1, '\n') == NULL)
        pulisci_buf();
    else
        login->campo1[strcspn(login->campo1, "\n")] = '\0';           /* tolgo carattere inutile */


    printf("Password: ");
    fgets(login->campo2, LEN_CAMPI, stdin);
    /*se non c'è il carattere '\n' nella stringa allora utente ha inserito più di 32 caratteri */
    if (strchr(login->campo2, '\n') == NULL)
        pulisci_buf();
    else
        login->campo2[strcspn(login->campo2, "\n")] = '\0';           /* tolgo carattere inutile */
}


/* stampa a video l'elenco dei comandi con una breve guida */
void print_comandi(){
    printf("***************************** ESCAPE ROOM MUSICALE *****************************\n");
    printf("**                                                                            **\n");
    printf("**  Digita un comando:                                                        **\n");
    printf("**  1) start room              -->  avvia lo scenario con codice room         **\n");
    printf("**  2) look [location|object]  -->  descrive room, location o object          **\n");
    printf("**  3) take object             -->  raccoglie un oggetto                      **\n");
    printf("**  4) use object1 [object2]   -->  usa uno/due oggetti                       **\n");
    printf("**  5) objs                    -->  elenco oggetti raccolti fin'ora           **\n");
    printf("**  6) end                     -->  termina gioco e connessione al server     **\n");
    printf("**                                                                            **\n");
    printf("********************************************************************************\n");
}  

/* pulisce lo standard input fino al carattere '\n' */
void pulisci_buf(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}