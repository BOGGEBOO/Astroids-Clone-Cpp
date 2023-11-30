CXXFLAGS := -g -std=c++17 -Wall -Wextra
LDFLAGS := -g -lsfml-graphics -lsfml-window -lsfml-system

SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc,%.o,$(SOURCES))


prog: $(OBJECTS)
	g++ $(CXXFLAGS) -o prog $(OBJECTS) $(LDFLAGS)

.PHONY: clean
clean:
	rm *.o prog


