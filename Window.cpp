#include "Window.h"

Window::Window() {
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;
	codo = 0.0f;
	hombro = 0.0f;
	muneca = 0.0f;
	falange_indice = 0.0f;
	falangina_indice = 0.0f;
	falangeta_indice = 0.0f;
	for (size_t i = 0; i < 1024; i++)
	{
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
	mainWindow = glfwCreateWindow(width, height, "Practica 6 Modelado Jerarquico", NULL, NULL);

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
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange() {
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange() {
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}


void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_E) {
			theWindow->hombro += 10.0;
	}
	if (key== GLFW_KEY_R) {
		theWindow->codo += 10.0;
	}
	if (key == GLFW_KEY_T) {
		theWindow->muneca += 10.0;
	}
	if (key == GLFW_KEY_Y) {
		theWindow->falange_indice += 10.0;
	}
	if (key == GLFW_KEY_U) {
		theWindow->falangina_indice += 10.0;
	}
	if (key == GLFW_KEY_I) {
		theWindow->falangeta_indice += 10.0;
	}


	
/*
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{

			theWindow->codo += 10.0;
		printf("Incremento de 10 grados en codo %f\n");
	}
	*/
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

Window::~Window() {
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}