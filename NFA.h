#include <vector>
#include "Edge.h"

#ifndef NFA_H
#define NFA_H

using namespace std;

class NFA {

public:
    NFA();

    bool accepts(string);

    vector<int> epsilonClosure(int);

    void print();

    // Every new state must have distinct ID, so increment the ID generator
    // each time you need a new one.
    inline static int newState() { return stateIDsource++; }

    static NFA singleSymbol(char c);

    static NFA unionOfNFAs(NFA &, NFA &);

    static NFA concatenate(NFA &, NFA &);

    static NFA star(NFA &);
private:
    static int stateIDsource;

    NFA(int, vector<int>, vector<int>, vector<Edge>);

    int initialState;

    vector<int> allStates;

    vector<int> acceptStates;

    vector<Edge> transitions;

    vector<int> currentStates;

};

void printVector(const vector<int> &);

void test();

#endif    /* NFA_H */

