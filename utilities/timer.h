///
/// Summary:  A timer
/// Remarks:  Uses SDL_GetTicks
///          
/// Authors:  Jack K., Karl M.
///

#ifndef TIMER_H
#define	TIMER_H

#include <glew.h>
#include <SDL.h>

namespace cx {
    namespace utilities{
            
            /// Summary:  A timer, effectively a stopwatch
            /// Remarks: Measures in milliseconds
            class timer {
    
    GLuint start_time = 0;
    GLuint current_time = 0;
    bool paused = false ;
    
public:
    //Reset stopwatch
    void reset_start ();
    //Get time elapsed from last call
    GLuint get_time_elapsed ();
    //Get total time elapsed from last reset_start()
    GLuint get_total_time ();
    
    void pause () {paused=true;};
    void unpause();
    //Wait to allow SDL to give up focus
    void wait () {SDL_Delay(1);}
}; 

inline GLuint timer::get_time_elapsed(){
    GLuint old_time =current_time;
    current_time=SDL_GetTicks();
    
    //If paused, return no time elapsed
    return paused ? 0 : current_time-old_time;
}


        }
    }

#endif	/* TIMER_H */

