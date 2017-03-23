#pragma once

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
 


struct RTCPstream{
	uint16_t sequenceNum; //Incremented per packet
	uint32_t timestamp; //Incremented in samples per packet
	uint32_t csrc; //Should be random
	uint16_t samplesPerPacket;
	uint16_t channelsPerPacket;
};

void transmitRTP(struct RTCPstream *stream,uint32_t audioBuffer[]);
void initRTPSocket();