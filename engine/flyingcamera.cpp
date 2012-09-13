#include "flyingcamera.h"

void cx::engine::flying_camera::update(GLuint time_elapsed) {
    //Get keys
    Uint8*keys = SDL_GetKeyState(NULL);
    //Set the velocity of the camera taking into account the orientation and 
    // which keys are pressed
     orientation.normalise();
    glm::vec3 vel = orientation.rotate(
            glm::vec3((keys[SDLK_d] - keys[SDLK_a]) * sensitivity.trans,
            (keys[SDLK_w] - keys[SDLK_s]) * sensitivity.trans,
            0.0f));
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
void cx::engine::flying_camera::delegate(SDL_Event) {
};

void cx::engine::flying_camera::on_mouse_move(SDL_Event) {
}

glm::mat4 cx::engine::flying_camera::get_transformation() {
    return look * orientation.getMatrix() * glm::translate(glm::mat4x4(1.0f), -position);

}

// For the moment up better be (0,0,1) and ahead (0,1,0) or vice versa
cx::engine::flying_camera::flying_camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up, cx::engine::eventing* events)
 {
    // Set the position, interest-direction and up-direction of the static camera.
    this->position = position;

    // Set the view transformation with a glm::lookAt call.
    glm::vec3 ahead(0, 1, 0);
    this->look = glm::lookAt(glm::vec3(0, 0, 0), ahead, up);
    orientation = cx::utilities::quaternionf(glm::normalize(glm::cross(ahead, direction)),
            std::acos(glm::dot(ahead, direction)*180/std::acos( -1.0f ))
            );
 //   orientation = glm::angleAxis (0.0f,glm::vec3(0.0,0.0,1.0));
    // Send an event to the message loop signifying the position the scene is rendered from.
    this->send_move_message();
}
