#include "SAP.h"

#define SERVER "239.255.255.255"
#define BUFLEN 1500  //Max length of buffer
#define PORT 9875   //The port on which to send data


void transmitSAP(struct SDPmessage *message){
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
	messageBuf[4]=message->srcIP[0];
	messageBuf[5]=message->srcIP[1];
	messageBuf[6]=message->srcIP[2];
	messageBuf[7]=message->srcIP[3];
	
	if(message->sessionName == NULL || strlen(message->sessionName) > 200)
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
	message->srcIP[0],message->srcIP[1],message->srcIP[2],message->srcIP[3],
	message->sessionName,
	message->map,
	message->channelStart, message->channelEnd,
	message->map, message->sampleRate,message->channelEnd-message->channelStart + 1,
	message->clockMaster[0],message->clockMaster[1],message->clockMaster[2],message->clockMaster[3],
	message->clockMaster[4],message->clockMaster[5],message->clockMaster[6],message->clockMaster[7],
	message->mediaClk
	);
	
	int messagelen = strlen(&messageBuf[8])+8;
	
	messageBuf[23] = 0; //trick to keep the null character out of the string
	
	printf("%d\r\n",messagelen);
		 
	//send the message
	if (sendto(s, messageBuf, messagelen, 0 , (struct sockaddr *) &si_other, slen)==-1)
	{
	//	die("sendto()");
	}

//    close(s);
}