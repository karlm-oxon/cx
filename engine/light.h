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

            struct parameters {
                std::string name;
                glm::vec4 position;
                glm::vec4 diffuse;
                glm::vec4 specular;
                float constantAttenuation, linearAttenuation, quadraticAttenuation;
                float spotCutoff, spotExponent;
                glm::vec3 spotDirection;

                parameters() {
                    name = "DefaultName";
                    position = glm::vec4 (0.0f,0.0f,0.0f,0.0f);
                    diffuse = glm::vec4 (0.0f,0.0f,0.0f,0.0f);
                    specular = glm::vec4 (0.0f,0.0f,0.0f,0.0f);
                    constantAttenuation = 0.0f;
                    linearAttenuation = 0.0f;
                    quadraticAttenuation = 0.0f;
                    spotCutoff = 180.0f;
                    spotExponent = 0.0f;
                    spotDirection = glm::vec3(0, 0, 0);
                }
            };
            
            parameters params;

            light(parameters iparams) : params(iparams){};

            void bind_uniforms(cx::engine::pipeline::program& program);
            void send_uniforms(glm::mat4& modelview);

            virtual ~light() {
            };
        private:

        };
    }
}

#endif	/* LIGHT_H */

