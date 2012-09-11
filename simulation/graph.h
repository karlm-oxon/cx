
///
///
///
///
///



#ifndef cx_simulation_graph
#define cx_simulation_graph



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


#include <functional>

#include "chunk.h"
#include "../engine/environment.h"
#include "../engine/eventing.h"
#include "../engine/base/eventable.h"
#include "../engine/base/renderable.h"
#include "../engine/base/scene.h"
#include "../engine/pipeline/program.h"
#include "../engine/pipeline/shader.h"

namespace cx {
    namespace simulation {
        class chunk;
        typedef std::complex<float> complexf;
    }
}



namespace cx {
    namespace simulation {
        ///
        ///

        class graph : cx::engine::base::eventable, cx::engine::base::scene {
        protected:

            ///
            ///

            struct uniform_list {
                unsigned int mat4_modelview;
                unsigned int mat4_projection;
            };

        public:

            ///
            ///

            struct attribute_list {
                unsigned int vec4_position;
                unsigned int vec4_color;
            };



        protected:
            cx::engine::environment* engine;
            std::function<complexf(complexf)> function;

            cx::simulation::graph::attribute_list attributes;
            cx::simulation::graph::uniform_list uniforms;

            cx::simulation::chunk* primary;
            std::vector<cx::simulation::chunk*> chunks;

            void on_idle(SDL_Event);
            void on_move(SDL_Event);

            virtual void initialise_camera();
            virtual void initialise_programs();
            virtual void initialise_renderables();

        public:
            graph(std::function<complexf(complexf)>, cx::engine::environment*, cx::engine::eventing*);

            virtual void delegate(SDL_Event);
        };
    }
}



#endif
