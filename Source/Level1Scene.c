//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "Stream.h"
#include "Level2Scene.h"
#include "DemoScene.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Entity.h"
#include "Vector2D.h"
#include "SpriteSource.h"
#include "EntityFactory.h"
#include "SandboxScene.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;
	// Add any scene-specific variables second.
	int numLives;
	Mesh* mesh;
	SpriteSource* spriteSource;
	Entity* entity;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static FILE* livesFile;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
	.numLives = 0,
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{

	FILE* liveStream = StreamOpen("Data/Level1_Lives.txt");

	if (liveStream != NULL)
	{
		instance.numLives = StreamReadInt(liveStream);
		StreamClose(&liveStream);
	}

	Mesh* mesh = MeshCreate();
	MeshBuildQuad(mesh,0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");

	SpriteSource* spriteSource = SpriteSourceCreate(); //issues

	SpriteSourceLoadTexture(spriteSource, 1, 1, "PlanetTexture.png"); //issues


}

// Initialize the entities and variables used by the scene.
static void Level1SceneInit()
{
	Entity* newEntity = EntityFactoryBuild("./Data/PlanetJump.txt");

	if (newEntity)
	{
		
		//Sprite* sprite = EntityGetSprite(newEntity);

		//sprite->mesh //cant access

		//entity-> //cant access

		//need to set sprites mesh

		//need to set sprites source

		//need to set sprites frame index to 0

		//DGL_Graphics_SetBackgroundColor()
		//DGL_Graphics_SetBlendMode();

	}


}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);


	instance.numLives--;
	if (instance.numLives <= 0) //remove now?
	{
		//set to LEVEL2
		SceneSystemSetNext(Level2SceneGetInstance());	
	}

	if (DGL_Input_KeyTriggered('0'))
	{
		SceneSystemSetNext(DemoSceneGetInstance());
	}
	if (DGL_Input_KeyTriggered('1'))
	{
		SceneRestart();
	}
	if (DGL_Input_KeyTriggered('2'))
	{
		SceneSystemSetNext(Level2SceneGetInstance());
	}
	if (DGL_Input_KeyTriggered('9'))
	{
		SceneSystemSetNext(SandboxSceneGetInstance());
	}

	

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	//SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void Level1SceneRender(void)
{
}

// Free any objects associated with the scene.
static void Level1SceneExit()
{
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
}


