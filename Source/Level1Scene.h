//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.h
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright � 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {	// Assume C declarations for C++.
#endif

	//------------------------------------------------------------------------------
	// Forward References:
	//------------------------------------------------------------------------------

	typedef struct Scene Scene;

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Typedefs:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Get the instance of the Stub Scene.
	// Returns:
	//	 Pointer to the base Scene structure for this derived Scene.
	const Scene* Level1SceneGetInstance(void);

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

