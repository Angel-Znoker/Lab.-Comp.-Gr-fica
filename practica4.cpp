#include <stdio.h>
#include <string.h>
#include <vector>
#include <cmath>
#include <glew.h>
#include <glfw3.h>

//glm
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

// Clases para dar orden y limpieza al código
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

const float toRadians = 3.14159265f / 180.0; //grados a radianes

Window mainWindow;
std::vector<Shader>shaderList;
std::vector<Mesh*>meshList;

// Archivos de vertexShader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";

void CreateObject() {
    
	GLfloat vPiramideT[] = {
			// vértices			// colores
		-0.5f, -0.435f, -0.3f,  1.0f, 0.0f, 0.0f,
		 0.0f, -0.435f,  0.57f, 1.0f, 0.0f, 0.0f,
		 0.0f,  0.435f,  0.0f,  1.0f, 0.0f, 0.0f,

		 0.0f, -0.435f,  0.57f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.435f, -0.3f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.435f,  0.0f,  0.0f, 1.0f, 0.0f,

		 0.5f, -0.435, -0.3f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.435, -0.3f,   0.0f, 0.0f, 1.0f,
		 0.0f,  0.435f, 0.0f,   0.0f, 0.0f, 1.0f,

		-0.5f, -0.435f, -0.3f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.435f, -0.3f,  1.0f, 1.0f, 0.0f,
		 0.0f, -0.435,  0.57f,  1.0f, 1.0f, 0.0f
	};

	GLfloat vOctaedro[] {
			// vértices				// colores
		 0.0f,  0.435f,  0.57f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.435f, -0.3f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.435f, -0.3f,  1.0f, 1.0f, 1.0f,

		 0.0f,  0.435f,  0.57f, 1.0f, 1.0f, 0.f,
		-0.5f,  0.435f, -0.3f,  1.0f, 1.0f, 0.f,
		-0.5f, -0.435f,  0.27,  1.0f, 1.0f, 0.f,

		 0.0f,  0.435f,  0.57f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.435f,  0.27,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.435f,  0.27,  1.0f, 1.0f, 1.0f,

		 0.0f,  0.435f,  0.57f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.435f,  0.27,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.435f, -0.3f,  0.0f, 0.0f, 1.0f,

		 0.0f, -0.435f, -0.6f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.435f,  0.27,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.435f,  0.27,  1.0f, 0.0f, 0.0f,

		 0.0f, -0.435f, -0.6f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.435f, -0.3f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.435f,  0.27,  1.0f, 1.0f, 1.0f,

		 0.0f, -0.435f, -0.6f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.435f, -0.3f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.435f, -0.3f,  0.0f, 1.0f, 0.0f,

		 0.0f, -0.435f, -0.6f,  1.0f, 1.0f, 1.0f,
		-0.5f, -0.435f,  0.27,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.435f, -0.3f,  1.0f, 1.0f, 1.0f
	};

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vPiramideT, 72);
    meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj3);

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj4);

	Mesh *obj5 = new Mesh();
	obj5->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj5);

	Mesh *obj6 = new Mesh();
	obj6->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj6);

	Mesh *obj7 = new Mesh();
	obj7->CreateMesh(vOctaedro, 144);
	meshList.push_back(obj7);

	Mesh *obj8 = new Mesh();
	obj8->CreateMesh(vOctaedro, 144);
	meshList.push_back(obj8);

	Mesh *obj9 = new Mesh();
	obj9->CreateMesh(vOctaedro, 144);
	meshList.push_back(obj9);

	Mesh *obj10 = new Mesh();
	obj10->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj10);

	Mesh *obj11 = new Mesh();
	obj11->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj11);

	Mesh *obj12 = new Mesh();
	obj12->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj12);

	Mesh *obj13 = new Mesh();
	obj13->CreateMesh(vOctaedro, 144);
	meshList.push_back(obj13);

	Mesh *obj14 = new Mesh();
	obj14->CreateMesh(vPiramideT, 72);
	meshList.push_back(obj14);
}

void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main() {
    mainWindow = Window(800, 600);
    mainWindow.Initialise();
    
	// creación de la figura
    CreateObject();
    CreateShaders();
    
    // Variable para cambiar los uniform del shader
	GLuint uniformFigure = 0;
    
	// cámara fija y proyección
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);

    //Loop mientras no se cierra la ventana
    while (!mainWindow.getShouldClose()) {
        //Recibir eventos del usuario
        glfwPollEvents();
		glm::mat4 figure(1.0);
        //Limpiar la ventana
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderList[0].useShader();

		uniformFigure = shaderList[0].getFigureLocation();

		glm::mat4 rotation(1.0);
		// rotación global en x y Y
        rotation = glm::rotate(rotation, mainWindow.angleY * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, mainWindow.angleX * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		// figuras en el primer nivel
		glm::mat4 model(1.0);
		model = glm::translate(model, glm::vec3(-0.1f, -0.0435f, -0.06f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		// multiplicación de matrices, la rotación global se aplica antes que las
		// transformaciones individuales
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
        meshList[0]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.0435f, -0.06f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[1]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.1f, -0.0435f, -0.06f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[2]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.05f, -0.0435f, 0.027f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[3]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.05f, -0.0435f, 0.027f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[4]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.0435f, 0.114f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[5]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.0435f, 0.057f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[6]->RenderMesh(24);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.05f, -0.0435f, -0.03f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[7]->RenderMesh(24);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.05f, -0.0435f, -0.03));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[8]->RenderMesh(24);

		// figuras del segundo nivel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.05f, 0.0435, -0.03f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[9]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.05f, 0.0435, -0.03f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[10]->RenderMesh(12);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0435, 0.057f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[11]->RenderMesh(12);
        
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0435f, 0.0));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[12]->RenderMesh(24);

		// último nivel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.1305f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		figure = projection * view * rotation * model;
		glUniformMatrix4fv(uniformFigure, 1, GL_FALSE, glm::value_ptr(figure));
		meshList[13]->RenderMesh(12);

        glUseProgram(0);
        mainWindow.swapBuffers();
        
    }
    return 0;
}
