#include "main.h"
#include "RTP.h"
#include "wave.h"


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
					   } while (0)
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
 uint64_t nextTransmit = 0;
 
static void
print_siginfo(siginfo_t *si)
{
   timer_t *tidp;
   int or;

   tidp = si->si_value.sival_ptr;

   printf("    sival_ptr = %p; ", si->si_value.sival_ptr);
   printf("    *sival_ptr = 0x%lx\n", (long) *tidp);

   or = timer_getoverrun(*tidp);
   if (or == -1)
	   errExit("timer_getoverrun");
   else
	   printf("    overrun count = %d\n", or);
}

struct RTCPstream stream;

uint64_t counter = 0;
struct timeval currenttime;

static void
handler(int sig, siginfo_t *si, void *uc)
{
   /* Note: calling printf() from a signal handler is not
	  strictly correct, since printf() is not async-signal-safe;
	  see signal(7) */
		
	


   //printf("Caught signal %d\n", sig);
   //print_siginfo(si);
  // counter ++;
   //if(counter == 60000)
	//	signal(sig, SIG_IGN);
}
int32_t audioBuffer[14400000];
int main(void)
{
	
	initRTPSocket();
	
	srand(time(NULL));   // should only be called once
	int r = rand();      // returns a pseudo-random integer between 0 and RAND_MAX
	
	uint64_t latency = 1;//in ms how much earlier to send audio
	
	loadWave("/test.wav",audioBuffer);
	
	gettimeofday(&currenttime,NULL);
	
	nextTransmit = ((currenttime.tv_sec*1000000)+currenttime.tv_usec) ;
	
	//mediaClk = time in samples the stream clock is offset from the PTP clock
	
	
	struct SDPmessage msg;
	msg.sessionId = 12345;
	msg.sessionVersion = 12345;
	msg.sessionName = "Testing2";
	msg.channelStart = 1;
	msg.channelEnd = 8;
	msg.srcIP[0] = 192;
	msg.srcIP[1] = 168;
	msg.srcIP[2] = 0;
	msg.srcIP[3] = 34;
	msg.sampleRate = 48000;
	msg.map = 99;
	msg.clockMaster[0]=00;
	msg.clockMaster[1]=0x1d;
	msg.clockMaster[2]=0xc1;
	msg.clockMaster[4]=0xfe;
	msg.clockMaster[3]=0xff;
	msg.clockMaster[5]=0x0b;
	msg.clockMaster[6]=0x2f;
	msg.clockMaster[7]=0x10;
	msg.mediaClk = 0;
	
	transmitSAP(&msg);
	
	stream.sequenceNum = 0;
	
	double timeInSamples = ((double)(currenttime.tv_sec+((double)currenttime.tv_usec)/1000000))*48000;
	
	stream.timestamp = timeInSamples;
	
	
	printf("%d %d %f %d\n",currenttime.tv_sec, currenttime.tv_usec, timeInSamples,stream.timestamp);
	stream.csrc = 1234;
	stream.samplesPerPacket = 48;
	stream.channelsPerPacket = 8;
	
	           timer_t timerid;
           struct sigevent sev;
           struct itimerspec its;
           long long freq_nanosecs;
           sigset_t mask;
           struct sigaction sa;


           /* Establish handler for timer signal */

      //     printf("Establishing handler for signal %d\n", SIG);
        //   sa.sa_flags = SA_SIGINFO;
        //   sa.sa_sigaction = handler;
           //sigemptyset(&sa.sa_mask);
           //if (sigaction(SIG, &sa, NULL) == -1)
           //    errExit("sigaction");

           /* Block timer signal temporarily */

         //  printf("Blocking signal %d\n", SIG);
           //sigemptyset(&mask);
          // sigaddset(&mask, SIG);
          // if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
          //     errExit("sigprocmask");

           /* Create the timer */

        //   sev.sigev_notify = SIGEV_SIGNAL;
        //   sev.sigev_signo = SIG;
        //   sev.sigev_value.sival_ptr = &timerid;
        //   if (timer_create(CLOCKID, &sev, &timerid) == -1)
       //        errExit("timer_create");

       //    printf("timer ID is 0x%lx\n", (long) timerid);

           /* Start the timer */

           freq_nanosecs = 100000;
           its.it_value.tv_sec = freq_nanosecs / 1000000000;
           its.it_value.tv_nsec = freq_nanosecs % 1000000000;
           its.it_interval.tv_sec = its.it_value.tv_sec;
           its.it_interval.tv_nsec = its.it_value.tv_nsec;

           //if (timer_settime(timerid, 0, &its, NULL) == -1)
          //      errExit("timer_settime");

           /* Sleep for a while; meanwhile, the timer may expire
              multiple times */

           /* Unlock the timer signal, so that timer notification
              can be delivered */

       //    printf("Unblocking signal %d\n", SIG);
       //    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
       //        errExit("sigprocmask");
		   
		   while(1)
		   {
			   gettimeofday(&currenttime, NULL);
			   
			   timeInSamples = ((double)(currenttime.tv_sec+((double)currenttime.tv_usec)/1000000))*48000;
			   
				while((timeInSamples+48) > stream.timestamp){
					//transmitTime(timeInSamples);
					transmitRTP(&stream, audioBuffer);
					stream.sequenceNum++;
					stream.timestamp += 48;
//					nextTransmit += 1000000;
				}

		   }

           exit(EXIT_SUCCESS);
    return 0;
}