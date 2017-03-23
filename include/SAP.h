#pragma once

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
 


enum audioFormat_t {L24};

struct SDPmessage {
	uint64_t sessionId;
	uint64_t sessionVersion;
	char *sessionName;
	uint16_t channelStart;
	uint16_t channelEnd;
	uint8_t srcIP[4];
	uint16_t sampleRate;
	uint8_t map;
	//audioFormat_t audioFormat; TODO: only 24-bit supported right now
	uint8_t clockMaster[8];
	uint64_t mediaClk;
} ;

void transmitSAP(struct SDPmessage *message);
