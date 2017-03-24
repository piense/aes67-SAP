#include "OutputStreamBuffer.h"

#include <stdio.h>

double getSampleFromBuffer(struct OutputStreamBuf *buf, uint64_t time){
	
	//Too late, buffer has moved on
	if(time < buf->headTimestamp){
		printf("Buffer error 1.\n");
		return 0;
	}
	
	if(buf->outputBufSize < (time-buf->headTimestamp)){
		printf("Buffer error 2.\n");
		return 0;
	}
	return buf->outputBuf[(time - buf->headTimestamp + buf->head)%(buf->outputBufSize)];
}

void advanceBuffer(struct OutputStreamBuf *buf, uint64_t samples){
	//TODO make this thread safe
	buf->headTimestamp += samples;
	buf->head = (buf->head+samples) % buf->outputBufSize;
}

void clearSamplesInBuffer(struct OutputStreamBuf *buf, uint64_t startTime, uint64_t sampleCount){
	//TODO
}
