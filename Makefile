# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Files
TARGET = engine
SRC = main.cpp
OBJ = main.o

# Default target
default: $(TARGET)

# Compile main.cpp to main.o
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Link main.o to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(TRANSOBJ) -o $(TARGET) $(LIBS)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: default clean run
