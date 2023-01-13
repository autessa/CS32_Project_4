
#ifndef MemberDatabase_h
#define MemberDatabase_h
#include <string>
#include <vector>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
using namespace std;

class MemberDatabase {
public:
    MemberDatabase() {};
    ~MemberDatabase();
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
private:
    vector<PersonProfile*> delPtrs;
    RadixTree<PersonProfile*> emailProfileMap; //FIXME: note may need to change to ptrs
    RadixTree<vector<string>> attrEmailMap;
};

#endif /* MemberDatabase_hpp */
