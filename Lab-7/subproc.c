#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void test_funct() {
	static int calledCount = 0;
	time_t currentTime;
	time(&currentTime);
	++calledCount;
	printf("test_funct - pid:%d, called:%d, time:%s",
			getpid(), calledCount, ctime(&currentTime));
}


int main(int argc, char* argv[])
{
	int callto = 10, maxSleep = 10;
	int seed = time(NULL);
	if(argc>=2) callto = atoi(argv[1]);
	if(argc>=3) maxSleep = atoi(argv[2]);
	if(argc>=4) seed = atoi(argv[3]);
	srand(seed);
	for(int i=0; i<callto; ++i) {
		test_funct();
		if(i+1!=callto) {
			int s = (rand()%maxSleep)+1;
			sleep(s);
		}
	}

	return 0;
}
