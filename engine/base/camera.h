
///
///
///
///
///



#ifndef cx_engine_base_camera
#define cx_engine_base_camera



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>
#include <ext.hpp>

#include "../eventing.h"
#include "eventable.h"




namespace cx {
    namespace engine {
        namespace base {
            ///
            ///

            class camera : cx::engine::base::eventable {
                

            protected:
                glm::vec3 position;
                glm::mat4 look;
                void send_move_message ();
            public:
                camera(glm::vec3, glm::vec3, glm::vec3, cx::engine::eventing*);
                camera();
                virtual glm::mat4 get_transformation();

                glm::vec3 get_position() {
                    return position;
                }
                virtual void delegate (SDL_Event){};

                virtual void update(GLuint time_elapsed) {
                };
            };
        }
    }
}



#endif
