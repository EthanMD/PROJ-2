//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Entity.h"
#include "Transform.h"
#include "Stream.h"
#include "stdio.h"
#include "Sprite.h"
#include "Physics.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Entity
{
	// The name of the entity.
	// A buffer is used to allow each entity to have a unique name.
	// The buffer is hardcoded to an arbitrary length that will be sufficient
	//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
	//	 arrays for this purpose but the additional complexity is unnecessary
	//	 and it is your responsibility to ensure that the memory is successfully
	//	 allocated and deallocated in all possible situations.
	// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	char name[32];

	// Pointer to an attached physics component.
	Physics* physics;

	// Pointer to an attached sprite component.
	Sprite* sprite;

	// Pointer to an attached transform component.
	Transform* transform;

} Entity;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
// 
// 
//------------------------------------------------------------------------------


// Dynamically allocate a new Entity.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Entity* EntityCreate(void) 
{
	Entity* entity = calloc(1, sizeof(Entity)); //Entity instead? like this in many create functions
	if (entity)
	{

		return entity;
	}

	return NULL;
}

// Free the memory associated with an Entity.
// (NOTE: All attached components must be freed using the corresponding Free() functions.)
// (NOTE: The Entity pointer must be set to NULL.)
// Params:
//	 entity = Pointer to the Entity pointer.
void EntityFree(Entity** entity)
{


	TransformFree(&(*entity)->transform);
	PhysicsFree(&(*entity)->physics);
	SpriteFree(&(*entity)->sprite);

	free(*entity); 
	*entity = NULL;
}

// Read (and construct) the components associated with a entity.
// [NOTE: See project instructions for implementation instructions.]
// Params:
//	 entity = Pointer to the Entity.
//	 stream = The data stream used for reading.
void EntityRead(Entity* entity, Stream stream)
{
	//UNREFERENCED_PARAMETER(entity);
	//UNREFERENCED_PARAMETER(stream);

	if (entity && stream) 
	{
		//read a token from the stream
		const char* token = StreamReadToken(stream);
		//use the token to set the entitys name
		
		if (!token)
		{
			return;
		}


		//strcpy_s(entity->name,sizeof(Entity*),token); //good?
		strcpy_s(entity->name, _countof(entity->name), token); //good?


		while (true) 
		{
			token = StreamReadToken(stream);

			//[NOTE:When setting the name, use strcpy_s() to reduce the risk of
			//buffer overruns. Additionally, do NOT hardcode the number "32" when
			//calling this function!  Instead, use the _countof() macro to get the
			//size of the "name" array.]
			//	•	Read a token from the stream.
			//	•	If “token” contains “Transform”

			if (!token)
			{
				break;
			}

			if (!strcmp(token,"Transform"))
			{
				//	1.	Create a new transform component using TransformCreate()
				Transform* transform = TransformCreate();

				//	2.	Call TransformRead(), passing the created transform
				TransformRead(transform, stream);
				//	3.	Add the transform to the entity
				EntityAddTransform(entity, transform);

			}
			else if (!strcmp(token, "Physics"))
			{
				//	•	Else if “token” contains “Physics
				//Repeat steps 1 - 3 above, replacing “Transform” with “Physics”.
				Physics* physics = PhysicsCreate();

				PhysicsRead(physics, stream);

				EntityAddPhysics(entity, physics);

			}
			else if (!strcmp(token, "Sprite"))
			{
				//Else if “token” contains “Sprite”,
				//Repeat steps 1 - 3 above, replacing “Transform” with “Sprite”.
				Sprite* sprite = SpriteCreate();

				SpriteRead(sprite, stream);

				EntityAddSprite(entity, sprite);

			}
			else if (token[0] == 0)
			{
				//Else if “token” is empty(zero - length string),
				//Break out of the while - loop.
				break;

			}

		}

	}
}

// Attach a Physics component to an Entity.
// Params:
//	 entity = Pointer to the Entity.
//   physics = Pointer to the Physics component to be attached.
void EntityAddPhysics(Entity* entity, Physics* physics)
{

	entity->physics = physics;


}

// Attach a sprite component to an Entity.
// Params:
//	 entity = Pointer to the Entity.
//   sprite = Pointer to the Sprite component to be attached.
void EntityAddSprite(Entity* entity, Sprite* sprite) 
{

	entity->sprite = sprite;

}

// Attach a transform component to an Entity.
// Params:
//	 entity = Pointer to the Entity.
//   transform = Pointer to the Transform component to be attached.
void EntityAddTransform(Entity* entity, Transform* transform) 
{

	entity->transform = transform;
}

// Set the Entity's name.
// [NOTE: Verify that both pointers are valid before setting the name.]
// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
//	 calling this function!  Instead, use the _countof() macro to get the
//	 size of the "name" array.]
// Params:
//	 entity = Pointer to the Entity.
//	 name = Pointer to the Entity's new name.
void EntitySetName(Entity* entity, const char* name) 
{


	if (entity && name) 
	{
		strcpy_s(entity->name, _countof(entity->name), name);
	}
}

// Get the Entity's name.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the Entity's name,
//		else return NULL.
const char* EntityGetName(const Entity* entity)
{


	if (entity)
	{
		return entity->name;
	}
	return NULL;
}

// Get the Physics component attached to an Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached physics component,
//		else return NULL.
Physics* EntityGetPhysics(const Entity* entity) 
{


	if (entity)
	{
		return entity->physics;
	}
	return NULL;
}

// Get the Sprite component attached to a Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Sprite component,
//		else return NULL.
Sprite* EntityGetSprite(const Entity* entity) 
{


	if (entity)
	{
		return entity->sprite;
	}
	return NULL;
}

// Get the Transform component attached to a Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Transform component,
//		else return NULL.
Transform* EntityGetTransform(const Entity* entity)
{

	if (entity)
	{
		return entity->transform;
	}
	return NULL;
}

// Update any components attached to the Entity.
// (Hint: You will need to call PhysicsUpdate().)
// (NOTE: You must first check for a valid pointer before calling this function.)
// Params:
//	 entity = Pointer to the Entity.
//	 dt = Change in time (in seconds) since the last game loop.
void EntityUpdate(Entity* entity, float dt) 
{

	if (entity->physics && entity->transform)
	{
		PhysicsUpdate(entity->physics, entity->transform, dt);
	}

}

// Render any visible components attached to the Entity.
// (Hint: You will need to call SpriteRender(), passing the Sprite and Transform components.)
// (NOTE: You must first check for valid pointers before calling this function.)
// Params:
//	 entity = Pointer to the Entity.
void EntityRender(Entity* entity)
{

	if (entity) 
	{
		SpriteRender(entity->sprite, entity->transform);
	}

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

