#pragma once
#include <unordered_map>
#include <string>

class Shaders {
	private:
		std::unordered_map<std::string, unsigned int> vertShaders;
		std::unordered_map<std::string, unsigned int> fragShaders;

		std::string readFileToString(std::string filePath);

	public:
		// There's probably a ton of room to rethink this specific design
		// But honestly this is fine for now. It'll be clear enough when using it
		int compileVertShader(const std::string filename);
		int compileFragShader(const std::string filename);
		const std::unordered_map<std::string, unsigned int> getVertShaders();
		const std::unordered_map<std::string, unsigned int> getFragShaders();
		unsigned int getVertShader(const std::string name);
		unsigned int getFragShader(const std::string name);
};

