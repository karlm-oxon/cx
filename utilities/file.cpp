
///
/// Summary:  Implementation of the cx::utilities::file class.
/// Remarks:  This should be taken with ./engine/utilities/file.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "file.h"



/// Summary:  Returns the complete contents of a file as a string.
/// Remarks:  Handles the file via an ifstream object, which is buffered into a stringstream and then finalised and
///           returned.
std::string cx::utilities::file::contents( std::string filename )
{
	// Create the handle to the file and the buffer.
	std::ifstream      stream ( filename.c_str() );
	std::stringstream  buffer;

	// Read the buffer and return it.
	buffer << stream.rdbuf();
	return buffer.str();
}
