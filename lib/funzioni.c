#include "funzioni.h"

/* inizializza la struttura con il carattere nullo */
void inizializza_formato(struct Formato_cmd *msg) {
    memset(msg->cmd, '\0', sizeof(msg->cmd));
    memset(msg->campo1, '\0', sizeof(msg->campo1));
    memset(msg->campo2, '\0', sizeof(msg->campo2));
}

/* text-protocols: da struttura a stringa */
void cmd_to_string(struct Formato_cmd richiesta, char buffer[]){
    sprintf(buffer, "%s %s %s", richiesta.cmd, richiesta.campo1, richiesta.campo2);
}

/* text-protocols: da struttura a stringa */
void resp_to_string(struct Formato_resp risposta, char buffer[]){
    sprintf(buffer, "%s %d %s|%s|%s|%s|", risposta.richiesta, risposta.bool_ret, risposta.notice, risposta.info, risposta.msg, risposta.info_next);
}

/* text-protocols: da stringa a struttura */
int cmd_parsing(char buffer[], struct Formato_cmd* richiesta){
    int ret; 
    inizializza_formato(richiesta);
    ret = sscanf(buffer, "%s %s %[^\n]", richiesta->cmd, richiesta->campo1, richiesta->campo2);

    return ret;
}

/* text-protocols: da stringa a struttura */
void resp_parsing(char buffer[], struct Formato_resp* risposta){
    sscanf(buffer, "%s %d %[^|]|%[^|]|%[^|]|%[^|]|", risposta->richiesta, &(risposta->bool_ret), risposta->notice, risposta->info, risposta->msg, risposta->info_next);
}

/* ricezione dati tramite socket di comunicazione */
int receive_data(int fd, char buff[]){
    uint16_t lmsg;                          /* lunghezza messaggio ricevuto */
    int len;                                /* lunghezza in formato host */
    int ret;                                /* usato per gestione ritorno funzioni */

    /* ricezione della lunghezza messaggio */
    ret = recv(fd, (void*)&lmsg, sizeof(uint16_t), 0);

    if(ret == 0)
        return ret;                         /* gestisco questo caso nel chimanate */
    else if(ret == -1){
        perror("Error recv dimensioni msg");
        exit(1);
    }

    /* conversione in formato host */
    len = ntohs(lmsg);

    ret = recv(fd, (void*)buff, len, 0);
    if(ret == -1){
        perror("Error recv");
        exit(1);
    }

    /* utile per rilevare chiusura comunicazione */
    return ret;                         
}

/* invio dati tramite socket di comunicazione */
int send_data(int sd, char buff[]){
    int ret;                                                /* usato per gestione ritorno funzioni */

    int len = strlen(buff) + 1;                             /* dimensione compreso '\0' */
    uint16_t lmsg = htons(len);                             /* converto in network order */


    /* invio al server la dimensione del messaggio */
    ret = send(sd, (void*) &lmsg, sizeof(uint16_t), 0);
    if(ret == -1){
        perror("Errore invio dimensioni messaggio");
        exit(1);
    }


    /* adesso invio il messaggio vero e proprio */
    ret = send(sd, (void*) buff, len, 0);
    if(ret == -1){
        perror("Errore invio");
        exit(1);
    }
    
    return ret;
}