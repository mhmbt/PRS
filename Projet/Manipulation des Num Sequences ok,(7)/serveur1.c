#include "UDP.h"

    int main(void)
  {
    struct sockaddr_in si_me, sadd_client,si_data;
     int s_ctrl,s_data, slen=sizeof(sadd_client);
     char buf[BUFLEN];
     char nomfichier[BUFLEN];
     char* numSeq;
     numSeq=(char*)malloc(BUFLEN+6);
     int numeroSeq=175;

     s_ctrl=CreationSocket(&si_me,PORTCONTROL,s_ctrl);
     s_data=CreationSocket(&si_data,6660,s_data);


     HandshakeServeur(s_ctrl, sadd_client,slen,buf);
      if (recvfrom(s_data, nomfichier, BUFLEN, 0, &sadd_client, &slen)==-1){
        fonctionErreur("recvfrom()");
      }
      printf("Nom du fichier demandé: %s\n",nomfichier);
      //rajouter un test que c'est bien un nom de fichier

/***********DANS LE DATA POUR LES FICHIER***************************************/

      //Envoi du premier message
      numSeq=manipulationSequence(numeroSeq,numSeq);
      numeroSeq++;
      strcpy(buf,"Premier message yeah\n");
      strcat(numSeq,buf);
      EnvoiMessage(numSeq,s_data,sadd_client);

    /*  if (recvfrom(s_data, nomfichier, BUFLEN, 0, &sadd_client, &slen)==-1){
        fonctionErreur("recvfrom()");
      }
      printf("%s\n",nomfichier);*/

/*****************CLOSE*********************************************/
      strcpy(numSeq,"FIN");
      EnvoiMessage(numSeq,s_data,sadd_client);
        close(s_data);
        close(s_ctrl);
      free(numSeq);
      return 0;
     }
