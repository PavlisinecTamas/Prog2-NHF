PROG = vonatjegy
SRCS = include/*.cpp include/*.hpp main.cpp
HEADS = include/*.h

CXX = g++
CXXFLAGS = -pedantic -Wall -Werror

.PHONY: all
all: $(PROG)

$(PROG): $(SRCS)
	$(CXX) $(SRCS) -o $@

$(SRCS): $(HEADS)

.PHONY: clean
clean:
	rm *.o $(PROG)
