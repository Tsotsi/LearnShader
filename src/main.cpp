#include <iostream>
#include "mygl.h"

using namespace std;

int main(int argc, char** argv)
{
    cout << "hello world!" << endl;
    if (!glfwInit())
    {
        return 1;
    }

    glfwSetErrorCallback(error_callback);

    // 创建window

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(800, 600, "My Shade Learning", NULL, NULL);
    if (!window)
    {
        return 2;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // rendering with opengl
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);



    glfwDestroyWindow(window);



    // 结束glfw
    glfwTerminate();
    return 0;
}