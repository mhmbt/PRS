#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
 #define BUFLEN 51
#define NPACK 10
#define PORTCONTROL 9930
#define SRV_IP "999.999.999.999"

void fonctionErreur(char *s);
void AckTools(int s, char* Compar, char* Envoi,char buf[BUFLEN],struct sockaddr_in si_other,int slen);
void HandshakeServeur(int s,struct sockaddr_in sadd_client, int slen, char buf[BUFLEN]);
int CreationSocket(struct sockaddr_in* si_mp,int port,int s);
//void GestionFichier(char buf [],int s,struct sockaddr_in add );
void EnvoiMessage(char buf [],int s,struct sockaddr_in add );
void EnvoiACK (char buf [],int s,struct sockaddr_in add);
char* manipulationSequence(int numeroSeq,char buf[6+BUFLEN] );
void transmissionFichier(int s,struct sockaddr_in add,char nomfichier[BUFLEN]);
