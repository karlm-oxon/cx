
///
/// Summary:  Prototypes for the cx::engine::eventable class.
/// Remarks:  The eventable class is an abstract class designed to be inherited as a bolt-on interface for any class
///           needing to have a knowledge of the SDL message loop.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_base_eventable
#define cx_engine_base_eventable



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <string>

namespace cx { namespace engine { class eventing; } }



namespace cx
{
	namespace engine
	{
		namespace base
		{
			/// Summary:  Describes an object that can interface with the event manager.
			/// Remarks:  Inheriting from this class adds the prerequisite that base::eventable be initialised with
			///           a pointer to an instance of the event manager, so as to ensure every child class has a link with the
			///           eventing system. The pure virtual delegate function should be overridden to call the internal
			///           event handlers in the child class.
			class eventable
			{
				protected:
					cx::engine::eventing*  events;

				public:
					eventable( cx::engine::eventing* );
					virtual void  delegate( SDL_Event )=0;
			};
		}
	}
}



#endif
