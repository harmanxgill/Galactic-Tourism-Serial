# Compiler and flags
CXX = g++                     # Use g++ instead of mpicxx since we are not using MPI
CXXFLAGS = -O3 -std=c++17 -Wall # Removed OpenMP and MPI flags, only optimization and C++17 standard
TARGET = galactic_tourism

# Paths
SRC_DIR = src
BUILD_DIR = build

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Link the target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build and executable files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
