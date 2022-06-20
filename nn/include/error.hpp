//
// Created by anmc on 22-6-20.
//

#ifndef NN_ERROR_HPP
#define NN_ERROR_HPP

#include <iostream>

class illegalParameterValue {

public:

    illegalParameterValue()
        : message("Illegal parameter value") {

    }

    explicit illegalParameterValue(const char* theMessage)
        : message(theMessage) {

    }

    void outputMessage() { std::cout << message << std::endl; }

private:

    std::string message;
};


#endif //NN_ERROR_HPP
