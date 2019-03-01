#include "Window.h"

float Window::axisX = 0.0f;
float Window::axisY = 0.0f;
float Window::axisZ = 0.5f;

float Window::camX = 0.0f;
float Window::camY = 0.0f;
float Window::camZ = 0.0f;

Window::Window()
{
    width = 800;
    height = 600;
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
    width = windowWidth;
    height = windowHeight;
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

int Window::Initialise()
{
    //Inicializaci—n de GLFW
    if (!glfwInit())
    {
        printf("Fallo inicializar GLFW");
        glfwTerminate();
        return 1;
    }
    //Asignando variables de GLFW y propiedades de ventana
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //para solo usar el core profile de OpenGL y no tener retrocompatibilidad
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //  Crear ventana
    mainWindow = glfwCreateWindow(width, height, "Ejercicio 1 de casa", NULL, NULL);
    
    if (!mainWindow)
    {
        printf("Fallo en crearse la ventana con GLFW");
        glfwTerminate();
        return 1;
    }
    //Obtener tama–o de Buffer
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    //asignar el contexto
    glfwMakeContextCurrent(mainWindow);
    
    // Manejo de teclado y mouse
    createCallbacks();
    
    //permitir nuevas extensiones
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK)
    {
        printf("Fallo inicializacion de GLEW");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }
    
    glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
    // Asignar valores de la ventana y coordenadas
    
    //Asignar Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    //Callback para detectar que se est‡ usando la ventana
    glfwSetWindowUserPointer(mainWindow, this);
    return 0;
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, ManejaTeclado);
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window)); // identificar que ventana current sea la principal

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE); // scape cierra ventana
	}

	// formas de detectar teclas
	if (key == GLFW_KEY_D && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		axisX += 0.01f;
	}

	if (key == GLFW_KEY_A && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		axisX -= 0.01f;
	}

	if (key == GLFW_KEY_W && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		axisY += 0.01f;
	}

	if (key == GLFW_KEY_S && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		axisY -= 0.01f;
	}

	if (key == GLFW_KEY_E && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		axisZ += 0.01f;
	}

	if (key == GLFW_KEY_Q && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		axisZ -= 0.01f;
	}

	if (key == GLFW_KEY_J && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		camX += 0.01f;
	}

	if (key == GLFW_KEY_L && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		camX -= 0.01f;
	}

	if (key == GLFW_KEY_I && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		camY += 0.01f;
	}

	if (key == GLFW_KEY_K && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		camY -= 0.01f;
	}

	if (key == GLFW_KEY_U && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		camZ += 0.01f;
	}

	if (key == GLFW_KEY_O && action == GLFW_REPEAT) { // una sola tecla
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0); // que tecla es
		camZ -= 0.01f;
	}
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
