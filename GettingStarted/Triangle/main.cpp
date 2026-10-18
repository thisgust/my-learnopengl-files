#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\0";


float vertices[] = {
	0.3f, 0.5f, 0.0f,
	 0.3f, -0.5f, 0.0f,
	 -0.3f,  -0.5f, 0.0f,
	 -0.3f, 0.5f, 0.0f
};

float vertices2[] = {
	-0.3f, -0.3f, 0.0f,
	0.3f, -0.3f, 0.0f,
	0.0f, 0.3f, 0.0f
};

uint32_t indices[] = {
	0, 1, 3,
	1, 2, 3
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void drawTriangle(unsigned int program, float vertices[], size_t vert_size) {
		glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);

		glUseProgram(program);
		glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawQuad(unsigned int program, float vertices[], uint32_t indices[], size_t vert_size, size_t ind_size) {
	glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);

	glUseProgram(program);
	glDrawElements(GL_TRIANGLES, ind_size, GL_UNSIGNED_INT, 0);
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL - Hello Window", nullptr, nullptr);
  	if (window == nullptr) {
   		std::cout << "Error creating window!";
    	glfwTerminate();
    	return -1;
  	}

  	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    	std::cout << "Failed to initialize GLAD!";
    	return -1;
  	}

  	glViewport(0, 0, WIDTH, HEIGHT);

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	unsigned int vertexShader, fragmentShader, shaderProgram, shaderProgram2;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource2, nullptr);
	glCompileShader(fragmentShader);
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader);
	glLinkProgram(shaderProgram2);

  	while (!glfwWindowShouldClose(window)) {
		drawQuad(shaderProgram, vertices, indices, sizeof(vertices), sizeof(indices));
		drawTriangle(shaderProgram2, vertices2, sizeof(vertices2));
   		glfwSwapBuffers(window);
    	glfwPollEvents();
  	}

	glfwTerminate();

	return 0;
}
