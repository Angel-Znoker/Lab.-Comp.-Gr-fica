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
    
    GLfloat vertices1[] = {
        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.0f, -0.5f,  0.87f, 1.0f, 0.0f, 0.0f,
         0.0f,  0.37f, 0.3f,  1.0f, 0.0f, 0.0f,
        
         0.0f, -0.5f,  0.87f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.37f, 0.3f,  0.0f, 1.0f, 0.0f,
        
         0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
         0.0f,  0.37f, 0.3f, 0.0f, 0.0f, 1.0f,
        
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
		 0.0f, -0.5f, 0.87f, 1.0f, 1.0f, 0.0f
    };

	GLfloat vertices2[] = {
		-0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f, -0.5f,  0.87f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.37f, 0.3f,  0.0f, 1.0f, 0.0f,

		 0.0f, -0.5f,  0.87f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.0f,  0.37f, 0.3f,  0.0f, 0.0f, 1.0f,

		 0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f,
		 0.0f,  0.37f, 0.3f, 1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.0f,  0.1f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.1f, 0.0f, 0.0f,
		 0.0f, -0.5f, 0.87f, 0.1f, 0.0f, 0.0f
	};

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices1);
    meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices1);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(vertices1);
	meshList.push_back(obj3);

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vertices1);
	meshList.push_back(obj4);

	Mesh *obj5 = new Mesh();
	obj5->CreateMesh(vertices1);
	meshList.push_back(obj5);

	Mesh *obj6 = new Mesh();
	obj6->CreateMesh(vertices1);
	meshList.push_back(obj6);

	Mesh *obj7 = new Mesh();
	obj7->CreateMesh(vertices2);
	meshList.push_back(obj7);

	Mesh *obj8 = new Mesh();
	obj8->CreateMesh(vertices2);
	meshList.push_back(obj8);

	Mesh *obj9 = new Mesh();
	obj9->CreateMesh(vertices2);
	meshList.push_back(obj9);

	Mesh *obj10 = new Mesh();
	obj10->CreateMesh(vertices2);
	meshList.push_back(obj10);

	Mesh *obj11 = new Mesh();
	obj11->CreateMesh(vertices2);
	meshList.push_back(obj11);

	Mesh *obj12 = new Mesh();
	obj12->CreateMesh(vertices2);
	meshList.push_back(obj12);

	Mesh *obj13 = new Mesh();
	obj13->CreateMesh(vertices1);
	meshList.push_back(obj13);

	Mesh *obj14 = new Mesh();
	obj14->CreateMesh(vertices1);
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
    
    // Variables para cambiar los uniform del shader
    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;
    GLuint uniformView = 0;
    
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
    //Loop mientras no se cierra la ventana
    while (!mainWindow.getShouldClose()) {
        //Recibir eventos del usuario
        glfwPollEvents();
        
		glm::mat4 view = glm::lookAt(glm::vec3(mainWindow.axisX, mainWindow.axisY, mainWindow.axisZ),
			glm::vec3(mainWindow.camX, mainWindow.camY, mainWindow.camZ),
			glm::vec3(0.0f, 1.0f, 0.0f));
        //Limpiar la ventana
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderList[0].useShader(); // manda a llamar y renderizar el shader a la tarjeta gr‡fica
        
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();
        uniformView= shaderList[0].getViewLocation();
        
        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(-0.3f, -0.45f, -1.5f));
        //model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
        
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
        meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, -1.5f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, -0.45f, -1.5f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.15f, -0.45f, -1.239f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.15f, -0.45f, -1.239f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, -0.978f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.15f, -0.45f, -1.239f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model,180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[6]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.15f, -0.45f, -1.239f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[7]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, -0.978f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[8]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.15f, -0.189f, -1.41f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[9]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.15f, -0.189f, -1.41f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[10]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.189f, -1.149f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[11]->RenderMesh();
        
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.189f, -1.149f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[12]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.072f, -1.323f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		meshList[13]->RenderMesh();

        glUseProgram(0);
        mainWindow.swapBuffers();
        
    }
    return 0;
}
