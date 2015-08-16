#pragma once

GLuint compileShader(const char* fileName, GLenum shaderType);
void addShader(GLuint program, GLuint shader);
