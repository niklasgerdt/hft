#ifndef EVENT_H_
#define EVENT_H_

#include <time.h>

struct eventHeader {
	char source;
	char destination;
	long id;
	struct timespec created;
	struct timespec published;
	struct timespec routed;
};

struct event {
	struct eventHeader header;
	int dataLength;
	char *data;
};

void initEventStore(const char *fileName);

void storeEvent(struct event *e);

void finalizeEventStore();

#endif /* EVENT_H_ */
