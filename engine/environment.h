
///
/// Summary:  Prototypes for the cx::engine::environment class.
/// Remarks:  The environment class describes the "space" in which the simulation is rendered, and how the operating
///           system understands that space.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_environment
#define cx_engine_environment



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <string>

#include "eventing.h"
#include "base/eventable.h"



namespace cx
{
	namespace engine
	{
		/// Summary:  Contains information on the user's hardware gathered at runtime.
		/// Remarks:  The graphics structure contains information on the user's graphics card and drivers.
		struct hardware
		{
			const SDL_VideoInfo*  graphics;
		};

		/// Summary:  Contains information on how the environment presents itself to the operating system.
		/// Remarks:  The identifier string refers to the name of the simulation's window in the windowing system;
		///           The dimensions vector contains the width and height of the simulation's window in pixels;
		///           The settings bitmask contains information about the system used by SDL to create the window.
		struct software
		{
			std::string   identifier;
			glm::ivec2    dimensions;
			unsigned int  settings;
			SDL_Surface*  handle;
		};

		/// Summary:  Describes the environment of the simulation.
		/// Remarks:  Contains methods to set up SDL and OpenGL; the use of these libraries is fixed in this engine.
		class environment : base::eventable
		{
			private:
				cx::engine::hardware  hardware;
				cx::engine::software  software;

			protected:
				void  initialise_sdl();
				void  initialise_opengl();

				void  on_resize( SDL_Event );

			public:
				environment( std::string, glm::ivec2, cx::engine::eventing* );
				~environment();
				float  get_aspect_ratio();

				virtual void delegate( SDL_Event );
		};
	}
}



#endif
