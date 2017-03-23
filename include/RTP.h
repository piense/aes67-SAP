#pragma once

#include "OutputStreamBuffer.h"
#include "SAP.h"
#include<stdio.h> //printf
#include<string.h> //memset
#include<arpa/inet.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t sampleRate = 48000; //Samples per second
uint64_t networkLatency = 144; //In samples, I'm thinking ideally it should be 3x samples per packet(?)
uint8_t myIP[4];
uint8_t clockMaster[8];
uint8_t map = 98;

//TODO
//Support for unicast
//Broadcast to unique IPs
struct RTCPstream{
	uint32_t sequenceNum; //Incremented per packet, starts randomly
	uint32_t timestamp; //Incremented in samples per packet, units are samples. Time is PTP converted to samples + mediaclk offset
	uint64_t offset; //In samples relative to PTP clock
	uint32_t csrc; //Should be random
	uint32_t samplesPerPacket;
	uint8_t channels; //8 or less for compatibility with Dante
	char *name;
	struct OutputStreamBuf *outputBufs; //array of output buffers
	struct SDPmessage *SDP;
};

struct audioStreams{
	struct RTCPstream *current;
	struct audioStreams *next;
} AudioStreams ;

void initializeAudioStreaming();
void newAudioStream(char *name, uint8_t channels, uint64_t sessionID, uint64_t sessionVersion);

void transmitRTP(struct RTCPstream *stream);
void initRTPSocket();