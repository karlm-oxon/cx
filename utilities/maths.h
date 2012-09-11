
///
///
///
///
///



#ifndef cx_utilities_maths
#define cx_utilities_maths



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <cmath>



namespace cx
{
	namespace utilities
	{
		///
		///
		class maths
		{
			private:
				maths();

			public:
				static glm::vec4  angle_to_hue( float angle );
		};
	}
}



#endif
