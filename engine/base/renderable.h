
///
/// Summary:  Prototypes for the cx::engine::renderable class.
/// Remarks:  The renderable class is an abstract class designed to be inherited as a bolt-on interface for any class
///           needing to send geometry into the OpenGL rendering pipeline.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_base_renderable
#define cx_engine_base_renderable



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <string>

namespace cx { namespace engine { namespace base { class scene; } } }



namespace cx
{
	namespace engine
	{
		namespace base
		{
			/// Summary:  Describes an object that can interface with a rendering manager.
			/// Remarks:  Inheriting from this class adds the prerequisite that base::renderable be initialised with
			///           a pointer to an instance of the rendering manager; this ensures every child class has a link
			///           with the rendering system. The pure virtual render member function should be overridden to
			///           send the child object's geometry to the OpenGL rendering pipeline.
			class renderable
			{
				protected:
					cx::engine::base::scene*  domain;

				public:
					renderable( cx::engine::base::scene* );
					virtual glm::mat4  get_transformation()=0;
					virtual void       render( void* )=0;
			};
		}
	}
}



#endif
