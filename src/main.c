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
	void initializeAudioStreaming();

//	srand(time(NULL));   // should only be called once
//	int r = rand();      // returns a pseudo-random integer between 0 and RAND_MAX
	
	loadWave("/test.wav",audioBuffer);
	
	
//	struct SDPmessage msg;
	//msg.sessionId = 12345;
	//msg.sessionVersion = 12345;
	//msg.sessionName = "Testing2";
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

	
	//Add some network streams here
	
	
	
	double timeInSamples = ((double)(currenttime.tv_sec+((double)currenttime.tv_usec)/1000000))*48000;

	newAudioStream()

	transmitSAP(&msg); //Need to do periodically

   while(1)
   {
	   gettimeofday(&currenttime, NULL);
	   
	   timeInSamples = ((double)(currenttime.tv_sec+((double)currenttime.tv_usec)/1000000))*48000;
	   
		while((timeInSamples+48) > stream.timestamp){
			transmitRTP(&stream, audioBuffer);
			stream.sequenceNum++;
			stream.timestamp += 48;
		}

   }

    return 0;
}