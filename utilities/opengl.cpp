
///
/// Summary:  Implementation of the cx::engine::utilities::opengl class.
/// Remarks:  This should be taken with ./engine/utilities/opengl.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///

#include "opengl.h"



/// Summary:  Returns the contents of the specified log for the object in question.
/// Remarks:  Valid values for log_type are object::shader and object::program; the id parameter must point to either a
///           shader ID or a program ID as set by OpenGL. The log returned is thus specific to that object,
std::string  cx::utilities::opengl::get_log( unsigned int id, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog )
{
	// Ascertain the length of the log.
	int  log_length;
	glGet__iv( id, GL_INFO_LOG_LENGTH, &log_length );

	// Buffer the log into a character array.
	char*  log_cstr = new char [log_length];
	glGet__InfoLog( id, log_length, NULL, log_cstr );

	// Transfer the character array into a string.
	std::string  log ( log_cstr );
	delete [] log_cstr;

	// Return the string containing the info log.
	return log;
}
