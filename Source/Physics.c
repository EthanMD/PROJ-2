//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Physics.h"
#include "Vector2D.h"
#include "Stream.h"
#include "Transform.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	//float		inverseMass;

} Physics;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new Physics component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Physics* PhysicsCreate(void) 
{
	Physics* physics = calloc(1, sizeof(Physics));
	if (physics)
	{
		return physics;
	}

	return NULL;
}

// Free the memory associated with a Physics component.
// (NOTE: The Physics pointer must be set to NULL.)
// Params:
//	 physics = Pointer to the Physics component pointer.
void PhysicsFree(Physics** physics)
{
	UNREFERENCED_PARAMETER(physics);

	free(*physics);
	*physics = NULL;
}

// Read the properties of a Physics component from a file.
// [NOTE: Read the acceleration and velocity values using StreamReadVector2D.]
// Params:
//	 physics = Pointer to the Physics component.
//	 stream = Pointer to the data stream used for reading.
void PhysicsRead(Physics* physics, Stream stream)
{
	UNREFERENCED_PARAMETER(physics);
	UNREFERENCED_PARAMETER(stream);

	StreamReadVector2D(stream, &physics->acceleration);
	StreamReadVector2D(stream, &physics->velocity);
}

// Get the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's acceleration structure,
//		else return a NULL pointer.
const Vector2D* PhysicsGetAcceleration(const Physics* physics)
{
	UNREFERENCED_PARAMETER(physics);


	if (physics) 
	{
		return &physics->acceleration;
	}

	return NULL;
}

// Get the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's velocity structure,
//		else return a NULL pointer.
const Vector2D* PhysicsGetVelocity(const Physics* physics)
{
	UNREFERENCED_PARAMETER(physics);


	if (physics)
	{
		return &physics->velocity;
	}

	return NULL;
}

// Get the old translation (position) of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return a pointer to the component's oldTranslation structure,
//		else return a NULL pointer.
const Vector2D* PhysicsGetOldTranslation(Physics* physics)
{
	UNREFERENCED_PARAMETER(physics);

	if (physics)
	{
		return &physics->oldTranslation;
	}

	return NULL;
}

// Set the acceleration of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 acceleration = Pointer to an acceleration vector.
void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration)
{
	UNREFERENCED_PARAMETER(physics);
	UNREFERENCED_PARAMETER(acceleration);

	physics->acceleration = *acceleration; 
}

// Set the velocity of a Physics component.
// Params:
//	 physics = Pointer to the Physics component.
//	 velocity = Pointer to a velocity vector.
void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
{
	UNREFERENCED_PARAMETER(physics);
	UNREFERENCED_PARAMETER(velocity);

	physics->velocity = *velocity;

}

// Update the state of a Physics component using the Semi-Implicit Euler method,
//	 as outlined in the "Dynamics" lecture slides and the project instructions.
// (NOTE: This function must verify that the Physics and Transform pointers are valid.)
// Params:
//	 physics = Pointer to the physics component.
//	 transform = Pointer to the associated transform component.
//	 dt = Change in time (in seconds) since the last game loop.
void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
{

	// Validate the pointers.

	// Get translation from the transform component

	// Store the translation (as oldTranslation) in the Physics component.
	Vector2DSet(&physics->oldTranslation, TransformGetTranslation(transform)->x, TransformGetTranslation(transform)->y);
	
	// Use the Vector2DScaleAdd function to perform the following calculation: velocity = acceleration * dt + velocity
	Vector2DScaleAdd(&physics->velocity, PhysicsGetAcceleration(physics), dt, PhysicsGetVelocity(physics));


	// Use the Vector2DScaleAdd function to perform the following calculation: translation = velocity * dt + translation
	DGL_Vec2 newTranslation;
	Vector2DScaleAdd(&newTranslation, PhysicsGetVelocity(physics), dt, TransformGetTranslation(transform));


	// Store the new translation in the transform component
	TransformSetTranslation(transform, &newTranslation);

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

