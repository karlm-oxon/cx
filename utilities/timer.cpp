///
/// Summary:  A timer
/// Remarks:  Uses SDL GetTicks
///          
/// Authors:  Jack K., Karl M.
///

#include "timer.h"

void cx::utilities::timer::reset_start() {
    start_time = SDL_GetTicks();
    current_time = start_time;
}

GLuint cx::utilities::timer::get_total_time() {
    return SDL_GetTicks() - start_time;
}

void cx::utilities::timer::unpause() {
    paused = false;
    current_time = SDL_GetTicks();
};