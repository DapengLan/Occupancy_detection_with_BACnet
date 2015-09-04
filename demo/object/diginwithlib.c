#include "libBBB.h"
#include <math.h>
#define GPIO_PIN1	47 //p8_15
#define GPIO_PIN2	46 //p8_16

#include <sys/time.h>		/* for setitimer */
#include <unistd.h>		/* for pause */
#include <signal.h>		/* for signal */

#define INTERVAL 50		/* number of milliseconds to go off */

int flagIn = 0;
int flagOut = 0;
int countPeopleIn = 0;
int countPeopleOut = 0;
int count = 0;
float countP = 0;
float samplingTime = 50;
float timePeriod = 350;
int idleCount = 0;

int value1;
int value2;

void countUpdate();

int countPeopleInFunc ();
int countPeopleOutFunc ();
//every 2s, reset all the value


int main()
{
	initPin(GPIO_PIN1);
	initPin(GPIO_PIN2);
	setPinDirection(GPIO_PIN1, IN);
	setPinDirection(GPIO_PIN2, IN);

  struct itimerval it_val;	/* for setting itimer */

  /* Upon SIGALRM, call DoStuff().
   * Set interval timer.  We want frequency in ms, 
   * but the setitimer call needs seconds and useconds. */
  if (signal(SIGALRM, (void (*)(int)) countPeopleInFunc) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
/*
  if (signal(SIGALRM, (void (*)(int)) countPeopleOutFunc) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
*/
  it_val.it_value.tv_sec =     INTERVAL/1000;
  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;	
  it_val.it_interval = it_val.it_value;
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    perror("error calling setitimer()");
    exit(1);
  }





/*
while(1)
	{
		value1 = getPinValue(GPIO_PIN1);
		value2 = getPinValue(GPIO_PIN2);
		countPeopleInFunc(value1);
		countPeopleOutFunc(value2);
	//	printf("value1: %d\n",value1);
	//	printf("value2: %d\n",value2);
	//printf("value1: %d\n",b);
		pauseNanoSec(50000);

	}
*/


  while (1) 
    pause();
	return 0;
}

void countUpdate() {
	idleCount = 0;
	countP += count * samplingTime / timePeriod ; //ceil?

	double temp = 0;
	temp = countP;
	int tempInt = round(temp);

	printf(" countP: %d\n", tempInt);
	count = 0;
	countPeopleIn = 0;
	countPeopleOut = 0;
	flagIn = 0;
	flagOut = 0;
	}

int countPeopleInFunc () {

	int x = getPinValue(GPIO_PIN1);

	if (x == 0 )
		{
			idleCount = 0;
			if (flagOut == 0)
			{
				flagIn = 1;
				countPeopleIn += 1;
			}
			else {
				countPeopleOut -= 1;
				count -= 1;
				if(countPeopleOut ==0 )
					 flagOut = 0;
			}
		}
	else
	{
		idleCount +=1;
		if(idleCount >= 40 )
		{
			countUpdate();
		}
	}

//printf(" countIn: %d\n", countPeopleIn);
countPeopleOutFunc();
	}

int countPeopleOutFunc () {

	int x = getPinValue(GPIO_PIN2);

	if (x == 0 )
		{
			idleCount = 0;
			if (flagIn == 0)
			{
				flagOut = 1;
				countPeopleOut += 1;
			}
			else {
				countPeopleIn -= 1;
				count += 1;
				if(countPeopleIn ==0 )
					 flagIn = 0;
			}
		}
	else
	{
		idleCount +=1;
		if(idleCount >= 40 )
		{
			countUpdate();
		}
	}
//printf(" countOut: %d\n", countPeopleOut);
	}

