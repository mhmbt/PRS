#include "UDP.h"

    int main(void)
  {
    struct sockaddr_in si_me, sadd_client,si_data;
     int s_ctrl,s_data, slen=sizeof(sadd_client);
     char buf[BUFLEN];


     s_ctrl=CreationSocket(&si_me,PORTCONTROL,s_ctrl);
     s_data=CreationSocket(&si_data,6660,s_data);


     HandshakeServeur(s_ctrl, sadd_client,slen,buf);
     printf("s_ctrl %d\n",s_ctrl );
      if (recvfrom(s_data, buf, BUFLEN, 0, &sadd_client, &slen)==-1){
        fonctionErreur("recvfrom()");}
        printf("Received packet from %s:%d\nData: %s\n\n",
        inet_ntoa(sadd_client.sin_addr), ntohs(sadd_client.sin_port), buf);
        //  GestionFichier(buf,s_data,sadd_client);


        close(s_data);
        close(s_ctrl);
      return 0;
     }
