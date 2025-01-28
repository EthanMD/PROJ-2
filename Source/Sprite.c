//------------------------------------------------------------------------------
//
// File Name:	Sprite.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"
#include "Stream.h"
#include "DGL.h"
#include "Trace.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Transform.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Sprite
{
	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	const SpriteSource* spriteSource;

	// The mesh used to draw the sprite.
	const Mesh* mesh;

} Sprite;
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

// Dynamically allocate a new Sprite component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (NOTE: You must initialize the 'alpha' member variable to 1.0f.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
Sprite* SpriteCreate(void) 
{
	Sprite* sprite = calloc(1, sizeof(Sprite*));
	if (sprite)
	{
		return sprite;
	}

	return NULL;
}

// Free the memory associated with a Sprite component.
// (NOTE: The Sprite pointer must be set to NULL.)
// Params:
//	 sprite = Pointer to the Sprite pointer.
void SpriteFree(Sprite** sprite) 
{
	UNREFERENCED_PARAMETER(sprite);

	free(*sprite);
	*sprite = NULL;
}


// Read the properties of a Sprite component from a file.
// [NOTE: Read the frameIndex value using StreamReadInt.]
// [NOTE: Read the alpha value using StreamReadFloat.]
// Params:
//	 sprite = Pointer to the Sprite component.
//	 stream = The data stream used for reading.
void SpriteRead(Sprite* sprite, Stream stream) 
{
	UNREFERENCED_PARAMETER(sprite);
	UNREFERENCED_PARAMETER(stream);

	sprite->frameIndex = StreamReadInt(stream);
	sprite->alpha = StreamReadFloat(stream);
	
}

// Render a Sprite (Sprite can be textured or untextured).
// Params:
//	 sprite = Pointer to the Sprite component.
//   transform = Pointer to the Transform component.
void SpriteRender(const Sprite* sprite, Transform* transform) 
{
	DGL_Color tintColor;
	tintColor.a = 0;
	tintColor.b = 0;
	tintColor.g = 0;
	tintColor.r = 0;

	UNREFERENCED_PARAMETER(sprite);
	UNREFERENCED_PARAMETER(transform);

	if (sprite->spriteSource) 
	{
		DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
		SpriteSourceSetTexture(sprite->spriteSource);
		SpriteSourceSetTextureOffset(sprite->spriteSource, sprite->frameIndex);
	}

	DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
	DGL_Graphics_SetCB_TransformData(TransformGetTranslation(transform), TransformGetScale(transform), TransformGetRotation(transform));
	DGL_Graphics_SetCB_Alpha(sprite->alpha);
	DGL_Graphics_SetCB_TintColor(&tintColor);
	MeshRender(sprite->mesh);

}

// Get a Sprite's alpha value.
// Params:
//	 sprite = Pointer to the Sprite component.
// Returns:
//	 If the pointer is valid,
//		then return the Sprite's alpha value (a value between 0.0f and 1.0f),
//		else return 0.0f.
float SpriteGetAlpha(const Sprite* sprite)
{
	UNREFERENCED_PARAMETER(sprite);

	if (sprite) 
	{
		return sprite->alpha;
	}

	return 0.0f;
}

// Set a Sprite's alpha value.
// (NOTE: Make sure to clamp the resulting alpha value between 0.0f and 1.0f, as the
//	input value might be outside of this range.)
// (HINT: The min() and max() macros can be combined to create a clamp function.)
// Params:
//	 sprite = Pointer to the Sprite component.
//   alpha = The Sprite's new alpha value.
void SpriteSetAlpha(Sprite* sprite, float alpha)
{
	UNREFERENCED_PARAMETER(sprite);
	UNREFERENCED_PARAMETER(alpha);

	sprite->alpha = min(1.0f, max(0.0f, alpha));
}

// Set a Sprite's current frame.
// (NOTE: You must verify that the frameIndex parameter is within the
//	range [0 to frame count - 1] before changing the Sprite's frame index!)
// Params:
//	 sprite = Pointer to the Sprite component.
//   frameIndex = New frame index for the Sprite (0 .. frame count - 1).
// ADDITIONAL REQUIREMENTS:
// - This function must make the following function call:
//     TraceMessage("SpriteSetFrame: frame index = %d", frameIndex);
void SpriteSetFrame(Sprite* sprite, unsigned int frameIndex) 
{
	UNREFERENCED_PARAMETER(sprite);
	UNREFERENCED_PARAMETER(frameIndex);

	if (frameIndex >= 0 && frameIndex >= sprite->frameIndex - 1) 
	{
		sprite->frameIndex = frameIndex; // issues?
	}


	TraceMessage("SpriteSetFrame: frame index = %d", frameIndex); 
}

// Set the Sprite's mesh.
// (NOTE: This mesh may be textured or untextured.)
// (NOTE: This mesh may contain any number of triangles.)
// Params:
//	 sprite = Pointer to the Sprite component.
//   mesh = Pointer to a Mesh object.
void SpriteSetMesh(Sprite* sprite, const Mesh* mesh) 
{
	UNREFERENCED_PARAMETER(sprite);
	UNREFERENCED_PARAMETER(mesh);


	sprite->mesh = mesh;

}

// Set a new SpriteSource for the specified Sprite.
// (NOTE: The spriteSource parameter may be NULL.  This will remove an existing
//	texture from a Sprite and cause the Sprite to be displayed as a colored mesh.)
// Params:
//	 sprite = Pointer to the Sprite component.
//	 spriteSource = Pointer to a SpriteSource (this pointer may be NULL).
void SpriteSetSpriteSource(Sprite* sprite, const SpriteSource* spriteSource) 
{
	UNREFERENCED_PARAMETER(sprite);
	UNREFERENCED_PARAMETER(spriteSource);


	sprite->spriteSource = spriteSource;

}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

