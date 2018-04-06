#include "UDP.h"

    int main(void)
  {
    struct sockaddr_in si_me, sadd_client,si_data;
     int s_ctrl,s_data, slen=sizeof(sadd_client);
     char buf[BUFLEN];
     char nomfichier[BUFLEN];

     s_ctrl=CreationSocket(&si_me,PORTCONTROL,s_ctrl);
     s_data=CreationSocket(&si_data,6660,s_data);


     HandshakeServeur(s_ctrl, sadd_client,slen,buf);
      if (recvfrom(s_data, nomfichier, BUFLEN, 0, &sadd_client, &slen)==-1){
        fonctionErreur("recvfrom()");
      }
      printf("Nom du fichier demandé: %s\n",nomfichier);
      //rajouter un test que c'est bien un nom de fichier


        close(s_data);
        close(s_ctrl);
      return 0;
     }
