#include <math.h>
#include "RTP.h"

#include <unistd.h>

#define SERVER "239.69.128.164"
//#define SERVER "239.255.255.255"
#define BUFLEN 1500  //Max length of buffer
#define PORT 5004   //The port on which to send data

struct sockaddr_in si_other;
int s, i, x, slen=sizeof(si_other);
char buf[BUFLEN];
char messageBuf[BUFLEN];

void initRTPSocket()
{
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
}

void transmitTime(double time){
	char messageBuf2[BUFLEN];
	sprintf(messageBuf2,"%f",time);
	
	if (sendto(s, messageBuf2, strlen(messageBuf2), 0, (struct sockaddr *) &si_other, slen)==-1)
	{

	}
	
}

uint64_t music = 0;

void transmitRTP(struct RTCPstream *stream,uint32_t audioBuffer[])
{

 
	//RTP header
	messageBuf[0]=128; //Version, padding, CC & M
	messageBuf[1]=99; //Stream type (from RTP map)?
	messageBuf[3]=stream->sequenceNum & 0x00FF;
	messageBuf[2]=(stream->sequenceNum & 0xFF00)>>8;
	
	messageBuf[7]=(stream->timestamp & 0x000000FF)>>0;
	messageBuf[6]=(stream->timestamp & 0x0000FF00)>>8;
	messageBuf[5]=(stream->timestamp & 0x00FF0000)>>16;
	messageBuf[4]=(stream->timestamp & 0xFF000000)>>24;
	
	messageBuf[8]=(stream->csrc & 0x000000FF)>>0;
	messageBuf[9]=(stream->csrc & 0x0000FF00)>>8;
	messageBuf[10]=(stream->csrc & 0x00FF0000)>>16;
	messageBuf[11]=(stream->csrc & 0xFF000000)>>24;

	double factor = 48000.0/(3.14159*500);
	
	int32_t sample;
	
	for(i = 0;i<stream->samplesPerPacket;i++)
	{
		for(x = 0;x<stream->channelsPerPacket;x++){
			if(x == 2){
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+2] = 0;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+1] = 0;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3] = 0;					
			}else if(x ==1){
				sample = audioBuffer[music++]*16;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+2] = (sample&0x0000FF)>>0;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+1] = (sample&0x00FF00)>>8;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+0] = (sample&0xFF0000)>>16;
				if(music == 10984320)
					music = 0;
			}else {
				sample = sin(((double)(stream->timestamp+i))/factor)*8388607.0*.05;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+2] = sample&0x0000FF;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3+1] = (sample&0x00FF00)>>8;
				messageBuf[12+i*stream->channelsPerPacket*3+x*3] = (sample&0xFF0000)>>16;
			}
		}
	}
	
	int messagelen = 12+stream->channelsPerPacket*stream->samplesPerPacket*3;

	//send the message
	if (sendto(s, messageBuf, messagelen, 0, (struct sockaddr *) &si_other, slen)==-1)
	{
		printf("error sending %d\n", messagelen);
	}

}