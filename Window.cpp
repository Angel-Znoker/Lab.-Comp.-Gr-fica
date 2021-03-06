#include "Window.h"

// inicializaci�n del punto de enfoque
float Window::axisX = 0.0f;
float Window::axisY = 0.0f;
float Window::axisZ = 1.0f;

// inicializacion centro de escena
float Window::camX = 0.0f;
float Window::camY = 0.0f;
float Window::camZ = 0.0f;

// inicializacion colores
float Window::red = 0.0f;
float Window::green = 0.0f;
float Window::blue = 0.0f;

Window::Window() {
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++) { // arreglo para teclas
		keys[i] = 0;
	}
}

// crea ventana
Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;
	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

int Window::Initialise() {
	//Inicializaci�n de GLFW
	if (!glfwInit()) {
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica 3", NULL, NULL);

	if (!mainWindow) {
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana activa
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window)); // identificar que ventana current sea la principal

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE); // scape cierra ventana
	}

	// formas de detectar teclas
	
	// axisX
	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
		axisX += 0.005f;
	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
		axisX -= 0.005f;
	
	// axisY
	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
		axisY += 0.005f;
	if (key == GLFW_KEY_S && action == GLFW_REPEAT)
		axisY -= 0.005f;
	
	// axis Z
	if (key == GLFW_KEY_E && action == GLFW_REPEAT)
		axisZ += 0.005f;
	if (key == GLFW_KEY_Q && action == GLFW_REPEAT)
		axisZ -= 0.005f;

	// camX
	if (key == GLFW_KEY_J && action == GLFW_REPEAT)
		camX += 0.005f;
	if (key == GLFW_KEY_L && action == GLFW_REPEAT)
		camX -= 0.005f;

	// camY
	if (key == GLFW_KEY_I && action == GLFW_REPEAT)
		camY += 0.005f;
	if (key == GLFW_KEY_K && action == GLFW_REPEAT)
		camY -= 0.005f;

	// camZ
	if (key == GLFW_KEY_U && action == GLFW_REPEAT)
		camZ += 0.005f;
	if (key == GLFW_KEY_O && action == GLFW_REPEAT)
		camZ -= 0.005f;

	// colores

	// Red
	if (key == GLFW_KEY_R && action == GLFW_REPEAT)
		red += 0.05;
	if (key == GLFW_KEY_F && action == GLFW_REPEAT)
		red -= 0.05;

	// Green
	if (key == GLFW_KEY_T && action == GLFW_REPEAT)
		green += 0.05;
	if (key == GLFW_KEY_G && action == GLFW_REPEAT)
		green -= 0.05;

	// Blue
	if (key == GLFW_KEY_Y && action == GLFW_REPEAT)
		blue += 0.05;
	if (key == GLFW_KEY_H && action == GLFW_REPEAT)
		blue -= 0.05;
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
