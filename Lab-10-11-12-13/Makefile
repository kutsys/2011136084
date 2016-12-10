
all : ipc1

ipc1 : ipc_producer ipc_consumer

ipc_producer : ipc_producer.c myfifo.h
	gcc -Wall -o ipc_producer ipc_producer.c

ipc_consumer : ipc_consumer.c myfifo.h
	gcc -Wall -o ipc_consumer ipc_consumer.c
