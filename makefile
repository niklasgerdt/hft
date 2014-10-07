MAIN=./src/main/c/
TEST=src/test/c/
UNITY_ROOT=$(TEST)/unity/src
INC_DIRS=-Isrc -I$(UNITY_ROOT)
SYMBOLS=-DTEST
CLEANUP = rm -f bin/*

all: clean zmq

clean:
	$(CLEANUP)

zmq: zmqpub zmqsub zmqpubsub

zmqpub:
	gcc -D_GNU_SOURCE $(MAIN)pub.c $(MAIN)mom/zeromqpubsub.c $(MAIN)mod/event.c $(MAIN)mod/util.c -o bin/zmqpub -lzmq -std=c99

zmqsub:
	gcc -D_GNU_SOURCE $(MAIN)sub.c $(MAIN)mom/zeromqpubsub.c $(MAIN)mod/event.c $(MAIN)mod/util.c -o bin/zmqsub -lzmq -std=c99

zmqpubsub:
	gcc -D_GNU_SOURCE $(MAIN)pubsub.c $(MAIN)mom/zeromqpubsub.c $(MAIN)mod/util.c -o bin/zmqpubsub -lzmq -std=c99
	
runzmqspike: all
	bin/zmqpub 1000 tcp://*:5000 NASDAQ 100

tests:
	gcc $(TEST)sizeofspike.c -o bin/sizeofspike.o
	bin/sizeofspike.o
