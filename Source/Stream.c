//------------------------------------------------------------------------------
//
// File Name:	Stream.c
// Author(s):	Ethan Macias-Denham (ethan.maciasdenham)
// Project:		Project 0
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Stub.h"
#include "Stream.h"
#include "Trace.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------



// Open a file for reading.
// (NOTE: Use fopen_s() with the "rt" option.)
// (NOTE: You must generate the following trace message if the file was not opened successfully:
//	  TraceMessage("Error: StreamOpen could not open file %s; %s", filePath, errorMsg);
//	  Where errorMsg is a char array containing the error message obtained using strerror_s().)
// Params:
//	 filePath = The file to be opened for reading.
// Returns:
//	 NULL if filePath is NULL or the file could not be opened.
//	 Pointer to a FILE object if the file was opened successfully.
Stream StreamOpen(const char* filePath)
{
	FILE* stream;
	fopen_s(&stream, filePath, "rt"); //what should this log be called?
	if (!stream) 
	{
		char errorMsg[90];
		strerror_s(errorMsg, 90, ERROR_FILE_NOT_FOUND);
		TraceMessage("Error: StreamOpen could not open file %c; %c", filePath, errorMsg);
		return NULL;
	}
		return stream;
}


// Read a single integer from a stream.
// (NOTE: Verify that the stream is valid first.)
// (NOTE: Use fscanf_s() to scan the input stream for an integer.)
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 0 if the stream was not opened succesfully;
//	 otherwise, an integer value read from the file.
int StreamReadInt(Stream stream) 
{
	int streamInt = 0;

	if (stream) 
	{
		if (fscanf_s(stream, "%i", &streamInt)) //understand
		{
			//integer value read from the file.
			return streamInt;
		}
	}
	// 0 if the stream was not opened succesfully;
	return 0;
}

//// Read a single float from a stream.
//// (NOTE: Verify that the stream is valid first.)
//// (NOTE: Use fscanf_s() to scan the input stream for a float.)
//// Params:
////	 stream = The file stream from which to read.
//// Returns:
////	 If the stream was opened succesfully,
////	   then return a float value read from the file,
////	   else return 0.
float StreamReadFloat(Stream stream) 
{
	float streamF = 0.0f;

	if (stream)
	{
		if (fscanf_s(stream, "%f", &streamF)) //understand
		{
			//integer value read from the file.
			return streamF;
		}
	}
	// 0 if the stream was not opened succesfully;
	return 0.0f;
}

//// Read the data for a Vector2D from a stream.
//// (NOTE: Verify that the stream and vector pointer are valid first.)
//// (HINT: Use StreamReadFloat() to read the x and y values, in sequence.)
//// Params:
////	 stream = The file stream from which to read.
//// Returns:
////	 If the stream and vector pointer are both valid,
////	   then fill the vector with two float values (x & y),
////	   else do nothing (optionally, write an error message to the trace log).
void StreamReadVector2D(Stream stream, Vector2D* vector)
{
	if (stream && vector)
	{
		
		float x = StreamReadFloat(stream);
		float y = StreamReadFloat(stream);
		if (x && y) 
		{
			vector->x = x;
			vector->y = y;
		}
	}
	// else do nothing(optionally, write an error message to the trace log).
}

//// Close an opened stream.
//// (NOTE: Do not attempt to close the stream if the pointer is null.)
//// (PRO TIP: Avoid dangling pointers by setting the FILE pointer to NULL.)
//// Params:
////	 stream = The file stream to be closed.
void StreamClose(Stream* stream) 
{
	if (stream)
	{
		fclose(*stream);
		*stream = NULL;
	}
}


// Read a token (a single word) from a file.
// Suggested steps:
//	 - Set the first value in tokenBuffer to 0
//	 - If the stream was opened successfully,
//	   - Read a string ("%s") into tokenBuffer using fscanf_s()
//	 - Return tokenBuffer
// Params:
//	 stream = The file stream from which to read.
// Returns:
//	 Pointer to tokenBuffer
const char* StreamReadToken(Stream stream)
{
	static char tokenBuffer[1024] = { 0 };

	if (stream)
	{
		unsigned int bufferSize = _countof(tokenBuffer);

		fscanf_s(stream, "%s", tokenBuffer, bufferSize);

		return tokenBuffer;
	}


	return NULL;
}
