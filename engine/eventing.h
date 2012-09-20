
///
/// Summary:  Prototypes for the cx::engine::eventing class.
/// Remarks:  The eventing class is an abstraction of the SDL message loop allowing for dynamic hooking and unhooking
///           of event handling delegate functions.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_eventing
#define cx_engine_eventing



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <map>
#include <string>

#include "base/eventable.h"



#define  SDL_CX_NULLEVENT  SDL_USEREVENT + 1
#define  SDL_CX_IDLEEVENT  SDL_USEREVENT + 2
#define  SDL_CX_MOVEEVENT  SDL_USEREVENT + 3



namespace cx
{
	namespace engine
	{
		/// Summary:  Describes the event manager for the simulation.
		/// Remarks:  This system is a thin abstraction of the SDL message loop, and therefore the types used are SDL
		///           types, i.e. SDL_Event and its children. Custom events are given the type SDL_UserEvent.
		class eventing : base::eventable
		{
			private:
				std::multimap<unsigned int, base::eventable*>  handlers;

				bool  interrupt;

			protected:
				void  on_quit( SDL_Event );

			public:
				eventing();
                                virtual ~eventing(){};
				void  hook( unsigned int, base::eventable* );
				void  start();
				void  unhook( unsigned int, base::eventable* );

				virtual void  delegate( SDL_Event );
		};
	}
}



#endif
