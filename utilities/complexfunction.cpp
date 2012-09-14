
///
/// Summary:  Implementation of the cx::utilities::complexparser class.
/// Remarks:  This should be taken with ./engine/utilities/complexparser.h by the compiler as being one discrete module.
/// Authors:  Jack K., Karl M.
///


#include "complexfunction.h"


/// Summary:  Returns a complex function entered by the user
/// Remarks:  Uses the CAS Complex Library for parsing. Gets input from
///           cx::utilities::getfunctioninput
void cx::utilities::complex_function::getFunction() {
    bool success = false;
    std::string fname;
    while (!success) {
        //Get function string from user
        fname = cx::utilities::getfunctioninput();
        //Attempt to parse the function. If it fails, try again
        f.createFunction(fname, fname, &success);
        //Add some sort of error message here
        if (!success) std::cerr<<"Parsing error. Did you remember to enter one single letter variable?"
                 << std::endl;
    }
   
    };
    
    

