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

	void run();
	

private:

	void initialiseSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	bool checkCollision(glm::vec3&, float, glm::vec3, float);
	void updateModelTransform();

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Camera myCamera;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Transform transform1;
	Transform transform2;
	Transform transform3;
	Shader shader;
	Audio audioDevice;

	unsigned int changeSound;
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

