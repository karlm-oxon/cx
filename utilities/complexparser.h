///
/// Summary:  Contains static utility functions pertaining to the modification of the host filesystem.
/// Authors:  Jack K., Karl M.
///




#ifndef COMPLEXPARSER_H
#define	COMPLEXPARSER_H

//For complex function parsing
#include <CAS IO.h>
#include <functional>
#include "getfunctioninput.h"

namespace cx {
    namespace utilities {
        
        struct complexparser {
            std::function<std::complex<float>(std::complex<float>)>getFunction ();
            
        };


    }
}
#endif	/* COMPLEXPARSER_H */

