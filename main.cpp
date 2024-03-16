#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* forwardingVectorShader = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShader = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
    "}\0";

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "MyOpenGLApp", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "window is null" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowTitle(window, "Test title");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        (void)window;
        std::cout << width << " " << height << std::endl;
        glViewport(0, 0, width, height);
    });

    float triangleVertices[] = {
        -0.5f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f,
        0.7f, -0.9f, 0.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    unsigned int vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &forwardingVectorShader, nullptr);
    glCompileShader(vertexShaderId);

    int compilationSucceeded;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compilationSucceeded);

    if (compilationSucceeded == GL_TRUE)
    {
        std::cout << "Vertex shader compilation successful" << std::endl;
    }
    else
    {
        char compilationLog[512];
        glGetShaderInfoLog(vertexShaderId, 512, NULL, compilationLog);
        std::cout << "Vertex shader compilation failed: " << compilationLog << std::endl;
    }

    unsigned int fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShader, nullptr);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &compilationSucceeded);
    
    if (compilationSucceeded == GL_TRUE)
    {
        std::cout << "Fragment shader compilation successful" << std::endl;
    }
    else
    {
        char compilationLog[512];
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, compilationLog);
        std::cout << "Fragment shader compilation failed: " << compilationLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &compilationSucceeded);
    if (compilationSucceeded == GL_TRUE)
    {
        std::cout << "Shader program built successfully" << std::endl;
    }
    else
    {
        char compilationLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, compilationLog);
        std::cout << "Shader program build failed: " << compilationLog << std::endl;
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
