#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>

#include<glew.h>

class Shader {
public:
    Shader();
    void CreatefromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
    std::string ReadFile(const char*  fileLocation);
	GLuint getFigureLocation();
    
    void useShader();
    void ClearShader();
    ~Shader();
    
private:
    GLuint shaderID, uniformFigure;
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* ShaderCode, GLenum shaderType);
};
