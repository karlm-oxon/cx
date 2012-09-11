
///
/// Summary:  Implementation of the cx::engine::base::renderable class.
/// Remarks:  This should be taken with ./engine/base/renderable.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "renderable.h"



/// Summary:  Constructs the renderable class.
/// Remarks:  This initialises the domain property to point at the rendering manager ("scene"), thus exposing the
///           rendering manager to any child class object, as a child class constructor must also call this constructor.
cx::engine::base::renderable::renderable( cx::engine::base::scene*  domain )
{
	// Set a reference to the rendering manager.
	this->domain = domain;
}



/// Summary:  Dummy member function provides an overridable standard form accessing a child class' model transform.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should return the model transform necessary
///           to translate and scale the object coordinates into world coordinates.
glm::mat4  cx::engine::base::renderable::get_transformation()
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::renderable::get_transformation must be overridden by the child class." );
}



/// Summary:  Dummy member function provides an overridable standard form for a child class' rendering subroutine.
/// Remarks:  This function cannot be declared pure virtual, as this class must be usable as an interface, rather than
///           merely an abstract class. The implementation of this function should send the correct geometry to the
///           OpenGL rendering pipeline in such a manner as described in the parameters array.
void  cx::engine::base::renderable::render( void*  parameters )
{
	// This member function may not be called, so raise an exception at runtime if it is.
	throw std::string( "The member function base::renderable::render must be overridden by the child class." );
}
