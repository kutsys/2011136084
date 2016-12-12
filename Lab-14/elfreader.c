#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define OPT_ELF_HEADER (1<<0)
#define OPT_PRO_HEADER (1<<1)
#define OPT_SEC_HEADER (1<<2)

int main(int argc, char* argv[]) {
	int opt = 0;
	char* exec = NULL;
	for(int i=1; i<argc; ++i) {
		if(argv[i][0]=='-') {
			int j=1;
			while(argv[i][j]!='\0') {
				switch(argv[i][j]) {
					case 'e':
						opt |= OPT_ELF_HEADER;
						break;
					case 'p':
						opt |= OPT_PRO_HEADER;
						break;
					case 's':
						opt |= OPT_SEC_HEADER;
						break;
					default:
						printf("warning. unknown option: %c\n", argv[i][j]);
				}
				++j;
			}
		}
		else
			exec = argv[i];
	}
	if(exec==NULL) {
		printf("error! input elf file name.\n");
		exit(EXIT_FAILURE);
	}
	char cmd[256] = "readelf -";
	if(opt==0 || (opt & OPT_ELF_HEADER))
		strcat(cmd, "h");
	if(opt & OPT_PRO_HEADER)
		strcat(cmd, "l");
	if(opt & OPT_SEC_HEADER)
		strcat(cmd, "S");
	strcat(cmd, " ");
	strcat(cmd, exec);
	system(cmd);
	exit(EXIT_SUCCESS);
}
