#include <iostream>
#include <cmath>
// luissergiov@fi-b.unam.mx
//https://es.coursera.org

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
float rot2 = 0.0f;
bool rotarn1 = false;
bool rotarn2 = false;
bool rotarp1 = false;
bool rotarp2 = false;
float rot3 = 0.0f;
bool puertar = false;
bool puertar2 = false;


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
bool active;



// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z, rotRodIzq = 0, rotRodDer, rotBraIzq, rotBraDer, rotcuerpo;//-Para animar al personaje 
//keyframes para Goku
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

//Animación para bills
float movRotBX = 0.0f,
movRotBY = 0.0f,
movRotBZ = 0.0f,
movBX = 0.0f,
movBY = 0.0f,
movBZ = 0.0f,
movRotBXinc = 0.0f,
movRotBYinc = 0.0f,
movRotBZinc = 0.0f,
movBXinc = 0.0f,
movBYinc = 0.0f,
movBZinc = 0.0f;

//animacion para carro
float	posCarX = 0.0f,
posCarY = 0.0f,
posCarZ = 0.0f,
rotCarX = 0.0f,
rotCarY = 0.0f,
rotCarZ = 0.0f;

float	posCarXInc = 0.0f,
posCarYInc = 0.0f,
posCarZInc = 0.0f,
rotCarXInc = 0.0f,
rotCarYInc = 0.0f,
rotCarZInc = 0.0f;

//Animacion de Goku en la nube 

float	posGnubeX = 0.0f,
posGnubeY = 0.0f,
posGnubeZ = 0.0f,
rotGnubeX = 0.0f,
rotGnubeY = 0.0f,
rotGnubeZ = 0.0f;

float	posGnubeXInc = 0.0f,
posGnubeYInc = 0.0f,
posGnubeZInc = 0.0f,
rotGnubeXInc = 0.0f,
rotGnubeYInc = 0.0f,
rotGnubeZInc = 0.0f;


bool anim = false;
float rotar = 0.0;
float posicion = 0.0;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
float movx = 0.0f;
float movz = 0.0f;
float rotvehiculo = 0.0;
																												   //Keyframes de Goku
//float movrotGokuX, movrotGokuX, movrotGokuY, movrotGokuZ, movGokuX, movGokuY, movGokuZ, movrotGokuXinc, movrotGokuYinc,
//movrotGokuZinc, movGokuXinc, movGokuYinc, movGokuZinc;
//Guardo la posición del personaje 

#define MAX_FRAMES 33 // -Número total de 9 frames
int i_max_steps = 190;//-Linea del tiempo de 190 unidades 
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames y -PARA varias la posición del personaje 
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
	//Goku
	float posPodX;		//Variable para PosicionX
	float posPodY;		//Variable para PosicionY
	float posPodZ;		//Variable para PosicionZ
	float rotPodX;
	float rotPodY;
	float rotPodZ;
	float giroTurbina;

	//Bills
	float movRotBX,
		movRotBY,
		movRotBZ,
		movBX,
		movBY,
		movBZ;

	//Carro
	float posCarX;		//Variable para PosicionX
	float posCarY;		//Variable para PosicionY
	float posCarZ;		//Variable para PosicionZ
	float rotCarX;
	float rotCarY;
	float rotCarZ;

	//Goku Nube 
	//Carro
	float posGnubeX;		//Variable para PosicionX
	float posGnubeY;		//Variable para PosicionY
	float posGnubeZ;		//Variable para PosicionZ
	float rotGnubeX;
	float rotGnubeY;
	float rotGnubeZ;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];//- Aquí  le paso el numero total de frames de la figura en este caso 9
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

	KeyFrame[FrameIndex].posPodX = posPodX;
	KeyFrame[FrameIndex].posPodY = posPodY;
	KeyFrame[FrameIndex].posPodZ = posPodZ;
	KeyFrame[FrameIndex].rotPodX = rotPodX;
	KeyFrame[FrameIndex].rotPodY = rotPodY;
	KeyFrame[FrameIndex].rotPodZ = rotPodZ;
	KeyFrame[FrameIndex].giroTurbina = giroTurbina;

	//Bills
	KeyFrame[FrameIndex].movRotBX = movRotBX;
	KeyFrame[FrameIndex].movRotBY = movRotBY;
	KeyFrame[FrameIndex].movRotBZ = movRotBZ;
	KeyFrame[FrameIndex].movBX = movBX;
	KeyFrame[FrameIndex].movBY = movBY;
	KeyFrame[FrameIndex].movBZ = movBZ;

	//Carro
	KeyFrame[FrameIndex].posCarX = posCarX;
	KeyFrame[FrameIndex].posCarY = posCarY;
	KeyFrame[FrameIndex].posCarZ = posCarZ;
	KeyFrame[FrameIndex].rotCarX = rotCarX;
	KeyFrame[FrameIndex].rotCarY = rotCarY;
	KeyFrame[FrameIndex].rotCarZ = rotCarZ;
	
	//Goku nube 
	KeyFrame[FrameIndex].posGnubeX = posGnubeX;
	KeyFrame[FrameIndex].posGnubeY = posGnubeY;
	KeyFrame[FrameIndex].posGnubeZ = posGnubeZ;
	KeyFrame[FrameIndex].rotGnubeX = rotGnubeX;
	KeyFrame[FrameIndex].rotGnubeY = rotGnubeY;
	KeyFrame[FrameIndex].rotGnubeZ = rotGnubeZ;

	FrameIndex++;
}

void resetElements(void)//-Resetear las posiciones 
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotRodDer = KeyFrame[0].rotRodDer;//recetear la animación
	rotBraIzq = KeyFrame[0].rotBraIzq;
	rotBraDer = KeyFrame[0].rotBraDer;
	rotcuerpo = KeyFrame[0].rotcuerpo;


	//Animación Goku
	/*movrotGokuX = KeyFrame[0].movrotGokuX;
	movrotGokuY = KeyFrame[0].movrotGokuY;
	movrotGokuZ = KeyFrame[0].movrotGokuZ;
	movGokuX = KeyFrame[0].movGokuX;
	movGokuY = KeyFrame[0].movGokuY;
	movGokuZ = KeyFrame[0].movGokuZ;*/

	//Goku
	posPodX = KeyFrame[0].posPodX;
	posPodY = KeyFrame[0].posPodY;
	posPodZ = KeyFrame[0].posPodZ;
	rotPodX = KeyFrame[0].rotPodX;
	rotPodY = KeyFrame[0].rotPodY;
	rotPodZ = KeyFrame[0].rotPodZ;
	giroTurbina = KeyFrame[0].giroTurbina;

	//Bills
	movRotBX = KeyFrame[0].movRotBX;
	movRotBY = KeyFrame[0].movRotBY;
	movRotBZ = KeyFrame[0].movRotBZ;
	movBX = KeyFrame[0].movBX;
	movBY = KeyFrame[0].movBY;
	movBZ = KeyFrame[0].movBZ;

	//Carro
	posCarX = KeyFrame[0].posCarX;
	posCarY = KeyFrame[0].posCarY;
	posCarZ = KeyFrame[0].posCarZ;
	rotCarX = KeyFrame[0].rotCarX;
	rotCarY = KeyFrame[0].rotCarY;
	rotCarZ = KeyFrame[0].rotCarZ;

	//goku nube
	//Carro
	posGnubeX = KeyFrame[0].posGnubeX;
	posGnubeY = KeyFrame[0].posGnubeY;
	posGnubeZ = KeyFrame[0].posGnubeZ;
	rotGnubeX = KeyFrame[0].rotGnubeX;
	rotGnubeY = KeyFrame[0].rotGnubeY;
	rotGnubeZ = KeyFrame[0].rotGnubeZ;

}

void interpolation(void)//Guardo las interpolaciones 

{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps; //incrementos=posicion final- posicion inicial/ numero de pasos o líneas 
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	
	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;

	//puntos medios entre la posicion final y posicion incial de la rotacion de la rodilla
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;
	KeyFrame[playIndex].rotInc5 = (KeyFrame[playIndex + 1].rotcuerpo - KeyFrame[playIndex].rotcuerpo) / i_max_steps;

	//Animación Goku
	//KeyFrame[playIndex].movrotGokuXinc = (KeyFrame[playIndex + 1].movrotGokuX - KeyFrame[playIndex].movrotGokuX) / i_max_steps;
	//KeyFrame[playIndex].movrotGokuYinc = (KeyFrame[playIndex + 1].movrotGokuY - KeyFrame[playIndex].movrotGokuY) / i_max_steps;
	//KeyFrame[playIndex].movrotGokuZinc = (KeyFrame[playIndex + 1].movrotGokuZ - KeyFrame[playIndex].movrotGokuZ) / i_max_steps;
	//KeyFrame[playIndex].movGokuXinc = (KeyFrame[playIndex + 1].movGokuX - KeyFrame[playIndex].movGokuX) / i_max_steps;
	//KeyFrame[playIndex].movGokuYinc = (KeyFrame[playIndex + 1].movGokuY - KeyFrame[playIndex].movGokuY) / i_max_steps;
	//KeyFrame[playIndex].movGokuZinc = (KeyFrame[playIndex + 1].movGokuZ - KeyFrame[playIndex].movGokuZ) / i_max_steps;
	
	//Goku
	posPodXInc = (KeyFrame[playIndex + 1].posPodX - KeyFrame[playIndex].posPodX) / i_max_steps;
	posPodYInc = (KeyFrame[playIndex + 1].posPodY - KeyFrame[playIndex].posPodY) / i_max_steps;
	posPodZInc = (KeyFrame[playIndex + 1].posPodZ - KeyFrame[playIndex].posPodZ) / i_max_steps;
	rotPodXInc = (KeyFrame[playIndex + 1].rotPodX - KeyFrame[playIndex].rotPodX) / i_max_steps;
	rotPodYInc = (KeyFrame[playIndex + 1].rotPodY - KeyFrame[playIndex].rotPodY) / i_max_steps;
	rotPodZInc = (KeyFrame[playIndex + 1].rotPodZ - KeyFrame[playIndex].rotPodZ) / i_max_steps;
	giroTurbinaInc = (KeyFrame[playIndex + 1].giroTurbina - KeyFrame[playIndex].giroTurbina) / i_max_steps;

	//Bills
	movRotBXinc = (KeyFrame[playIndex + 1].movRotBX - KeyFrame[playIndex].movRotBX) / i_max_steps;
	movRotBYinc = (KeyFrame[playIndex + 1].movRotBY - KeyFrame[playIndex].movRotBY) / i_max_steps;
	movRotBZinc = (KeyFrame[playIndex + 1].movRotBZ - KeyFrame[playIndex].movRotBZ) / i_max_steps;
	movBXinc = (KeyFrame[playIndex + 1].movBX - KeyFrame[playIndex].movBX) / i_max_steps;
	movBYinc = (KeyFrame[playIndex + 1].movBY - KeyFrame[playIndex].movBY) / i_max_steps;
	movBZinc = (KeyFrame[playIndex + 1].movBZ - KeyFrame[playIndex].movBZ) / i_max_steps;

	//carro
	posCarXInc = (KeyFrame[playIndex + 1].posCarX - KeyFrame[playIndex].posCarX) / i_max_steps;
	posCarYInc = (KeyFrame[playIndex + 1].posCarY - KeyFrame[playIndex].posCarY) / i_max_steps;
	posCarZInc = (KeyFrame[playIndex + 1].posCarZ - KeyFrame[playIndex].posCarZ) / i_max_steps;
	rotCarXInc = (KeyFrame[playIndex + 1].rotCarX - KeyFrame[playIndex].rotCarX) / i_max_steps;
	rotCarYInc = (KeyFrame[playIndex + 1].rotCarY - KeyFrame[playIndex].rotCarY) / i_max_steps;
	rotCarZInc = (KeyFrame[playIndex + 1].rotCarZ - KeyFrame[playIndex].rotCarZ) / i_max_steps;

	// Goku nube 
	posGnubeXInc = (KeyFrame[playIndex + 1].posGnubeX - KeyFrame[playIndex].posGnubeX) / i_max_steps;
	posGnubeYInc = (KeyFrame[playIndex + 1].posGnubeY - KeyFrame[playIndex].posGnubeY) / i_max_steps;
	posGnubeZInc = (KeyFrame[playIndex + 1].posGnubeZ - KeyFrame[playIndex].posGnubeZ) / i_max_steps;
	rotGnubeXInc = (KeyFrame[playIndex + 1].rotGnubeX - KeyFrame[playIndex].rotGnubeX) / i_max_steps;
	rotGnubeYInc = (KeyFrame[playIndex + 1].rotGnubeY - KeyFrame[playIndex].rotGnubeY) / i_max_steps;
	rotGnubeZInc = (KeyFrame[playIndex + 1].rotGnubeZ - KeyFrame[playIndex].rotGnubeZ) / i_max_steps;
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
	//Model Planeta((char*)"Models/planetakio/planeta.obj");
	Model Carro((char*)"Models/carroOri/carro.obj");
	//Model LlantaIzq((char*)"Models/carroOri/llantai.obj");
	//Model LlantaDer((char*)"Models/carroOri/llantad.obj");
	Model Bills((char*)"Models/bills/bills1.obj");
	Model Nubes((char*)"Models/Nubes/nubes.obj");
	Model Puerta((char*)"Models/PuertaGa/puertag.obj");
	Model Kaio((char*)"Models/kaio/kaioh.obj");
	Model Planetakaio((char*)"Models/prueba/planetakaio.obj");
	Model Planetagoku((char*)"Models/casaG/casag.obj");
	Model bulma((char*)"Models/bulma/bulma.obj");
	Model gokunube((char*)"Models/gokunube/goku.obj");
	Model PuertaIz((char*)"Models/Pizq/puertaIzq.obj");
	Model PuertaDe((char*)"Models/Pder/puertaDer.obj");

	// Build and compile our shader program

	//Inicialización de KeyFrames
	
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
	//	//KeyFrame[i].movrotGokuZ = 715.0f; //¿700
	//	//KeyFrame[i].movGokuX = -90.0f;  //Mov en  -X para avanzar
	//	//KeyFrame[i].movGokuY = -35.0f;
	//	//KeyFrame[i].movGokuZ = 0.0f;
	//} //Hasta aqui descomento 

	// goku
	KeyFrame[0].posPodX = 0.0f;
	KeyFrame[0].posPodY = 0.0f;
	KeyFrame[0].posPodZ = 0.0f;
	KeyFrame[0].rotPodX = 0.0f;//-90
	KeyFrame[0].rotPodY = 0.0f;
	KeyFrame[0].rotPodZ = 0.0f;
	KeyFrame[0].giroTurbina = 10.0f;//1000

	KeyFrame[1].posPodX = -5.0f;//-50
	KeyFrame[1].posPodY = 20.0f;//-300
	KeyFrame[1].posPodZ = 0.0f;
	KeyFrame[1].rotPodX = -6.0f;//-60
	KeyFrame[1].rotPodY = 0.0f;
	KeyFrame[1].rotPodZ = 0.0f;
	KeyFrame[1].giroTurbina = 20.0f;//2000

	KeyFrame[2].posPodX = -10.0f;//-100
	KeyFrame[2].posPodY = 30.0f;//400
	KeyFrame[2].posPodZ = 25.0f;//350
	KeyFrame[2].rotPodX = -20.0f;
	KeyFrame[2].rotPodY = 0.0f;
	KeyFrame[2].rotPodZ = 0.0f;
	KeyFrame[2].giroTurbina = 30.0f;//3000

	KeyFrame[3].posPodX = -10.0f;//-200
	KeyFrame[3].posPodY = 20.0f;//400
	KeyFrame[3].posPodZ = 70.0f;//700
	KeyFrame[3].rotPodX = 0.0f;
	KeyFrame[3].rotPodY = 0.0f;
	KeyFrame[3].rotPodZ = 42.0f;//720
	KeyFrame[3].giroTurbina = 40.0f;//4000

	KeyFrame[4].posPodX = -20.0f;//-200
	KeyFrame[4].posPodY = 30.0f;//400
	KeyFrame[4].posPodZ = 35.0f;//1050
	KeyFrame[4].rotPodX = 0.0f;
	KeyFrame[4].rotPodY = 0.0f;
	KeyFrame[4].rotPodZ = 42.0f;//720
	KeyFrame[4].giroTurbina = 50.0f;//5000

	KeyFrame[5].posPodX = -40.0f;//-500
	KeyFrame[5].posPodY = 10.0f;//200
	KeyFrame[5].posPodZ = 30.0f;//1400
	KeyFrame[5].rotPodX = 0.0f;
	KeyFrame[5].rotPodY = -40.0f;
	KeyFrame[5].rotPodZ = 72.0f;//720
	KeyFrame[5].giroTurbina = 40.0f;//4000

	KeyFrame[6].posPodX = -40.0f;//-800
	KeyFrame[6].posPodY = 10.0f;//100
	KeyFrame[6].posPodZ = 15.0f;//1500
	KeyFrame[6].rotPodX = 0.0f;
	KeyFrame[6].rotPodY = -30.0f;
	KeyFrame[6].rotPodZ = 72.0f;//720
	KeyFrame[6].giroTurbina = 30.0f;//3000

	KeyFrame[7].posPodX = -55.0f;//-110
	KeyFrame[7].posPodY = 20.0f;
	KeyFrame[7].posPodZ = 25.0f;//1550
	KeyFrame[7].rotPodX = 0.0f;
	KeyFrame[7].rotPodY = -40.0f;
	KeyFrame[7].rotPodZ = 72.0f;//720
	KeyFrame[7].giroTurbina = 20.0f;//2000
	//
	KeyFrame[8].posPodX = -55.0f;//-800
	KeyFrame[8].posPodY = 10.0f;//100
	KeyFrame[8].posPodZ = 25.0f;//1500
	KeyFrame[8].rotPodX = 0.0f;
	KeyFrame[8].rotPodY = -30.0f;
	KeyFrame[8].rotPodZ = 72.0f;//720
	KeyFrame[8].giroTurbina = 30.0f;//3000
	//
	KeyFrame[9].posPodX = -50.0f;//-500
	KeyFrame[9].posPodY = 10.0f;//200
	KeyFrame[9].posPodZ = 20.0f;//1400
	KeyFrame[9].rotPodX = 0.0f;
	KeyFrame[9].rotPodY = -20.0f;
	KeyFrame[9].rotPodZ = 72.0f;//720
	KeyFrame[9].giroTurbina = 40.0f;//4000


	KeyFrame[10].posPodX = -30.0f;//-1300
	KeyFrame[10].posPodY = -10.0f;
	KeyFrame[10].posPodZ = 30.0f;//1600
	KeyFrame[10].rotPodX = 0.0f;
	KeyFrame[10].rotPodY = -35.0f;
	KeyFrame[10].rotPodZ = 72.0f;//720
	KeyFrame[10].giroTurbina = 10.0f;//1000

	KeyFrame[11].posPodX = -35.0f;//-1350
	KeyFrame[11].posPodY = -10.0f;
	KeyFrame[11].posPodZ = 30.0f;//1600
	KeyFrame[11].rotPodX = 0.0f;
	KeyFrame[11].rotPodY = -40.0f;
	KeyFrame[11].rotPodZ = 72.0f;//720
	KeyFrame[11].giroTurbina = 50.0f;//500

	//BILLS
	KeyFrame[0].movRotBX = 0.0f;  //Movernos en -X para que suba
	KeyFrame[0].movRotBY = 0.0f;
	KeyFrame[0].movRotBZ = 0.0f;
	KeyFrame[0].movBX = 0.0f;  //Mov en  -X para avanzar
	KeyFrame[0].movBY = 0.0f;
	KeyFrame[0].movBZ = 0.0f;

	KeyFrame[1].movRotBX = 0.0f;  //Movernos en -X para que suba
	KeyFrame[1].movRotBY = 0.0f;
	KeyFrame[1].movRotBZ = 0.0f;
	KeyFrame[1].movBX = 20.0f;  //Mov en  -X para avanzar
	KeyFrame[1].movBY = 0.0f;
	KeyFrame[1].movBZ = 0.0f;

	KeyFrame[2].movRotBX = 24.0f;  //Movernos en -X para que suba //-100
	KeyFrame[2].movRotBY = 0.0f;
	KeyFrame[2].movRotBZ = 0.0f;
	KeyFrame[2].movBX = 20.0f;  //Mov en  -X para avanzar
	KeyFrame[2].movBY = 0.0f;
	KeyFrame[2].movBZ = 0.0f;

	KeyFrame[3].movRotBX = 25.0f;  //Movernos en -X para que suba	//-134
	KeyFrame[3].movRotBY = 0.0f;
	KeyFrame[3].movRotBZ = 0.0f;
	KeyFrame[3].movBX = 30.0f;  //Mov en  -X para avanzar
	KeyFrame[3].movBY = 20.0f;
	KeyFrame[3].movBZ = 0.0f;

	KeyFrame[4].movRotBX = -22.0f;  //Movernos en -X para que suba  //-80.0
	KeyFrame[4].movRotBY = 0.0f;
	KeyFrame[4].movRotBZ = 0.0f;
	KeyFrame[4].movBX = -30.0f;  //Mov en  -X para avanzar
	KeyFrame[4].movBY = 20.0f;  //
	KeyFrame[4].movBZ = 0.0f;

	KeyFrame[5].movRotBX = -23.0f;  //Movernos en -X para que suba  //-80.0
	KeyFrame[5].movRotBY = 0.0f;
	KeyFrame[5].movRotBZ = 0.0f;
	KeyFrame[5].movBX = -20.0f;  //Mov en  -X para avanzar
	KeyFrame[5].movBY = 30.0f;  //Empezamos a descender
	KeyFrame[5].movBZ = 0.0f;

	KeyFrame[6].movRotBX = -26.0f;  //Movernos en -X para que suba
	KeyFrame[6].movRotBY = 0.0f;
	KeyFrame[6].movRotBZ = 00.0f;
	KeyFrame[6].movBX = -20.0f;  //Mov en  -X para avanzar
	KeyFrame[6].movBY = 20.0f;
	KeyFrame[6].movBZ = 0.0f;

	KeyFrame[7].movRotBX = -29.0f;  //Movernos en -X para que suba
	KeyFrame[7].movRotBY = 0.0f;
	KeyFrame[7].movRotBZ = 00.0f;
	KeyFrame[7].movBX = -20.0f;  //Mov en  -X para avanzar
	KeyFrame[7].movBY = 20.0f;
	KeyFrame[7].movBZ = 0.0f;

	KeyFrame[8].movRotBX = -36.0f;  //Movernos en -X para que suba  //La rotacion 
	KeyFrame[8].movRotBY = 0.0f;
	KeyFrame[8].movRotBZ = 0.0f;
	KeyFrame[8].movBX = -20.0f;  //Mov en  -X para avanzar
	KeyFrame[8].movBY = -10.0f;
	KeyFrame[8].movBZ = 0.0f;

	KeyFrame[9].movRotBX = -38.0f;  //Movernos en -X para que suba  //La rotacion  /-360
	KeyFrame[9].movRotBY = 0.0f;
	KeyFrame[9].movRotBZ = 20.0f;
	KeyFrame[9].movBX = -30.0f;  //Mov en  -X para avanzar
	KeyFrame[9].movBY = -25.0f;
	KeyFrame[9].movBZ = 0.0f;

	KeyFrame[10].movRotBX = -40.0f;  //Movernos en -X para que suba  //La rotacion  /-360
	KeyFrame[10].movRotBY = 0.0f;
	KeyFrame[10].movRotBZ = 20.0f;
	KeyFrame[10].movBX = -20.0f;  //Mov en  -X para avanzar
	KeyFrame[10].movBY = -10.0f;
	KeyFrame[10].movBZ = 0.0f;

	KeyFrame[11].movRotBX = -36.0f;  //Movernos en -X para que suba  //La rotacion  /360
	KeyFrame[11].movRotBY = 0.0f;
	KeyFrame[11].movRotBZ = 20.0f;
	KeyFrame[11].movBX = -30.0f;  //Mov en  -X para avanzar
	KeyFrame[11].movBY = -25.0f;
	KeyFrame[11].movBZ = 0.0f;


	//Carro
	KeyFrame[0].posCarX = 0.0f;
	KeyFrame[0].posCarY = 0.0f;
	KeyFrame[0].posCarZ = 0.0f;
	KeyFrame[0].rotCarX = 0.0f;//-90
	KeyFrame[0].rotCarY = 0.0f;
	KeyFrame[0].rotCarZ = 0.0f;

	KeyFrame[1].posCarX = 0.0f;
	KeyFrame[1].posCarY = 0.0f;
	KeyFrame[1].posCarZ = 0.0f;
	KeyFrame[1].rotCarX = 0.0f;//-90
	KeyFrame[1].rotCarY = 0.0f;
	KeyFrame[1].rotCarZ = 72.386f;


	KeyFrame[2].posCarX = 1.0f;
	KeyFrame[2].posCarY = 0.0f;
	KeyFrame[2].posCarZ = 0.0f;
	KeyFrame[2].rotCarX = -85.054f;//-45.054
	KeyFrame[2].rotCarY = 25.07f;
	KeyFrame[2].rotCarZ = 73.787f;

	//KeyFrame[2].posCarX = 0.0f;
	//KeyFrame[2].posCarY = 0.0f;
	//KeyFrame[2].posCarZ = 0.0f;
	//KeyFrame[2].rotCarX = 0.0f;//-90
	//KeyFrame[2].rotCarY = 0.0f;
	//KeyFrame[2].rotCarZ = 24.536f;

	//KeyFrame[3].posCarX = 0.0f;
	//KeyFrame[3].posCarY = 0.0f;
	//KeyFrame[3].posCarZ = 0.0f;
	//KeyFrame[3].rotCarX = 0.0f;//-90
	//KeyFrame[3].rotCarY = 0.0f;
	//KeyFrame[3].rotCarZ = 61.053f;

	//KeyFrame[4].posCarX = 0.0f;
	//KeyFrame[4].posCarY = 0.0f;
	//KeyFrame[4].posCarZ = 0.0f;
	//KeyFrame[4].rotCarX = 0.0f;//-90
	//KeyFrame[4].rotCarY = 17.36f;
	//KeyFrame[4].rotCarZ = 61.053f;

	//KeyFrame[5].posCarX = 0.0f;
	//KeyFrame[5].posCarY = 0.0f;
	//KeyFrame[5].posCarZ = 0.0f;
	//KeyFrame[5].rotCarX = 0.0f;//-90
	//KeyFrame[5].rotCarY = 55.809f;
	//KeyFrame[5].rotCarZ = 61.053f;

	//KeyFrame[6].posCarX = 0.0f;
	//KeyFrame[6].posCarY = 0.0f;
	//KeyFrame[6].posCarZ = 0.0f;
	//KeyFrame[6].rotCarX = 0.0f;//-90
	//KeyFrame[6].rotCarY = 160.41f;
	//KeyFrame[6].rotCarZ = 61.053f;

	//KeyFrame[4].posCarX = 0.0f;
	//KeyFrame[4].posCarY = -11.652f;
	//KeyFrame[4].posCarZ = 0.0f;
	//KeyFrame[4].rotCarX = 0.0f;//-90
	//KeyFrame[4].rotCarY = 234.872f;
	//KeyFrame[4].rotCarZ = 61.053f;

	//KeyFrame[4].posCarX = 0.0f;
	//KeyFrame[4].posCarY = 0.0f;
	//KeyFrame[4].posCarZ = 0.0f;
	//KeyFrame[4].rotCarX = 0.0f;//-90
	//KeyFrame[4].rotCarY = 53.488f;
	//KeyFrame[4].rotCarZ = 0.0f;
	
	//KeyFrame[4].posCarX = 0.0f;
	//KeyFrame[4].posCarY = 0.0f;
	//KeyFrame[4].posCarZ = 0.0f;
	//KeyFrame[4].rotCarX = -6.15f;//-90
	//KeyFrame[4].rotCarY = 25.518f;
	//KeyFrame[4].rotCarZ = 36.573f;

	//KeyFrame[5].posCarX = 0.0f;
	//KeyFrame[5].posCarY = 0.0f;
	//KeyFrame[5].posCarZ = 0.0f;
	//KeyFrame[5].rotCarX = -7.21f;//43.603
	//KeyFrame[5].rotCarY = 39.613f;//
	//KeyFrame[5].rotCarZ = 34.619f;

	//KeyFrame[5].posCarX = 0.0f;
	//KeyFrame[5].posCarY = -1.286f;
	//KeyFrame[5].posCarZ = 0.0f;
	//KeyFrame[5].rotCarX = 12.085f;//43.603
	//KeyFrame[5].rotCarY = 55.672f;//
	//KeyFrame[5].rotCarZ = 60.475f;

	//Goku nube 
	KeyFrame[0].posGnubeX = 0.0f;
	KeyFrame[0].posGnubeY = 0.0f;
	KeyFrame[0].posGnubeZ = 0.0f;
	KeyFrame[0].rotGnubeX = 0.0f;//-90
	KeyFrame[0].rotGnubeY = 0.0f;
	KeyFrame[0].rotGnubeZ = 0.0f;

	KeyFrame[1].posGnubeX = 0.0f;
	KeyFrame[1].posGnubeY = 0.0f;
	KeyFrame[1].posGnubeZ = 4.591f;
	KeyFrame[1].rotGnubeX = 0.0f;//-90
	KeyFrame[1].rotGnubeY = 0.0f;
	KeyFrame[1].rotGnubeZ = 0.0f;


	KeyFrame[2].posGnubeX = 0.0f;
	KeyFrame[2].posGnubeY = 0.0f;
	KeyFrame[2].posGnubeZ = 15.0f;
	KeyFrame[2].rotGnubeX = 0.0f;//-45.054
	KeyFrame[2].rotGnubeY = 19.736f;
	KeyFrame[2].rotGnubeZ = 0.0f;

	KeyFrame[3].posGnubeX = 0.0f;
	KeyFrame[3].posGnubeY = 0.0f;
	KeyFrame[3].posGnubeZ = 15.0f;
	KeyFrame[3].rotGnubeX = -6.291f;//-45.054
	KeyFrame[3].rotGnubeY = 74.48f;
	KeyFrame[3].rotGnubeZ = -13.642f;

	KeyFrame[4].posGnubeX = 15.0f;
	KeyFrame[4].posGnubeY = 0.0f;
	KeyFrame[4].posGnubeZ = 15.0f;
	KeyFrame[4].rotGnubeX = -6.291f;//-45.054
	KeyFrame[4].rotGnubeY = 74.48f;
	KeyFrame[4].rotGnubeZ = -13.642f;

	KeyFrame[5].posGnubeX = 15.0f;
	KeyFrame[5].posGnubeY = 0.0f;
	KeyFrame[5].posGnubeZ = 15.0f;
	KeyFrame[5].rotGnubeX = -6.291f;//-45.054
	KeyFrame[5].rotGnubeY = 120.00f;
	KeyFrame[5].rotGnubeZ = -13.642f;

	KeyFrame[6].posGnubeX = 19.0f;
	KeyFrame[6].posGnubeY = 0.0f;
	KeyFrame[6].posGnubeZ = 15.00f;
	KeyFrame[6].rotGnubeX = -6.291f;//-45.054
	KeyFrame[6].rotGnubeY = 120.00f;
	KeyFrame[6].rotGnubeZ = -13.642f;

	KeyFrame[7].posGnubeX = 19.0f;
	KeyFrame[7].posGnubeY = 0.0f;
	KeyFrame[7].posGnubeZ = -16.5f;
	KeyFrame[7].rotGnubeX = -6.291f;//-45.054
	KeyFrame[7].rotGnubeY = 180.00f;
	KeyFrame[7].rotGnubeZ = -13.642f;

	KeyFrame[8].posGnubeX = -16.0f;
	KeyFrame[8].posGnubeY = 0.0f;
	KeyFrame[8].posGnubeZ = -16.5f;
	KeyFrame[8].rotGnubeX = -6.291f;//-45.054
	KeyFrame[8].rotGnubeY = 270.00f;
	KeyFrame[8].rotGnubeZ = -13.642f;

	KeyFrame[9].posGnubeX = -16.0f;
	KeyFrame[9].posGnubeY = 0.0f;
	KeyFrame[9].posGnubeZ = -16.5f;
	KeyFrame[9].rotGnubeX = -6.291f;//-45.054
	KeyFrame[9].rotGnubeY = 360.00f;
	KeyFrame[9].rotGnubeZ = -13.642f;

	KeyFrame[10].posGnubeX = -16.0f;
	KeyFrame[10].posGnubeY = 0.0f;
	KeyFrame[10].posGnubeZ = 8.831f;
	KeyFrame[10].rotGnubeX = -6.291f;//-45.054
	KeyFrame[10].rotGnubeY = 360.00f;
	KeyFrame[10].rotGnubeZ = -13.642f;

	KeyFrame[11].posGnubeX = -16.0f;
	KeyFrame[11].posGnubeY = 0.0f;
	KeyFrame[11].posGnubeZ = 8.831f;
	KeyFrame[11].rotGnubeX = -6.291f;//-45.054
	KeyFrame[11].rotGnubeY = 450.00f;
	KeyFrame[11].rotGnubeZ = -13.642f;

	KeyFrame[12].posGnubeX = 0.0f;
	KeyFrame[12].posGnubeY = 0.0f;
	KeyFrame[12].posGnubeZ = 8.831f;
	KeyFrame[12].rotGnubeX = -6.291f;//-45.054
	KeyFrame[12].rotGnubeY = 450.00f;
	KeyFrame[12].rotGnubeZ = -13.642f;

	KeyFrame[13].posGnubeX = 0.0f;
	KeyFrame[13].posGnubeY = 0.0f;
	KeyFrame[13].posGnubeZ = 0.0f;
	KeyFrame[13].rotGnubeX = -6.291f;//-45.054
	KeyFrame[13].rotGnubeY = 540.00f;
	KeyFrame[13].rotGnubeZ = -13.642f;

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
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 92.0f);//32
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 1.0f, 1.0f, 1.0f); //0.937f, 0.941f, 0.619f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.0f, 0.0f, 0.0f);//0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.1f, 0.1f, 0.1f);//0.5f, 0.5f, 0.5f);


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
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.52f);//52

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.1f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.52f);//52
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 92.0f);//52

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
		/*view = camera.GetViewMatrix();*/
		//model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0));
		//model = glm::rotate(model, glm::radians(-rotRodIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Planetakaio.Draw(lightingShader);
	

		//view = camera.GetViewMatrix();
		//model = glm::translate(tmp, glm::vec3(-0.5f, 0.0f, -0.1f));
		//model = glm::translate(model, glm::vec3(posX, posY, posZ));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Carro.Draw(lightingShader);

		//Goku
		
		model = glm::translate(model, glm::vec3(0.0f + posPodX, -21.751f + posPodY, -10.66f + posPodZ));
		model = glm::rotate(model, glm::radians(rotPodX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPodY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPodZ), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Goku.Draw(lightingShader);
		
		//BILLS
	
		model = glm::translate(model, glm::vec3(0.0f + movBX, 0.0f + movBY, 0.0f + movBZ));  //Variables con las que se va a mover la nave
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(movRotBX), glm::vec3(1.0f, 0.0f, 0.0f)); //Ubicacion de la nave en rotacion X
		model = glm::rotate(model, glm::radians(movRotBY), glm::vec3(0.0f, 1.0f, 0.0f));  //Ubicacion de la nave en rotacion Y
	    model = glm::rotate(model, glm::radians(movRotBZ), glm::vec3(0.0f, 0.0f, 1.0f));  //Ubicacion de la nave en rotacion Z
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Bills.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f + posCarX, 0.0f + posCarY, 0.0f + posCarZ));
		model = glm::rotate(model, glm::radians(rotCarX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotCarY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotCarZ), glm::vec3(0.0f, 0.0f, 1.00f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Carro.Draw(lightingShader);

		//NUBES
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Nubes.Draw(lightingShader);

		//Puerta
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.539f , 20.295f, 6.871f));
		model = glm::rotate(model, glm::radians(35.794f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-14.39f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-4.225f), glm::vec3(0.0f, 0.0f, 1.00f));
		model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta.Draw(lightingShader);

		model = glm::mat4(1);
		//model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Kaio.Draw(lightingShader);


		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-188.069f, 0.495f , 4.376f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bulma.Draw(lightingShader);

		model = glm::mat4(1);
		/*model = glm::translate(model, glm::vec3(0.0f, 0.853f, 0.583f));*/
		model = glm::translate(model, glm::vec3(-189.979f + posGnubeX, 1.8f + posGnubeY, 0.527f + posGnubeZ));
		model = glm::rotate(model, glm::radians(rotGnubeX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotGnubeY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotGnubeZ), glm::vec3(0.0f, 0.0f, 1.00f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		gokunube.Draw(lightingShader);

		model = glm::mat4(1);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		gokunube.Draw(lightingShader);
		Planetagoku.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-188.943f, 2.513f, 2.641f));
		model = glm::rotate(model, glm::radians(rot3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaDe.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-191.064f, 2.513f, 2.641f));
		model = glm::rotate(model, glm::radians(-rot3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PuertaIz.Draw(lightingShader);

		//Carro
		//model = glm::mat4(1);
		//view = camera.GetViewMatrix();
		//model = glm::translate(model, glm::vec3(0.0f + movx, 0.0f, 0.0f + movz)); // Translate it down a bit so it's at the center of the scene
		//model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Carro.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.55f + movx, 21.224f, -12.668f + movz)); // Translate it down a bit so it's at the center of the scene
		//model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotar), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaIzq.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(2.789f + movx, 21.158f, -12.352f + movz)); // Translate it down a bit so it's at the center of the scene
		//model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotar), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaIzq.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(0.734f + movx, 20.679f, -14.621f + movz)); // Translate it down a bit so it's at the center of the scene
		//model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotar), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaDer.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(2.96f + movx, 20.622f, -14.335f + movz)); // Translate it down a bit so it's at the center of the scene
		//model = glm::rotate(model, glm::radians(rotvehiculo), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(rotar), glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "activatransparencia"), 0);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//LlantaDer.Draw(lightingShader);


	
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

		if (play)// Si ya está activa la animacion 
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
				//posX += KeyFrame[playIndex].incX; //Voy guardando cada frame y voy incrementando la posición 
				//posY += KeyFrame[playIndex].incY;
				//posZ += KeyFrame[playIndex].incZ;

				//rotRodIzq += KeyFrame[playIndex].rotInc;
				//rotRodDer += KeyFrame[playIndex].rotInc2;//rodilla derecha

				//rotBraIzq += KeyFrame[playIndex].rotInc3;
				//rotBraDer += KeyFrame[playIndex].rotInc4;
				//rotcuerpo += KeyFrame[playIndex].rotInc5;

				//Goku
				posPodX += posPodXInc;
				posPodY += posPodYInc;
				posPodZ += posPodZInc;
				rotPodX += rotPodXInc;
				rotPodY += rotPodYInc;
				rotPodZ += rotPodZInc;

				//Bills
				movRotBX += movRotBXinc;
				movRotBY += movRotBYinc;
				movRotBZ += movRotBZinc;
				movBX += movBXinc;
				movBY += movBYinc;
				movBZ += movBZinc;
				
				//Carro
				posCarX += posCarXInc;
				posCarY += posCarYInc;
				posCarZ += posCarZInc;
				rotCarX += rotCarXInc;
				rotCarY += rotCarYInc;
				rotCarZ += rotCarZInc;

				//Nube Goku
				//Carro
				posGnubeX += posGnubeXInc;
				posGnubeY += posGnubeYInc;
				posGnubeZ += posGnubeZInc;
				rotGnubeX += rotGnubeXInc;
				rotGnubeY += rotGnubeYInc;
				rotGnubeZ += rotGnubeZInc;

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
	if (keys[GLFW_KEY_M])
	{
		active = !active;
		anim = !anim;
		if (active)
		{
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			LightP1 = glm::vec3(0);
		}
	}
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
	if (keys[GLFW_KEY_L]) 
	{
		active = !active;
		if (active)
			rotarp1 = true;
		else

			rotarp1 = false;
	}
	if (keys[GLFW_KEY_I]) {
		active = !active;
		if (active)
			rotarn1 = true;
		else

			rotarn1 = false;
	}

	if (keys[GLFW_KEY_U]) {
		active = !active;
		if (active)
			puertar = true;
		else

			puertar = false;
	}

	

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

	//Animacion puerta y nubes
	if (rotarp1)
	{
		if (rotarp2 == false)
		{
			rot2 -= 0.1f;

			if (rot2 <= -90.0f)
			{
				rotarp2 = true;
			}

		}

		if (rotarp2 == true)
		{
			rot2 += 0.1f;
			if (rot2 >= 0.0f)
			{
				rotarp2 = false;
			}

		}

	}

	if (rotarn1)
	{
		if (rotarn2 == false)
		{
			rot -= 0.1f;

			if (rot <= -360.0f)
			{
				rotarn2 = true;
			}

		}

		if (rotarn2 == true)
		{
			rot += 0.1f;
			if (rot >= 0.0f)
			{
				rotarn2 = false;
			}

		}

	}

	//Puerta goku
	if (puertar)
	{
		if (puertar2 == false)
		{
			rot3 -= 0.1f;

			if (rot3 <= -90.0f)
			{
				puertar2 = true;
			}

		}

		if (puertar2 == true)
		{
			rot3 += 0.1f;
			if (rot3 >= 0.0f)
			{
				puertar2 = false;
			}

		}

	}


}