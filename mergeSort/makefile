CC=gcc
CFLAGS=-Wall -std=c11

SRCS=mergeSort.c
OBJS=$(SRCS:.c=.o)
EXECUTABLE=run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del *.o $(EXECUTABLE)