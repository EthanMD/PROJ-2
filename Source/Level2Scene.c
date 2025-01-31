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
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Sprite.h"
#include "DGL.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Physics.h"
#include "Level1Scene.h"
#include "DemoScene.h"
#include "SandboxScene.h"
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
static void Level2SceneMovementController(Entity* entity);

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

	Level2SceneMovementController(instance.entity);
	EntityUpdate(instance.entity, dt);




	if (DGL_Input_KeyTriggered('0'))
	{
		SceneSystemSetNext(DemoSceneGetInstance());
	}
	if (DGL_Input_KeyTriggered('1'))
	{
		SceneSystemSetNext(Level1SceneGetInstance());
	}
	if (DGL_Input_KeyTriggered('2'))
	{
		SceneRestart();
	}
	if (DGL_Input_KeyTriggered('9'))
	{
		SceneSystemSetNext(SandboxSceneGetInstance());
	}

	if (DGL_Input_KeyTriggered('Z'))
	{
		Sprite* mySprite = EntityGetSprite(instance.entity);
		SpriteSetAlpha(mySprite, 0.5f);
	}
	if (DGL_Input_KeyTriggered('X'))
	{
		Sprite* mySprite = EntityGetSprite(instance.entity);
		SpriteSetAlpha(mySprite, 1.0f);
	}










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
	EntityRender(instance.entity);
}

// Free any objects associated with the scene.
static void Level2SceneExit()
{
	EntityFree(&instance.entity);
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
	MeshFree(&instance.mesh);

}






static void Level2SceneMovementController(Entity* entity)
{
	//Get the Physics and Transform components from the Entity
	Physics* physics = EntityGetPhysics(entity);
	Transform* transform = EntityGetTransform(entity);

	//Verify that the pointers are valid.
	if (!physics || !transform) //better way
	{
		return;
	}

	//Get the mouse cursor position (in screen coordinates):
	DGL_Vec2 mousePos = DGL_Input_GetMousePosition();

	//Convert the screen coordinates to world coordinates
	DGL_Vec2 newMousePos = DGL_Camera_ScreenCoordToWorld(&mousePos);

	//Get the spaceship’s current translation
	const Vector2D translation = *TransformGetTranslation(transform);

	Vector2D dirVector = { 0 };
	//Calculate a direction vector from the spaceship to the mouse position.
	//Hint : Use Vector2DSub() to subtract one vector from another.
	Vector2DSub(&dirVector, &newMousePos, &translation);

	//Normalize the direction vector using Vector2DNormalize()
	Vector2DNormalize(&dirVector, &dirVector);


	//Set the transform’s rotation, using Vector2DToAngleRad() to convert the direction vector into an angle(in radians).
	float angle = Vector2DToAngleRad(&dirVector);
	TransformSetRotation(transform, angle);

	//Set the Physics component’s velocity = direction vector* spaceshipSpeed.
	Vector2D velocity;

	Vector2DScale(&velocity, &dirVector, spaceshipSpeed);
	PhysicsSetVelocity(physics, &velocity);

}





