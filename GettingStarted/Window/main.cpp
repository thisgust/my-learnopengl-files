#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
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

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD!";
    return -1;
  }
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glViewport(0, 0, WIDTH, HEIGHT);

  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
