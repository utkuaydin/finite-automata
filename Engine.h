
#ifndef REGEXENGINE_ENGINE_H
#define REGEXENGINE_ENGINE_H

#include "NFA.h"

class Engine {
public:
    NFA createNFA(const string &convertedExpression);
};


#endif // REGEXENGINE_ENGINE_H
