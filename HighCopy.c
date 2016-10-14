#include <stdio.h>
#include <time.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	char buf[BUF_SIZE];
	char* copysrc=NULL;
	char* copydst=NULL;
	FILE* srcfp = NULL;
	FILE* dstfp = NULL;
	int count = 0;
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

	if((srcfp=fopen(copysrc, "r"))==NULL ||
		(dstfp=fopen(copydst, "w"))==NULL){
		printf(" !! file open error !!\n");
		return -1;
	}

	while((count=fread(buf, 1, BUF_SIZE, srcfp))>0){
		fwrite(buf, 1, count, dstfp);
		if(clock()-begin_clock >= printDotTerm){
			putc('*', stdout);
			fflush(stdout);
			begin_clock = clock();
		}
	}

	fclose(srcfp);
	fclose(dstfp);

	return 0;
}
