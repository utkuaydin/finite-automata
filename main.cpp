#include <cstdlib>

#include "NFA.h"
#include "InfixToPostfixConverter.h"

using namespace std;

/*
 * 
 */
int main(int argc, char **argv) {
    string testing = "(a|b)*abb";



    InfixToPostfixConverter converter = testInfixToPostfix(testing);
    test(converter.getPosfixExpression());
}

