
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "utility.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <iostream>
using namespace std;

MemberDatabase::~MemberDatabase() {
    for (auto p : delPtrs)
        delete p;
    delPtrs.clear();
}

bool MemberDatabase::LoadDatabase(string filename) {
    string line;
    unordered_set<string> uniqueEmail;
    ifstream file(filename);
    string name;
    string email;
    string num;
    if (file.is_open()) {
        while(getline(file, name)) {
            if (name.empty())
                continue;

            getline(file, email);

            //check for duplicate emails
            if (uniqueEmail.count(email))
                return false;
            else
                uniqueEmail.insert(email);

            PersonProfile* p = new PersonProfile(name, email);
            emailProfileMap.insert(email, p);
            delPtrs.push_back(p);

            getline(file, num);
            for (int i = 0; i < stoi(num); i++) {
                getline(file, line);
                AttValPair av = stringToPair(line);
                p->AddAttValPair(av);

                //insert into attrEmailMap
                auto result = attrEmailMap.search(line);
                if (!result) {
                    vector<string> e = {email};
                    attrEmailMap.insert(line, e);
                }
                else
                    result->push_back(email);
            }
        }
        file.close();
        return true;
    }
    else
        return false;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const {
    string key = pairToString(input);
    auto result = attrEmailMap.search(key);
    if (!result)
        return vector<string>();
    else
        return *result;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const{
    PersonProfile** member = emailProfileMap.search(email);
    if (member == nullptr)
        return nullptr;
    else
        return *member;
}
