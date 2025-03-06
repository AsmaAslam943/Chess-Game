# Makefile for Chess Game

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# SFML settings
# For Intel Macs
# SFML_INCLUDE = -I/usr/local/include
# SFML_LIB = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

# For Apple Silicon Macs (M1/M2/M3) - these are more common now
SFML_INCLUDE = -I/opt/homebrew/include
SFML_LIB = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# Build targets
TARGET = chess
SOURCES = main.cpp Chess.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

Chess.o: Chess.cpp Chess.h

main.o: main.cpp Chess.h

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run