
#include "PersonProfile.h"
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

PersonProfile::PersonProfile(string name, string email) {
    m_name = name;
    m_email = email;
}

string PersonProfile::GetName() const {
    return m_name;
}

string PersonProfile::GetEmail() const {
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval) {
    auto result = attValMap.search(attval.attribute);
    if (!result) {
        unordered_set<string> s = {attval.value};
        attValMap.insert(attval.attribute, s);
        attributes.push_back(attval);
    }
    else {
        auto it = result->find(attval.value);
        if (it != result->end())
            return;
        else {
            result->insert(attval.value);
            attributes.push_back(attval);
        }
    }
}

int PersonProfile::GetNumAttValPairs() const {
    return static_cast<int>(attributes.size());
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const {
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
        return false;
    else {
        attval = attributes[attribute_num];
        return true;
    }
}
