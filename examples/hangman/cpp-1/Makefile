CXX = g++
CXXFLAGS = -Wall -Wextra -I../c
LDFLAGS =

TARGET = hangman
OBJS = main.o
C_OBJS = ../c/hangman.o

all: $(TARGET)

$(TARGET): $(OBJS) $(C_OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(C_OBJS) $(LDFLAGS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
