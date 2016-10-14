#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{
	char block[1024];
	int in, out;
	int nread;
	char* copysrc=NULL;
	char* copydst=NULL;
	clock_t begin_clock = clock();
	int printDotTerm = CLOCKS_PER_SEC / 1000;

	if(argc<=1 || argv[1]==NULL)
		copysrc = "copysrc";
	else
		copysrc = argv[1];
	if(argc<=2 || argv[2]==NULL)
		copydst = "copied";
	else
		copydst = argv[2];

	in = open(copysrc, O_RDONLY);
	out = open(copydst, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	if(in==-1 || out==-1){
		printf(" !! file open error !!\n");
		exit(-1);
	}

	while((nread=read(in,block,sizeof(block))) > 0){
		write(out, block, nread);
		if(clock()-begin_clock >= printDotTerm){
			putc('.', stdout);
			fflush(stdout);
			begin_clock = clock();
		}
	}
	printf("\n");

	close(in); 
	close(out);
	exit(0);
}
