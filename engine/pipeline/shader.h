
///
/// Summary:  Prototypes for the cx::engine::pipeline::shader class.
/// Remarks:  The shader class describes an OpenGL shader object, containing routines for loading external GLSL
///           code and compiling it within the programmable pipeline.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_pipeline_shader
#define cx_engine_pipeline_shader



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <string>

#include "../../utilities/file.h"
#include "../../utilities/opengl.h"



namespace cx
{
	namespace engine
	{
		namespace pipeline
		{
			/// Summary:  Describes an OpenGL programmable pipeline shader object.
			/// Remarks:  Takes a single GLSL file as input for compilation. Creation of a shader program, a linked
			///           combination of at least a vertex and a fragment shader, is left to the pipeline class.
			class shader
			{
				protected:
					unsigned int id;
					unsigned int type;

				public:
					shader( unsigned int, std::string );
					~shader();

					unsigned int get_id()   { return id; }
					unsigned int get_type() { return type; }
			};
		}
	}
}



#endif
