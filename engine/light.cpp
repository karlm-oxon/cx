///
/// Summary:  Light class which stores variables related
///           to position of light to send to GLSL. 
/// Remarks:  This would be a lot easier with UBOs, but for compatability           
///           and as I don't know how, I won't use them
///
/// Authors:  Jack K., Karl M.
///

#include "light.h"



void cx::engine::light::bind_uniforms(cx::engine::pipeline::program& program) {
    uniforms.position = program.bindUniform(params.name + "." + "position");
    uniforms.diffuse = program.bindUniform(params.name + "." + "diffuse");
    uniforms.specular = program.bindUniform(params.name + "." + "specular");
    uniforms.constantAttenuation = program.bindUniform(params.name + "." + "constantAttenuation");
    uniforms.linearAttenuation = program.bindUniform(params.name + "." + "linearAttenuation");
    uniforms.quadraticAttenuation = program.bindUniform(params.name + "." + "quadraticAttenuation");
    uniforms.spotCutoff = program.bindUniform(params.name + "." + "spotCutoff");
    uniforms.spotExponent = program.bindUniform(params.name + "." + "spotExponent");
    uniforms.spotDirection = program.bindUniform(params.name + "." + "spotDirection");

}


//Assumes a program called in bind_uniforms is already bound

void cx::engine::light::send_uniforms(glm::mat4& modelview) {
    glUniform4fv(uniforms.position, 1, glm::value_ptr(modelview*params.position));
    glUniform4fv(uniforms.diffuse, 1, glm::value_ptr(params.diffuse));
    glUniform4fv(uniforms.specular, 1, glm::value_ptr(params.specular));
    glUniform3fv(uniforms.spotDirection, 1, glm::value_ptr(params.spotDirection));
    glUniform1f(uniforms.constantAttenuation, params.constantAttenuation);
    glUniform1f(uniforms.linearAttenuation, params.linearAttenuation);
    glUniform1f(uniforms.spotCutoff, params.spotCutoff);
    glUniform1f(uniforms.spotExponent, params.spotExponent);
    glUniform1f(uniforms.quadraticAttenuation, params.quadraticAttenuation);



}