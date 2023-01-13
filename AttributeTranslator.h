
#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include <vector>
#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

class AttributeTranslator {
public:
    AttributeTranslator() {}; //TODO: figure what needs to be initialized 
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<vector<AttValPair>> attributes;
};


#endif /* AttributeTranslator_hpp */

