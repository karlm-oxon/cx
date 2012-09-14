
///
///
///
///
///



#include "engine.h"
#include "simulation.h"
#include "utilities.h"




#include <iostream>



int main(int argc, char** argv);




int main(int argc, char** argv) {
   // try {
        cx::engine::eventing* events = new cx::engine::eventing();
        cx::engine::environment* engine = new cx::engine::environment(std::string("Hello, world!"), glm::ivec2(640, 480), events);
        
        cx::utilities::complex_function parser;
        cx::simulation::graph* graph = new cx::simulation::graph(0.001, engine, events);

        events->start();

        delete engine;
        delete events;

        return 0;
 //   } catch (std::string e) {
  //      std::cerr << e << std::endl;

        return -1;
    }
//}




///
///
