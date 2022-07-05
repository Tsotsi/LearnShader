//
// Created by slin on 2022/7/5.
//

#ifndef LEARNSHADE_GL_H
#define LEARNSHADE_GL_H
#ifdef __APPLE__
//#define GL_SILENCE_DEPRECATION
#endif
#include "GLFW/glfw3.h"

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
#endif //LEARNSHADE_GL_H
