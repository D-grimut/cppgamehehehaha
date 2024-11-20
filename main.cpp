#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    shitos = glfwCreateWindow(700, 700, "init", NULL, NULL);
    if (!shitos)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(shitos);
    gladLoadGL();
    glViewport(0, 0, 700, 700);

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
    GLfloat vertices[] = {
        // Positions        // Colors
        // First Triangle (Orange)
        1.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.2f,   // Top vertex
        -1.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-left
        1.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.2f,  // Bottom-right

        -1.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.2f,  // Top vertex
        1.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.2f,   // Bottom-left
        -1.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-right

        // Second Triangle (Blue)
        0.9f, 0.9f, 0.0f, 0.0f, 0.0f, 1.0f,   // Top vertex
        -0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right

        -0.9f, 0.9f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top vertex
        0.9f, 0.9f, 0.0f, 0.0f, 0.0f, 1.0f,   // Bottom-left
        -0.9f, -0.9f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
        // Third triangle (Orange)
        0.8f, 0.8f, 0.0f, 1.0f, 0.5f, 0.2f,   // Top vertex
        -0.8f, -0.8f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-left
        0.8f, -0.8f, 0.0f, 1.0f, 0.5f, 0.2f,  // Bottom-right

        -0.8f, 0.8f, 0.0f, 1.0f, 0.5f, 0.2f,  // Top vertex
        0.8f, 0.8f, 0.0f, 1.0f, 0.5f, 0.2f,   // Bottom-left
        -0.8f, -0.8f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-right

        // 4th Triangle (Blue)
        0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f,   // Top vertex
        -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right

        -0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top vertex
        0.7f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f,   // Bottom-left
        -0.7f, -0.7f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
        // 5th Triangle(Orange)
        0.6f, 0.6f, 0.0f, 1.0f, 0.5f, 0.2f,   // Top vertex
        -0.6f, -0.6f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-left
        0.6f, -0.6f, 0.0f, 1.0f, 0.5f, 0.2f,  // Bottom-right

        -0.6f, 0.6f, 0.0f, 1.0f, 0.5f, 0.2f,  // Top vertex
        0.6f, 0.6f, 0.0f, 1.0f, 0.5f, 0.2f,   // Bottom-left
        -0.6f, -0.6f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-right

        // 6th Triangle (Blue)
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // Top vertex
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right

        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top vertex
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // Bottom-left
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
        // 7th Triangle (Orange)
        0.4f, 0.4f, 0.0f, 1.0f, 0.5f, 0.2f,   // Top vertex
        -0.4f, -0.4f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-left
        0.4f, -0.4f, 0.0f, 1.0f, 0.5f, 0.2f,  // Bottom-right

        -0.4f, 0.4f, 0.0f, 1.0f, 0.5f, 0.2f,  // Top vertex
        0.4f, 0.4f, 0.0f, 1.0f, 0.5f, 0.2f,   // Bottom-left
        -0.4f, -0.4f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-right

        // 8th Triangle (Blue)
        0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,   // Top vertex
        -0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right

        -0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,  // Top vertex
        0.3f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,   // Bottom-left
        -0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
        // 9th Triangle (Orange)
        0.2f, 0.2f, 0.0f, 1.0f, 0.5f, 0.2f,   // Top vertex
        -0.2f, -0.2f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-left
        0.2f, -0.2f, 0.0f, 1.0f, 0.5f, 0.2f,  // Bottom-right

        -0.2f, 0.2f, 0.0f, 1.0f, 0.5f, 0.2f,  // Top vertex
        0.2f, 0.2f, 0.0f, 1.0f, 0.5f, 0.2f,   // Bottom-left
        -0.2f, -0.2f, 0.0f, 1.0f, 0.5f, 0.2f, // Bottom-right

        // 10th Triangle (Blue)
        0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,   // Top vertex
        -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
        0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right

        -0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f, // Top vertex
        0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-left
        -0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f // Bottom-right
    };

    GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main while loop
    while (!glfwWindowShouldClose(shitos))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        // int i = 0;
        // while (i < 60)
        // {
        //     glDrawArrays(GL_TRIANGLES, i, 6);
        //     i += 6;
        // }
        glDrawArrays(GL_TRIANGLES, 0, 60);
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