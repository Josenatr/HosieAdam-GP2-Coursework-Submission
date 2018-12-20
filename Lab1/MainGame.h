#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Audio.h"
#include "Texture.h"
#include "transform.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run(); //method used to run game
	

private:

	void initialiseSystems(); //method used to initialise game systems
	void processInput(); //method used to process key inputs
	void gameLoop(); //method used for game loop
	void drawGame(); //method used to draw game
	bool checkCollision(glm::vec3&, float, glm::vec3, float); //boolean method used for checking if collision has occurred
	void updateModelTransform(); //method used to allow ability to update model transform outside drawGame()

	Display _gameDisplay; 
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Camera myCamera;
	Texture texture1;
	Texture texture2;
	Transform transform1;
	Transform transform2;
	Shader shader;
	Audio audioDevice;


	//unsigned int used for audio within game
	unsigned int backGroundMusic1;
	unsigned int backGroundMusic2;
	unsigned int currentMusic;
	unsigned int catNoise;
	unsigned int deerNoise;
	unsigned int ratNoise;
	unsigned int cowNoise;
	unsigned int wolfNoise;
	unsigned int goatNoise;


	//the floats used for setting transform 3's position
	float trans2X;
	float trans2Y;
	float trans2Z;
	float trans2Xrot;

};

