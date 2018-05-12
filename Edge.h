#ifndef EDGE_H
#define EDGE_H

#include <iostream>

using namespace std;

class Edge {

public:
    Edge();

    Edge(int, int, char);

    void print();

    static Edge epsilonTransition(int, int);

    inline int getSourceState() { return sourceState; }

    inline int getDestinationState() { return destinationState; }

    inline char getSymbol() { return symbol; }

    inline bool isEpsilonTransition() { return symbol == EPSILON; }

private:
    int sourceState;
    int destinationState;
    char symbol;

    // Instead of epsilon sign we have $, because epsilon is not in ASCII table.
    static const char EPSILON = '$';

};

#endif // EDGE_H
