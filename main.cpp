#include <cstdlib>

#include "NFA.h"
#include "InfixToPostfixConverter.h"
#include "Engine.h"

using namespace std;

int main(int argc, char **argv) {
    string expression = "(a|b)*abb";

    Engine engine;
    NFA nfa = engine.createNFA(expression);

    bool result = nfa.accepts("aaaaaaabbbbbbb");
    return 0;
}

