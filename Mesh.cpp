#include "Mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
}

void Mesh::CreateMesh(GLfloat *vertices, int t) {
    glGenVertexArrays(1, &VAO); //generar 1 VAO
    glBindVertexArray(VAO);//asignar VAO
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Datos al VBO, son estáticos ya que no serán modificados
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * t, vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::RenderMesh(int v) {
	// v es el numero de vertices totales que tiene la figura

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// El stride cambia de valor para diferenciar vertices de colores
	// Dibijado de figura
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    
	// color de figura
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glDrawArrays(GL_TRIANGLES, 0, v);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh() {
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO); ///LIMPIAR BUFFER PARAE EVITAR OCUPAR LA MEMORIA
        VBO = 0;
    }

    if(VAO!=0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}

Mesh::~Mesh() {
    ClearMesh();
}

