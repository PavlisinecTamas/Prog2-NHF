PROG = vonatjegy
SRCS = *.cpp *.hpp
HEADS = *.h

CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -g #-fsanitize=address

.PHONY: all
all: $(PROG)

$(PROG): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) -o $@

$(SRCS): $(HEADS)

.PHONY: clean
clean:
	rm $(PROG)
