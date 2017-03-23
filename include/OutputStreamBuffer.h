#pragma once

#include <stdlib.h>
#include <stdint.h>

struct OutputStreamBuf
{
	uint16_t outputBufSize;	 //Could be global, but we'll leave it per stream for now
	uint16_t head;
	uint16_t tail;
	uint64_t headTimestamp; //samples since epoch.
	double *outputBuf;
};

void putSamples(struct OutputStreamBuf *buf, uint64_t sourceTimestamp, uint64_t bufferTimestamp);
double getSampleFromBuffer(struct OutputStreamBuf *buf, uint64_t time);
void advanceBuffer(struct OutputStreamBuf *buf, uint64_t samples);
