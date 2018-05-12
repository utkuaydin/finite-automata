#include <cstdlib>
#include <fstream>

#include "NFA.h"
#include "InfixToPostfixConverter.h"
#include "Engine.h"

using namespace std;

int main(int argc, char **argv) {
    Engine engine;
    NFA nfa = engine.createNFA(argv[1]);

    cout << "The following NFA was built:" << endl;
    nfa.print();

    ifstream inputFile(argv[2]);
    unsigned int lineCount = 1;
    string line;

    while (getline(inputFile, line)) {
        bool accepts = nfa.accepts(line);

        if (accepts) {
            cout << "Accepted, line " << lineCount << ": " << line << endl;
        }

        lineCount++;
    }

    return 0;
}

