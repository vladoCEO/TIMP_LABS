CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I/usr/include/unittest++
LDFLAGS = -L/usr/lib -lUnitTest++
TARGET = run_tests
OBJS = main.o modAlphaCipher.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

modAlphaCipher.o: modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) -c modAlphaCipher.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
