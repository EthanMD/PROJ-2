//------------------------------------------------------------------------------
//
// File Name:	Transform.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Stream.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Transform
{
	// The translation (or world position) of an entity.
	Vector2D	translation;

	// The rotation (or orientation) of an entity (in radians).
	float	rotation;

	// The scale (or size) of an entity.
	// (Hint: This should be initialized to (1, 1).)
	Vector2D	scale;

} Transform;
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

// Dynamically allocate a new Transform component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: You must initialize the scale values to non-zero values.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Transform* TransformCreate(void)
{
	Transform* transform = calloc(1, sizeof(Transform*));
	if (transform)
	{
		return transform;
	}

	return NULL;

}

// Free the memory associated with a Transform component.
// (NOTE: The Transform pointer must be set to NULL.)
// Params:
//	 transform = Pointer to the Transform pointer.
void TransformFree(Transform** transform) 
{
	UNREFERENCED_PARAMETER(transform);

	free(*transform);
	*transform = NULL;   // correct?


}

// Read the properties of a Transform component from a file.
// [NOTE: Read the translation value using StreamReadVector2D.]
// 
// [NOTE: Read the rotation value using StreamReadFloat.]
// 
// [NOTE: Read the scale value using StreamReadVector2D.]
// Params:
//	 transform = Pointer to the Transform component.
//	 stream = The data stream used for reading.
void TransformRead(Transform* transform, Stream stream) 
{
	UNREFERENCED_PARAMETER(transform);
	UNREFERENCED_PARAMETER(stream);

	StreamReadVector2D(stream, &transform->translation); 

	StreamReadFloat(stream);

	StreamReadVector2D(stream, &transform->scale); 

}

// Get the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's translation,
//		else return a NULL pointer.
const Vector2D* TransformGetTranslation(const Transform* transform) 
{
	UNREFERENCED_PARAMETER(transform);


	if (transform) 
	{
		return &transform->translation;
	}


	return NULL;
}

// Get the rotation value of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return the component's rotation value (in radians),
//		else return 0.0f.
float TransformGetRotation(const Transform* transform) 
{
	UNREFERENCED_PARAMETER(transform);

	if (transform) 
	{
		return transform->rotation;
	}


	return 0.0f;
}

// Get the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
// Returns:
//	 If the Transform pointer is valid,
//		then return a pointer to the component's scale,
//		else return a NULL pointer.
const Vector2D* TransformGetScale(const Transform* transform)
{
	UNREFERENCED_PARAMETER(transform);

	if (transform)
	{
		return &transform->scale;
	}

	return NULL;
}

// Set the translation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new translation.
void TransformSetTranslation(Transform* transform, const Vector2D* translation) 
{
	UNREFERENCED_PARAMETER(transform);
	UNREFERENCED_PARAMETER(translation);

	transform->translation = *translation;
}

// Set the rotation of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 rotation = The rotation value (in radians).
void TransformSetRotation(Transform* transform, float rotation)
{
	UNREFERENCED_PARAMETER(transform);
	UNREFERENCED_PARAMETER(rotation);

	transform->rotation = rotation;
}

// Set the scale of a Transform component.
// Params:
//	 transform = Pointer to the Transform component.
//	 translation = Pointer to the new scale.
void TransformSetScale(Transform* transform, const Vector2D* scale)
{
	UNREFERENCED_PARAMETER(transform);
	UNREFERENCED_PARAMETER(scale);

	transform->scale = *scale;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

