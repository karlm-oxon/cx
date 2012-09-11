
///
/// Summary:  Implementation of the cx::engine::base::scene class.
/// Remarks:  This should be taken with ./engine/base/scene.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "scene.h"



/// Summary:  Dummy member function provides an overridable standard form for a child class' programs initialisation.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should initialise the scene's camera.
void cx::engine::base::scene::initialise_camera()
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::scene::initialise_camera must be overridden by the child class." );
}



/// Summary:  Dummy member function provides an overridable standard form for a child class' programs initialisation.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should initialise the programs list
///           as appropriate.
void cx::engine::base::scene::initialise_programs()
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::scene::initialise_programs must be overridden by the child class." );
}




/// Summary:  Dummy member function provides an overridable standard form for a child class' renderables initialisation.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should initialise the renderables list
///           as appropriate.
void cx::engine::base::scene::initialise_renderables()
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::scene::initialise_renderables must be overridden by the child class." );
}



/// Summary:  Dummy member function provides an overridable standard form for a child class' rendering routine.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should call the rendering subroutine of
///           each member of the renderables list, as well as interacting with OpenGL in any other way necessary to
///           render the scene successfully.
void cx::engine::base::scene::render()
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::scene::render must be overridden by the child class." );
}

