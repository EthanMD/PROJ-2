//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Mesh.h"
#include "DGL.h"
#include "stdio.h"
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct Mesh
{
	// The name of the Mesh.  This will be used later in the semester.
	char name[32];

	// Pointer to the DGL_Mesh resource.
	const DGL_Mesh* meshResource;

	// The draw mode to use when rendering the mesh (Usually "DGL_DM_TRIANGLELIST").
	DGL_DrawMode drawMode;
} Mesh;
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

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new Mesh object but leave it empty.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// Returns:
//	 If the mesh was created successfully,
//	   then return a pointer to the created Mesh,
//	   else return NULL.
Mesh* MeshCreate() 
{
	Mesh* mesh = calloc(1, sizeof(Mesh));
	if (mesh)
	{
		return mesh;
	}

	return NULL;
}



// Build a quadrilateral mesh and store it in the specified Mesh object.
// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
// (NOTE: The Mesh name can be stored using strcpy_s(). For example:
//    strcpy_s(mesh->name, _countof(mesh->name), name); )
// (NOTE: The drawMode should be set to DGL_DM_TRIANGLELIST.)
// Params:
//   mesh = Pointer to an existing, empty Mesh object.
//	 xHalfSize = The X half-size of the mesh.
//	 yHalfSize = The Y half-size of the mesh.
//   uSize = The U size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//   vSize = The V size of the mesh, relative to texture coordinates (0.0 .. 1.0).
//	 name = A name for the mesh.
void MeshBuildQuad(Mesh* mesh, float xHalfSize, float yHalfSize, float uSize, float vSize, const char* name)
{
	strcpy_s(mesh->name, _countof(mesh->name), name);
	mesh->drawMode = DGL_DM_TRIANGLELIST;

	DGL_Graphics_StartMesh();

	// This shape has 2 triangles
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){  0.0f, vSize },
		&(DGL_Vec2){ xHalfSize,  yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize,  0.0f },
		&(DGL_Vec2){ xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize, vSize });
	DGL_Graphics_AddTriangle(
		&(DGL_Vec2){ -xHalfSize, -yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){  0.0f, vSize },
		&(DGL_Vec2){ -xHalfSize, yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){  0.0f,  0.0f },
		&(DGL_Vec2){ xHalfSize, yHalfSize }, &(DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f }, &(DGL_Vec2){ uSize,  0.0f });

	// Save the mesh (as a list of triangles).
	mesh->meshResource = DGL_Graphics_EndMesh();
	//assert(mesh && "Failed to create meshColor!"); // issue assert not working
}

// Build a "spaceship" mesh and store it in the specified Mesh object.
// (NOTE: This must be a "unit"-sized triangular mesh with the same characteristics as
//    the "triangular, colored mesh" created in DemoScene.c.)
// (NOTE: The DGL_Mesh object must be created using DGL_Graphics_StartMesh,
//    DGL_Graphics_AddTriangle, and DGL_Graphics_EndMesh.)
// (NOTE: The Mesh name can be stored using strcpy_s().)
// (NOTE: The drawMode should be set to DGL_DM_TRIANGLELIST.)
// Params:
//   mesh = Pointer to an existing, empty Mesh object.
void MeshBuildSpaceship(Mesh* mesh) //possibly messed up
{
	UNREFERENCED_PARAMETER(mesh);

	mesh->drawMode = DGL_DM_TRIANGLELIST;

	DGL_Graphics_StartMesh();



	DGL_Graphics_AddTriangle(
		&(DGL_Vec2) { 0.5f, 0.0f }, & DGL_Color_Yellow, & (DGL_Vec2){ 0.0f, 0.0f },
		& (DGL_Vec2) {-0.5f, -0.5f}, & DGL_Color_Red, & (DGL_Vec2){ 0.0f, 0.0f },
		& (DGL_Vec2) {-0.5f, 0.5f}, & DGL_Color_Red, & (DGL_Vec2){ 0.0f, 0.0f });
	
	
	


	mesh->meshResource = DGL_Graphics_EndMesh();

}

// Render a mesh.
// (NOTE: This is done using DGL_Graphics_DrawMesh().)
// Params:
//   mesh = Pointer to a Mesh to be rendered.
void MeshRender(const Mesh* mesh) 
{

	DGL_Graphics_DrawMesh(mesh->meshResource, mesh->drawMode);
	
}

// Free the memory associated with a mesh.
// (NOTE: The DGL_Mesh resource must be freed using DGL_Graphics_FreeMesh().)
// (NOTE: The Mesh object must be freed using free().
// (NOTE: The Mesh pointer must be set to NULL.)
// Params:
//   mesh = Pointer to the Mesh pointer.
void MeshFree(Mesh** mesh) 
{

	DGL_Graphics_FreeMesh(&(*mesh)->meshResource); 

	free(*mesh);
	*mesh = NULL;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------


