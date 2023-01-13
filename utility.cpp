
#include "utility.h"
#include <string>
#include "provided.h"
using namespace std;

AttValPair stringToPair(string input) {
    size_t index = input.find(",");
    return AttValPair(input.substr(0, index), input.substr(index+1));
}

string pairToString(AttValPair input) {
    return (input.attribute + "," + input.value);
}

