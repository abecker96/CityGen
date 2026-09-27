// Graphics includes
#include <glad/glad.h>	// Always include GLAD first
#include <GLFW/glfw3.h>

// Other includes
#include <iostream>

// Should probably turn this whole file into an object so we don't start getting globals floating around
// Definitely should happen. Later.
GLFWwindow* G_window;

// GLFW window resize callback function (if user resizes window)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int makeWindow(int w, int h)
{
	// GLFW Window init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	G_window = glfwCreateWindow(w, h, "LearnOpenGL", NULL, NULL);
	if (G_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(G_window);

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Tell GLFW info about the window
	glViewport(0, 0, w, h);
	glfwSetFramebufferSizeCallback(G_window, framebuffer_size_callback);
	return 0;
}

bool windowLoop()
{
	if (glfwWindowShouldClose(G_window))
	{
		// GLFW/GLAD/OpenGL cleanup should happen here
		glfwTerminate();
		return false;
	}

	// Do window/graphics stuff
	glfwSwapBuffers(G_window);
	glfwPollEvents();

	return true;
}