CC=g++
CFLAGS=-c -Wall -std=c++14
LDFLAGS=
SOURCES=main.cpp proxy.cpp complex_led.cpp primitive_led.cpp server.cpp
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