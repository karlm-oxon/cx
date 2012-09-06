
///
/// Summary:  Implementation of the cx::engine::eventing class.
/// Remarks:  This should be taken with ./engine/eventing.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "eventing.h"



/// Summary:  Constructs the eventing class and the eventable parent class.
cx::engine::eventing::eventing() : base::eventable( this )
{
	// Initialise the state of the event manager.
	this->interrupt = false;

	// This class must handle the SDL_QUIT event.
	this->events->hook( SDL_QUIT, this );
}



/// Summary:  Hook a type, handler pair into the event manager.
/// Remarks:  If the pair already exists, the call to hook() will be ignored.
void  cx::engine::eventing::hook( unsigned int  type, base::eventable*  handler )
{
	// Search the portion of the multimap with a matching type for a matching handler: if one is found, exit this subroutine.
	std::pair<std::multimap<unsigned int, base::eventable*>::iterator, std::multimap<unsigned int, base::eventable*>::iterator>  haystack = this->handlers.equal_range( type );
	for (std::multimap<unsigned int, base::eventable*>::iterator  i = haystack.first; i != haystack.second; i++)
		if (i->second == handler)
			return;

	// If execution reaches this point, the handler hasn't already been found, so must be added.
	this->handlers.insert( std::pair<unsigned int, base::eventable*>( type, handler ) );
}


/// Summary:  Unhook a type, handler pair from the event manager.
/// Remarks:  If the pair does not exist, the call to unhook() will be ignored.
void  cx::engine::eventing::unhook( unsigned int  type, base::eventable*  handler )
{
	// Search the portion of the multimap with a matching type for a matching handler: if one is found, erase it.
	std::pair<std::multimap<unsigned int, base::eventable*>::iterator, std::multimap<unsigned int, base::eventable*>::iterator>  haystack = this->handlers.equal_range( type );
	for (std::multimap<unsigned int, base::eventable*>::iterator  i = haystack.first; i != haystack.second; i++)
		if (i->second == handler)
			this->handlers.erase( i );
}



/// Summary:  Begins the event loop.
/// Remarks:  Once executed, start() loops indefinitely until the program ends. Therefore, anything which must be
///           executed in parallel must be loaded into an external thread before start() is called.
/// Gotchas:  This function may take up 100% of a CPU core, but even if so the program will not freeze.
void  cx::engine::eventing::start()
{
	// Parse the message loop until explicitly interrupted by an SDL_QUIT event.
	while (!interrupt)
	{
		// Process all events in the message queue.
		SDL_Event event;
		while (SDL_PollEvent( &event ))
		{
			// Iterate through every handler of that type, calling the delegation function.
			std::pair<std::multimap<unsigned int, base::eventable*>::iterator, std::multimap<unsigned int, base::eventable*>::iterator>  haystack = this->handlers.equal_range( event.type );
			for (std::multimap<unsigned int, base::eventable*>::iterator  i = haystack.first; i != haystack.second; i++)
				i->second->delegate( event );
		}

		// As event processing for this frame is over, send the next frame's idle event.
		event.type      = SDL_CX_IDLEEVENT;
		event.user.type = SDL_CX_IDLEEVENT;
		SDL_PushEvent( &event );
	}
}



/// Summary:  Handles the SDL_QUIT event.
/// Remarks:  This subroutine sets a flag to end the execution of the event manager.
void  cx::engine::eventing::on_quit( SDL_Event  event )
{
	// Interrupt the execution of the event manager.
	this->interrupt = true;
}



/// Summary:  Delegate events to internal functions.
/// Remarks:  Called automatically by the event manager. This subroutine is essentially an extension of the SDL
///           message loop.
void  cx::engine::eventing::delegate( SDL_Event  event )
{
	// Call the correct function based on the kind of event.
	switch (event.type)
	{
		case SDL_QUIT: on_quit( event );
	}
}
