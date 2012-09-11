
///
///
///
///
///



#ifndef cx_engine_base_camera
#define cx_engine_base_camera



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>

#include "../eventing.h"



namespace cx
{
	namespace engine
	{
		namespace base
		{
			///
			///
			class camera
			{
				private:
					glm::mat4  look;

				protected:
					glm::vec3  position;

				public:
					camera( glm::vec3, glm::vec3, glm::vec3 );
					glm::mat4  get_transformation();

					glm::vec3  get_position() { return position; }
			};
		}
	}
}



#endif
