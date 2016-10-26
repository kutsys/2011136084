#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printnothiddenfile(char* dir, int depth){
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;

	if((dp=opendir(dir))==NULL){
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}

	chdir(dir);
	while((entry=readdir(dp))!=NULL){
		lstat(entry->d_name, &statbuf);
		// not search hidden subdirectory
		//if(entry->d_name[0]=='.')
		//	continue;
		if(S_ISDIR(statbuf.st_mode)){
			// print only hidden file
			if(strcmp(".", entry->d_name)==0 ||
			   strcmp("..", entry->d_name)==0) continue;
			printf("%*s%s\n", depth, "", entry->d_name);
			printnothiddenfile(entry->d_name, depth+4);
		}
		else
			printf("%*s%s\n", depth, "", entry->d_name);
	}
	chdir("..");
	closedir(dp);
}

int main()
{
	char buf[1024];
	int bufsize = sizeof(buf);
	printf("Directory scan of %s:\n", getcwd(buf, bufsize));
	printnothiddenfile(buf, 4);
	printf("done.\n");

	exit(0);
}
