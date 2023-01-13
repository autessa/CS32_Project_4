//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }
    std::cout << "finished" << std::endl;
      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}


/* PersonProfile use a vector and unordered set to check if pair is already there
   Attribute Translator --> use map/radix tree
   Member Database --> use map/radix tree (2 maps: pairs->emails, emails->profile pointer)
   Matcher Maker - GetMemberbyEmail, get pair from PersonProfile, put the pair attribute translator, then use what get from attribute translator and put that into member database, keep a count of how many matches each email gets (counter aka map), dump whatever get from translator and throw it into set (gets rid of duplicates), use std sort and give extra parameter
 Radix Tree: map of string --> vector of T(template character)*/


//MHa7@sky.com

//
//#include "RadixTree.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main() {
//
//    RadixTree<string> cases;
//    cases.insert("never", "gonna");
//    assert(*cases.search("never") == "gonna");
//    cases.insert("never", "down");
//    assert(*cases.search("never") == "down");
//    assert(*cases.search("never") != "gonna");
//    cases.insert("neverland", "peter");
//    assert(*cases.search("neverland") == "peter");
//    assert(cases.search("neve") == nullptr);
//    assert(*cases.search("never") == "down");
//    cases.insert("neve", "pan");
//    assert(*cases.search("never") == "down");
//    assert(*cases.search("neve") == "pan");
//    cases.insert("try", "cherry");
//    assert(*cases.search("try") == "cherry");
//    cases.insert("faster", "up");
//    cases.insert("fast", "you");
//    assert(*cases.search("faster") == "up");
//    assert(*cases.search("fast") == "you");
//    cases.insert("slow", "hurry");
//    cases.insert("slower", "rush");
//    assert(*cases.search("slow") == "hurry");
//    assert(*cases.search("slower") == "rush");
//    cases.insert("water", "glass");
//    cases.insert("watch", "birds");
//    assert(*cases.search("water") == "glass");
//    assert(*cases.search("watch") == "birds");
//    assert(cases.search("wat") == nullptr);
//    cases.insert("waste", "land");
//    assert(*cases.search("waste") == "land");
//    assert(*cases.search("water") == "glass");
//    assert(*cases.search("watch") == "birds");
//    assert(cases.search("wa") == nullptr);
//    cases.insert("wa", "leave");
//    assert(*cases.search("wa") == "leave");
//    cases.insert("cabs", "taxi");
//    cases.insert("cat", "meow");
//    cases.insert("cab", "nyc");
//    cases.insert("cart", "shopping");
//    assert(*cases.search("cabs") == "taxi");
//    assert(*cases.search("cat") == "meow");
//    assert(*cases.search("cab") == "nyc");
//    assert(*cases.search("cart") == "shopping");
//    assert(cases.search("ca") == nullptr);
//    cases.insert("Cat", "new");
//    assert(*cases.search("Cat") == "new");
//    cout << "passed" <<endl;
//}
