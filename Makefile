# ImGui paths
IMGUI_DIR = C:/Libraries/imgui
IMGUI_BACKENDS = $(IMGUI_DIR)/backends

IMGUI_SRCS = \
    $(IMGUI_DIR)/imgui.cpp \
    $(IMGUI_DIR)/imgui_draw.cpp \
    $(IMGUI_DIR)/imgui_widgets.cpp \
    $(IMGUI_DIR)/imgui_tables.cpp \
    $(IMGUI_DIR)/imgui_demo.cpp \
    $(IMGUI_BACKENDS)/imgui_impl_win32.cpp \
    $(IMGUI_BACKENDS)/imgui_impl_opengl3.cpp

#Compiler
CC  = gcc
CXX = g++

# Paths
SRC_DIR  = src
OBJ_DIR  = build
BIN      = $(OBJ_DIR)/app.exe


# GLAD paths
GLAD_INC = C:/Libraries/glad/include
GLAD_SRC = C:/Libraries/glad/src/glad.c

#GLM paths
GLM_INC = C:/Libraries/glm

# GLFW paths
GLFW_INC = C:/Libraries/glfw-3.4/include 
GLFW_LIB = C:/Libraries/glfw-3.4/lib

# Include paths
INCLUDES = -Iinclude -I$(GLAD_INC) -I$(GLFW_INC) -I$(IMGUI_DIR) -I$(IMGUI_BACKENDS)

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 $(INCLUDES) -I$(GLM_INC)
CFLAGS   = -Wall $(INCLUDES)

# Libraries
LIBS = -L$(GLFW_LIB) -lglfw3 -lopengl32 -lglu32 -lgdi32 -ldwmapi

# Sources
CPP_SRCS = $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS   = $(filter-out $(GLAD_SRC), $(wildcard $(SRC_DIR)/*.c))
OBJS     = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SRCS)) \
           $(patsubst $(SRC_DIR)/%.c,   $(OBJ_DIR)/%.o, $(C_SRCS)) \
           $(OBJ_DIR)/glad.o

IMGUI_OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(IMGUI_SRCS)))
OBJS += $(IMGUI_OBJS)

# Default target
all: $(BIN)

# Link
$(BIN): $(OBJS) | $(OBJ_DIR)
	@echo "Linking $(BIN)..."
	$(CXX) -o $@ $^ $(LIBS)

# Compile C++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling C++ $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling C $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile glad.c
$(OBJ_DIR)/glad.o: $(GLAD_SRC) | $(OBJ_DIR)
	@echo "Compiling glad..."
	$(CC) $(CFLAGS) -c $< -o $@

# Make build directory
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(IMGUI_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling ImGui core $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(IMGUI_BACKENDS)/%.cpp | $(OBJ_DIR)
	@echo "Compiling ImGui backend $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	@echo "Cleaning..."
	@del /Q $(OBJ_DIR)\*.o $(BIN) 2>nul || exit 0

.PHONY: all clean

