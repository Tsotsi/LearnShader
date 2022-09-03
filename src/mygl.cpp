//
// Created by slin on 2022/7/5.
//

#include <iostream>
#include "linmath/linmath.h"
#include "mygl.h"


void error_callback(int error, const char *description) {
    std::cerr << "Error: " << error << ", " << description << std::endl;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_F1 && action == GLFW_RELEASE)
        s_showStats = !s_showStats;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}


void display(GLFWwindow *window, double currentTime) {
//    glClearColor(1.0, 0.0, 0.0, 1.0);
//    glClearColor(1,0.5,0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
}

unsigned int compileShader(const std::string &source, unsigned int type) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
//    int wc = source.length();
//    glShaderSource(shader, 1, &src, &wc);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader."
                  << std::endl;
        std::cout << message << std::endl;
    }
    return id;
}

unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vert = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int frag = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vert);
    glDeleteShader(frag);
    return program;
}

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] =
        {
                {-0.6f, -0.4f, 1.f, 0.f, 0.f},
                {0.6f,  -0.4f, 0.f, 1.f, 0.f},
                {0.f,   0.6f,  0.f, 0.f, 1.f}
        };

static const char *vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";

static const char *fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

static const std::string vertex_shader_str =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "void main(){\n"
        "gl_Position = position;\n"
//        "if(gl_VertexID == 0) gl_Position = vec4(0.25, -0.25, 0.0, 1.0);\n"
//        "else if(gl_VertexID == 1) gl_Position = vec4(-0.25, -0.25, 0.0, 1.0);\n"
//        "else if(gl_VertexID == 2) gl_Position = vec4(0.25, 0.25, 0.0, 1.0);\n"
        "}\n";
static const std::string fragment_shader_str =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "void main(){\n"
        "color = vec4( 1.0, 1.0, 0.0, 1.0 );\n"
        "}\n";

int app() {
    if (!glfwInit()) {
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    // 创建window

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "My Shade Learning", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -2;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
//    gladLoadGL();
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // rendering with opengl
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);

    glfwSwapInterval(1);
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    // compile shaders
    /*GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));
*/

    /// clean buffer begin
    unsigned int buf;
    float positions[6] = {
            -.5f, -.5f,
            0.0f, 0.5f,
            .5f, -.5f,
    };
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    unsigned int shader = createShader(vertex_shader_str, fragment_shader_str);

    std::cout << "shader id: " << shader << std::endl;
    std::cout << "vertex shader: \n" << vertex_shader_str << std::endl;
    std::cout << "fragment shader id: \n" << fragment_shader_str << std::endl;
    /// clean buffer end

    while (!glfwWindowShouldClose(window)) {
        // Keep running
//        display(window, glfwGetTime());
//        float ratio;
//        int width, height;
//        mat4x4 m, p, mvp;
//
//        glfwGetFramebufferSize(window, &width, &height);
//        ratio = width / (float) height;
//
//        glViewport(0, 0, width, height);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        mat4x4_identity(m);
//        mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//        mat4x4_mul(mvp, p, m);
//
//        glUseProgram(program);
//        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

        /// draw clean buffer
//        glClearColor(0.5, 0.5, 0.5, 1.0);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float) height;

//        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
//        glBindBuffer(GL_ARRAY_BUFFER, buf);
//        glBindVertexArray(buf);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwDestroyWindow(window);



    // 结束glfw
    glfwTerminate();
    return 0;
}

int appWithBgfx() {
//    glfwSetErrorCallback(error_callback);
//    if (!glfwInit())
//        return 1;
//    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//    GLFWwindow *window = glfwCreateWindow(1024, 768, "helloworld", nullptr, nullptr);
//    if (!window)
//        return 1;
//    glfwSetKeyCallback(window, key_callback);
//    // Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
//    // Most graphics APIs must be used on the same thread that created the window.
//    bgfx::renderFrame();
//    // Initialize bgfx using the native window handle and window resolution.
//    bgfx::Init init;
//#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
//    init.platformData.ndt = glfwGetX11Display();
//    init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
//#elif BX_PLATFORM_OSX
//    init.platformData.nwh = glfwGetCocoaWindow(window);
//#elif BX_PLATFORM_WINDOWS
//    init.platformData.nwh = glfwGetWin32Window(window);
//#endif
//    int width, height;
//    glfwGetWindowSize(window, &width, &height);
//    init.resolution.width = (uint32_t) width;
//    init.resolution.height = (uint32_t) height;
//    init.resolution.reset = BGFX_RESET_VSYNC;
//    if (!bgfx::init(init))
//        return 1;
//    // Set view 0 to the same dimensions as the window and to clear the color buffer.
//    const bgfx::ViewId kClearView = 0;
//    bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
//    bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
//    while (!glfwWindowShouldClose(window)) {
//        glfwPollEvents();
//        // Handle window resize.
//        int oldWidth = width, oldHeight = height;
//        glfwGetWindowSize(window, &width, &height);
//        if (width != oldWidth || height != oldHeight) {
//            bgfx::reset((uint32_t) width, (uint32_t) height, BGFX_RESET_VSYNC);
//            bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
//        }
//        // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
//        bgfx::touch(kClearView);
//        // Use debug font to print information about this example.
//        bgfx::dbgTextClear();
//        bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(width / 2 / 8), 20) - 20,
//                           bx::max<uint16_t>(uint16_t(height / 2 / 16), 6) - 6, 40, 12, s_logo, 160);
//        bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");
//        bgfx::dbgTextPrintf(0, 1, 0x0f,
//                            "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");
//        bgfx::dbgTextPrintf(80, 1, 0x0f,
//                            "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
//        bgfx::dbgTextPrintf(80, 2, 0x0f,
//                            "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");
//        const bgfx::Stats *stats = bgfx::getStats();
//        bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
//                            stats->width, stats->height, stats->textWidth, stats->textHeight);
//        // Enable stats or debug text.
//        bgfx::setDebug(s_showStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
//        // Advance to next frame. Process submitted rendering primitives.
//        bgfx::frame();
//    }
//    bgfx::shutdown();
//    glfwTerminate();
    return 0;
}