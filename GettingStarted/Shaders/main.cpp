#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

float vertices2[] = {
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f 
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}   

void drawTriangle(Shader program, float vertices[], size_t vert_size) {
		glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);
		program.use();
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


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	Shader shader1("shaders/vertex.glsl", "shaders/frag.glsl");

	while(!glfwWindowShouldClose(window)) {
		drawTriangle(shader1, vertices, sizeof(vertices));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
