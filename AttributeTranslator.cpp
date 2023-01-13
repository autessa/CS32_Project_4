
#include "AttributeTranslator.h"
#include "utility.h"
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool AttributeTranslator::Load(string filename) {
    string line;
    unordered_set<string> uniqueString;
    ifstream file(filename);
    if (file.is_open()) {
        while(getline(file, line) && !line.empty()) {
            //check for duplicate lines
            uniqueString.insert(line);
        }
        file.close();
        //iterate through set
        for (auto it = uniqueString.begin(); it != uniqueString.end(); it++) {
            //find second comma in string
            size_t index = 0;
            index = it->find(",");
            index = it->find(",", index + 1);
            //split into first and second half
            string first = it->substr(0, index);
            string second = it->substr(index+1);
            //convert string to pair
            AttValPair valuePair = stringToPair(second);
            //insert into radix tree
            auto result = attributes.search(first);
            if (!result) {
                vector<AttValPair> v = {valuePair};
                attributes.insert(first, v);
            }
            else
                result->push_back(valuePair);
        }
        return true;
    }
    else
        return false;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    string key = pairToString(source);
    auto result = attributes.search(key);
    if (!result)
        return vector<AttValPair>();
    else
        return *result;
}
