//
// Created by slin on 2022/7/5.
//

#ifndef LEARNSHADE_GL_H
#define LEARNSHADE_GL_H
#ifdef __APPLE__
//#define GL_SILENCE_DEPRECATION
#endif

#include <stdio.h>
//#include <bx/bx.h>
//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include "glad/glad.h"
#include "logo.h"

static bool s_showStats = false;
void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void display(GLFWwindow* window, double currentTime);
unsigned int compileShader(const std::string& source, unsigned int type);
unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
int app();
int appWithBgfx();
#endif //LEARNSHADE_GL_H
