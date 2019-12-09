#Source: https://gist.github.com/Wenchy/64db1636845a3da0c4c7
CC := g++
CFLAGS := -Wall -g -O3 -std=c++17
TARGET := mstream

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean