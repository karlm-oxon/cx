
///
/// Summary:  Implementation of the cx::engine::pipeline::program class.
/// Remarks:  This should be taken with ./engine/pipeline/program.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "program.h"



/// Summary:  Constructs a program object.
/// Remarks:  Sends each compiled shader contained in the parameters vector to the linker so that a full program can be
///           made active on the OpenGL programmable pipeline.
cx::engine::pipeline::program::program( std::vector<cx::engine::pipeline::shader> shaders )
{
	// Create a new program in the pipeline.
	this->id = glCreateProgram();

	// For each shader present, attach it to the program object we are building.
	for (std::vector<cx::engine::pipeline::shader>::iterator i = shaders.begin(); i != shaders.end(); i++)
		glAttachShader( this->id, i->get_id() );

	// Attempt to link the program.
	int status;
	glLinkProgram( this->id );
	glGetProgramiv( this->id, GL_LINK_STATUS, &status );

	// If something went wrong, raise an exception and delete the program.
	if (!status)
	{
		std::string exception = utilities::opengl::get_log( this->id, glGetProgramiv, glGetProgramInfoLog );
		glDeleteProgram( this->id );
		throw exception;
	}
}



/// Summary:  Binds a handle to a GLSL variable.
/// Remarks:  The binding_function should typically be glGetAttribLocation or glGetUniformLocation.
int  cx::engine::pipeline::program::bind( std::string variable, PFNGLGETATTRIBLOCATIONPROC binding_function )
{
	// Bind a handle to the specified variable in this program, as long as it's valid.
	int  handle = binding_function( this->id, variable.c_str() );
	if (handle == -1)
		throw std::string( "Could not bind a handle to the GLSL variable " ) + variable + std::string( "." );
	return handle;
}



/// Summary:  Destroys a program object.
/// Remarks:  When the program object is no longer being used, this unloads the program from the programmable pipeline.
cx::engine::pipeline::program::~program()
{
	// Delete this program object.
	glDeleteProgram( this->id );
}
