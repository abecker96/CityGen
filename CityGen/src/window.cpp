// Graphics includes
#include <glad/glad.h>	// Always include GLAD first
#include <GLFW/glfw3.h>

// Other includes
#include <iostream>
#include "shaders.h"

// Should probably turn this whole file into an object so we don't start getting globals floating around
// Definitely should happen. Later.
GLFWwindow* G_window;

// GLFW window resize callback function (if user resizes window)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Not sure if this belongs in the window object yet. Might want a separate inputs object
// Then again, probably won't be a ton of development happening here past the initial stages. Might be better to keep it simple
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
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

	Shaders shaders;
	shaders.compileVertShader("src/shaders/standard.vert");
	shaders.compileFragShader("src/shaders/standard.frag");

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, shaders.getVertShader("src/shaders/standard.vert"));
	glAttachShader(shaderProgram, shaders.getFragShader("src/shaders/standard.frag"));
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
	processInput(G_window);

	// Simple rendering stuff here
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Do window/graphics stuff
	glfwSwapBuffers(G_window);
	glfwPollEvents();

	return true;
}

// This will definitely need to *at least* take some more arguments.
// At least extended into its own module/object to allow multiple objects to be registered
// and then drawn later.
void draw()
{
	// Screenspace coords
	// X     Y     Z
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Probably only want to do the stuff above once each time a new renderable object is rendered
	// GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
	// GL_STATIC_DRAW: the data is set only once and used many times.
	// GL_DYNAMIC_DRAW : the data is changed a lot and used many times.



}