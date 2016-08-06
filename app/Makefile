
CC := $(CROSS_COMPILE)g++

CFLAGS := -Itclap -march=armv7-a -mfloat-abi=hard -mfpu=vfp3 -mthumb-interwork -mthumb -Og -g -feliminate-unused-debug-types -W -Wall -Werror -Wwrite-strings -pedantic
LDFLAGS=

SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=alt_pll_reconfig

all: $(SOURCES) $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o: 
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	rm *.o
	rm $(EXECUTABLE)
