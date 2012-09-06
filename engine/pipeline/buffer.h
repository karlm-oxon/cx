
///
/// Summary:  Prototypes for the cx::engine::pipeline::buffer class.
/// Remarks:  The buffer class describes an OpenGL data buffer which is stored on the GPU and utilised within the
///           programmable pipeline.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_pipeline_buffer
#define cx_engine_pipeline_buffer



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>



namespace cx
{
	namespace engine
	{
		namespace pipeline
		{
			/// Summary:  Describes a GPU-based data buffer stored in the OpenGL programmable pipeline.
			/// Remarks:  Stores the data buffer of specified size in the storage area for the specified target,
			///           automatically creating an OpenGL handle to that buffer for later use.
			class buffer
			{
				protected:
					unsigned int  id;
					unsigned int  target;

				public:
					buffer( unsigned int, void*, int, unsigned int );
					~buffer();

					unsigned int  get_id()     { return id; }
					unsigned int  get_target() { return target; }
			};
		}
	}
}



#endif
