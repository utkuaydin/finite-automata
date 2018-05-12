#include <stack>
#include "Engine.h"
#include "InfixToPostfixConverter.h"

NFA Engine::createNFA(const string &expression) {
    InfixToPostfixConverter converter(expression);
    const string &convertedExpression = converter.getPosfixExpression();
    stack<NFA> stack;
    
    for (char character : convertedExpression) {
        if (character == '&') {
            NFA second = stack.top();
            stack.pop();

            NFA first = stack.top();
            stack.pop();

            stack.push(NFA::concatenate(first, second));
        } else if (character == '|') {
            NFA second = stack.top();
            stack.pop();

            NFA first = stack.top();
            stack.pop();

            stack.push(NFA::unionOfNFAs(first, second));
        } else if (character == '*') {
            NFA nfa = stack.top();
            stack.pop();

            stack.push(NFA::star(nfa));
        } else {
            stack.push(NFA::singleSymbol(character));
        }
    }

    return stack.top();
}
