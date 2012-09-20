///
/// Summary:  Prototypes for the cx::engine::pipeline::texture class.
/// Remarks:  Describes a GPU-based texture stored in the OpenGL programmable pipeline.
///           
/// Authors:  Jack K., Karl M.
///
#include "texture.h"

/// Summary:  Constructs an OpenGL buffer object.
/// Remarks:  The data provided is stored in the specified area on the programmable pipeline in the specified manner.
cx::engine::pipeline::texture::texture(const unsigned int itype, const unsigned int itexture_unit):
type (itype), texture_unit(itexture_unit)
{
	 
    glActiveTexture(texture_unit);
    glGenTextures(1, &this->id);
   
   
}


void cx::engine::pipeline::texture::bind(){
     glActiveTexture(texture_unit);
     glBindTexture(this->type, this->id);
}

void cx::engine::pipeline::texture::unbind(){
     glBindTexture(this->type, (GLuint) NULL);
}

/// Summary:  Destroys an OpenGL buffer object.
/// Remarks:  When the buffer is no longer being used, this deletes the buffer from the programmable pipeline.
cx::engine::pipeline::texture::~texture()
{
	// Delete the buffer from the programmable pipeline.
	glDeleteTextures (1,&this->id);
}