//
// Created by slin on 2022/7/5.
//

#ifndef LEARNSHADE_GL_H
#define LEARNSHADE_GL_H
#ifdef __APPLE__
//#define GL_SILENCE_DEPRECATION
#endif
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void display(GLFWwindow* window, double currentTime);

int appRun();
#endif //LEARNSHADE_GL_H
