///
/// Summary:  Camera class which can freely move and orient in space
/// Remarks:  WASD is as standard, along camera axes. Arrow keys control  
///           pitch and yaw, as does mouse. Q and E roll the camera
/// Authors:  Jack K., Karl M.
///

namespace cx {
    namespace engine {
        class flying_camera;
    }
}

#ifndef FLYINGCAMERA_H
#define	FLYINGCAMERA_H

#include "base/camera.h"
#include "../utilities/timer.h"
#include "environment.h"
#include "../utilities/GLQuaternion.h"

namespace cx {
    namespace engine {

        class flying_camera : public cx::engine::base::camera {
        private:
            
            //Timer for finding mouse motion speed
         //   cx::utilities::timer mouse_time;

            //Sensitivity to key presses
            struct {
                double trans = 0.01;
                double mouse = 0.005;
                double rot = 0.0005;
                double wheel = 0.05;
            } sensitivity;
            float wheel=0;
            //Orientation of camera
            cx::utilities::quaternionf orientation;
            //Moves orientation of camera with the mouse
            void on_mouse_move(SDL_Event);
            void on_mouse_button(SDL_Event event);
            //Called every frame to move the camera with the keys
            void update(GLuint time_elapsed);
        public:
            flying_camera(glm::vec3, glm::vec3, glm::vec3, cx::engine::eventing*);
            //For handling mouse motion
            void delegate(SDL_Event);
            //Returns the camera's view matrix
            glm::mat4 get_transformation ();
        };

    }

}
#endif	/* FLYINGCAMERA_H */

