TARGET=test-madd
OBJS=test-madd.o matrix.o
SRCS=$(patsubst %.o,%.c,$(OBJS))
HEADERS=matrix.h 
CC=gcc
CFLAGS= -Wall -pthread -g

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean: 
	@rm -f $(OBJS) $(TARGET)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

sub:
	@zip $${PWD##*/}.zip $(SRCS) $(HEADERS) Makefile
