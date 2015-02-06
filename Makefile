CC=g++
CFLAGS=-c -Wall 
TAILFLAGS=-lpthread
DEFINES=-D_FILE_OFFSET_BITS=64
LDFLAGS=
SOURCES=main.cpp tcp_socket_server.h debug_output.h global_data.h measure_data_type.h common_lib.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=controller

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(DEFINES) $(OBJECTS) -o $@ $(TAILFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@ $(TAILFLAGS)
clean:
	rm -rf *o ${EXECUTABLE}

