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
    vector<int> t, p;
    unsigned long current = 0;

    while (true) {
        p.push_back(initialState);

        do {
            t = p;

            for (int i : p) {
                for (int j : epsilonClosure(i)) {
                    p.push_back(j);
                }
            }
        } while (t != p);

        vector<int> intersection;

        for (int i : t) {
            for (int j : acceptStates) {
                if (i == j) {
                    intersection.push_back(i);
                }
            }
        }

        if (intersection.empty()) {
            break;
        }

        if (current >= str.length()) {
            break;
        }

        char character = str[current];
        t.clear();

        for (int i : p) {
            for (Edge transition : transitions) {
                if (transition.getSourceState() == i && transition.getSymbol() == character) {
                    t.push_back(transition.getDestinationState());
                }
            }
        }

        intersection.clear();

        for (int i : t) {
            for (int j : acceptStates) {
                if (i == j) {
                    intersection.push_back(i);
                }
            }
        }

        if (intersection.empty()) {
            break;
        }

        p = t;
    }

    vector<int> intersection;

    for (int i : t) {
        for (int j : acceptStates) {
            if (i == j) {
                intersection.push_back(i);
            }
        }
    }

    return !intersection.empty();
}

vector<int> NFA::epsilonClosure(int state) {
    vector<int> states;

    for (Edge transition : transitions) {
        if (transition.isEpsilonTransition() && transition.getSourceState() == state) {
            states.push_back(transition.getDestinationState());
        }
    }

    return states;
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
    int initialState = NFA::newState();
    Edge firstTransition = Edge::epsilonTransition(initialState, nfa1.initialState);
    Edge secondTransition = Edge::epsilonTransition(initialState, nfa2.initialState);

    vector<int> allStates = {initialState};
    vector<int> acceptStates;
    vector<Edge> transitions = {firstTransition, secondTransition};

    for (int state : nfa1.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa2.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa1.acceptStates) {
        acceptStates.push_back(state);
    }

    for (int state : nfa2.acceptStates) {
        acceptStates.push_back(state);
    }

    for (Edge transition : nfa1.transitions) {
        transitions.push_back(transition);
    }

    for (Edge transition : nfa2.transitions) {
        transitions.push_back(transition);
    }

    return NFA(initialState, allStates, acceptStates, transitions);
}

NFA NFA::concatenate(NFA &nfa1, NFA &nfa2) {
    vector<int> allStates;
    vector<int> acceptStates;
    vector<Edge> transitions;

    for (int state : nfa1.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa2.allStates) {
        allStates.push_back(state);
    }

    for (Edge transition : nfa1.transitions) {
        transitions.push_back(transition);
    }

    for (Edge transition : nfa2.transitions) {
        transitions.push_back(transition);
    }

    for (int state : nfa1.acceptStates) {
        Edge transition = Edge::epsilonTransition(state, nfa2.initialState);
        transitions.push_back(transition);
    }

    for (int state : nfa2.acceptStates) {
        acceptStates.push_back(state);
    }

    return NFA(nfa1.initialState, allStates, acceptStates, transitions);
}

NFA NFA::star(NFA &nfa) {
    vector<int> allStates;
    vector<int> acceptStates;
    vector<Edge> transitions;

    for (int state : nfa.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa.acceptStates) {
        Edge transition = Edge::epsilonTransition(state, nfa.initialState);
        transitions.push_back(transition);
        acceptStates.push_back(state);
    }

    for (Edge transition : nfa.transitions) {
        transitions.push_back(transition);
    }

    int initialState = NFA::newState();
    Edge transition = Edge::epsilonTransition(initialState, nfa.initialState);
    transitions.push_back(transition);
    acceptStates.push_back(initialState);

    return NFA(initialState, allStates, acceptStates, transitions);
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
