///
/// Summary:  Gets a complex function from user and parses it
/// Authors:  Jack K., Karl M.
///




#ifndef COMPLEXPARSER_H
#define	COMPLEXPARSER_H

//For complex function parsing
#include <CAS IO.h>

#include <functional>
#include "getfunctioninput.h"
#include <iostream>

namespace cx {
    namespace utilities {
        
        class complex_function {
            CAS::CasUnaryFunction f;
        public:
            void getFunction ();
            std::complex<float> operator () (std::complex<float>);
            
            
        };
        
   inline  std::complex<float> complex_function::operator () (std::complex<float> z){
       return (std::complex<float>) f((std::complex<double>) z);
   };


    }
}
#endif	/* COMPLEXPARSER_H */

