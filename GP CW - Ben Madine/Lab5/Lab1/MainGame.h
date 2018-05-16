#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initaliseSystem();
	void processingInputs();
	void loopGame();
	void gameDrawing();
	void ModelTransformManager();

	void PatrikStarModelTransforms();
	void PatrikStartModelGraphics();

	void MrEggModelTransforms();
	void MrEggModelGraphics();

	void BombManModelTransforms();
	void BombManModelGraphics();

	void LightBulbModelTransforms();
	void LightBulbModelGraphics();

	void MarioModelTransofrms();
	void MarioGraphics();

	void setRimToon();
	void setFog(float zPos);
	void geomShader();
	void hairyShaderMethod();
	void setRipple();
	void setLightingEffect();
	

	Display _gameDisplay;
	GameState _gameState;

	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Mesh mesh4;
	Mesh mesh5;

	Texture texture;
	Texture texture1;

	Overlay overlay;

	Shader shaderRimToon;
	Shader shaderFog;
	Shader shaderGeometry;
	Shader shaderHairy;
	Shader shaderSkyBox;
	Shader shaderRipple;
	Shader shaderLighting;
	Shader shaderLightSource;

	glm::mat4 modelView;

	Camera myCam;

	float counter;

	void SkyBoxMethod();
	unsigned int loadCubemap(std::vector<std::string> faces);

};

