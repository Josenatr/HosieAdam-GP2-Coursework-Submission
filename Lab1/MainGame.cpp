#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>



Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Texture* texture();
	Shader* shader();

}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initialiseSystems();
	gameLoop();
}

void MainGame::initialiseSystems()
{
	_gameDisplay.initDisplay();
	mesh1.loadModel("..\\res\\Models\\monkey3.obj");
	mesh2.loadModel("..\\res\\Models\\spaceship.obj");


	texture1.init("..\\res\\Textures\\water.jpg"); //
	texture2.init("..\\res\\Textures\\metalTexture.jpg");
	shader.initShader("..\\res\\Textures\\shader"); //new shader


	changeSound = audioDevice.loadSound("..\\res\\Audio\\swoosh.wav");
	backGroundMusic1 = audioDevice.loadSound("..\\res\\Audio\\background1.wav");
	backGroundMusic2 = audioDevice.loadSound("..\\res\\Audio\\background2.wav");
	catNoise = audioDevice.loadSound("..\\res\\Audio\\CatNoise2.wav");
	deerNoise = audioDevice.loadSound("..\\res\\Audio\\DeerNoise.wav");
	ratNoise = audioDevice.loadSound("..\\res\\Audio\\RatNoise.wav");
	cowNoise = audioDevice.loadSound("..\\res\\Audio\\CowNoise.wav");
	wolfNoise = audioDevice.loadSound("..\\res\\Audio\\WolfNoise.wav");
	goatNoise = audioDevice.loadSound("..\\res\\Audio\\GoatNoise.wav");

	currentMusic = backGroundMusic1;

	audioDevice.playSound(backGroundMusic1);

	myCamera.initCamera(glm::vec3(trans2X, trans2Y, trans2Z - 100), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		updateModelTransform();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)
			{

				// controls for model movement
			case SDLK_a:
				trans2X = trans2X + 0.25f;
				break;
			case SDLK_d:
				trans2X = trans2X - 0.25f;
				break;
			case SDLK_w:
				trans2Y = trans2Y + 0.25f;
				break;
			case SDLK_s:
				trans2Y = trans2Y - 0.25f;
				break;
			case SDLK_SPACE:
				trans2Z = trans2Z + 0.25f;
				break;
			case SDLK_LALT:
				trans2Z = trans2Z - 0.25f;
				break;


				//other controls
			case SDLK_1:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(changeSound);
				audioDevice.playSound(backGroundMusic2);
				mesh1.loadModel("..\\res\\Models\\monkey3.obj");
				texture1.init("..\\res\\Textures\\Brown.jpg");
				break;
			case SDLK_2:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(wolfNoise);
				mesh1.setSphereData(*transform1.GetPos(), 15.0f);
				mesh1.loadModel("..\\res\\Models\\wolf.obj");
				texture1.init("..\\res\\Textures\\DarkGrey.jpg");
				break;
			case SDLK_3:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(ratNoise);
				mesh1.setSphereData(*transform1.GetPos(), 0.02f);
				mesh1.loadModel("..\\res\\Models\\rat.obj");
				texture1.init("..\\res\\Textures\\LightGrey.jpg");
				break;
			case SDLK_4:
				audioDevice.stopSound(currentMusic);		
				audioDevice.playSound(catNoise);
				mesh1.loadModel("..\\res\\Models\\cat.obj");
				texture1.init("..\\res\\Textures\\Orange.jpg");
				break;
			case SDLK_5:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(deerNoise);
				mesh1.loadModel("..\\res\\Models\\deer.obj");
				texture1.init("..\\res\\Textures\\LightBrown.jpg");
				break;
			case SDLK_6:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(cowNoise);
				mesh1.loadModel("..\\res\\Models\\cow.obj");
				texture1.init("..\\res\\Textures\\Black.jpg");
				break;
			case SDLK_7:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(goatNoise);
				mesh1.loadModel("..\\res\\Models\\goat.obj");
				texture1.init("..\\res\\Textures\\White.jpg");
				break;

			}
		}
	}

}

bool MainGame::checkCollision(glm::vec3& m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distanceSq = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distanceSq < ((m1Rad + m2Rad)*(m1Rad + m2Rad)))
		return true;
	
	
		return false;
	

	
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(255.0f, 255.0f, 255.0f, 1.0f);

	shader.Bind();
	if (checkCollision(mesh1.GetSpherePos(), mesh1.GetSphereRad(), mesh2.GetSpherePos(), mesh2.GetSphereRad()) == false)
	{
		// code for object 1 - the monkey head
		shader.Update(transform1, myCamera);
		texture1.Bind(0);
		mesh1.draw();
	}
	//code for object 2 - the asteroid
	shader.Update(transform2, myCamera);
	texture2.Bind(0);
	mesh2.draw();

	myCamera.initCamera(glm::vec3(trans2X, trans2Y, trans2Z - 15), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);

	
	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();

}

void MainGame::updateModelTransform()
{
	transform1.SetPos(glm::vec3(0.0f, 0.0f, 15.0f));
	transform1.SetRot(glm::vec3(0.0f, 135.0f, 0.0f));
	transform1.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	transform2.SetPos(glm::vec3(trans2X, trans2Y, trans2Z));
	transform2.SetRot(glm::vec3(trans2Xrot, 0.0f, 0.0f));
	transform2.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));

	mesh1.setSphereData(*transform1.GetPos(), 10.0f);
	mesh2.setSphereData(*transform2.GetPos(), 1.0f);
}