#pragma once
#include<glew.h>
class Mesh
{
public:
    Mesh();
    void CreateMesh(GLfloat *vertices);
    void bindVAO();
    void RenderMesh();
    void ClearMesh();
    ~Mesh();
    
private:
    GLuint VAO, VBO;
};
