
///
///
///
///
///



#ifndef cx_utilities_maths
#define cx_utilities_maths



#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

#include <cmath>



namespace cx {
    namespace utilities {
        ///
        ///

        class maths {
        private:
            maths();

        public:
            static glm::vec4 angle_to_hue(float angle);
        };

        //Differentiate a function f, about x. The step size h should be large
        // in comparison to rate of change of f. Greater tabSize corresponds
        // to greater accuracy but takes longer.
        template<typename T = float, int tabSize = 5>
                class Ridders {
            const T shrink, shrinksq;
            const T large = 1e100;
            const T safety;
            T tab [tabSize] [tabSize];
        public:

           
            inline T maxAbs(const T& x, const T& y) {
                return fabs(x) > fabs(y) ? x : y;
            }
            
            template<typename FunctPtr>
            T operator () (FunctPtr f, const T x, T h) {
                if (h == 0) return 0;
                T ret;
                T error;
                tab [0][0] = (f(x + h) - f(x - h)) / (2.0 * h);
                error = large;
                for (int i = 1; i < tabSize; i++) {
                    h /= shrink;
                    tab [0][i] = (f(x + h) - f(x - h)) / (2.0 * h);
                    T fac = shrinksq;
                    for (int j = 1; j <= i; j++) {
                        tab [j][i] = (tab [j - 1][i] * fac - tab[j - 1][i - 1]) / (fac - 1.0);
                        fac *= shrinksq;
                        T newerror = maxAbs(tab[j][i] - tab[j - 1][i], tab[j][i] - tab[j - 1][i - 1]);
                        if (newerror <= error) {
                            error = newerror;
                            ret = tab[j][i];
                        }
                    }
                    if (fabs(tab[i][i] - tab[i - 1][i - 1]) >= safety * error) break;
                }
                return ret;
            }

            Ridders(T ishrink = 1.4, T isafety = 2.0) : shrink(ishrink), shrinksq(ishrink*ishrink), safety(isafety) {


            }
        };
    }
}



#endif
