#include <shaders.h>

// Graphics includes
#include <glad/glad.h>	// Always include GLAD first
#include <GLFW/glfw3.h>

// Other includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int Shaders::compileVertShader(const std::string filepath)
{
	int success;
	char infoLog[512];

	unsigned int shaderHandle;
	shaderHandle = glCreateShader(GL_VERTEX_SHADER);

	std::string src = readFileToString(filepath);
	const char* shader_source = src.c_str();

	std::cout << "Compiling vertex shader:" << std::endl;
	std::cout << shader_source << std::endl << std::endl;

	glShaderSource(shaderHandle, 1, &shader_source, NULL);
	glCompileShader(shaderHandle);
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		vertShaders[filepath] = shaderHandle;
	}

	return success;
}

int Shaders::compileFragShader(const std::string filepath)
{
	int success;
	char infoLog[512];

	unsigned int shaderHandle;
	shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

	std::string src = readFileToString(filepath);
	const char* shader_source = src.c_str();

	std::cout << "Compiling fragment shader:" << std::endl;
	std::cout << shader_source << std::endl << std::endl;

	glShaderSource(shaderHandle, 1, &shader_source, NULL);
	glCompileShader(shaderHandle);
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else
	{
		fragShaders[filepath] = shaderHandle;
	}

	return success;
}

unsigned int Shaders::getVertShader(const std::string name)
{
	return vertShaders[name];
}

unsigned int Shaders::getFragShader(const std::string name)
{
	return fragShaders[name];
}
const std::unordered_map<std::string, unsigned int> Shaders::getVertShaders()
{
	return vertShaders;
}

const std::unordered_map<std::string, unsigned int> Shaders::getFragShaders()
{
	return fragShaders;
}

std::string Shaders::readFileToString(std::string filePath)
{
	std::ifstream fileStream(filePath);
	if (!fileStream.is_open()) {
		throw std::runtime_error("Could not open file: " + filePath);
	}

	std::stringstream buffer;
	buffer << fileStream.rdbuf();
	return buffer.str();
}