//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "StubScene.h"
#include "Stream.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Sprite.h"
#include "DGL.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float spaceshipSpeed = 500.0f;
static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
	int numHealth;

	Mesh* mesh;
	Entity* entity;

} Level2Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneUpdate(float dt);
static void Level2SceneExit(void);
static void Level2SceneUnload(void);
static void Level2SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	.numLives = 0, .numHealth = 0
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* Level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level2SceneLoad(void)
{

	instance.mesh = MeshCreate();

	MeshBuildSpaceship(instance.mesh);

	





	//FILE* liveStream = StreamOpen("Data/Level2_Lives.txt");
	//if (liveStream != NULL) 
	//{
	//	instance.numLives = StreamReadInt(liveStream);
	//	StreamClose(&liveStream);
	//}


}

// Initialize the entities and variables used by the scene.
static void Level2SceneInit()
{

	instance.entity = EntityFactoryBuild("./Data/SpaceshipHoming.txt");

	if (instance.entity) 
	{
		
		Sprite* mySprite = EntityGetSprite(instance.entity);

		SpriteSetMesh(mySprite, instance.mesh);

		DGL_Graphics_SetBackgroundColor(&DGL_Color_Black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);



	}














	//FILE* healthStream = StreamOpen("Data/Level2_Health.txt");
	//if (healthStream != NULL)
	//{
	//	instance.numHealth = StreamReadInt(healthStream);

	//	StreamClose(&healthStream);
	//}
}


// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);



















	//instance.numHealth--;
	//if (instance.numHealth <= 0)
	//{
	//	instance.numLives--;
	//	if (instance.numLives > 0)
	//	{
	//		SceneRestart();
	//		//SceneSystemRestart();
	//	}
	//	else 
	//	{
	//		SceneSystemSetNext(SandboxSceneGetInstance()); //change to sandbox
	//	}

	//}




	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	//SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void Level2SceneRender(void)
{
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
}


