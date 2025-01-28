//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.c
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
#include "SandboxScene.h"
#include "Trace.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Mesh.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandboxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	Mesh* mesh;

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static DGL_Vec2 posSpaceship = { 0.f, 0.f };
static float alpha = 1.0f;
static const DGL_Vec2 scaleColored = { 100.f, 100.f };
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);

//static void SandboxSceneTraceFloat(const char* text, float f);
//static void SandboxSceneTraceVector(const char* text, const Vector2D* v);
//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandboxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandboxSceneLoad, SandboxSceneInit, SandboxSceneUpdate, SandboxSceneRender, SandboxSceneExit, SandboxSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Stub Scene.
// Returns:
//	 Pointer to the base Scene structure for this derived Scene.
const Scene* SandboxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void SandboxSceneLoad(void)
{
	instance.mesh = MeshCreate();



}

// Initialize the entities and variables used by the scene.
static void SandboxSceneInit()
{
	MeshBuildSpaceship(instance.mesh);
	//MeshBuildQuad();
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
	UNREFERENCED_PARAMETER(dt);

	
	

}

// Render any objects associated with the scene.
void SandboxSceneRender(void)
{
	DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	DGL_Graphics_SetCB_Alpha(alpha);
	DGL_Graphics_SetCB_TintColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Graphics_SetCB_TransformData(&posSpaceship, &scaleColored, 0.f);

	
	MeshRender(instance.mesh);

}

// Free any objects associated with the scene.
static void SandboxSceneExit()
{


}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
	MeshFree(&instance.mesh);

}


