#pragma once

#include <stdlib.h>
#include <stdint.h>

//TODO: no need for 64 bit buffer variables
struct OutputStreamBuf
{
	uint64_t outputBufSize;	 //Could be global, but we'll leave it per stream for now
	uint64_t head;
	uint64_t tail;
	uint64_t headTimestamp; //samples since epoch.
	double *outputBuf;
};

void putSamples(struct OutputStreamBuf *buf, uint64_t sourceTimestamp, uint64_t bufferTimestamp);
double getSampleFromBuffer(struct OutputStreamBuf *buf, uint64_t time);
void advanceBuffer(struct OutputStreamBuf *buf, uint64_t samples);
