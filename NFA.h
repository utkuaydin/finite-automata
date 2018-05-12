#include <vector>
#include "Edge.h"

#ifndef NFA_H
#define NFA_H

using namespace std;

class NFA {

public:
    inline static int newState() { return stateId++; }

    vector<int> epsilonClosure(int);

    static NFA singleSymbol(char c);

    static NFA unionOfNFAs(NFA &, NFA &);

    static NFA concatenate(NFA &, NFA &);

    static NFA star(NFA &);

    bool accepts(string);

    void print();
private:
    NFA(int, vector<int>, vector<int>, vector<Edge>);

    static int stateId;

    int initialState;

    vector<int> allStates;

    vector<int> acceptStates;

    vector<Edge> transitions;
};

void printVector(const vector<int> &);

#endif // NFA_H

