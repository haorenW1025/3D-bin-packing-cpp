CC=g++
LDFLAGS=-std=c++11 -O3 -lm
EXECUTABLE=bin_packing
SOURCES=src/MovingMgr.cpp src/SAMgr.cpp src/GAMgr.cpp src/main.cpp
OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(CFLAGS) $(OBJECTS) -I include

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
