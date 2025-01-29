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

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);

static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const Vector2D* v);
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
}

// Initialize the entities and variables used by the scene.
static void SandboxSceneInit()
{
}

// Update the the variables used by the scene.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
    // Tell the compiler that the 'dt' variable is unused.
    UNREFERENCED_PARAMETER(dt);

    FILE* stream = StreamOpen("Data/VectorTests.txt");

    if (stream != NULL)
    {
        Vector2D vector1;

        //DONE ZERO
        Vector2DZero(&vector1);
        SandboxSceneTraceVector("Vector2DZero", &vector1);

        //DONE SET
        Vector2DSet(&vector1, 1.5f, 1.0f);
        SandboxSceneTraceVector("Vector2DSet", &vector1);

        //DONE NEG
        Vector2DNeg(&vector1, &vector1);
        SandboxSceneTraceVector("Vector2DNeg", &vector1);

        //DONE ADD
        Vector2DAdd(&vector1, &vector1, &vector1);
        SandboxSceneTraceVector("Vector2DAdd", &vector1);

        //DONE SUB
        Vector2DSet(&vector1, 1.0f, 1.0f);
        Vector2DSub(&vector1, &vector1, &vector1);
        SandboxSceneTraceVector("Vector2DSub", &vector1);

        //DONE READ
        StreamReadVector2D(stream, &vector1);
        SandboxSceneTraceVector("StreamReadVector2D", &vector1);

        //DONE NORMALIZE
        Vector2DNormalize(&vector1, &vector1);
        SandboxSceneTraceVector("Vector2DNormalize", &vector1);

        //DONE READFLOAT
        float scale = StreamReadFloat(stream); // issue?
        SandboxSceneTraceFloat("StreamReadFloat", scale);

        //DONE VEC SCALE
        //scale = StreamReadFloat(stream);
        Vector2DScale(&vector1, &vector1, scale);
        SandboxSceneTraceVector("Vector2DScale", &vector1);

        ///DONE SCALE ADD
        Vector2DScaleAdd(&vector1, &vector1, scale, &vector1);
        SandboxSceneTraceVector("Vector2DScaleAdd", &vector1);

        //FIX SCALE SUB
        Vector2DScaleSub(&vector1, &vector1, scale, &vector1);
        SandboxSceneTraceVector("Vector2DScaleSub", &vector1);

        //DONE VEC LENGTH
        float length = Vector2DLength(&vector1);
        SandboxSceneTraceFloat("Vector2DLength", length);

        //DONE VEC SQUARE LENGTH
        float squareLength = Vector2DSquareLength(&vector1);
        SandboxSceneTraceFloat("Vector2DSquareLength", squareLength);


        Vector2D vector2, vector3;

        //DONE STREAM READ VEC1
        StreamReadVector2D(stream, &vector2);
        SandboxSceneTraceVector("StreamReadVector2D", &vector2);

        //DONE STREAM READ VEC2
        StreamReadVector2D(stream, &vector3);
        SandboxSceneTraceVector("StreamReadVector2D", &vector3);

        //DONE VEC DIST
        float distance = Vector2DDistance(&vector2, &vector3);
        SandboxSceneTraceFloat("Vector2DDistance", distance);

        //DONE VEC SQR DIST
        float squareDistance = Vector2DSquareDistance(&vector2, &vector3);
        SandboxSceneTraceFloat("Vector2DSquareDistance", squareDistance);

        //DONE VEC DOT PRODUCT
        float dotProduct = Vector2DDotProduct(&vector2, &vector3);
        SandboxSceneTraceFloat("Vector2DDotProduct", dotProduct);


        Vector2D vector4;

        //DONE STREAM READ F
        float angleDeg;
        angleDeg = StreamReadFloat(stream);
        SandboxSceneTraceFloat("StreamReadFloat", angleDeg);

        //DONE VEC ANGLE TO DEG
        Vector2DFromAngleDeg(&vector4, angleDeg);
        SandboxSceneTraceVector("Vector2DFromAngleDeg", &vector4);

        //DONE STREAM READ F
        float angleRad;
        angleRad = StreamReadFloat(stream);
        SandboxSceneTraceFloat("StreamReadFloat", angleRad);

        //DONE VEC ANGLE RAD
        Vector2DFromAngleRad(&vector4, angleRad);
        SandboxSceneTraceVector("Vector2DFromAngleRad", &vector4);

        //DONE VEC TO ANGLE RAD
        float angleRadFromVector = Vector2DToAngleRad(&vector4);
        SandboxSceneTraceFloat("Vector2DToAngleRad", angleRadFromVector);

        StreamClose(&stream);
    }

    SceneSystemSetNext(NULL);
}

// Render any objects associated with the scene.
void SandboxSceneRender(void)
{
}

// Free any objects associated with the scene.
static void SandboxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
}

static void SandboxSceneTraceFloat(const char* text, float f)
{


    TraceMessage("Vector Test: %s = %f", text, f);
}

static void SandboxSceneTraceVector(const char* text, const Vector2D* v)
{


    TraceMessage("Vector Test: %s = [%f, %f]", text, v->x, v->y);
}

