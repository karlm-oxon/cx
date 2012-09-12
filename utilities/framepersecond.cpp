/* 
 * File:   framepersecond.cpp
 * Author: qfeuille
 * 
 * Created on 12 September 2012, 14:54
 */

#include "framepersecond.h"

void cx::utilities::frame_per_second::countfps(){
 frames++;
 GLuint time_passed=clock.get_total_time();
            if ( time_passed>= 5000) {
                GLfloat seconds = (GLfloat)(time_passed) / 1000.0;
                GLfloat fps = frames / seconds;
                std::cout<<frames<<" frames in "<<seconds<<" seconds = "<<fps<<" FPS\n";
                clock.reset_start();
                frames = 0;
            }
 
}

