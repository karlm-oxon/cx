
///
/// Summary:  Implementation of the cx::engine::pipeline::buffer class.
/// Remarks:  This should be taken with ./engine/pipeline/buffer.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "buffer.h"



/// Summary:  Constructs an OpenGL buffer object.
/// Remarks:  The data provided is stored in the specified area on the programmable pipeline in the specified manner.
cx::engine::pipeline::buffer::buffer( unsigned int target, void* data, int size, unsigned int usage )
{
	// Set up the properties of the object.
	this->target = target;
	glGenBuffers( 1, &this->id );

	// Bind the buffer to OpenGL.
	glBindBuffer( this->target, this->id );
	glBufferData( this->target, size, data, usage );
	glBindBuffer( this->target, NULL );
}



/// Summary:  Destroys an OpenGL buffer object.
/// Remarks:  When the buffer is no longer being used, this deletes the buffer from the programmable pipeline.
cx::engine::pipeline::buffer::~buffer()
{
	// Delete the buffer from the programmable pipeline.
	glDeleteBuffers( 1, &this->id );
}
