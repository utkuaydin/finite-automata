#include <stack>
#include "Engine.h"
#include "InfixToPostfixConverter.h"

NFA Engine::createNFA(const string &expression) {
    // Create a NFA from given expression.

    // Convert given expression to a postfix one.
    InfixToPostfixConverter converter(expression);
    const string &convertedExpression = converter.getPostfixExpression();

    // Create a stack for our NFA building process.
    stack<NFA> stack;
    
    for (char character : convertedExpression) {
        if (character == '&') {
            // Get the two NFAs that we have on the stack,
            // concatenate them and put the result back.
            NFA second = stack.top();
            stack.pop();

            NFA first = stack.top();
            stack.pop();

            stack.push(NFA::concatenate(first, second));
        } else if (character == '|') {
            // Get the two NFAs that we have on the stack, create
            // a union with them and put the result back.
            NFA second = stack.top();
            stack.pop();

            NFA first = stack.top();
            stack.pop();

            stack.push(NFA::unionOfNFAs(first, second));
        } else if (character == '*') {
            // Create a new NFA with the star operator
            // by using the item on the top of the stack.
            NFA nfa = stack.top();
            stack.pop();

            stack.push(NFA::star(nfa));
        } else {
            // Add the character to our stack.
            stack.push(NFA::singleSymbol(character));
        }
    }

    // Return the resulting NFA.
    return stack.top();
}
