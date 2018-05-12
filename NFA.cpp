#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <set>
#include "NFA.h"

using namespace std;

int NFA::stateId = 0;

NFA::NFA() = default;

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

    for (int i = 0; i < transitions.size(); ++i) {
        transitions[i].print();
    }
}

bool NFA::accepts(string str) {
    //checks whether this automaton accepts 's'. Implement this method
    //using given algorithm in project document.

    set<int> nextStates, temp;
    unsigned long current = 0;

    while (true) {
        nextStates.insert(initialState);

        do {
            temp = nextStates;

            for (int i : nextStates) {
                const vector<int> &closure = epsilonClosure(i);

                for (int j : closure) {
                    nextStates.insert(j);
                }
            }
        } while (temp != nextStates);

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

    vector<int> intersection;

    for (int i : temp) {
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

void test(string postFixString) {
    cout << "Testing..." << endl;
    cout << endl;
    cout << "Trying to construct automaton that recognizes: " << endl;
    cout << "(a|b)*abb" << endl;

    stack<NFA> resultNFA;
    int index = 0;

    while (index < postFixString.length()) {
        char character = postFixString[index++];

        if (character == '&') {
            NFA nfa2 = resultNFA.top();
            resultNFA.pop();
            NFA nfa1 = resultNFA.top();
            resultNFA.pop();
            resultNFA.push(NFA::concatenate(nfa1, nfa2));
        } else if (character == '|') {
            NFA nfa2 = resultNFA.top();
            resultNFA.pop();
            NFA nfa1 = resultNFA.top();
            resultNFA.pop();
            resultNFA.push(NFA::unionOfNFAs(nfa1, nfa2));
        } else if (character == '*') {
            NFA nfa = resultNFA.top();
            resultNFA.pop();
            resultNFA.push(NFA::star(nfa));
        } else {
            resultNFA.push(NFA::singleSymbol(character));
        }
    }

    string testString = "abbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbababb";

    if (resultNFA.top().accepts(testString)) {
        cout << "NFA accepts " << testString << endl;
    } else {
        cout << "NFA did not accept " << testString << endl;
        exit(-1);
    }

    cout << "All tests passed!" << endl;
    cout << "Here is the resulting NFA: " << endl;
    resultNFA.top().print();

}
