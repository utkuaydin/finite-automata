#include "InfixToPostfixConverter.h"

InfixToPostfixConverter::InfixToPostfixConverter(string infix) {
    cc = 0;
    regex = infix + "\0";
    c = regex[cc++];
    E();
}

void InfixToPostfixConverter::E() {
    T();
    while (c == '|') {
        c = regex[cc++];
        T();
        postfix += "|";
    }
}

void InfixToPostfixConverter::T() {
    F();
    while (c != '\0' && strchr(")|*+?", c) == NULL) { /* '(' or LITERAL */
        F();
        postfix += "&";
    }
}

void InfixToPostfixConverter::F() {
    G();
    while (c != '\0' && strchr("*+?", c) != NULL) {
        postfix += c;
        c = regex[cc++];
    }
}

void InfixToPostfixConverter::G() {
    if (c == '\0')
        fatal("unexpected end of expression!");
    if (c == '\\') { /* escape */
        c = regex[cc++];
        if (c == '\0')
            fatal("escape at end of string");
        postfix += c;
        c = regex[cc++];
    } else if (strchr("()|*+?", c) == NULL) { /* non-meta chacter */
        if (c == '&')
            postfix += "&";
        else
            postfix += c;
        c = regex[cc++];
    } else if (c == '(') {
        c = regex[cc++];
        E();
        if (c != ')')
            fatal("mismatched parantheses!");
        c = regex[cc++];
    } else
        fatal("bogus expression!");
}

void InfixToPostfixConverter::fatal(const char *message) {
    cout << message << endl;
    exit(-1);
}

InfixToPostfixConverter testInfixToPostfix(string stringToPostFix) {
    //example
    // InfixToPostfixConverter converter("((a|b)*aba*)");
    // cout << converter.getPosfixExpression() << endl;
    InfixToPostfixConverter converter(stringToPostFix);
    cout << converter.getPosfixExpression() << endl;
	return converter;
}
