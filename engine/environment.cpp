
///
/// Summary:  Implementation of the cx::engine::environment class.
/// Remarks:  This should be taken with ./engine/environment.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///



#include "environment.h"



/// Summary:  Constructs the environment class and the eventable parent class.
/// Remarks:  This function's main task is to call the initialise_sdl and initialise_opengl subroutines.
cx::engine::environment::environment( std::string  identifier, glm::ivec2  dimensions, cx::engine::eventing*  events ) : eventable( events )
{
	// Initialise the SDL window manager system.
	this->software.identifier = identifier;
	this->software.dimensions = dimensions;
	initialise_sdl();

	// Initialise the OpenGL graphics library.
	initialise_opengl();

	// This class must handle the SDL_VIDEORESIZE event.
	this->events->hook( SDL_VIDEORESIZE, this );
}



/// Summary:  Destroys the environment at the end of the program.
cx::engine::environment::~environment()
{
	// Exit SDL gracefully.
	SDL_Quit();
}



/// Summary:  Initialises OpenGL.
/// Remarks:  Checks that the system has a recent version of OpenGL installed; then sets up basic OpenGL features, i.e.
///           blending and depth testing.
void  cx::engine::environment::initialise_opengl()
{
	// Attempt to initialise OpenGL through the GLEW library.
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
		throw std::string( (const char*)glewGetErrorString( glew_status ) );

	// Validate the user's OpenGL version.
	if (!GLEW_VERSION_2_1)
		throw std::string( "This software relies on OpenGL 2.1, which is not supported by your system." );

	// Enable and configure blending for all rendering the simulation performs.
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    // Enable and configure depth-testing for all rendering the simulation performs.
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
    glClearDepth( 1.0 );
}



/// Summary:  Initialises SDL.
/// Remarks:  Checks that the system is capable of hosting an SDL window; chooses the best possible settings; then
///           attempts to create the window such that it conforms to our internal representation.
void  cx::engine::environment::initialise_sdl()
{
	// Attempt to initialise the SDL graphics subsystem.
	if (SDL_Init( SDL_INIT_VIDEO ) < 0)
		throw std::string( SDL_GetError() );

	// Attempt to ascertain the user's graphics settings.
	this->hardware.graphics = SDL_GetVideoInfo();
	if (!this->hardware.graphics)
		throw std::string( SDL_GetError() );

	// Set the SDL graphics options.
	this->software.settings  = SDL_OPENGL | SDL_HWPALETTE;                                                          // Standard OpenGL binding with SDL-controlled colour palette.
	this->software.settings |= (this->hardware.graphics->hw_available == 1) ? SDL_HWSURFACE : SDL_SWSURFACE;        // Use graphics hardware if available, else, fall back to software rendering.
	this->software.settings |= (this->hardware.graphics->blit_hw == 1)      ? SDL_HWACCEL   : 0;                    // Use hardware-accelerated blitting if available, else, fall back to software blitting.

	// Set the SDL/OpenGL pre-initialisation options.
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// Attempt to bind an SDL graphics window.
	this->software.handle = SDL_SetVideoMode( this->software.dimensions.x, this->software.dimensions.y, this->hardware.graphics->vfmt->BitsPerPixel, this->software.settings );
	if (!this->software.handle)
		throw std::string( SDL_GetError() );

	// Set the title of the window.
	SDL_WM_SetCaption( this->software.identifier.c_str(), this->software.identifier.c_str() );
}



/// Summary:  Handles the SDL_VIDEORESIZE event.
/// Remarks:  Updates the internal representation of the window, then notifies SDL and OpenGL of the changes.
void cx::engine::environment::on_resize( SDL_Event  event )
{
	// Update the internal representation of the graphics window.
	this->software.dimensions.x = event.resize.w;
	this->software.dimensions.y = event.resize.h;
	this->software.handle       = SDL_SetVideoMode( this->software.dimensions.x, this->software.dimensions.y, this->hardware.graphics->vfmt->BitsPerPixel, this->software.settings );

	// Inform OpenGL of the changes.
	glViewport( 0, 0, this->software.dimensions.x, this->software.dimensions.y );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    SDL_GL_SwapBuffers();
}



/// Summary:  Delegate events to internal functions.
/// Remarks:  Called automatically by the event manager. This subroutine is essentially an extension of the SDL
///           message loop.
void  cx::engine::environment::delegate( SDL_Event  event )
{
	// Call the correct function based on the type of event.
	switch (event.type)
	{
		case SDL_VIDEORESIZE: on_resize( event );
	}
}
