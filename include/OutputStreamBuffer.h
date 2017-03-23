#pragma once


void putSamples(struct OutputStreamBuf *buf, uint64_t sourceTimestamp, uint64_t bufferTimestamp);
void getSamples(struct OutputStreamBuf *buf);//Fetches, clears, and advances the buffer, zeroes if no data available

struct OutputStreamBuf
{
	uint8_t sampleBitDepth;
	uint16_t outputBufSize;	 //Could be global, but we'll leave it per stream for now
	uint16_t head;
	uint16_t tail;
	uint64_t headTimestamp; //samples since epoch.
	uint8_t *outputBuf;
}