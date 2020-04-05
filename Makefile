CC=g++
LDFLAGS=-std=c++11 -O3 -lm
EXECUTABLE=bin_packing
SOURCES=src/mgr.cpp src/main.cpp
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) -I include

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
