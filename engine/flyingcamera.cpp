#include <SDL/SDL_events.h>

#include "flyingcamera.h"

void cx::engine::flying_camera::update(GLuint time_elapsed) {
    //Get keys
    Uint8*keys = SDL_GetKeyState(NULL);
    //Set the velocity of the camera taking into account the orientation and 
    // which keys are pressed
     orientation.normalise();
    glm::vec3 vel = orientation.rotate(
            glm::vec3((keys[SDLK_d] - keys[SDLK_a]) * sensitivity.trans,
            (keys[SDLK_w] - keys[SDLK_s]) * sensitivity.trans+wheel,
            0.0f));
    wheel=0;
    float pitchVel = (keys[SDLK_UP] - keys[SDLK_DOWN]) * sensitivity.rot;
    float yawVel = (keys[SDLK_LEFT] - keys[SDLK_RIGHT]) * sensitivity.rot;
    float rollVel = (keys[SDLK_q] - keys[SDLK_e]) * sensitivity.rot;
    //Update the state variables
    orientation =
            orientation
            * cx::utilities::quaternionf (glm::vec3(0, 1, 0),time_elapsed*rollVel)
            * cx::utilities::quaternionf( glm::vec3(1, 0, 0),time_elapsed*pitchVel)
            * cx::utilities::quaternionf (glm::vec3(0, 0, 1),time_elapsed*yawVel);
    position += (float) time_elapsed*vel;
   
    //If position has changed, update
    if (vel.x != 0 || vel.y != 0 || vel.z != 0)
        this->send_move_message();

};


//These don't do anything yet
void cx::engine::flying_camera::delegate(SDL_Event event) {
      // Call the correct function based on the type of event.
    switch (event.type) {
        case SDL_MOUSEMOTION: on_mouse_move(event);
            break;
        case SDL_MOUSEBUTTONUP: on_mouse_button (event);
    }
};

void cx::engine::flying_camera::on_mouse_move(SDL_Event event) {
  //  GLint time=mouse_time.get_time_elapsed();
    if ((event.motion.state & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK){
   orientation=orientation
            *cx::utilities::quaternionf (glm::vec3(1,0,0),-sensitivity.mouse*event.motion.yrel)
            *cx::utilities::quaternionf (glm::vec3(0,0,1),-sensitivity.mouse*event.motion.xrel);
    orientation.normalise();
    }
}

void cx::engine::flying_camera::on_mouse_button(SDL_Event event) {
  //  GLint time=mouse_time.get_time_elapsed();
    if (event.button.button ==SDL_BUTTON_WHEELUP){
        wheel += sensitivity.wheel;
    }
    else if (event.button.button ==SDL_BUTTON_WHEELDOWN){
        wheel -= sensitivity.wheel;
    }
}


glm::mat4 cx::engine::flying_camera::get_transformation() {
    return look*orientation.getMatrix() * glm::translate(glm::mat4x4(1.0f), -position);

}


cx::engine::flying_camera::flying_camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up, cx::engine::eventing* events)
 {
    // Set the position, interest-direction and up-direction of the static camera.
    this->position = position;
    glm::vec3 norm_dir = glm::normalize(direction);
    glm::vec3 norm_up = glm::normalize(up);
//    mouse_time.reset_start();
    // Set the view transformation with a glm::lookAt call.
     glm::vec3 ahead (0,1,0); glm::vec3 eup (0,0,1);
    this->look = glm::lookAt(glm::vec3(0, 0, 0), ahead, eup);
    if (ahead!= norm_dir){
    orientation = cx::utilities::quaternionf(glm::normalize(glm::cross(ahead,norm_dir )),
            std::acos(glm::dot(ahead,norm_dir))
            );
    }
    else {orientation.s=0;
            orientation.v =glm::vec3 (1,0,0);}
    eup=orientation.rotate(eup);
    if (norm_up!=eup){
    orientation =  cx::utilities::quaternionf(glm::normalize(glm::cross(eup, norm_up)),
            std::acos(glm::dot(eup, norm_up)))*orientation;
    }
            
    orientation.normalise();
    events->hook( SDL_MOUSEMOTION, this );
    events->hook( SDL_MOUSEBUTTONUP, this );
    this->wheel=0;
    // Send an event to the message loop signifying the position the scene is rendered from.
    this->send_move_message();
}
