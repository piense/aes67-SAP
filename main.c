#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define SERVER "239.255.255.255"
#define BUFLEN 1000  //Max length of buffer
#define PORT 9875   //The port on which to send data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\r\n");
        exit(1);
    }
 
	//Sap header
	message[0]=32;
	message[1]=00;
	message[2]=23;
	message[3]=23;
	message[4]=192;
	message[5]=168;
	message[6]=0;
	message[7]=34;
	
	sprintf(&message[8],"application/sdpAv=0\r\no=- 1311738121 1311738121 IN IP4 192.168.0.34\r\ns=Stage right I/O\r\nc=IN IP4 239.0.0.1/32\r\nt=0 0\r\nm=audio 5004 RTP/AVP 96\r\ni=Channels 1-8\r\na=rtpmap:96 L24/48000/8\r\na=recvonly\r\na=ptime:1\r\na=ts-refclk:ptp=IEEE1588-2008:00-1D-C1-FF-FE-0B-2F-10:domain-nmbr=0\r\na=mediaclk:direct=893293533\r\n");
	int messagelen = strlen(&message[8])+8;
	
	message[23] = 0; //trick to keep the null character out of the string
	
	printf("%d\r\n",messagelen);
		 
	//send the message
	if (sendto(s, message, messagelen, 0 , (struct sockaddr *) &si_other, slen)==-1)
	{
		die("sendto()");
	}
         

 
    close(s);
    return 0;
}