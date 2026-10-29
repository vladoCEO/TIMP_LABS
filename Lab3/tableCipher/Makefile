CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I/usr/include/unittest++
LDFLAGS = -L/usr/lib -lUnitTest++
TARGET = run_table_tests
OBJS = main.o tableCipher.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp tableCipher.h
	$(CXX) $(CXXFLAGS) -c main.cpp

tableCipher.o: tableCipher.cpp tableCipher.h
	$(CXX) $(CXXFLAGS) -c tableCipher.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
