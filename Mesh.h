#pragma once
#include<glew.h>
class Mesh {
public:
    Mesh();
	void CreateMesh(GLfloat *vertices, int t);
    void RenderMesh(int v);
    void ClearMesh();
    ~Mesh();
    
private:
    GLuint VAO, VBO;
};
