/*
Semestre 2019-2
Práctica 7 Texturizado
Hecho por: Ing. José Roque Román Guadarrama. Usando librería stb_image.h 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

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
#include"Mesh_texturizado.h"
#include"Shader.h"
#include "Sphere.h"
#include"Window.h"
#include "Camera.h"
#include"Texture.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
const float phi = (1 + sqrt(5.0)) / 2;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
float codo = 0.0f;

Texture T_dado_12;
Camera camera;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader_t.vert";
static const char* fShader = "shaders/shader_t.frag";
Sphere sp = Sphere(1, 20, 20);

void CreateObject() {
	unsigned int indices[] = { 
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};
	GLfloat vertices[] = {
		// X	 Y		Z		S		T
		-0.5f,	-0.5f,	0.5f,	0.0f,	0.0f,
		0.0f,	-0.5f,	0.5f,	1.0f,	0.0f,
		0.5f,	-0.5f,	0.0f,	1.0f,	1.0f,
		0.0f,	0.5f,	0.0f,	0.0f,	1.0f
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
		8, 9, 10,
		10, 11, 8,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20
	};

	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		u		v
		-0.5f, -0.5f,  0.5f,	0.5f,	0.33f, // 0
		 0.5f, -0.5f,  0.5f,	0.75f,	0.33f, // 1
		 0.5f,  0.5f,  0.5f,	0.75f,	0.66f, // 2
		-0.5f,  0.5f,  0.5f,	0.5f,	0.66f, // 3
		// back
		-0.5f, -0.5f, -0.5f,	0.0f,	0.33f, // 4
		 0.5f, -0.5f, -0.5f,	0.25f,	0.33f, // 5
		 0.5f,  0.5f, -0.5f,	0.25f,	0.66f, // 6
		-0.5f,  0.5f, -0.5f,	0.0f,	0.66f, // 7
		//right
		 0.5f, -0.5f,  0.5f,	0.75f,	0.33f, // 8
		 0.5f, -0.5f, -0.5f,	1.0f,	0.33f, // 9
		 0.5f,  0.5f, -0.5f,	1.0f,	0.66f, // 10
		 0.5f,  0.5f,  0.5f,	0.75f,	0.66f, // 11
		 //left
		-0.5f, -0.5f, -0.5f,	0.25f,	0.33f, // 12
		-0.5f, -0.5f,  0.5f,	0.5f,	0.33f, // 13
		-0.5f,  0.5f,  0.5f,	0.5f,	0.66f, // 14
		-0.5f,  0.5f, -0.5f,	0.25f,	0.66f, // 15
		//bottom
		-0.5f, -0.5f, -0.5f,	0.5f,	0.0f, // 16
		 0.5f, -0.5f, -0.5f,	0.75f,	0.0f, // 17
		 0.5f, -0.5f,  0.5f,	0.75f,	0.33f, // 18
		-0.5f, -0.5f,  0.5f,	0.5f,	0.33f, // 19
		//top
		-0.5f,  0.5f,  0.5f,	0.5f,	0.66f, // 20
		 0.5f,  0.5f,  0.5f,	0.75f,	0.66f, // 21
		 0.5f,  0.5f, -0.5f,	0.75f,	1.0f, // 22
		-0.5f,  0.5f, -0.5f,	0.5f,	1.0f, // 23
	};
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 120, 36);
	meshList.push_back(cubo);
}

void CrearDodecaedro() {
	unsigned int indices[] = {
		// 1
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		// 2
		5, 6, 7,
		5, 7, 8,
		5, 8, 9,
		// 3
		10, 11, 12,
		10, 12, 13,
		10, 13, 14,
		// 4
		15, 16, 17,
		15, 17, 18,
		15, 18, 19,
		// 5
		20, 21, 22,
		20, 22, 23,
		20, 23, 24,
		// 6
		25, 26, 27,
		25, 27, 28,
		25, 28, 29,
		// 7
		30, 31, 32,
		30, 32, 33,
		30, 33, 34,
		// 8
		35, 36, 37,
		35, 37, 38,
		35, 38, 39,
		// 9
		40, 41, 42,
		40, 42, 43,
		40, 43, 44,
		// 10
		45, 46, 47,
		45, 47, 48,
		45, 48, 49,
		// 11
		50, 51, 52,
		50, 52, 53,
		50, 53, 54,
		// 12
		55, 56, 57,
		55, 57, 58,
		55, 58, 59
	};

	GLfloat vertices[] = {
		// 1
		0.0f,			-1.0f / phi,	phi,	0.816f,	0.384f, // 0
		-1.0f,			-1.0f,			1.0f,	0.641f, 0.329f, // 1
		-1.0f / phi,	-1.0f * phi,	0.0f,	0.715f,	0.237f, // 2
		1.0f / phi,		-1.0f * phi,	0.0f,	0.922f,	0.236f, // 3
		1.0f,			-1.0f,			1.0f,	1.000f,	0.327f, // 4
		// 2
		0.0f,			-1.0f / phi,	phi,		0.360f,	1.000f, // 5
		1.0f,			-1.0f,			1.0f,		0.286f, 0.909f, // 6
		phi,			0.0f,			1.0f / phi, 0.463f,	0.854f, // 7
		1.0f,			1.0f,			1.0f,		0.641f,	0.9126f, // 8
		0.0f,			1.0f / phi,		phi,		0.568f,	1.000f, // 9
		//3
		0.0f,			-1.0f / phi,	phi,		0.643f,	0.911f, // 10
		0.0f,			1.0f / phi,		phi,		0.462f,	0.856f, // 11
		-1.0f,			1.0f,			1.0f,		0.535f,	0.763f, // 12
		-1 * phi,		0.0f,			1.0f / phi, 0.746f,	0.763f, // 13
		-1.0f,			-1.0f,			1.0f,		0.817f,	0.8545f, // 14
		// 4
		0.0f,			1.0f / phi,		phi,   0.466f,	0.673f, // 15
		1.0f,			1.0f,			1.0f,  0.285f,	0.619f, // 16
		1.0f / phi,		phi,			0.0f,  0.363f,	0.527f, // 17
		-1.0f / phi,	1 * phi,		0.0f,  0.567f,	0.528f, // 18
		-1.0f,			1.0f,			1.0f,  0.640f,	0.6185f, // 19
		// 5
		1.0f,			1.0f,			1.0f,		 0.537f,	0.763f, // 20
		phi,			0.0f,			1.0f / phi,  0.465f,	0.675f, // 21
		phi,			0.0f,			-1.0f / phi, 0.642f,	0.619f, // 22
		1.0f,			1.0f,			-1.0f,		 0.816f,	0.674f, // 23
		1.0f / phi,		phi,			0.0f,		 0.746f,	0.766f, // 24
		// 6
		phi,			0.0f,			1.0f / phi,  0.185f,	0.765f, // 25
		1.0f,			-1.0f,			1.0f,		 0.006f,	0.710f, // 26
		1.0f / phi,		-1.0f * phi,	0.0f,		 0.075f,	0.618f, // 27
		1.0f,			-1.0f,			-1.0f,		 0.288f,	0.621f, // 28
		phi,			0.0f,			-1.0f / phi, 0.359f,	0.707f, // 29
		// 7
		-1.0f * phi,	0.0f,			-1.0f / phi, 0.258f,	0.382f, // 30
		-1.0f,			1.0f,			-1.0f,		 0.182f,	0.292f, // 31
		0.0f,			1.0f / phi,		-1.0f * phi, 0.359f,	0.239f, // 32
		0.0f,			-1.0f / phi,	-1.0f * phi, 0.534f,	0.292f, // 33
		-1.0f,			-1.0f,			-1.0f,		 0.466f,	0.382f, // 34
		// 8
		-1.0f,			1.0f,			1.0f,		 0.638f,	0.148f, // 35
		-1.0f * phi,	0.0f,			1.0f / phi,	 0.462f,	0.092f, // 36
		-1.0f * phi,	0.0f,			-1.0f / phi, 0.532f,	0.000f, // 37
		-1.0f,			1.0f,			-1.0f,		 0.746f,	0.000f, // 38
		-1.0f / phi,	1 * phi,		0.0f,		 0.818f,	0.090f, // 39
		// 9
		-1.0f,			-1.0f,			1.0f,		 0.712f,	0.238f, // 40
		-1.0f * phi,	0.0f,			1.0f / phi,	 0.638f,	0.148f, // 41
		-1.0f * phi,	0.0f,			-1.0f / phi, 0.818f,	0.090f, // 42
		-1.0f,			-1.0f,			-1.0f,		 0.995f,	0.145f, // 43
		-1.0f / phi,	-1.0f * phi,	0.0f,		 0.921f,	0.239f, // 44
		// 10
		-1.0f / phi,	-1.0f * phi,	0.0f,		 0.366f,	0.529f, // 45
		-1.0f,			-1.0f,			-1.0f,		 0.180f,	0.475f, // 46
		0.0f,			-1.0f / phi,	-1.0f * phi, 0.254f,	0.381f, // 47
		1.0f,			-1.0f,			-1.0f,		 0.466f,	0.382f, // 48
		1.0f / phi,		-1.0f * phi,	0.0f,		 0.530f,	0.472f, // 49
		// 11
		phi,			0.0f,			-1.0f / phi, 0.535f,	0.470f, // 50
		1.0f,			-1.0f,			-1.0f,		 0.466f,	0.382f, // 51
		0.0f,			-1.0f / phi,	-1.0f * phi, 0.640f,	0.328f, // 52
		0.0f,			1.0f / phi,		-1.0f * phi, 0.816f,	0.383f, // 53
		1.0f,			1.0f,			-1.0f,		 0.744f,	0.472f, // 54
		// 12
		1.0f / phi,		phi,			0.0f,		 0.076f,	0.620f, // 55
		1.0f,			1.0f,			-1.0f,		 0.007f,	0.529f,	// 56
		0.0f,			1.0f / phi,		-1.0f * phi, 0.178f,	0.477f, // 57
		-1.0f,			1.0f,			-1.0f,		 0.363f,	0.528f, // 58
		-1.0f / phi,	1.0 * phi,		0.0f,		 0.288f,	0.622f, // 59
	};

	Mesh *dodecaedro = new Mesh();
	dodecaedro->CreateMesh(vertices, indices, 25 * 12, 9 * 12);
	meshList.push_back(dodecaedro);
}

void CreateShaders() {
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main() {
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CrearDodecaedro();
	CreateShaders();

	camera = Camera(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 3.0f, 0.3f);
	//para crear la textura
	T_dado_12 = Texture("Textures/dado2.tga");
	T_dado_12.LoadTexture();
	
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	GLuint uniformView = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose()) {
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;
		//Recibir eventos del usuario
		glfwPollEvents();
		
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Limpiar la ventana
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLoaction();
		uniformProjection = shaderList[0].getProjectLocation();
		uniformView = shaderList[0].getViewLocation();
		//ejercicio 1:
		glm::mat4 model(1.0); 

		model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		T_dado_12.UseTexture();
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}