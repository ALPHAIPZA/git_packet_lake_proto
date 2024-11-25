# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/protocol_sorter

# Source files
SRCS = $(SRC_DIR)/ProtocolSorter.cpp $(SRC_DIR)/main.cpp
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default rule
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
