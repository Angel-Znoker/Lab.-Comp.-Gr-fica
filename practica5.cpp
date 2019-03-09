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
//clases para dar orden y limpieza al còdigo
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


void CreateObject()
{
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
void CrearCubo()
{
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
	-0.5f, -1.0f, -0.5f,
	 0.5f, -1.0f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};

GLfloat cubo_vertices2[] = {
	// front
	-0.5f, -1.5f,  0.5f,
	 0.5f, -1.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -1.0f, -0.5f,
	 0.5f, -1.0f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};

Mesh *cubo1 = new Mesh();
cubo1->CreateMesh(cubo_vertices2, cubo_indices,24, 36);
meshList.push_back(cubo1);

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreateObject();
	CrearCubo();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	GLuint uniformColor = 0;

	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	glm::mat4 projection = glm::ortho(-1, 1, -1, 1, 1, 10);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
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

		// cuerpo
		glm::mat4 model(1.0);
		glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[0]->RenderMesh();

		// ojos
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.13f, 0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.047f, 0.06f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.13f, 0.6f, -1.0f));
		model = glm::scale(model, glm::vec3(0.047f, 0.06f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		// cabeza
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		// piernas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.125f, -0.3f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.125f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.125f, -0.3f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.125f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[1]->RenderMesh();

		// brazos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.3f, 0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.125f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, 0.25f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.125f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[1]->RenderMesh();

		// antenas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.125f, 0.8f, -1.0f));
		model = glm::scale(model, glm::vec3(0.03125f, 0.12f, 0.0625f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[1]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.125f, 0.8f, -1.0f));
		model = glm::scale(model, glm::vec3(0.03125f, 0.12f, 0.0625f));
		model = glm::rotate(model, 315 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		meshList[1]->RenderMesh();

		// hombros y manos
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, 0.33f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.3f, 0.33f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, 0.04f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.3f, 0.04f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		// pies
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.125f, -0.52f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.125f, -0.52f, -1.0f));
		model = glm::scale(model, glm::vec3(0.125f, 0.15f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		// puntas de antenas
		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.13f, 0.839f, -1.0f));
		model = glm::scale(model, glm::vec3(0.047f, 0.09f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		model = glm::mat4(1.0);
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.13f, 0.839f, -1.0f));
		model = glm::scale(model, glm::vec3(0.047f, 0.09f, 0.5f));
		sp.init();
		sp.load();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		sp.render();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	sp.~Sphere();
	meshList[0]->~Mesh();
	meshList[1]->~Mesh();
	return 0;
}