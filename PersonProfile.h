
#ifndef PersonProfile_h
#define PersonProfile_h
#include <vector>
#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <unordered_set>
using namespace std;

class PersonProfile {
public:
    PersonProfile(string name, string email);
    string GetName() const;
    string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    string m_name;
    string m_email;
    RadixTree<unordered_set<string>> attValMap;
    vector<AttValPair> attributes;
};

#endif /* PersonProfile_hpp */
