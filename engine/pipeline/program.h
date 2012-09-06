
///
/// Summary:  Prototypes for the cx::engine::pipeline::program class.
/// Remarks:  The shader class describes an OpenGL program object, containing routines for linking an arbitrary set
///           of shaders into a program in the programmable pipeline.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_pipeline_program
#define cx_engine_pipeline_program



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <vector>

#include "shader.h"



namespace cx
{
	namespace engine
	{
		namespace pipeline
		{
			/// Summary:  Describes an OpenGL programmable pipeline program.
			/// Remarks:  Takes a vector of shaders to be linked to create a program: a combination of at least one
			///           vertex and fragment shader into a GPU-based application for rendering geometry.
			class program
			{
				protected:
					unsigned int id;

				public:
					program( std::vector<cx::engine::pipeline::shader> );
					~program();

					unsigned int get_id() { return id; }
			};
		}
	}
}



#endif
