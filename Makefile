PROG = vonatjegy
SRCS = *.cpp *.hpp
HEADS = *.h

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
