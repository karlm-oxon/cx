
///
/// Summary:  Implementation of the cx::engine::pipeline::shader class.
/// Remarks:  This should be taken with ./engine/pipeline/shader.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "shader.h"



/// Summary:  Constructs a shader object.
/// Remarks:  Automatically creates a shader of the specified type, by loading the contents of the file given and then
///           sending this GLSL code to the OpenGL shader compiler.
cx::engine::pipeline::shader::shader( unsigned int type,const std::string file, bool fromString )
{
	// Set the type of this shader.
	this->type = type;
        
        std::string  code;
	const char*  code_cstr ;
	int          code_length;
        
        if (!fromString){
	// Load the source code from the file.
	 code        = cx::utilities::file::contents( file );
        }
        
        else {
           code=file; 
        }
        
        code_cstr   = code.c_str();
	code_length = code.size();
        
	// Check that the file is not blank.
	if (code.size() == 0)
		throw std::string( "Shader instantiated with a blank file." );

	// Send the file to OpenGL's GLSL compiler.
	int status;
	this->id = glCreateShader( this->type );
	glShaderSource( this->id, 1, &code_cstr, &code_length );
	glCompileShader( this->id );
	glGetShaderiv( this->id, GL_COMPILE_STATUS, &status );

	// Check the compilation status, raising an exception if compilation did not complete.
	if (!status)
		throw cx::utilities::opengl::get_log( this->id, glGetShaderiv, glGetShaderInfoLog );
}



/// Summary:  Destroys a shader object.
/// Remarks:  When the shader object is no longer being used, this unloads the shader from the programmable pipeline.
cx::engine::pipeline::shader::~shader()
{
	// Delete this shader object.
	glDeleteShader( this->id );
}
