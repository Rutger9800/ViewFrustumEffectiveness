#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include"mge/core/Mesh.hpp"
#include"mge/core/World.hpp"
#include"mge/core/Texture.hpp"
#include"mge/core/Light.hpp" 
#include"mge/core/Camera.hpp"
#include"mge/core/GameObject.hpp"

#include"mge/materials/AbstractMaterial.hpp"
#include"mge/materials/TextureMaterial.hpp"
#include"mge/materials/AssignmentMaterial.hpp"



#include"CameraBehaviour.hpp"
#include"mge/behaviours/KeysBehaviour.hpp"
#include"Classes/WorldGen.hpp"

#include"mge/util/DebugHud.hpp"
#include"mge/util/ShaderUtil.h"

#include"SpecialScene.hpp"

SpecialScene::SpecialScene() :AbstractGame(), _hud(0)
{
}

void SpecialScene::initialize()
{
	AbstractGame::initialize(); 
	std::cout << "initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "Hud initialized" << std::endl << std::endl;
	maxSeconds = 22;
	storeTime = 0;
}

void SpecialScene::_initializeScene()
{
	objCreatedByGen = 3600;
	VFCbool = true;
	_csv = new CSVwriter("../_vs2015/csvfiles/" + std::to_string(objCreatedByGen) + " VFC " + std::to_string(VFCbool) + ".csv");

	//meshes
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");
	//Mesh* monkeyMesh = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj");
	Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	Mesh* terrainMesh = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");

	//materials
	AbstractMaterial* grayMat = new ADSColorMaterial(glm::vec3(0.5, 0.5, 0.5), 1.0f, 32, 1.0f);//gray
	AbstractMaterial* greenMat = new ADSColorMaterial(glm::vec3(0, 0.6, 0), 0.5f, 8, 1.0f);//green
	AbstractMaterial* orangeTexMaterial = new AssignmentMaterial(Texture::load(config::MGE_TEXTURE_PATH + "orange.png"), 1.0f, 32, 1.0f);
	AbstractMaterial* runicMaterial = new AssignmentMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"), 1.0f, 32, 1.0f);

	//behaviours
	KeysBehaviour* keyBehave = new KeysBehaviour();

	//   \/ SCENE setup \/
	GameObject* plane = new GameObject("grassplane", glm::vec3(1, -1, 0), planeMeshDefault, greenMat);
	plane->scale(glm::vec3(20, 20, 20));
	//_world->add(plane);

	GameObject* sphere = new GameObject("spherio", glm::vec3(0, 0, 1), sphereMesh, grayMat, keyBehave);
	//_world->add(sphere);

	//Light
	Light* pointLight = new Light("lightOne", glm::vec3(-4, 2, 8), glm::vec3(1, 1, 1));
	_world->add(pointLight);

	//-camera
	float camDistanceToTarget = 10.0f;
	CameraBehaviour* camBehave = new CameraBehaviour(camDistanceToTarget, 15.0f, 12.0f, sphere, _window);
	Camera* camera = new Camera("camera", glm::vec3(1, 0.5f, 1)
		, glm::perspective(glm::radians(60.0f), config::SCREENX / config::SCREENY, 0.1f, 1000.0f));
	camera->setBehaviour(camBehave);
	_world->add(camera);
	_world->setMainCamera(camera);

	WorldGen* WorldGenerator = new WorldGen(sphereMesh, objCreatedByGen);//call the world generator to create the given mesh x amount of times
	_world->add(WorldGenerator);
	_renderer->toggleViewFrustumCulling(VFCbool);
}

void SpecialScene::_render()
{
	if (_countSeconds > maxSeconds) _window->close();


	AbstractGame::_render();
	//send info once per second
	if (_countSeconds == 0 || storeTime != _countSeconds) {
		_renderer->renderObjectsInfo(_hud, _csv);
		storeTime = _countSeconds;
	}
	glClearColor(0, 0.5, 1, 0.5);
	_updateHud();
}

void SpecialScene::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS: ") + std::to_string((int)_fps) + " | FrameTime: " + std::to_string(_frameTime) + "\n";
	//_hud->setObjectsInfo("OBJs Scene" + std::to_string(_world->getChildCount()));
	_hud->setDebugInfo(debugInfo);
	_hud->draw();
	_csv->AddFrameTime(_fps);

}

SpecialScene::~SpecialScene()
{

}