
///
/// Summary:  Implementation of the cx::utilities::complexparser class.
/// Remarks:  This should be taken with ./engine/utilities/complexparser.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///


#include "complexparser.h"


/// Summary:  Returns a complex function entered by the user
/// Remarks:  Uses the CAS Complex Library for parsing. Gets input from
///           cx::utilities::getfunctioninput
std::function<std::complex<float>(std::complex<float>)> cx::utilities::complexparser::getFunction() {
    bool success = false;
    std::string fname;
    CasUnaryFunction f;
    while (!success) {
        //Get function string from user
        fname = cx::utilities::getfunctioninput();
        //Attempt to parse the function. If it fails, try again
        f.createFunction(fname, fname, &success);
        //Add some sort of error message here
    }
    //Return function as a lambda by value
    return [=] (std::complex<float> z) mutable {
        return (std::complex<float>)f((std::complex<double>)z);
    };
    
    
}
