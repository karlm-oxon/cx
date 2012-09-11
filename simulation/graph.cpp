#include "graph.h"



///
///
cx::simulation::graph::graph(std::function<complexf(complexf)> function, cx::engine::environment* engine, cx::engine::eventing* events ) : cx::engine::base::eventable( events ), cx::engine::base::scene()
{
	// Set the reference to the SDL and OpenGL environment this scene renders into.
	this->engine   = engine;
	this->function = function;

	// Call the resource initialisation subroutines.
	initialise_camera();
	initialise_programs();
	initialise_renderables();

	// Set up eventing.
	events->hook( SDL_CX_IDLEEVENT, this );
	events->hook( SDL_CX_MOVEEVENT, this );
}



///
///
void  cx::simulation::graph::on_idle( SDL_Event event )
{
	// Set up the programmable pipeline program.
	glUseProgram( this->programs[0]->get_id() );

	// Create the transformation matrices.
	glm::mat4  model;
	glm::mat4  view       = camera->get_transformation();
	glm::mat4  projection = (glm::mat4)glm::perspective( 45.0, (double)this->engine->get_aspect_ratio(), 1.0, 256.0 );

	// Iterate over all renderable objects.
	for (std::vector<cx::engine::base::renderable*>::iterator  i = renderables.begin(); i != renderables.end(); i++)
	{
		// Create the modelview transformation.
		glm::mat4  modelview;
		model     = (*i)->get_transformation();
		modelview =  view * model;

		// Send the transformations to the programmable pipeline.
        glUniformMatrix4fv( uniforms.mat4_modelview,  1, GL_FALSE, glm::value_ptr( modelview ) );
        glUniformMatrix4fv( uniforms.mat4_projection, 1, GL_FALSE, glm::value_ptr( projection ) );

        // Call the rendering subroutine for this renderable object.
        (*i)->render( (void*)&attributes );
	}

	// Tell SDL to display the contents of the OpenGL rendered scene.
	SDL_GL_SwapBuffers();
}



///
///
void  cx::simulation::graph::on_move( SDL_Event event )
{
	// Ascertain the new position of the camera.
	glm::vec3 position = *(glm::vec3*)event.user.data1;
}



///
///
void  cx::simulation::graph::delegate( SDL_Event event )
{
	if (event.type == SDL_USEREVENT) std::cerr << "idle" << std::endl;

	// Call the correct function based on the type of event.
	switch (event.type)
	{
		case SDL_CX_IDLEEVENT: on_idle( event ); break;
		case SDL_CX_MOVEEVENT: on_move( event ); break;
	}
}



///
///
void  cx::simulation::graph::initialise_camera()
{
	// Set up a static camera.
	this->camera = new cx::engine::base::camera ( glm::vec3( 0.0, 0.0, 10.0 ), glm::vec3( 0.0, 0.0, 0.0 ), glm::vec3( 0.0, 1.0, 0.0 ) );
}



///
///
void  cx::simulation::graph::initialise_programs()
{
	// Create the vertex and fragment shaders.
	cx::engine::pipeline::shader  basic_fragment ( GL_FRAGMENT_SHADER, std::string( "basic.fragment.glsl" ) );
	cx::engine::pipeline::shader  basic_vertex   ( GL_VERTEX_SHADER,   std::string( "basic.vertex.glsl" ) );

	// Build the shaders into a program.
	cx::engine::pipeline::program*  basic = new cx::engine::pipeline::program( { basic_vertex, basic_fragment } );
	this->programs.push_back( basic );

	// Set up the attributes and uniforms passed to the programmable pipeline.
	this->attributes.vec4_position = this->programs[0]->bind( "position",   glGetAttribLocation );
	this->attributes.vec4_color    = this->programs[0]->bind( "color",      glGetAttribLocation );
	this->uniforms.mat4_modelview  = this->programs[0]->bind( "modelview",  glGetUniformLocation );
	this->uniforms.mat4_projection = this->programs[0]->bind( "projection", glGetUniformLocation );
}



///
///
void  cx::simulation::graph::initialise_renderables()
{
	// Specify the correct format for a chunk.
	cx::simulation::chunk::specification.function         = this->function;
	cx::simulation::chunk::specification.levels_of_detail = 2;
	cx::simulation::chunk::specification.resolution       = 10;
	cx::simulation::chunk::specification.scale_data       = 0.02;
	cx::simulation::chunk::specification.scale_world      = 0.025;

	// Create the parameters for a test chunk.
	chunk::local_parameters  p;
	p.center = glm::vec2( 0.0, 0.0 );

	// Push the test chunk onto the renderables list.
	cx::simulation::chunk*  c = new cx::simulation::chunk( p, this );
	this->renderables.push_back( c );
}
