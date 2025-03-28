#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 1200;

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"   // specify that first set of float numbers in vertices is position: location = 0
                                 "layout (location = 1) in vec3 aColor;\n" // specify that second set of float numbers in vertices is color: location = 1
                                 "out vec3 vertexColor;\n"                 // Pass to fragment shader
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "   vertexColor = aColor;\n" // Pass color attribute
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "in vec3 vertexColor;\n" // Input from vertex shader
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(vertexColor, 1.0);\n" // Use vertex color
                                   "}\n\0";

void neverSkipLegDay(float *vertices, int squareCount)
{

    for (int i = 0; i < squareCount; i++)
    {
        GLfloat r = ((float)rand() / RAND_MAX);
        GLfloat g = ((float)rand() / RAND_MAX);
        GLfloat b = ((float)rand() / RAND_MAX);

        int index = i * 6 * 6;
        GLfloat pos = (float)(0.1f * (squareCount - i));
        GLfloat zpos = (float)(-0.1f * i);

        // Triangle 1
        // coord 1
        vertices[index + 0] = pos;
        vertices[index + 1] = pos;
        vertices[index + 2] = zpos;
        vertices[index + 3] = r;
        vertices[index + 4] = g;
        vertices[index + 5] = b;
        
        // coord 2
        vertices[index + 6] = -pos;
        vertices[index + 7] = -pos;
        vertices[index + 8] = zpos;
        vertices[index + 9] = r;
        vertices[index + 10] = g;
        vertices[index + 11] = b;

        // coord 2
        vertices[index + 12] = pos;
        vertices[index + 13] = -pos;
        vertices[index + 14] = zpos;
        vertices[index + 15] = r;
        vertices[index + 16] = g;
        vertices[index + 17] = b;

        // Triangle 2
        // coord 1
        vertices[index + 18] = -pos;
        vertices[index + 19] = pos;
        vertices[index + 20] = zpos;
        vertices[index + 21] = r;
        vertices[index + 22] = g;
        vertices[index + 23] = b;

        // coord 2
        vertices[index + 24] = pos;
        vertices[index + 25] = pos;
        vertices[index + 26] = zpos;
        vertices[index + 27] = r;
        vertices[index + 28] = g;
        vertices[index + 29] = b;

        // coord 3
        vertices[index + 30] = -pos;
        vertices[index + 31] = -pos;
        vertices[index + 32] = zpos;
        vertices[index + 33] = r;
        vertices[index + 34] = g;
        vertices[index + 35] = b;
    }
}
void printVertices(float *vertices, int squareCount)
{
    int j = 0;
    for (int i = 0; i < squareCount * 6 * 6; i++)
    {

        if (i % 6 == 0)
        {
            std::cout << vertices[i] << " ";
            std::cout << vertices[i + 1] << " ";
            std::cout << vertices[i + 2] << " ";
            std::cout << vertices[i + 3] << " ";
            std::cout << vertices[i + 4] << " ";
            std::cout << vertices[i + 5] << " ";
            std::cout << i
                      << std::endl;
        }
    }
    std::cout << std::endl;
}

int main()
{
    GLFWwindow *shitos;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    shitos = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "init", NULL, NULL);
    if (!shitos)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(shitos);
    gladLoadGL();

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint didySpecialShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(didySpecialShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(didySpecialShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, didySpecialShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(didySpecialShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    GLfloat vertices[10 * 6 * 6];

    GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindVertexArray(VAO);

    // Make the VAO the current Vertex Array Object by binding it
    // Vertex attrib 0 (position)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // vertex attrib 1 (color)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main while loop
    while (!glfwWindowShouldClose(shitos))
    {
        neverSkipLegDay(vertices, 10);
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // updating existing buffer without having to relocate it.
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindVertexArray(VAO);

        // 6 * 10 = 60 vertices
        glDrawArrays(GL_TRIANGLES, 0, 60);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(shitos);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return 0;
}