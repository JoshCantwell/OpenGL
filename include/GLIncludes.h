#ifndef GL_INCLUDES_H
#define GL_INCLUDES_H

// Prevent Windows headers from polluting the namespace
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <glad/glad.h>   // must come first
#include <GLFW/glfw3.h>  // must come after glad
#include <glm/glm.hpp>   // math library (safe after OpenGL)

#endif

