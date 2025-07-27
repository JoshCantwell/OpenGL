# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude 
# Paths
SRC_DIR = src
INC_DIR = include
OBJ_DIR = build
BIN = build/app.exe

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Libraries
LIBS = -lopengl32 -lglu32 -lgdi32 -lassimp -lstdc++ -lz 

# Default rule
all: $(BIN)

# Link
$(BIN): $(OBJS)
	@echo "Linking..."
	$(CXX) -o $@ $^ $(LIBS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if missing
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

# Clean
clean:
	@echo "Cleaning..."
	@del /Q $(OBJ_DIR)\*.o $(BIN) 2>nul || true

.PHONY: all clean

