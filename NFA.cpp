#include <stdlib.h>
#include <iostream>

#include "NFA.h"

int NFA::stateIDsource = 0;

NFA::NFA() {
}

NFA::NFA(int initialState, vector<int> allStates, vector<int> acceptStates, vector<Edge> transitions) {
    this->initialState = initialState;
    this->allStates = allStates;
    this->acceptStates = acceptStates;
    this->transitions = transitions;
}

void NFA::print() {
    cout << "States : " << endl;
    printVector(allStates);
    cout << "Transitions : " << endl;
    for (int i = 0; i < transitions.size(); ++i) {
        transitions[i].print();
    }
}

bool NFA::accepts(string str) {
    //checks whether this automaton accepts 's'. Implement this method
    //using given algorithm in project document.

    currentStates.clear();
    //TODO implement accepts!

    cout << "Not implemented! accepts" << endl;
    exit(-1);
}

vector<int> NFA::epsilonClosure(int state) {
    //finds the set of states that are in epsilon closure of given 'state' within
    //this automaton. (set of states that can be reached from 'state' using
    //epsilon transitions)

    //TODO implement kleeneClosure!
    cout << "Not implemented! kleeneClosure" << endl;
    exit(-1);
}

NFA NFA::singleSymbol(char c) {
    int initialState = NFA::newState();
    int finalState = NFA::newState();

    //we have just two states here
    vector<int> allStates;
    allStates.push_back(initialState);
    allStates.push_back(finalState);

    //there is a single accept state,
    vector<int> acceptStates;
    acceptStates.push_back(finalState);

    //there is a single transition in this automaton, which takes initial state
    //to final state if input is given as the same as 'symbol' variable.
    Edge onlyOneTransition(initialState, finalState, c);
    vector<Edge> transitions;
    transitions.push_back(onlyOneTransition);

    //create an NFA with such properties.
    return NFA(initialState, allStates, acceptStates, transitions);
}

NFA NFA::unionOfNFAs(NFA &nfa1, NFA &nfa2) {
    NFA result;

    for (int state : nfa1.acceptStates) {
        Edge transition = Edge::epsilonTransition(state, nfa2.initialState);
    }

    vector<int> allStates = {};

    for (int state : nfa1.allStates) {

    }

    //TODO implement unionOfNFAs!
    //since we can't use keyword 'union' in C++, it was renamed to unionOfNFAs.
    cout << "Not implemented! unionOfNFAs" << endl;
    exit(-1);
}

NFA NFA::concatenate(NFA &nfa1, NFA &nfa2) {
    //TODO implement concatenate!
    cout << "Not implemented! concatenate" << endl;
    exit(-1);
}

NFA NFA::star(NFA &nfa) {
    //TODO implement star!
    cout << "Not implemented! star" << endl;
    exit(-1);
}

void printVector(const vector<int> &a) {
    cout << '[';
    for (int i = 0; i < a.size() - 1; ++i) {
        cout << a[i] << ", ";
    }
    cout << a.back() << ']' << endl;
}

void test() {
    cout << "Testing..." << endl;
    cout << endl;
    cout << "Trying to construct automaton that recognizes: " << endl;
    cout << "(a|b)*abb" << endl;

    // ab|*a&b&b&

    NFA a = NFA::singleSymbol('a');
    NFA b = NFA::singleSymbol('b');
    NFA un = NFA::unionOfNFAs(a, b);
    NFA star = NFA::star(un);

    NFA anotherA = NFA::singleSymbol('a');
    NFA anotherB = NFA::singleSymbol('b');
    NFA lastB = NFA::singleSymbol('b');

    NFA ab = NFA::concatenate(anotherA, anotherB);
    NFA abb = NFA::concatenate(ab, lastB);

    NFA result = NFA::concatenate(star, abb);

    string testString = "aababb";

    if (result.accepts(testString)) {
        cout << "NFA accepts " << testString << endl;
    } else {
        cout << "NFA did not accept " << testString << endl;
        exit(-1);
    }

    cout << "All tests passed!" << endl;
    cout << "Here is the resulting NFA: " << endl;
    result.print();

}
