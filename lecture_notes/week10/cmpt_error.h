// cmpt_error.h

// By defining CMPT_ERROR_H, we avoid including this file more than once: if
// CMPT_ERROR_H is already defined, then the code is *not* included.
#ifndef CMPT_ERROR_H
#define CMPT_ERROR_H

#include <string>
#include <stdexcept>

// C++ already has function called error, and so we put our error function
// inside a namespace called cmpt. Thus, to use this error function, we will
// write its full name, cmpt::error.
namespace cmpt {

// runtime_error is a pre-defined C++ object meant to be "thrown" when an error
// occurs while a program is running. When it is thrown, the program will end
// and print the given error message.
inline void error(const std::string& message)
{
    throw std::runtime_error(message);
}

} // namespace cmpt

#endif
