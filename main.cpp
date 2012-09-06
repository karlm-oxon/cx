

#include "engine.h"
#include "utilities.h"


int main( int argc, char** argv )
{
	cx::engine::eventing*     events = new cx::engine::eventing();
	cx::engine::environment*  engine = new cx::engine::environment( std::string( "Hello, world!" ), glm::ivec2( 640, 480 ), events );

	events->start();

	delete engine;
	delete events;

	return 0;
}
