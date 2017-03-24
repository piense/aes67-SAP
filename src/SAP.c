#include "SAP.h"
#include "RTP.h"

#define SERVER "239.255.255.255"
#define BUFLEN 1500  //Max length of buffer
#define PORT 9875   //The port on which to send data


void transmitSAP(struct RTCPstream *message){
	struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char messageBuf[BUFLEN];
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
       // die("socket");
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
	messageBuf[0]=32;
	messageBuf[1]=00;
	messageBuf[2]=23;
	messageBuf[3]=23;
	messageBuf[4]=myIP[0];
	messageBuf[5]=myIP[1];
	messageBuf[6]=myIP[2];
	messageBuf[7]=myIP[3];
	
	if(message->name == NULL || strlen(message->name) > 200)
		return;
	
	sprintf(&messageBuf[8],"application/sdpAv=0\r\n"
	"o=- %"PRId64" %"PRId64" IN IP4 %d.%d.%d.%d\r\n"
	"s=%s\r\n"
	"c=IN IP4 239.69.128.164/32\r\n"
	"t=0 0\r\n"
	"m=audio 5004 RTP/AVP %d\r\n"
	"i=Channels %d-%d\r\n"
	"a=rtpmap:%d L24/%d/%d\r\n"
	"a=recvonly\r\n"
	"a=ptime:1\r\n"
	"a=ts-refclk:ptp=IEEE1588-2008:%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X:domain-nmbr=0\r\n"
	"a=mediaclk:direct=%"PRId64"\r\n",
	message->sessionId, message->sessionVersion,
	myIP[0],myIP[1],myIP[2],myIP[3],
	message->name,
	message->map,
	message->channelStart, message->channelEnd,
	message->map, sampleRate,message->channelEnd-message->channelStart + 1,
	clockMaster[0],clockMaster[1],clockMaster[2],clockMaster[3],
	clockMaster[4],clockMaster[5],clockMaster[6],clockMaster[7],
	message->offset
	);
	
	int messagelen = strlen(&messageBuf[8])+8;
	
	messageBuf[23] = 0; //trick to keep the null character out of the string
	printf("Sending SAP message for %s\n",message->name);
		 
	//send the message
	if (sendto(s, messageBuf, messagelen, 0 , (struct sockaddr *) &si_other, slen)==-1)
	{
	//	die("sendto()");
	}

//    close(s);
}