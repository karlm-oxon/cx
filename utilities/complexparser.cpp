
#include "complexparser.h"

std::function<std::complex<float>(std::complex<float>)> cx::utilities::complexparser::getFunction() {
    bool success = false;
    std::string fname;
    CasUnaryFunction f;
    while (!success) {
        fname = cx::utilities::getfunctioninput();
        f.createFunction(fname, fname, &success);
    }

    return [=] (std::complex<float> z) mutable {
        return (std::complex<float>)f((std::complex<double>)z);
    };
    
    
}
