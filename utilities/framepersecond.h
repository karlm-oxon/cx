/* 
 * File:   framepersecond.h
 * Author: qfeuille
 *
 * Created on 12 September 2012, 14:54
 */

#include "timer.h"
#include <iostream>

#ifndef FRAMEPERSECOND_H
#define	FRAMEPERSECOND_H

namespace cx{
    namespace utilities{

class frame_per_second {
    timer clock;
    GLuint frames;
public:
    void countfps();

};

    }
}

#endif	/* FRAMEPERSECOND_H */

