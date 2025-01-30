//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "SpriteSource.h"
#include "DGL.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct SpriteSource
{
	// The dimensions of the sprite sheet.
	// (Hint: These should be initialized to (1, 1).)
	int	numRows;
	int	numCols;

	// Pointer to a texture resource created using the DigiPen Graphics Library (DGL).
	const DGL_Texture* texture;

} SpriteSource;
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

// Dynamically allocate a new SpriteSource object.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: numRows and numCols should be initialized to 1.)
// Returns:
//	 If the memory allocation was successful,
//	   then return a pointer to the allocated memory,
//	   else return NULL.
SpriteSource* SpriteSourceCreate() 
{
	SpriteSource* spriteSource = calloc(1, sizeof(SpriteSource));
	if (spriteSource)
	{
		return spriteSource;
	}

	return NULL;
}

// Free the memory associated with a SpriteSource object.
// (NOTE: The DGL_Texture resource must be freed using DGL_Graphics_FreeTexture().)
// (NOTE: The SpriteSource object must be freed using free().
// (NOTE: The SpriteSource pointer must be set to NULL.)
// Params:
//	 spriteSource = Pointer to the SpriteSource pointer.
void SpriteSourceFree(SpriteSource** spriteSource)
{
	UNREFERENCED_PARAMETER(spriteSource);

	DGL_Graphics_FreeTexture(&(*spriteSource)->texture);

	free(*spriteSource);
	*spriteSource = NULL; 
}

// Load a texture from a file (may be an Col x Row sprite sheet).
// (NOTE: The folder path, "Assets/" should be prepended to the texture name before
//    opening the file.  The function sprintf_s can be used for this purpose.
//    https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l)
// Params:
//	 numCols = The number of columns in the sprite sheet.
//	 numRows = The number of rows in the sprite sheet.
//	 textureName = The name of the texture to be loaded.
void SpriteSourceLoadTexture(SpriteSource* spriteSource, int numCols, int numRows, const char* textureName)
{
	UNREFERENCED_PARAMETER(spriteSource);
	UNREFERENCED_PARAMETER(numCols);
	UNREFERENCED_PARAMETER(numRows);
	UNREFERENCED_PARAMETER(textureName);

	char texturePath[256];
	sprintf_s(texturePath, sizeof(texturePath), "./Assets/%s", textureName);

	spriteSource->texture = DGL_Graphics_LoadTexture(texturePath);

	spriteSource->numCols = numCols;
	spriteSource->numRows = numRows;

}

// Returns the maximum number of frames possible, given the dimensions of the sprite sheet.
// (Hint: Frame count = numCols * numRows.)
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
// Returns:
//	 If the SpriteSource pointer is valid,
//		then return the calculated frame count (numCols * numRows),
//		else return 0.
unsigned SpriteSourceGetFrameCount(const SpriteSource* spriteSource)
{
	UNREFERENCED_PARAMETER(spriteSource);

	if (spriteSource)
	{
		return (spriteSource->numCols * spriteSource->numRows);
	}

	return 0;
}

// Returns the UV coordinates of the specified frame in a sprite sheet.
// (Hint: Refer to the Week 2 lecture slides for the correct calculations.)
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
//	 frameIndex = A frame index within a sprite sheet.
//   u = Pointer to a float to contain the U coordinate. 
//   v = Pointer to a float to contain the V coordinate. 
void SpriteSourceGetUV(const SpriteSource* spriteSource, unsigned int frameIndex, float* u, float* v) 
{
	UNREFERENCED_PARAMETER(spriteSource);
	UNREFERENCED_PARAMETER(frameIndex);
	UNREFERENCED_PARAMETER(u);
	UNREFERENCED_PARAMETER(v);


	//uSize = 1.0f / numColumns;
	//vSize = 1.0f / numRows

	//uOffset = uSize * (frameIndex % numColumns);
	//vOffset = vSize * (frameIndex / numColumns);


	float uOffset = 1.0f / spriteSource->numCols;
	float vOffset = 1.0f / spriteSource->numRows;

	*u = uOffset / (frameIndex % spriteSource->numCols);
	*v = vOffset / (frameIndex / spriteSource->numCols);
}

// Sets a SpriteSource texture for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTexture(const SpriteSource* spriteSource) 
{
	UNREFERENCED_PARAMETER(spriteSource);


	DGL_Graphics_SetTexture(spriteSource->texture);

}

// Sets the texture UV offsets for rendering.
// Params:
//	 spriteSource = Pointer to the SpriteSource object.
void SpriteSourceSetTextureOffset(const SpriteSource* spriteSource, unsigned frameIndex)
{
	UNREFERENCED_PARAMETER(spriteSource);
	UNREFERENCED_PARAMETER(frameIndex);

	DGL_Vec2 offset = { 0,0 };

	SpriteSourceGetUV(spriteSource, frameIndex, &offset.x, &offset.y);
	DGL_Graphics_SetCB_TextureOffset(&offset);

	//issues?
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

