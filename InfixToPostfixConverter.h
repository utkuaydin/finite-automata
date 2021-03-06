#ifndef INFIXTOPOSTFIXCONVERTER_H
#define INFIXTOPOSTFIXCONVERTER_H

#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class InfixToPostfixConverter {

public:
    InfixToPostfixConverter(string);

    inline string getPostfixExpression() { return postfix; }

private:
    string regex;

    char c;

    int cc;

    string postfix;

    void E();

    void T();

    void F();

    void G();

    void fatal(const char *);
};

#endif // INFIXTOPOSTFIXCONVERTER_H

