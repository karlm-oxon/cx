
///
///
///
///
///



#include "engine.h"
#include "simulation.h"
#include "utilities.h"



#include <iostream>



int                  main( int argc, char** argv );
std::complex<float>  function( std::complex<float> );



///
///
int main( int argc, char** argv )
{
	try
	{
		cx::engine::eventing*     events = new cx::engine::eventing();
		cx::engine::environment*  engine = new cx::engine::environment( std::string( "Hello, world!" ), glm::ivec2( 640, 480 ), events );

		cx::simulation::graph*  graph = new cx::simulation::graph( function, engine, events );

		events->start();

		delete engine;
		delete events;

		return 0;
	}
	catch (std::string e)
	{
		std::cerr << e << std::endl;

		return -1;
	}
}



///
///
std::complex<float>  function( std::complex<float> z )
{
	return std::exp( z );
}
