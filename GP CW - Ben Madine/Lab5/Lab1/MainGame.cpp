#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include "stb_image.h"
#include <string>

unsigned int skyBox[6];
glm::vec3 lightPos;

#pragma region Transform
Transform patrikTrans;
Transform bombTrans;
Transform mrEggTrans;
Transform lightBulbTrans;
Transform marioTrans;
#pragma endregion

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display

	///<summary - Meshes>\\\
		The different meshes used for the models, five meshes for all five models. 	
#pragma region Meshes 
	Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Mesh* mesh4();
	Mesh* mesh5();
#pragma endregion
	///<summary - Textures>\\\
		The different textures which can be applied to models. None which are used in this project.
#pragma region Texture/Overlay
	Texture* texture(); //load texture
	Texture* texture1(); //load texture
	Overlay* overlay(); //load texture
#pragma endregion
	///<summary - Shaders>\\\
		All the different shaders used in this project, open the region which specifies what the shaders are and what they are linked to. 
#pragma region Shader
	Shader* shaderRimToon(); //Rim and Toon shader, linked to Pactrick star
	Shader* shaderFog(); //Fog shader, linked to Mr Egg man 
	Shader* shaderGeometry(); // Explosion shader linked to Bomb man
	Shader* shaderHairy(); //Hariy shader linked to Pactrick star
	Shader* shaderSkyBox(); ///<Not used> /// Sky box Shader 
	Shader* shaderRipple(); //Ripple Shader, linked to Pactrick star
	Shader* shaderLighting(); // Phong Lighting, applied to Mario
	Shader* shaderLightSource(); //Light source, applied to light bulb
#pragma endregion
}

MainGame::~MainGame() 
{
}

void MainGame::run()
{	
	///<summary - Methods>\\\
		The initaliseSystem method simply assigns values. For example, the shader file locations are set etc. The camera position is also set as well as the counter. \\\
		The loopGame method simply calls the methods every frame.
	initaliseSystem(); 
	loopGame();	
}

void MainGame::initaliseSystem()
{
	///<summary>\\\
	This methoda assigns values, more description in the previous method.
	_gameDisplay.initDisplay(); 

#pragma region Textures
	texture.init("..\\res\\bricks.jpg"); //load texture
	texture1.init("..\\res\\water.jpg"); //load texture
#pragma endregion

#pragma region Shaders
//	shaderSkyBox.init("..\\res\\shaderSkyBox.vert", "..\\res\\shaderSkyBox.frag"); //Sky Box SHader
	shaderRipple.initFragVert("..\\res\\shaderRipple.vert", "..\\res\\shaderRipple.frag");
	shaderRimToon.initFragVert("..\\res\\shaderRimToon.vert", "..\\res\\shaderRimToon.frag"); //Patrik Star Shader
	shaderFog.initFragVert("..\\res\\shaderFog.vert", "..\\res\\shaderFog.frag"); //Mr Egg man shader
	shaderHairy.initFragVertGeom("..\\res\\shaderGeoHairy.vert", "..\\res\\shaderGeoHairy.frag", "..\\res\\shaderGeoHairy.geom"); //Hairy Shader
	shaderGeometry.initFragVertGeom("..\\res\\shaderGeoText.vert", "..\\res\\shaderGeoText.frag", "..\\res\\shaderGeoText.geom"); //Bomb man Shader
	shaderLighting.initFragVert("..\\res\\shaderLightEffect.vert", "..\\res\\shaderLightEffect.frag");
	shaderLightSource.initFragVert("..\\res\\shaderLightSource.vert", "..\\res\\shaderLightSource.frag");
#pragma endregion

#pragma region Meshes
	mesh1.loadModel("..\\res\\Patrick.obj");
	mesh2.loadModel("..\\res\\MrEgg.obj");
	mesh3.loadModel("..\\res\\bombman.obj");
	mesh4.loadModel("..\\res\\lightbulb.obj");
	mesh5.loadModel("..\\res\\Mario.obj");
#pragma endregion

	overlay.init("..\\res\\bricks.jpg");

	myCam.initCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void MainGame::loopGame()
{
	///<summary>\\\
	Contains to load methods when gamestate is not equaling EXIT
	while (_gameState != GameState::EXIT)
	{
		processingInputs();

		ModelTransformManager();

		gameDrawing();
	}
}

void MainGame::processingInputs()
{
	///<summary>\\\
	Used for key presses, not used in this project
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

void MainGame::ModelTransformManager()
{
	///<summary - Transforms>\\\
	Loads the model transforms, so the rotation, scale and position values
	PatrikStarModelTransforms();
	MrEggModelTransforms();
	BombManModelTransforms();
	LightBulbModelTransforms();
	MarioModelTransofrms();
}

///<summary - Patrick Star>\\\
	Handles all the lighting effects, positons and binding for the patrick star model. To Change these effects, see the <other shader> region to find out!.
#pragma region Patrik Star Methods
void MainGame::setRimToon()
{
	shaderRimToon.setTheVectorThreeValue("lightDir", lightPos);
	shaderRimToon.swtTheMatrixFourValue("u_vm", myCam.GetView());
	shaderRimToon.swtTheMatrixFourValue("u_pm", myCam.GetProjection());
	shaderRimToon.swtTheMatrixFourValue("v_pos", patrikTrans.GetModel());
}

void MainGame::PatrikStarModelTransforms()
{
	patrikTrans.SetPos(glm::vec3(1, 3, 0.0));
	patrikTrans.SetRot(glm::vec3(0.0, counter * 15, 0.0));
	patrikTrans.SetScale(glm::vec3(0.6, 0.6, 0.6));
}

void MainGame::PatrikStartModelGraphics()
{
	shaderRimToon.Binding();
	setRimToon();
	shaderRimToon.Update(patrikTrans, myCam);
	texture.Bind(0);
	mesh1.draw();
	mesh1.updateSphereData(*patrikTrans.GetPos(), 0.62f);
}
#pragma endregion
///<summary - MrEgg Man>\\\
	Handles all the lighting effects, positons and binding for the Mr Egg Man model. To Change these effects, see the <other shader> region to find out!.
#pragma region MrEgg Man Methods
void MainGame::MrEggModelTransforms()
{
	///<Summary - Positions, rotations and scale is set>\\\

	mrEggTrans.SetPos(glm::vec3(-2.5, -2.0, -sinf(counter * 10) * 5));
	mrEggTrans.SetRot(glm::vec3(0.0, counter * 15, 0.0));
	mrEggTrans.SetScale(glm::vec3(0.05, 0.05, 0.05));
}

void MainGame::MrEggModelGraphics()
{
	///<Summary - The shader is bound, the fog is applied to an offset of the model so the fog will encompass the model at a range> \\\
	<updates the fog shader, draws the mesh and updates the sphere data>\\\

	shaderFog.Binding();
	setFog(mesh2.getSpherePos().z + 5);
	shaderFog.Update(mrEggTrans, myCam);
	mesh2.draw();
	mesh2.updateSphereData(*mrEggTrans.GetPos(), 0.62f);
}

void MainGame::setFog(float zPos)
{
	///<Summary - The light direction vector is applied, the view and projection matrix are assigned> \\\
		<the fog colour and distance values are then set>\\\

	shaderFog.setTheVectorThreeValue("lightDir", lightPos);

	shaderFog.swtTheMatrixFourValue("u_vm", myCam.GetView());
	shaderFog.swtTheMatrixFourValue("u_pm", myCam.GetProjection());

	shaderFog.setTheVectorThreeValue("fogColor", glm::vec3(0.2, 0.2, 0.2));
	shaderFog.setTheFloatValue("minDist", -5.0f);
	shaderFog.setTheFloatValue("maxDist", 5.0f);

	shaderFog.setTheFloatValue("zpos", zPos);
}
#pragma endregion
///<summary - Bomb Man>\\\
	Handles all the lighting effects, positons and binding for the Bomb Man model. To Change these effects, see the <other shader> region to find out!.
#pragma region Bomb Man Methods
void MainGame::BombManModelTransforms()
{
	///<Summary - Positions, rotations and scale is set>\\\

	bombTrans.SetPos(glm::vec3(4, -2, 0));
	bombTrans.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	bombTrans.SetScale(glm::vec3(0.6, 0.6, 0.6));
}

void MainGame::BombManModelGraphics()
{
	///<Summary - The shader is bound, the geometry shader is called which consists of the shader attributes> \\\
		<updates the geometry shader, draws the mesh and updates the sphere data>\\\

	shaderGeometry.Binding();
	geomShader();
	shaderGeometry.Update(bombTrans, myCam);
	mesh3.draw();
	mesh3.updateSphereData(*bombTrans.GetPos(), 0.62f);
}

void MainGame::geomShader()
{
	///<Summary - The time variable specifies the rate of the explosion effect> \\\
			<The random colour values are set, they change values every frame>\\\

	shaderGeometry.setTheFloatValue("time", 0.1f + (counter * 15));

	shaderGeometry.setTheFloatValue("randColourX", rand() % 1);
	shaderGeometry.setTheFloatValue("randColourY", rand() % 2);
	shaderGeometry.setTheFloatValue("randColourZ", rand() % 3);
}
#pragma endregion
///<summary - Light Bulb>\\\
	Handles all the lighting effects, positons and binding for the light bulb model.
#pragma region Light Bulb Methods
void MainGame::LightBulbModelTransforms()
{
	///<Summary - Positions, rotations and scale is set>\\\

	lightBulbTrans.SetPos(lightPos);
	lightBulbTrans.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	lightBulbTrans.SetScale(glm::vec3(0.6, 0.6, 0.6));
}

void MainGame::LightBulbModelGraphics()
{
	///<Summary - The shader is bound> \\\
			<updates the light source shader, draws the mesh and updates the sphere data>\\\

	shaderLightSource.Binding();
	shaderLightSource.Update(lightBulbTrans, myCam);
	texture.Bind(0);
	mesh4.draw();
	mesh4.updateSphereData(*lightBulbTrans.GetPos(), 0.62f);
}
#pragma endregion
///<summary - Mario>\\\
	Handles all the lighting effects, positons and binding for the Mario model.
#pragma region Mario Methods
void MainGame::setLightingEffect()
{ 
	///<Summary - the object colour specifies the colour of the light bulb, whereas the light colour specifies the colour of the lighting effect> \\\
				<the light postions determines the position of the light source, which is the light bulb model position and the view posiiton is the cameras position>\\\

	shaderLighting.setTheVectorThreeValue("objectColor", 1.0f, 0.5f, 0.31f);
	shaderLighting.setTheVectorThreeValue("lightColor", 1.0f, 1.0f, 1.0f);
	shaderLighting.setTheVectorThreeValue("lightPos", lightPos); 
	shaderLighting.setTheVectorThreeValue("viewPos", myCam.getPos()); 
}

void MainGame::MarioModelTransofrms()
{
	///<Summary - Positions, rotations and scale is set>\\\

	marioTrans.SetPos(glm::vec3(-1, -2, 1));
	marioTrans.SetRot(glm::vec3(counter * 15, 0.0, 0.0));
	marioTrans.SetScale(glm::vec3(1, 1, 1));
}

void MainGame::MarioGraphics()
{
	///<Summary - The shader is bound> \\\
				<updates the light effect shader, draws the mesh and updates the sphere data>\\\

	shaderLighting.Binding();
	setLightingEffect();
	shaderLighting.Update(marioTrans, myCam);
	texture.Bind(0);
	mesh5.draw();
	mesh5.updateSphereData(*marioTrans.GetPos(), 0.62f);
}
#pragma endregion
///<summary - Extra Shaders, not applied to models>\\\
	These shaders are not applied to any models, so will need to be done manually. A description of how to do this will be in section 4.0 of the document, or open up this region to find out!
#pragma region Other Shaders 
///<summary - How to apply to other shaders>\\\
	In order to apply these two shaders to other shaders, 2 sets are needed. Set the appropriate shader to the bound shader and call the method.\\\
		<Example - Applying Hairy to the Bomb Man Model>
			/*
			shaderHairy.Binding();
			hairyShaderMethod();
			shaderHairy.Update(bombTrans, myCam);
			*/
		///These lines replace the lines in the original method.\\\
		<Keywords Needed For Hairy - shaderHairy.Binding(); hairyShaderMethod(); shaderHairy.Update(MODEL TRANSFORM, myCam);>\\\
		<Keywords Needed For Ripple - shaderRipple.Binding(); setRipple(); shaderRipple.Update(MODEL TRANSFORM, myCam);>

void MainGame::hairyShaderMethod()
{
	///<Summary - The random colours are assigned, simply just changes the colour of the model every frame to a random colour> \\\

	shaderHairy.setTheFloatValue("randColourX", rand() % 1);
	shaderHairy.setTheFloatValue("randColourY", rand() % 2);
	shaderHairy.setTheFloatValue("randColourZ", rand() % 3);
}

void MainGame::setRipple()
{
	///<summary - Sets the time between ripples for the shader>\\\

	shaderRipple.setTheFloatValue("time", 0.1f + counter * 2);
}
#pragma endregion

void MainGame::gameDrawing()
{
	///<summary>\\\
	Sets the light position\\\
	Clears the game display\\\
	Calls the graphic methods for each model\\\
	Sets the counter variable\\\
	Swaps the buffer objects

	lightPos = glm::vec3(3, 0, -sinf(counter * 5) * 5);
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	PatrikStartModelGraphics();

	MrEggModelGraphics();
	
	BombManModelGraphics();

	LightBulbModelGraphics();

	MarioGraphics();

	counter = counter + 0.001f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 