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
	Texture* texture1();
	Texture* texture2();
	Shader* shader();



}

MainGame::~MainGame()
{
}

void MainGame::run() //this method initialises the systems and starts the game loop
{
	initialiseSystems(); 
	gameLoop();
}

void MainGame::initialiseSystems()
{
	_gameDisplay.initDisplay();
	mesh1.loadModel("..\\res\\Models\\cube.obj"); //loads the first instance of mesh 1
	mesh2.loadModel("..\\res\\Models\\spaceship.obj"); //loads mesh 2, the controllable spaceship mesh


	texture1.init("..\\res\\Textures\\water.jpg"); //sets the texture for mesh 1
	texture2.init("..\\res\\Textures\\metalTexture.jpg"); //sets the texture for mesh 2
	shader.initShader("..\\res\\Textures\\shader"); //initialises the shader

	//the following lines are used to load all of the audio used in the game
	backGroundMusic1 = audioDevice.loadSound("..\\res\\Audio\\background1.wav");
	backGroundMusic2 = audioDevice.loadSound("..\\res\\Audio\\background2.wav");
	catNoise = audioDevice.loadSound("..\\res\\Audio\\CatNoise2.wav");
	deerNoise = audioDevice.loadSound("..\\res\\Audio\\DeerNoise.wav");
	ratNoise = audioDevice.loadSound("..\\res\\Audio\\RatNoise.wav");
	cowNoise = audioDevice.loadSound("..\\res\\Audio\\CowNoise.wav");
	wolfNoise = audioDevice.loadSound("..\\res\\Audio\\WolfNoise.wav");
	goatNoise = audioDevice.loadSound("..\\res\\Audio\\GoatNoise.wav");

	currentMusic = backGroundMusic1; //sets the current music to backgroundMusic1

	audioDevice.playSound(backGroundMusic1); //plays backgroundMusic1

}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT) //while the game is running we run the 3 methods below
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

				// controls for model and camera movement, camera uses same coordinats variables as the model to allow for the camera to follow the model
			case SDLK_a:
				trans2X = trans2X + 0.25f; //adds 0.25f to trans2X which moves the model and camera to the left
				break;

			case SDLK_d:
				trans2X = trans2X - 0.25f; //movement to the right
				break;
			
			case SDLK_w:
				trans2Y = trans2Y + 0.25f; //movement up
				break;
			
			case SDLK_s:
				trans2Y = trans2Y - 0.25f; //movement down
				break;
			
			case SDLK_SPACE:
				trans2Z = trans2Z + 0.25f; //movement forward
				break;
			
			case SDLK_LALT:
				trans2Z = trans2Z - 0.25f; //movement backward
				break;


				//controls used to spawn new models using number keys
			case SDLK_1:
				audioDevice.stopSound(currentMusic); //stops the current music, this is used to stop overlap of sound if models are spawned in quickly
				audioDevice.playSound(backGroundMusic2); //plays the new sound specific to the model
				currentMusic = backGroundMusic2; //sets the new sound to be currentMusic

				mesh1.loadModel("..\\res\\Models\\monkey3.obj"); //changes the model used for mesh1
				texture1.init("..\\res\\Textures\\brown.jpg"); //changes the texture used for mesh1
				break;
			
			case SDLK_2:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(wolfNoise);
				currentMusic = wolfNoise;
				mesh1.setSphereData(*transform1.GetPos(), 15.0f);
				mesh1.loadModel("..\\res\\Models\\wolf.obj");
				texture1.init("..\\res\\Textures\\DarkGrey.jpg");
				break;
			
			case SDLK_3:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(ratNoise);
				currentMusic = ratNoise;
				mesh1.setSphereData(*transform1.GetPos(), 0.02f);
				mesh1.loadModel("..\\res\\Models\\rat.obj");
				texture1.init("..\\res\\Textures\\LightGrey.jpg");
				break;
			
			case SDLK_4:
				audioDevice.stopSound(currentMusic);		
				audioDevice.playSound(catNoise);
				currentMusic = catNoise;
				mesh1.loadModel("..\\res\\Models\\cat.obj");
				texture1.init("..\\res\\Textures\\Orange.jpg");
				break;
			
			case SDLK_5:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(deerNoise);
				currentMusic = deerNoise;
				mesh1.loadModel("..\\res\\Models\\deer.obj");
				texture1.init("..\\res\\Textures\\LightBrown.jpg");
				break;
			
			case SDLK_6:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(cowNoise);
				currentMusic = cowNoise;
				mesh1.loadModel("..\\res\\Models\\cow.obj");
				texture1.init("..\\res\\Textures\\Black.jpg");
				break;
			
			case SDLK_7:
				audioDevice.stopSound(currentMusic);
				audioDevice.playSound(goatNoise);
				currentMusic = goatNoise;
				mesh1.loadModel("..\\res\\Models\\goat.obj");
				texture1.init("..\\res\\Textures\\White.jpg");
				break;

			}
		}
	}

}

bool MainGame::checkCollision(glm::vec3& m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distanceSq = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z)); //equation used to work out the distance between the two objects

	if (distanceSq < ((m1Rad + m2Rad)*(m1Rad + m2Rad))) //if statement used to check if a collision has occurred
		return true;
	
		return false;
	

	
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(255.0f, 255.0f, 255.0f, 1.0f);

	shader.Bind();
	if (checkCollision(mesh1.GetSpherePos(), mesh1.GetSphereRad(), mesh2.GetSpherePos(), mesh2.GetSphereRad()) == false)
	{
		// code for object 1 - the cube
		shader.Update(transform1, myCamera);
		texture1.Bind(0);
		mesh1.draw();
	}
	//code for object 2 - the rocket ship
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