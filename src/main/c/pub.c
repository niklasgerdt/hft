#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod/util.h"
#include "pubsub.h"

int eventMesasgeLength;

int main(int argc, char *argv[]) {
	long pauseNanos = atol(argv[1]);
	char *address = argv[2];
	char channel = argv[3][0];
	eventMesasgeLength = atoi(argv[4]);
	initTerminator();
	initEventStore("EVENTSTORE-PUB");
	initPub(address, channel);
	printf("Running with params: %d, %s, %s, %d\n", pauseNanos, address, channel, eventMesasgeLength);

	long idCount = 0;
	char *eData = malloc(eventMesasgeLength * sizeof(char));
	memset(eData, 'A', eventMesasgeLength);
	while (killSignal == 0) {
		struct eventHeader eh = { .source = channel, .id = idCount, .created = currentTime() };
		struct event e = { .header = eh, .dataLength=eventMesasgeLength, .data = eData };
		pub(&e);
		e.header.published = currentTime();
		pause(pauseNanos);
		storeEvent(&e);
		idCount++;
	}

	finalizeEventStore();
	destroyPub();
	return 0;
}
