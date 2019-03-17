#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include <gtc\random.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Sphere.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
Sphere sp = Sphere(0.5, 20, 20);


void CreateObject() {
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.5f,
		 0.0f, -1.0f, 0.5f,
		 0.0f, -1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//ejercicio 1 para hacer en clase, el cubo
void CrearCubo() {
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};
	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	
	Mesh *cubo1 = new Mesh();
	cubo1->CreateMesh(cubo_vertices, cubo_indices,24, 36);
	meshList.push_back(cubo1);
}

void CreateShaders() {
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main() {
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CrearCubo();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth()/mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose()) {
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		
		glm::mat4 model(1.0);
		glm::mat4 modelTemp(1.0);
		glm::mat4 modelCara(1.0);
		glm::mat4 modelByMI(1.0);
		glm::mat4 modelByMD(1.0);
		glm::mat4 modelPieI(1.0);
		glm::mat4 modelPieD(1.0);

		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		sp.init();
		sp.load();

		// cabeza
		model = glm::translate(model, glm::vec3(0.0f, 0.25f, -1.0f));
		modelCara = model = glm::rotate(model, glm::radians(mainWindow.getRotacion() * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		// cuerpo
		color = glm::vec3(0.1294f, 0.4314f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		modelTemp = model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		// ojos
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelCara, glm::vec3(-0.1, 0.05f, 0.225f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = glm::translate(modelCara, glm::vec3(0.1, 0.05f, 0.225f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		// brazo izquierdo
		color = glm::vec3(1.0f, 0.8196f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelTemp, glm::vec3(-0.625f, 0.375f, 0.0f));
		modelByMI = model = glm::rotate(model, glm::radians(mainWindow.getRotacionBrazoI() * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = glm::translate(modelByMI, glm::vec3(0.0f, -0.375f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelByMI, glm::vec3(0.0f, -0.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		// brazo derecho
		color = glm::vec3(1.0f, 0.8196f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelTemp, glm::vec3(0.625f, 0.375f, 0.0f));
		modelByMD = model = glm::rotate(model, glm::radians(mainWindow.getRotacionBrazoD() * toRadians), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = glm::translate(modelByMD, glm::vec3(0.0f, -0.375f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelByMD, glm::vec3(0.0f, -0.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		// pierna izquierda
		color = glm::vec3(1.0f, 0.8196f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelTemp, glm::vec3(-0.25f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getRotacionPiernaI() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modelPieI = model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelPieI, glm::vec3(0.0f, -0.375f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		// pierna derecha
		color = glm::vec3(1.0f, 0.8196f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelTemp, glm::vec3(0.25f, -0.5f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getRotacionPiernaD() * toRadians), glm::vec3(0.0f, 0.0f, 1.0f));
		modelPieD = model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.75f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[0]->RenderMesh();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		
		model = glm::translate(modelPieD, glm::vec3(0.0f, -0.375f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	sp.~Sphere();
	meshList[0]->~Mesh();
	return 0;
}