# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Files
TARGET = engine
SRC = main.cpp square.cpp floor.cpp axis.cpp torus.cpp
OBJ = $(SRC:.cpp=.o) # Convert all .cpp files to .o files

# Default target
default: $(TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: default clean run
