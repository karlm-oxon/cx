
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






