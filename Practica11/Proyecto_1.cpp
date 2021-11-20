#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(-100.0f, 2.0f, -45.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0, rotRodDer, rotBraIzq, rotBraDer, rotcuerpo;//-Para animar al personaje 
//keyframes para el carro
float	posPodX = 0.0f,
posPodY = 0.0f,
posPodZ = 0.0f,
rotPodX = 0.0f,
rotPodY = 0.0f,
rotPodZ = 0.0f,
giroTurbina = 0.0f;
float	posPodXInc = 0.0f,
posPodYInc = 0.0f,
posPodZInc = 0.0f,
rotPodXInc = 0.0f,
rotPodYInc = 0.0f,
rotPodZInc = 0.0f,
giroTurbinaInc = 0.0f;
																												   //Keyframes de Goku
//float movrotGokuX, movrotGokuX, movrotGokuY, movrotGokuZ, movGokuX, movGokuY, movGokuZ, movrotGokuXinc, movrotGokuYinc,
//movrotGokuZinc, movGokuXinc, movGokuYinc, movGokuZinc;
//Guardo la posici�n del personaje 

#define MAX_FRAMES 33 // -N�mero total de 9 frames
int i_max_steps = 190;//-Linea del tiempo de 190 unidades 
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames y -PARA varias la posici�n del personaje 
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotRodDer;// Maneja la rotacion de la rodilla derecha
	float rotInc; //Maneja el incrementodiferente al de la rodilla izquierda 
	float rotInc2;
	float rotBraIzq;
	float rotInc3;
	float rotBraDer;
	float rotInc4;
	float rotcuerpo;
	float rotInc5;
	//Variables para mover a goku
	//float movrotGokuX = 0.0f,
	//	movrotGokuY = 0.0f,
	//	movrotGokuZ = 0.0f,
	//	movGokuX = 0.0f,
	//	movGokuY = 0.0f,
	//	movGokuZ = 0.0f,
	//	//Incremeto para mover a goku
	//	movrotGokuXinc = 0.0f,
	//	movrotGokuYinc = 0.0f,
	//	movrotGokuZinc = 0.0f,
	//	movGokuXinc = 0.0f,
	//	movGokuYinc = 0.0f,
	//	movGokuZinc = 0.0f;
	//CARRO
	float posPodX;		//Variable para PosicionX
	float posPodY;		//Variable para PosicionY
	float posPodZ;		//Variable para PosicionZ
	float rotPodX;
	float rotPodY;
	float rotPodZ;
	float giroTurbina;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];//- Aqu�  le paso el numero total de frames de la figura en este caso 9
int FrameIndex =33;			//introducir datos
bool play = false;//booleano que va a indicar cuando se activa o no esta activada
int playIndex = 0;//Donde me encuento actualmente cuando inicio la animacion 

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(posX,posY,posZ),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0)
};

glm::vec3 LightP1;




void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);
	
	KeyFrame[FrameIndex].posX = posX;//- Nos permite salvar kas posiciones y las rotaciones 
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	
	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	//Para salvar al frame 
	KeyFrame[FrameIndex].rotRodDer = rotRodDer;
	KeyFrame[FrameIndex].rotBraIzq = rotBraIzq;
	KeyFrame[FrameIndex].rotBraDer = rotBraDer;
	KeyFrame[FrameIndex].rotcuerpo = rotcuerpo;

	//Animacion para goku 
	//KeyFrame[FrameIndex].movrotGokuX = movrotGokuX;
	//KeyFrame[FrameIndex].movrotGokuY = movrotGokuY;
	//KeyFrame[FrameIndex].movrotGokuZ = movrotGokuZ;
	//KeyFrame[FrameIndex].movGokuX = movGokuX;
	//KeyFrame[FrameIndex].movGokuY = movGokuY;
	//KeyFrame[FrameIndex].movGokuZ = movGokuZ;

	//KeyFrame[FrameIndex].posPodX = posPodX;
	KeyFrame[FrameIndex].posPodY = posPodY;
	KeyFrame[FrameIndex].posPodZ = posPodZ;
	KeyFrame[FrameIndex].rotPodX = rotPodX;
	KeyFrame[FrameIndex].rotPodY = rotPodY;
	KeyFrame[FrameIndex].rotPodZ = rotPodZ;
	KeyFrame[FrameIndex].giroTurbina = giroTurbina;
	

	FrameIndex++;
}

void resetElements(void)//-Resetear las posiciones 
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;//recetear la animaci�n
	rotBraIzq = KeyFrame[0].rotBraIzq;
	rotBraDer = KeyFrame[0].rotBraDer;
	rotcuerpo = KeyFrame[0].rotcuerpo;


	//Animaci�n Goku
	/*movrotGokuX = KeyFrame[0].movrotGokuX;
	movrotGokuY = KeyFrame[0].movrotGokuY;
	movrotGokuZ = KeyFrame[0].movrotGokuZ;
	movGokuX = KeyFrame[0].movGokuX;
	movGokuY = KeyFrame[0].movGokuY;
	movGokuZ = KeyFrame[0].movGokuZ;*/

	//carro
	posPodX = KeyFrame[0].posPodX;
	posPodY = KeyFrame[0].posPodY;
	posPodZ = KeyFrame[0].posPodZ;
	rotPodX = KeyFrame[0].rotPodX;
	rotPodY = KeyFrame[0].rotPodY;
	rotPodZ = KeyFrame[0].rotPodZ;
	giroTurbina = KeyFrame[0].giroTurbina;
}

void interpolation(void)//Guardo las interpolaciones 

{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps; //incrementos=posicion final- posicion inicial/ numero de pasos o l�neas 
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	
	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;

	//puntos medios entre la posicion final y posicion incial de la rotacion de la rodilla
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;
	KeyFrame[playIndex].rotInc5 = (KeyFrame[playIndex + 1].rotcuerpo - KeyFrame[playIndex].rotcuerpo) / i_max_steps;

	//Animaci�n Goku
	//KeyFrame[playIndex].movrotGokuXinc = (KeyFrame[playIndex + 1].movrotGokuX - KeyFrame[playIndex].movrotGokuX) / i_max_steps;
	//KeyFrame[playIndex].movrotGokuYinc = (KeyFrame[playIndex + 1].movrotGokuY - KeyFrame[playIndex].movrotGokuY) / i_max_steps;
	//KeyFrame[playIndex].movrotGokuZinc = (KeyFrame[playIndex + 1].movrotGokuZ - KeyFrame[playIndex].movrotGokuZ) / i_max_steps;
	//KeyFrame[playIndex].movGokuXinc = (KeyFrame[playIndex + 1].movGokuX - KeyFrame[playIndex].movGokuX) / i_max_steps;
	//KeyFrame[playIndex].movGokuYinc = (KeyFrame[playIndex + 1].movGokuY - KeyFrame[playIndex].movGokuY) / i_max_steps;
	//KeyFrame[playIndex].movGokuZinc = (KeyFrame[playIndex + 1].movGokuZ - KeyFrame[playIndex].movGokuZ) / i_max_steps;

	//Carro
	posPodXInc = (KeyFrame[playIndex + 1].posPodX - KeyFrame[playIndex].posPodX) / i_max_steps;
	posPodYInc = (KeyFrame[playIndex + 1].posPodY - KeyFrame[playIndex].posPodY) / i_max_steps;
	posPodZInc = (KeyFrame[playIndex + 1].posPodZ - KeyFrame[playIndex].posPodZ) / i_max_steps;
	rotPodXInc = (KeyFrame[playIndex + 1].rotPodX - KeyFrame[playIndex].rotPodX) / i_max_steps;
	rotPodYInc = (KeyFrame[playIndex + 1].rotPodY - KeyFrame[playIndex].rotPodY) / i_max_steps;
	rotPodZInc = (KeyFrame[playIndex + 1].rotPodZ - KeyFrame[playIndex].rotPodZ) / i_max_steps;
	giroTurbinaInc = (KeyFrame[playIndex + 1].giroTurbina - KeyFrame[playIndex].giroTurbina) / i_max_steps;

}




int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 11", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

	/*Model BotaDer((char*)"Models/Personaje/bota.obj");
	Model PiernaDer((char*)"Models/Personaje/piernader.obj");
	Model PiernaIzq((char*)"Models/Personaje/piernaizq.obj");
	Model Torso((char*)"Models/Personaje/torso.obj");
	Model BrazoDer((char*)"Models/Personaje/brazoder.obj");
	Model BrazoIzq((char*)"Models/Personaje/brazoizq.obj");*/
	Model Cabeza((char*)"Models/Personaje/cabeza.obj");
	Model Goku((char*)"Models/goku/sccc.obj");
	Model Planeta((char*)"Models/planetakio/planeta.obj");
	Model Carro((char*)"Models/carroOri/carro.obj");
	

	// Build and compile our shader program

	//Inicializaci�n de KeyFrames
	
	//for(int i=0; i<MAX_FRAMES; i++) //para hacer yo las animaciones con teclas 
	//{
	//	KeyFrame[i].posX = 0;
	//	KeyFrame[i].incX = 0;
	//	KeyFrame[i].incY = 0;
	//	KeyFrame[i].incZ = 0;
	//	KeyFrame[i].rotRodIzq = 0;
	//	KeyFrame[i].rotInc = 0;

	//	KeyFrame[i].rotRodDer = 0;//Inicializo los atributos 
	//	KeyFrame[i].rotInc2 = 0;
	//	KeyFrame[i].rotBraIzq = 0;//Inicializo los atributos 
	//	KeyFrame[i].rotInc3 = 0;
	//	KeyFrame[i].rotBraDer = 0;//Inicializo los atributos 
	//	KeyFrame[i].rotInc4 = 0;
	//	KeyFrame[i].rotcuerpo = 0;//Inicializo los atributos 
	//	KeyFrame[i].rotInc5 = 0;


	//	//KeyFrame[i].movrotGokuX = -60.0f;  //Movernos en -X para que suba  //La rotacion  /-360
	//	//KeyFrame[i].movrotGokuY = 0.0f;
	//	//KeyFrame[i].movrotGokuZ = 715.0f; //�700
	//	//KeyFrame[i].movGokuX = -90.0f;  //Mov en  -X para avanzar
	//	//KeyFrame[i].movGokuY = -35.0f;
	//	//KeyFrame[i].movGokuZ = 0.0f;
	//} //Hasta aqui descomento 

	// CARRO
	KeyFrame[0].posPodX = 0.0f;
	KeyFrame[0].posPodY = 0.0f;
	KeyFrame[0].posPodZ = 0.0f;
	KeyFrame[0].rotPodX = 0.0f;//-90
	KeyFrame[0].rotPodY = 0.0f;
	KeyFrame[0].rotPodZ = 0.0f;
	KeyFrame[0].giroTurbina = 10.0f;//1000

	KeyFrame[1].posPodX = -5.0f;//-50
	KeyFrame[1].posPodY = 30.0f;//-300
	KeyFrame[1].posPodZ = 0.0f;
	KeyFrame[1].rotPodX = -6.0f;//-60
	KeyFrame[1].rotPodY = 0.0f;
	KeyFrame[1].rotPodZ = 0.0f;
	KeyFrame[1].giroTurbina = 20.0f;//2000

	KeyFrame[2].posPodX = -10.0f;//-100
	KeyFrame[2].posPodY = 40.0f;//400
	KeyFrame[2].posPodZ = 35.0f;//350
	KeyFrame[2].rotPodX = -30.0f;
	KeyFrame[2].rotPodY = 0.0f;
	KeyFrame[2].rotPodZ = 0.0f;
	KeyFrame[2].giroTurbina = 30.0f;//3000

	KeyFrame[3].posPodX = -20.0f;//-200
	KeyFrame[3].posPodY = 40.0f;//400
	KeyFrame[3].posPodZ = 70.0f;//700
	KeyFrame[3].rotPodX = 0.0f;
	KeyFrame[3].rotPodY = 0.0f;
	KeyFrame[3].rotPodZ = 72.0f;//720
	KeyFrame[3].giroTurbina = 40.0f;//4000

	KeyFrame[4].posPodX = -20.0f;//-200
	KeyFrame[4].posPodY = 40.0f;//400
	KeyFrame[4].posPodZ = 45.0f;//1050
	KeyFrame[4].rotPodX = 0.0f;
	KeyFrame[4].rotPodY = 0.0f;
	KeyFrame[4].rotPodZ = 72.0f;//720
	KeyFrame[4].giroTurbina = 50.0f;//5000

	KeyFrame[5].posPodX = -50.0f;//-500
	KeyFrame[5].posPodY = 20.0f;//200
	KeyFrame[5].posPodZ = 40.0f;//1400
	KeyFrame[5].rotPodX = 0.0f;
	KeyFrame[5].rotPodY = -40.0f;
	KeyFrame[5].rotPodZ = 72.0f;//720
	KeyFrame[5].giroTurbina = 40.0f;//4000

	KeyFrame[6].posPodX = -80.0f;//-800
	KeyFrame[6].posPodY = 10.0f;//100
	KeyFrame[6].posPodZ = 50.0f;//1500
	KeyFrame[6].rotPodX = 0.0f;
	KeyFrame[6].rotPodY = -60.0f;
	KeyFrame[6].rotPodZ = 72.0f;//720
	KeyFrame[6].giroTurbina = 30.0f;//3000

	KeyFrame[7].posPodX = -110.0f;//-110
	KeyFrame[7].posPodY = 50.0f;
	KeyFrame[7].posPodZ = 55.0f;//1550
	KeyFrame[7].rotPodX = 0.0f;
	KeyFrame[7].rotPodY = -80.0f;
	KeyFrame[7].rotPodZ = 72.0f;//720
	KeyFrame[7].giroTurbina = 20.0f;//2000

	KeyFrame[8].posPodX = -30.0f;//-1300
	KeyFrame[8].posPodY = -10.0f;
	KeyFrame[8].posPodZ = 60.0f;//1600
	KeyFrame[8].rotPodX = 0.0f;
	KeyFrame[8].rotPodY = -75.0f;
	KeyFrame[8].rotPodZ = 72.0f;//720
	KeyFrame[8].giroTurbina = 10.0f;//1000

	KeyFrame[9].posPodX = -35.0f;//-1350
	KeyFrame[9].posPodY = -10.0f;
	KeyFrame[9].posPodZ = 60.0f;//1600
	KeyFrame[9].rotPodX = 0.0f;
	KeyFrame[9].rotPodY = -80.0f;
	KeyFrame[9].rotPodZ = 72.0f;//720
	KeyFrame[9].giroTurbina = 50.0f;//500

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1,&skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices),&skyboxVertices,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");
	
	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.937f, 0.941f, 0.619f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.1f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.52f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.1f);//0.09
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.52f);//0.032

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.1f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.52f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.1f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.52f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.1f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.52f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 52.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();


		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp



		//Carga de modelo 
		//Personaje
		view = camera.GetViewMatrix();
		glm::mat4 model(1);
		view = camera.GetViewMatrix();
		model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Planeta.Draw(lightingShader);
		
		//Carro
		//model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f + posPodX, 0.0f + posPodY, 0.0f + posPodZ));
		//model = glm::rotate(model, glm::radians(rotPodX), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotPodY), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotPodZ), glm::vec3(0.0f, 0.0f, 1.0f));
		////model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		view = camera.GetViewMatrix();
		model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Carro.Draw(lightingShader);

		//Goku
		//model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f + posPodX, -21.751f + posPodY, -10.66f + posPodZ));
		model = glm::rotate(model, glm::radians(rotPodX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPodY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPodZ), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Goku.Draw(lightingShader);
		//Animacion goku 
		
		
		//view = camera.GetViewMatrix();
		//model = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f)); //Ubicacion de la nave en el mapa
		//model = glm::translate(model, glm::vec3(movGokuX, movGokuY, movGokuZ));  //Variables con las que se va a mover la nave
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//tmp = model = glm::rotate(model, glm::radians(movrotGokuX), glm::vec3(1.0f, 0.0f, 0.0f)); //Ubicacion de la nave en rotacion X
		//tmp = model = glm::rotate(model, glm::radians(movrotGokuY), glm::vec3(0.0f, 1.0f, 0.0f));  //Ubicacion de la nave en rotacion Y
		//tmp = model = glm::rotate(model, glm::radians(movrotGokuZ), glm::vec3(0.0f, 0.0f, 1.0f));  //Ubicacion de la nave en rotacion Z
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Goku.Draw(lightingShader);

		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);  //Llamo al shader de skybox
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);//Mando a llamar la textura en forma de cubo 
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}


void animacion()
{

		//Movimiento del personaje

		if (play)// Si ya est� activa la animacion 
		{
			if (i_curr_steps >= i_max_steps) //end of animation between frames? en que parte de la animacion me encuentro
			{
				playIndex++;
				if (playIndex>FrameIndex - 2)	//end of total animation?
				{
					printf("termina anim\n");
					playIndex = 0;
					play = false;
				}
				else //Next frame interpolations
				{
					i_curr_steps = 0; //Reset counter
									  //Interpolation
					interpolation();//- Calculo de las interpolaciones
				}
			}
			else
			{
				//Draw animation
				//posX += KeyFrame[playIndex].incX; //Voy guardando cada frame y voy incrementando la posici�n 
				//posY += KeyFrame[playIndex].incY;
				//posZ += KeyFrame[playIndex].incZ;

				//rotRodIzq += KeyFrame[playIndex].rotInc;
				//rotRodDer += KeyFrame[playIndex].rotInc2;//rodilla derecha

				//rotBraIzq += KeyFrame[playIndex].rotInc3;
				//rotBraDer += KeyFrame[playIndex].rotInc4;
				//rotcuerpo += KeyFrame[playIndex].rotInc5;

				//carro
				posPodX += posPodXInc;
				posPodY += posPodYInc;
				posPodZ += posPodZInc;
				rotPodX += rotPodXInc;
				rotPodY += rotPodYInc;
				rotPodZ += rotPodZInc;

				//Animaci�n Goku
				/*movrotGokuX += movrotGokuXinc;
				movrotGokuY += movrotGokuYinc;
				movrotGokuZ += movrotGokuZinc;
				movGokuX += movGokuXinc;
				movGokuY += movGokuYinc;
				movGokuZ += movGokuZinc;*/
			/*	movrotGokuX += KeyFrame[playIndex].movrotGokuXinc;
				movrotGokuY += KeyFrame[playIndex].movrotGokuYinc;
				movrotGokuZ += KeyFrame[playIndex].movrotGokuZinc;
				movGokuX += KeyFrame[playIndex].movGokuXinc;
				movGokuY += KeyFrame[playIndex].movGokuYinc;
				movGokuZ += KeyFrame[playIndex].movGokuZinc;*/

				i_curr_steps++;
			}

		}
	}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	//if (keys[GLFW_KEY_L])
	//{
	//	if (play == false && (FrameIndex > 1))
	//	{

	//		resetElements();
	//		//First Interpolation				
	//		interpolation();

	//		play = true;
	//		playIndex = 0;
	//		i_curr_steps = 0;
	//	}
	//	else
	//	{
	//		play = false;
	//	}

	//}

	//if (keys[GLFW_KEY_K])
	//{
	//	if (FrameIndex<MAX_FRAMES)
	//	{
	//		saveFrame();
	//	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			printf("inicia Animacion \n");
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
			printf("termina anim\n");
		}
	}

	//To Save a KeyFrame
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}

	


	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	//para ver a GOKU
	//To play KeyFrame animation 
	//if (key == GLFW_KEY_P && action == GLFW_PRESS)
	//{
	//	if (play == false && (FrameIndex > 1))
	//	{
	//		printf("inicia Animacion \n");
	//		resetElements();
	//		//First Interpolation				
	//		interpolation();

	//		play = true;
	//		playIndex = 0;
	//		i_curr_steps = 0;
	//	}
	//	else
	//	{
	//		play = false;
	//		printf("termina anim\n");

	//	}
	//}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	if (keys[GLFW_KEY_1])
	{

		rot += 1;

	}

	if (keys[GLFW_KEY_2])
	{
		if (rotRodIzq<80.0f)
			rotRodIzq += 1.0f;
			
	}

	if (keys[GLFW_KEY_3])
	{
		if (rotRodIzq>-45)
			rotRodIzq -= 1.0f;
		
	}

	if (keys[GLFW_KEY_4])
	{
		if (rotRodDer < 80.0f)
			rotRodDer += 1.0f;

	}

	if (keys[GLFW_KEY_5])
	{
		if (rotRodDer > -45)
			rotRodDer -= 1.0f;

	}

	if (keys[GLFW_KEY_6])
	{
		if (rotBraIzq < 10.0f)
			rotBraIzq += 1.0f;

	}

	if (keys[GLFW_KEY_7])
	{
		if (rotBraIzq > -5)
			rotBraIzq -= 1.0f;

	}

	if (keys[GLFW_KEY_8])
	{
		if (rotBraDer < 5.0f)
			rotBraDer += 1.0f;

	}

	if (keys[GLFW_KEY_9])
	{
		if (rotBraDer > -15)
			rotBraDer -= 1.0f;

	}
	if (keys[GLFW_KEY_0])
	{
		if (rotcuerpo > -25)
			rotcuerpo -= 1.0f;

	}
	/*if (keys[GLFW_KEY_P])
	{
		if (rotcuerpo < 25)
			rotcuerpo += 1.0f;

	}*/

	

	//Mov Personaje
	if (keys[GLFW_KEY_H])
	{
		posZ += 1;
	}

	if (keys[GLFW_KEY_Y])
	{
		posZ -= 1;
	}

	if (keys[GLFW_KEY_G])
	{
		posX -= 1;
	}

	if (keys[GLFW_KEY_J])
	{
		posX += 1;
	}




	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}






}