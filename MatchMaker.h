
#ifndef MatchMaker_h
#define MatchMaker_h
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
using namespace std;

class MatchMaker {
public:
    MatchMaker(const MemberDatabase &mdb, const AttributeTranslator& at);
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
private:
    const AttributeTranslator* m_at;
    const MemberDatabase* m_data;
   
};

#endif /* MatchMaker_hpp */
