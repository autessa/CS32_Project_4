
#include "MatchMaker.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "utility.h"
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

MatchMaker::MatchMaker(const MemberDatabase &mdb, const AttributeTranslator& at) {
    m_data = &mdb;
    m_at = &at;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const {
    unordered_set<string> uniqueAtts;
    unordered_map<string, int> attMatchCounter;
    vector<EmailCount> emailCounts;
    
    //spec update says we can choose to return one or more matches
    if (threshold <= 0)
        threshold = 1;
    
    const PersonProfile* p = m_data->GetMemberByEmail(email);

    AttValPair avp;
    int size = p->GetNumAttValPairs();
    for (int i = 0; i < size; i++) {
        p->GetAttVal(i, avp);
        auto pairVector = m_at->FindCompatibleAttValPairs(avp);
        for (auto &it : pairVector) {
            uniqueAtts.insert(pairToString(it));
        }
    //    copy(pairSet.begin(), pairSet.end(), inserter(uniqueAtts, uniqueAtts.end()));
    }

    //go through attribute set and get matching emails
    for (auto &it : uniqueAtts) {
        avp = stringToPair(it);
        auto emails = m_data->FindMatchingMembers(avp);
        for (auto ct = emails.begin(); ct != emails.end(); ct++)
            if (*ct == email) {
                ct = emails.erase(ct);
                break;
            }
        //go through matching email vector and search in counter to see if email exists
        for (auto &et : emails) {
            //creates or gets key
            ++attMatchCounter[et];
        }
    }

    for (auto &it : attMatchCounter) { //colon method needs & and dots
        if (it.second >= threshold)
            emailCounts.push_back(EmailCount(it.first, it.second));
    }

    sort(emailCounts.begin(), emailCounts.end(), [](EmailCount a, EmailCount b) {
       if (a.count == b.count)
           return a.email < b.email;
       return a.count > b.count;
    });
    //how to get person's attribute values, use size and for loop to get values from vector
    //get matching attributes from translator using FindCompatibleAttValPairs
    //put compatible attributes in uniqueAtts to remove duplicates
    //use FindingMatchingMembers for each attvalpair to get vector of emails
    //put these emails into counter, and set count to 1 if first time match
    //else find email already in vector and increment count by 1
    //sort using count of EmailCount to get vector in decreasing order
    //if counts are equal use emails to order alphabetically
    return emailCounts;
}

