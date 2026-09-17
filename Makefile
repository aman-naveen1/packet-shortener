CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Iinclude

TARGET = packet_shortener
TEST = packet_shortener_tests

all: $(TARGET)

$(TARGET): src/main.cpp src/packet_shortener.cpp include/packet_shortener.hpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/packet_shortener.cpp -o $(TARGET)

$(TEST): tests/test_packet_shortener.cpp src/packet_shortener.cpp include/packet_shortener.hpp
	$(CXX) $(CXXFLAGS) tests/test_packet_shortener.cpp src/packet_shortener.cpp -o $(TEST)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(TARGET) $(TEST)

.PHONY: all test clean
