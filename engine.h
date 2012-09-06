
///
/// Summary:  Header file which includes every prerequisite library needed by the Cx Engine module.
/// Remarks:  Including this file grants full SDL and OpenGL functionality, every class defined by the Cx Engine, and
///           all of the standard library necessary to interface with the Cx Engine.
/// Authors:  Jack K., Karl M.
///



#ifndef cx_engine_h
#define cx_engine_h



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <map>
#include <string>
#include <vector>

#include "engine/environment.h"
#include "engine/eventing.h"

#include "engine/base/eventable.h"
#include "engine/base/renderable.h"

#include "engine/pipeline/shader.h"
#include "engine/pipeline/program.h"



#endif
