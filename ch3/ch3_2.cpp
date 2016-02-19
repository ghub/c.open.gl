#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

const std::string BASE("ch3/ch3_2.");

std::string readShaderSource(const char* const ext)
{
    std::ifstream ifs(BASE + ext);
    std::ostringstream oss;
    oss << ifs.rdbuf();
    return oss.str();
}

std::string readVertexSource()
{
    return readShaderSource("vert");
}

std::string readFragmentSource()
{
    return readShaderSource("frag");
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float vertices[] = {
         0.0f,  0.5f, // Vertex 1 (X, Y)
         0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f, // Vertex 3 (X, Y)
    };
    int bytes = sizeof(vertices);
    int rows = 3;
    int stride = bytes / rows;
    glBufferData(GL_ARRAY_BUFFER, bytes, vertices, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string shaderSource = readVertexSource();
    const GLchar* vertexSource = shaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    shaderSource = readFragmentSource();
    const GLchar* fragmentSource = shaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, stride, 0);

    GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    auto t_start = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        glUniform3f(uniColor, (std::sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

        glDrawArrays(GL_TRIANGLES, 0, rows);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
}
