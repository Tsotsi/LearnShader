//
// Created by slin on 2022/7/5.
//

#include <iostream>
#include "mygl.h"


void error_callback(int error, const char* description)
{
    std::cerr << "Error: "<< description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void display(GLFWwindow* window, double currentTime){
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int appRun(){
    if (!glfwInit())
    {
        return 1;
    }
    glfwSetErrorCallback(error_callback);

    // 创建window

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "My Shade Learning", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 2;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    // rendering with opengl
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);
    // glViewport(0, 0, width, height);
    
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        // Keep running
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);



    // 结束glfw
    glfwTerminate();
    return 0;
}