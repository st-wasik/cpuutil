TARGET = cpuutil

CFLAGS += -O3 -Wfatal-errors

default: $(TARGET)

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

cpuutil: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)