///
/// Summary:  Light class which stores variables related
///           to position of light to send to GLSL. 
/// Remarks:  This would be a lot easier with UBOs, but for compatability           
///           and as I don't know how, I won't use them
///
/// Authors:  Jack K., Karl M.
///

#include "light.h"

cx::engine::light::light(
        std::string iname,
        glm::vec4 iposition,
        glm::vec4 idiffuse,
        glm::vec4 ispecular,
        float iconstantAttenuation,
        float ilinearAttenuation,
        float iquadraticAttenuation,
        float ispotCutoff,
        float ispotExponent,
        glm::vec3 ispotDirection) :

name(iname),
position(iposition),
diffuse(idiffuse),
specular(ispecular),
constantAttenuation(iconstantAttenuation),
linearAttenuation(ilinearAttenuation),
quadraticAttenuation(iquadraticAttenuation),
spotCutoff(ispotCutoff),
spotExponent(ispotExponent),
spotDirection(ispotDirection) {
}

void cx::engine::light::bind_uniforms(cx::engine::pipeline::program& program) {
    uniforms.position = program.bindUniform(name + "." + "position");
    uniforms.diffuse = program.bindUniform(name + "." + "diffuse");
    uniforms.specular = program.bindUniform(name + "." + "specular");
    uniforms.constantAttenuation = program.bindUniform(name + "." + "constantAttenuation");
    uniforms.linearAttenuation = program.bindUniform(name + "." + "linearAttenuation");
    uniforms.quadraticAttenuation = program.bindUniform(name + "." + "quadraticAttenuation");
    uniforms.spotCutoff = program.bindUniform(name + "." + "spotCutoff");
    uniforms.spotExponent = program.bindUniform(name + "." + "spotExponent");
    uniforms.spotDirection = program.bindUniform(name + "." + "spotDirection");

}


//Assumes a program called in bind_uniforms is already bound

void cx::engine::light::send_uniforms(glm::mat4& modelview) {
    glUniform4fv(uniforms.position, 1, glm::value_ptr(modelview*position));
    glUniform4fv(uniforms.diffuse, 1, glm::value_ptr(diffuse));
    glUniform4fv(uniforms.specular, 1, glm::value_ptr(specular));
    glUniform3fv(uniforms.spotDirection, 1, glm::value_ptr(spotDirection));
    glUniform1f(uniforms.constantAttenuation, constantAttenuation);
    glUniform1f(uniforms.linearAttenuation, linearAttenuation);
    glUniform1f(uniforms.spotCutoff, spotCutoff);
    glUniform1f(uniforms.spotExponent, spotExponent);
    glUniform1f(uniforms.quadraticAttenuation, quadraticAttenuation);



}