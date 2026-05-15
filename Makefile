CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = src/main.cpp src/Server.cpp

TARGET = MiniRedisCPP

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)