CC=g++
CFLAGS=-c -Werror -Wall -Wextra -pedantic -std=c++14
LDFLAGS=
SOURCES=main.cpp proxy.cpp led.cpp server.cpp ledServer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ledServer

.PHONY: all clean

all: $(SOURCES) $(EXECUTABLE)

clean: 
	rm -f $(EXECUTABLE) *.o
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@