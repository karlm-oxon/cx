
///
/// Summary:  Contains static utility functions pertaining to the OpenGL backend.
/// Remarks:  In some functions an object ID must be supplied, and OpenGL must know what kind of object it is. In these
///           situations, the cx::utilities::object enumeration must be referenced.
/// Authors:  Jack K., Karl M.
///

#ifndef cx_utilities_opengl
#define cx_utilities_opengl



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <string>



namespace cx
{
	namespace utilities
	{
		class opengl
		{
			private:
				opengl();

			public:
				static std::string  get_log( unsigned int, PFNGLGETSHADERIVPROC, PFNGLGETSHADERINFOLOGPROC );
		};
	}
}



#endif
