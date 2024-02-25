CC = gcc
CFLAGS = -O3 -march=native -Wall -std=c11 -g
# CFLAGS = -Wall -std=c11 -g

SRCS = quickSort.c
OBJS = $(SRCS:.c=.o)
EXECUTABLE = run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del  *.o $(EXECUTABLE).exe