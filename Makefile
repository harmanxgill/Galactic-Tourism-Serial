# Compiler and flags
CXX = mpicxx
CXXFLAGS = -fopenmp -O3 -std=c++17 -Wall
TARGET = galactic_tourism

# Source files
SOURCES = main.cpp particle.cpp sph_solver.cpp transparency.cpp visualization_utils.cpp parallel_utils.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile individual source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets
.PHONY: all clean
