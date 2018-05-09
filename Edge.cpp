#include "Edge.h"

Edge::Edge() = default;

Edge::Edge(int source, int destination, char symbol) {
    this->sourceState = source;
    this->destinationState = destination;
    this->symbol = symbol;
}

Edge Edge::epsilonTransition(int sourceState, int destinationState) {
    return {sourceState, destinationState, EPSILON};
}

void Edge::print() {
    cout << '(' << sourceState << ", " << destinationState << ", ";
    if (isEpsilonTransition()) {
        cout << "epsilon";
    } else {
        cout << "'" << symbol << "'";
    }
    cout << ')' << endl;
}
