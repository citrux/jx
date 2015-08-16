#include <iostream>
#include <fstream>
#include "shader.hpp"

ShaderManager::ShaderManager() {
    program = glCreateProgram();
}

ShaderManager::~ShaderManager() {
    glDeleteProgram(program);
}

char* readFile(const char* fileName) {
    std::ifstream is(fileName, std::ios::in|std::ios::binary|std::ios::ate);
	if (!is.is_open()) {
		std::cerr << "Unable to open file " << fileName << std::endl;
		exit(1);
	}

	long size = is.tellg();

    auto buffer = new char[size+1];
	is.seekg(0, std::ios::beg);
	is.read (buffer, size);
	is.close();
	buffer[size] = 0;
    return buffer;
}

GLuint ShaderManager::compileShader(const char* fileName, GLenum shaderType) {
    GLuint handler;

    // get a shader handler
    handler = glCreateShader(shaderType);
    // read the shader source from a file
    // conversions to fit the next function
    const char* buffer = readFile(fileName);
    // pass the source text to GL
    glShaderSource(handler, 1, &buffer, 0);
    // finally compile the shader
    glCompileShader(handler);
    return handler;
}

void ShaderManager::addShader(const char* fileName, GLenum shaderType) {
    auto shader = compileShader(fileName, shaderType);
    glAttachShader(program, shader);
    glLinkProgram(program);
};

void ShaderManager::run() {
    glUseProgram(program);
}

void ShaderManager::stop() {
    glUseProgram(0);
}

void ShaderManager::uniform1i(const char* varName, int value) {
    glUniform1i(glGetUniformLocation(program, varName), value);
}

void ShaderManager::uniform2f(const char* varName, glm::vec2 value) {
    glUniform2f(glGetUniformLocation(program, varName), value.x, value.y);
}


