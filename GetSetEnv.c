#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	const char* getList[] = {
		"HOME", "PS1", "PATH", "LD_LIBRARY_PATH"
	};
	const int getListSize = sizeof(getList) / sizeof(char*);
	int i;
	for(i=0; i<getListSize; ++i)
		printf("$%s : %s\n", getList[i], getenv(getList[i]));

	char* setStr = "TEST_ENV";
	printf("$%s : %s\n", setStr, getenv(setStr));
	printf("call setenv .. $%s set to 1234.\n", setStr);
	setenv(setStr, "1234", 1);
	printf("$%s : %s\n", setStr, getenv(setStr));

	exit(0);
}
