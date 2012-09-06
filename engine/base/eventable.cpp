
///
/// Summary:  Implementation of the cx::engine::base::eventable class.
/// Remarks:  This should be taken with ./engine/base/eventable.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "eventable.h"



/// Summary:  Constructs the eventable class.
/// Remarks:  This initialises the events property to point at the event manager, thus exposing the event manager to
///           any child class object, as a child class constructor must also call this constructor.
cx::engine::base::eventable::eventable( cx::engine::eventing*  events )
{
	// Set a reference to the event manager.
	this->events = events;
}



/// Summary:  Dummy member function provides an overridable standard form for a child class' delegating subroutine.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should call the correct internal subroutine
///           as described by the event parameter.
void  cx::engine::base::eventable::delegate( SDL_Event  event )
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::eventable::delegate must be overridden by the child class." );
}
