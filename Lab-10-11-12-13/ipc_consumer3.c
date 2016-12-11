#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include "mymsg.h"

// Lab-12
int main(int argc, char* argv[]) {
	const char* studentName = "Lee Do-hyung";
	char myPid[16];	
	sprintf(myPid, "%d", getpid());
	char producerPid[MYMSG_SIZE], studentId[MYMSG_SIZE];
	int msgKey = msgget(MYMSG_KEY, 0666 | IPC_CREAT);
	if(msgKey==-1) {
		perror("msgget failed\n");
		exit(EXIT_FAILURE);
	}
	MyMsg msgBuf; 
	while(1) {
		// receive 1.producerPid 2.studentId
		msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
				PRODUCER_PUSHED, 0);
		strcpy(producerPid, msgBuf.msgBody);
		msgrcv(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long),
				PRODUCER_PUSHED, 0);
		strcpy(studentId, msgBuf.msgBody);
		printf("producer_pid:%s, student_id:%s\n",
				producerPid, studentId);

		// send 1.myPid 2.studentName 
		msgBuf.msgType = CONSUMER_PUSHED;
		strcpy(msgBuf.msgBody, myPid);
		msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);
		msgBuf.msgType = CONSUMER_PUSHED;
		strcpy(msgBuf.msgBody, studentName);
		msgsnd(msgKey, &msgBuf, sizeof(MyMsg)-sizeof(long), 0);
	}
	exit(EXIT_FAILURE);
}
