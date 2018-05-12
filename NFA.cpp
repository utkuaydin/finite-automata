#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <set>
#include "NFA.h"

using namespace std;

int NFA::stateId = 0;

NFA::NFA(int initialState, vector<int> allStates, vector<int> acceptStates, vector<Edge> transitions) {
    this->initialState = initialState;
    this->allStates = allStates;
    this->acceptStates = acceptStates;
    this->transitions = transitions;
}

void NFA::print() {
    cout << "States: " << endl;
    printVector(allStates);
    cout << "Transitions: " << endl;

    for (Edge &transition : transitions) {
        transition.print();
    }
}

bool NFA::accepts(string str) {
    // Checks whether this automaton accepts the string.
    set<int> nextStates, temp;
    unsigned long current = 0;

    while (true) {
        // Add the initial state to our set of
        // states that'll be processed next.
        nextStates.insert(initialState);

        do {
            temp = nextStates;

            // Add states that can be reached via an epsilon
            // transition to our next states set.
            for (int i : nextStates) {
                const vector<int> &closure = epsilonClosure(i);

                for (int j : closure) {
                    nextStates.insert(j);
                }
            }
        } while (temp != nextStates);

        // Check if we're already
        // in an accepted state.
        vector<int> intersection;

        for (int i : temp) {
            for (int j : acceptStates) {
                if (i == j) {
                    intersection.push_back(i);
                }
            }
        }

        if (!intersection.empty()) {
            break;
        }

        // Add states that can be reached with
        // the current character.
        if (current >= str.length()) {
            break;
        }

        char character = str[current++];
        temp.clear();

        for (int i : nextStates) {
            for (Edge transition : transitions) {
                if (transition.getSourceState() == i && transition.getSymbol() == character) {
                    temp.insert(transition.getDestinationState());
                }
            }
        }

        // Check if we're already
        // in an accepted state.
        intersection.clear();

        for (int i : temp) {
            for (int j : acceptStates) {
                if (i == j) {
                    intersection.push_back(i);
                }
            }
        }

        if (!intersection.empty()) {
            break;
        }

        nextStates = temp;
    }

    // Check if we're already
    // in an accepted state.
    vector<int> intersection;

    for (int i : temp) {
        for (int j : acceptStates) {
            if (i == j) {
                intersection.push_back(i);
            }
        }
    }

    // Return true if the string is accepted.
    return !intersection.empty();
}

vector<int> NFA::epsilonClosure(int state) {
    // Put every state that can be reached from
    // the given state via an epsilon closure.
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

    // We have just two states here.
    vector<int> allStates;
    allStates.push_back(initialState);
    allStates.push_back(finalState);

    // There is a single accept state,
    vector<int> acceptStates;
    acceptStates.push_back(finalState);

    // There is a single transition in this automaton, which takes initial state
    // to final state if input is given as the same as 'symbol' variable.
    Edge onlyOneTransition(initialState, finalState, c);
    vector<Edge> transitions;
    transitions.push_back(onlyOneTransition);

    // Create an NFA with such properties.
    return NFA(initialState, allStates, acceptStates, transitions);
}

NFA NFA::unionOfNFAs(NFA &nfa1, NFA &nfa2) {
    // In order to make a union, first create a new initial state and then create
    // epsilon transitions to other NFAs' initial states.

    int initialState = NFA::newState();
    Edge firstTransition = Edge::epsilonTransition(initialState, nfa1.initialState);
    Edge secondTransition = Edge::epsilonTransition(initialState, nfa2.initialState);

    // Add our new transitions to NFA's transition set and copy the rest.
    vector<Edge> transitions = {firstTransition, secondTransition};

    for (Edge transition : nfa1.transitions) {
        transitions.push_back(transition);
    }

    for (Edge transition : nfa2.transitions) {
        transitions.push_back(transition);
    }

    // Add our new initial state to our NFA's state set.
    vector<int> allStates = {initialState};

    for (int state : nfa1.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa2.allStates) {
        allStates.push_back(state);
    }

    // Copy all accepted states.
    vector<int> acceptStates;

    for (int state : nfa1.acceptStates) {
        acceptStates.push_back(state);
    }

    for (int state : nfa2.acceptStates) {
        acceptStates.push_back(state);
    }

    // Create a new NFA.
    return NFA(initialState, allStates, acceptStates, transitions);
}

NFA NFA::concatenate(NFA &nfa1, NFA &nfa2) {
    vector<int> acceptStates;

    // Copy all states.
    vector<int> allStates;

    for (int state : nfa1.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa2.allStates) {
        allStates.push_back(state);
    }

    // Copy all transitions.
    vector<Edge> transitions;

    for (Edge transition : nfa1.transitions) {
        transitions.push_back(transition);
    }

    for (Edge transition : nfa2.transitions) {
        transitions.push_back(transition);
    }

    // Connect every accepted state of the first machine to the initial state
    // of the second one.
    for (int state : nfa1.acceptStates) {
        Edge transition = Edge::epsilonTransition(state, nfa2.initialState);
        transitions.push_back(transition);
    }

    // Second machine's accepted states will be our new machine's accepted states.
    for (int state : nfa2.acceptStates) {
        acceptStates.push_back(state);
    }

    // First machine's initial state will be our new machine's initial state.
    return NFA(nfa1.initialState, allStates, acceptStates, transitions);
}

NFA NFA::star(NFA &nfa) {
    // Copy all states and transitions.
    vector<int> allStates;
    vector<int> acceptStates;
    vector<Edge> transitions;

    for (int state : nfa.allStates) {
        allStates.push_back(state);
    }

    for (int state : nfa.acceptStates) {
        // Connect all accepted states to NFA's initial state via an epsilon transition.
        Edge transition = Edge::epsilonTransition(state, nfa.initialState);
        transitions.push_back(transition);
        acceptStates.push_back(state);
    }

    for (Edge transition : nfa.transitions) {
        transitions.push_back(transition);
    }

    // Create a new initial state.
    int initialState = NFA::newState();

    // Connect our new initial state to given NFA's initial state via epsilon transition.
    Edge transition = Edge::epsilonTransition(initialState, nfa.initialState);
    transitions.push_back(transition);
    acceptStates.push_back(initialState);

    // Return our newly created NFA.
    return NFA(initialState, allStates, acceptStates, transitions);
}

void printVector(const vector<int> &a) {
    cout << '[';
    for (int i = 0; i < a.size() - 1; ++i) {
        cout << a[i] << ", ";
    }
    cout << a.back() << ']' << endl;
}

