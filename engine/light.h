///
/// Summary:  Light class which stores variables related
///           to position of light to send to GLSL. 
/// Remarks:  This would be a lot easier with UBOs, but for compatability           
///           and as I don't know how, I won't use them
///
/// Authors:  Jack K., Karl M.
///

#ifndef LIGHT_H
#define	LIGHT_H

#include <string>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "pipeline/program.h"

namespace cx {
    namespace engine {

        class light {
            std::string name;

            struct uniform_list {
                unsigned int position;
                unsigned int diffuse;
                unsigned int specular;
                unsigned int constantAttenuation, linearAttenuation, quadraticAttenuation;
                unsigned int spotCutoff, spotExponent;
                unsigned int spotDirection;

            };
            uniform_list uniforms;
        public:
            glm::vec4 position;
            glm::vec4 diffuse;
            glm::vec4 specular;
            float constantAttenuation, linearAttenuation, quadraticAttenuation;
            float spotCutoff, spotExponent;
            glm::vec3 spotDirection;

            light(
                    std::string iname,
                    glm::vec4 iposition,
                    glm::vec4 idiffuse,
                    glm::vec4 ispecular,
                    float iconstantAttenuation = 0.0f,
                    float ilinearAttenuation = 1.0f,
                    float iquadraticAttenuation = 0.0f,
                    float ispotCutoff = 180.0f,
                    float ispotExponent = 0.0f,
                    glm::vec3 ispotDirection = glm::vec3(0, 0, 0));

            void bind_uniforms(cx::engine::pipeline::program& program);
            void send_uniforms(glm::mat4& modelview);

            virtual ~light() {
            };
        private:

        };
    }
}

#endif	/* LIGHT_H */

