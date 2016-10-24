#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define INPUT_TERMINAL 10

void printPmonPrompt();
pid_t getPtestId();
int killPtest();
int runPtest();
void printPtestIsRunning(int sig);
void printHelp();

int main(void)
{
	char sel = -1;
	(void) signal(SIGALRM, printPtestIsRunning);
	alarm(5);
	while(1){
		if(sel!=INPUT_TERMINAL)
			printPmonPrompt();
		sel = getchar();
		fflush(stdin);
		switch(sel){
			case 'q': case 'Q':
				printf("exit pmon...\n");
				exit(0);
			case 'k': case 'K':
				killPtest();
				break;
			case 's': case 'S':
				runPtest();
				break;
			case 'r': case 'R':
				killPtest();
				runPtest();
				break;
			case 'h': case 'H':
				printHelp();
				break;
			case INPUT_TERMINAL:
				break;
			default:
				printf("wrong command. input 'h' for help.\n");
				break;
		}
	}
}

void printPmonPrompt()
{
	printf(">> ");
}
pid_t getPtestId()
{
	/* return ptest process id */
	/* return -1 if not running */
	FILE* fp;
	pid_t ret;
	system("pidof ptest > /tmp/pidof");
	fp = fopen("/tmp/pidof", "r");
	if(fscanf(fp, "%d", &ret)==EOF)
		ret = -1;
	fclose(fp);
	return ret;
}
int killPtest()
{
	/* kill ptest */
	/* return whether killing ptest success or fail */
	/* 0==fail, 1==success */
	pid_t ptestId = getPtestId();
	if(ptestId==-1){
		printf("ptest is not running\n");
		return 0;
	}
	else {
		if(kill(ptestId, SIGTERM)==-1)
			kill(ptestId, SIGKILL);
		return 1;
	}
}
int runPtest()
{
	/* run ptest */
	/* return whether running ptest success or fail */
	/* 0==fail, 1==success */
	pid_t ptestId = getPtestId();
	if(ptestId!=-1){
		printf("pid:%d\n", ptestId);
		printf("ptest is already running\n");
		return 0;
	}
	char* ptestPath = "./ptest &";
	system(ptestPath);
	return 1;
}
void printPtestIsRunning(int sig)
{
	pid_t ptestId = getPtestId();
	if(ptestId!=-1)
		printf("pmon::ptest is running\n");
	else
		printf("pmon::ptest is not running\n");
	alarm(5);
}
void printHelp()
{
	puts("Q (quit) : quit pmon program");
	puts("K (kill) : terminate ptest program");
	puts("S (start) : start ptest program");
	puts("R (restart) : restart ptest program");
}
