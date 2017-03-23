#include "main.h"
#include "RTP.h"
#include "wave.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int32_t audioBuffer[14400000];

int main(void)
{
	uint64_t timeInSamples;
	
	void initializeAudioStreaming();

//	srand(time(NULL));   // should only be called once
//	int r = rand();      // returns a pseudo-random integer between 0 and RAND_MAX
	
	loadWave("/test.wav",audioBuffer);

	myIP[0] = 192;
	myIP[1] = 168;
	myIP[2] = 0;
	myIP[3] = 34;
	sampleRate = 48000;
	clockMaster[0]=00;
	clockMaster[1]=0x1d;
	clockMaster[2]=0xc1;
	clockMaster[4]=0xfe;
	clockMaster[3]=0xff;
	clockMaster[5]=0x0b;
	clockMaster[6]=0x2f;
	clockMaster[7]=0x10;
	
	struct timeval currenttime;

	newAudioStream("Testing2",8,12345,12345);

	
	
	struct audioStreams *currentStream;
	
	currentStream = &AudioStreams;
	
	while(currentStream != NULL){			
		transmitSAP(currentStream->current); //Need to do periodically
		currentStream = currentStream->next;
	}

	while(1)
	{
		gettimeofday(&currenttime, NULL);
		timeInSamples = ((double)(currenttime.tv_sec+((double)currenttime.tv_usec)/1000000))*sampleRate;

		currentStream = &AudioStreams;
		
		while(currentStream != NULL){			
			while((timeInSamples+48) > currentStream->current->timestamp){
				transmitRTP( currentStream->current);
			}	
			currentStream = currentStream->next;
		}
	}

    return 0;
}