///
/// Summary:  Contains a quaternion class for flying camera.
/// Authors:  Jack K., Karl M.
///



#ifndef GLQUATERNION_H
#define	GLQUATERNION_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace cx {
    namespace utilities {

        class quaternionf {
            
        public:
            float s;
            glm::vec3 v;

            quaternionf(glm::vec3 axis, float angle) {
                axis = glm::normalize(axis);
                v = (float) sin(angle / 2) * axis;
                s = cos(angle / 2);
            }

            quaternionf(const quaternionf& quat): s(quat.s),v(quat.v){
            }

            quaternionf() {
            };

            glm::vec3 rotate(const glm::vec3 & w);

            void normalise();
            quaternionf getConjugate();

            glm::mat4x4 getMatrix();



            quaternionf operator *(const quaternionf &param);


        };

        inline quaternionf quaternionf::operator *(const quaternionf &param) {
            quaternionf temp;
            temp.s = s * param.s - (glm::dot(v, param.v));
            temp.v = (v * param.s)+(param.v * s)+(glm::cross(v, param.v));
            return temp;
        }

        inline quaternionf quaternionf::getConjugate() {
            quaternionf ret; ret.s=s; ret.v=v*-1.0f;
            return ret;
        };

        inline void quaternionf::normalise() {
            float TOLERANCE = 0.0001;
            float mag = sqrt(s * s + glm::dot(v, v));
            if (mag != 0 && fabs(mag - 1) > TOLERANCE) {
                s = s / mag;
                v = v * (1 / mag);
            }
        }
        
        inline glm::vec3 quaternionf::rotate(const glm::vec3 & w) {
                return w + 2.0f * glm::cross(v, glm::cross(v, w) + s * w);
            }
        
        inline glm::mat4x4 quaternionf::getMatrix (){
	double x2 = v.x * v.x;
	double y2 = v.y * v.y;
	double z2 = v.z * v.z;
	double xy = v.x * v.y;
	double xz = v.x * v.z;
	double yz = v.y * v.z;
	double wx = s * v.x;
	double wy = s * v.y;
	double wz = s * v.z;
 
	return glm::mat4x4 (1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

    }
}
#endif	/* GLQUATERNION_H */

