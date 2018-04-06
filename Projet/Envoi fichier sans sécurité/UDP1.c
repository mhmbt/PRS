#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "UDP.h"
#define BUFLEN 12
#define NPACK 10
#define PORTCONTROL 9930

#define SRV_IP "999.999.999.999"

void fonctionErreur(char *s){
  perror(s);
   exit(-1);
  }

void AckTools(int s, char* Compar, char* Envoi,char buf[BUFLEN],struct sockaddr_in si_other,int slen){
    if(strstr(buf, Compar)!=NULL){
      printf("Compar=%s et BUF=%s\n",Compar,buf);
      printf("Envoi=%s et BUF=%s\n",Envoi,buf);
      if (sendto(s,Envoi ,11, 0, &si_other, slen)==-1){
       fonctionErreur("sendto()");}
     }else //if(strcmp(buf, Compar)!=0)
     { printf("Compar=%s et BUF=%s\n",Compar,buf);
     fonctionErreur("Pas comparé" );}

}


void HandshakeServeur(int s,struct sockaddr_in sadd_client, int slen, char buf[BUFLEN]){
  if (recvfrom(s, buf, BUFLEN, 0, &sadd_client, &slen)!=-1){
    int port= 6660;
    char porc[4];
    char envoi[7];
    sprintf(porc,"%d",port);
    printf("sprintf:%s\n", porc);
    strcpy(envoi,"SYN-ACK");
    strcat(envoi,porc);
    printf("strcat:%s\n", envoi);
    AckTools(s,"SYN",envoi,buf,sadd_client,slen);}

  else if(recvfrom(s, buf, BUFLEN, 0, &sadd_client, &slen)==-1){
    fonctionErreur("recvfrom");}

  if (recvfrom(s, buf, BUFLEN, 0, &sadd_client, &slen)!=-1){
    printf("%s\n",buf );
    if(strstr(buf, "ACK")!=NULL){
      printf("ACK et BUF=%s\n",buf);
      printf("Connexion initialisé\n" );
    }else {
      printf("Compar=%s et BUF=%s\n","ACK",buf);
      fonctionErreur("Problème de comparaison" );}}
  else if(recvfrom(s, buf, BUFLEN, 0, &sadd_client, &slen)==-1){
      fonctionErreur("recvfrom");}
}

int CreationSocket(struct sockaddr_in* si_mp,int port,int s){
  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
        fonctionErreur("socket");}

  memset((char *) si_mp, 0, sizeof(*si_mp));
   (*si_mp).sin_family = AF_INET;
   (*si_mp).sin_port = htons(port);
   (*si_mp).sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(s, si_mp, sizeof(*si_mp))==-1){
         fonctionErreur("bind");
       }
      return s;
}

/*void GestionFichier(char buf [],int s,struct sockaddr_in add ){
  FILE* fichier = fopen ("PLO.pdf","rb");
  printf("J'ai ouvert le fichier\n");
  if (fichier!=NULL) {
    int i,conteur=0;
    int slen=sizeof(add);


  */
  /*  while (fread(buf, 1,512, fichier) != 0) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
    {

      buf[512]=conteur;
      buf[513]=0;//Le fichier n'est pas fini

      printf(" %s\n",buf );
      EnvoiMessage(buf,s,add);
      printf("J'ai envoyé à %d\n",add.sin_port );

      conteur++;
      if(conteur%5==0){
          if (recvfrom(s, buf, BUFLEN, 0, &add, &slen)==-1){
            fonctionErreur("ERREUR du SERVEUR");
          }
          printf("RECU %d\n",buf[0] );
          if(buf[1]==1){
            printf("IL Y A UN PROBLEM\n" );
              conteur=buf[0];
              fseek(fichier,(conteur+1)*512,SEEK_SET);
          }else{
            printf("TOUT VA BIEN\n");
          }
      }
      for (i = 0; i < 512; i++) {
        buf[i]=NULL;
      }
    }

    printf("J'envoi LA FIN %s \n",buf );
    buf[512]=conteur;
    buf[513]=1;//FERMETURE DE CONNECTION
    EnvoiMessage(buf,s,add);



      //******************************************************************
    //buf[0]=numSeq;
    //numSeq++;

    fclose(fichier);
  }

}*/

void EnvoiMessage(char buf [],int s,struct sockaddr_in add ){
  if (sendto(s, buf,(size_t)(BUFLEN+6), 0, &add, sizeof(add))==-1){
      fonctionErreur("fonctionEnvoiMessage");}
}

void EnvoiACK (char buf [],int s,struct sockaddr_in add){
  if (sendto(s, buf,1, 0, &add, sizeof(add))==-1){
      fonctionErreur("fonctionEnvoiMessage");}
}

char* manipulationSequence(int numeroSeq,char buf[6+BUFLEN] ){
  char num[6];
  sprintf(num,"%d",numeroSeq);

  if (numeroSeq<=9){
    strcpy(buf,"00000");
  }
  else if(numeroSeq>=10 && numeroSeq<=99){
    strcpy(buf,"0000");
  }
  else if (numeroSeq>=100 && numeroSeq<=999){
    strcpy(buf,"000");
  }
  else if (numeroSeq>=1000 && numeroSeq<=9999){
    strcpy(buf,"00");
  }
  else if (numeroSeq>=10000 && numeroSeq<=99999) {
    strcpy(buf,"0");
  }
  strcat(buf,num);
  printf("Numéro Séquence :%s\n",buf);
  return buf;
}

void transmissionFichier(int s,struct sockaddr_in add,char nomfichier[BUFLEN]){
  FILE* fichier = fopen (nomfichier,"rb");
  char buf[BUFLEN];
  int slen=sizeof(add);
  int numeroSeq=1,i;
  char* numSeq;
  numSeq=(char*)malloc(BUFLEN+6);
  if (fichier==NULL) {
    fonctionErreur("Le fichier n'existe pas");}
  else{
    while (fread(buf, 1,BUFLEN, fichier) != 0) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
      {
        numSeq=manipulationSequence(numeroSeq,numSeq);
        numeroSeq++;
        strcat(numSeq,buf);
        printf("%s\n", numSeq);
        EnvoiMessage(numSeq,s,add);
        if (recvfrom(s, buf, 9, 0, &add, &slen)==-1){
          fonctionErreur("recvfrom()");
        }
        for (i = 0; i < BUFLEN; i++) {
          buf[i]=NULL;
        }
      }

  }
  free(numSeq);
  fclose(fichier);
}
