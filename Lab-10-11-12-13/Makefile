
all : ipc1 ipc2

ipc2 : ipc_producer2 ipc_consumer2

ipc_producer2 : ipc_producer2.c myshm.h
	gcc -Wall -o ipc_producer2 ipc_producer2.c

ipc_consumer2 : ipc_consumer2.c myshm.h
	gcc -Wall -o ipc_consumer2 ipc_consumer2.c

ipc1 : ipc_producer ipc_consumer

ipc_producer : ipc_producer.c myfifo.h
	gcc -Wall -o ipc_producer ipc_producer.c

ipc_consumer : ipc_consumer.c myfifo.h
	gcc -Wall -o ipc_consumer ipc_consumer.c
