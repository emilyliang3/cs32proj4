//main.cpp

/*#include "PersonProfile.h"
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
}*/

#include "RadixTree.h"
#include <string>
#include <cassert>
using namespace std;

int main() {
    RadixTree<string> r;
    r.insert("hello", "goodbye");
    r.insert("pencil", "yellow");
    r.insert("balls", "naur");
    r.insert("help", "nor "); //splitting edge, adding 2 nodes
    r.insert("ballsyyy", "lol"); //word matches edge but is longer
    r.insert("pen", "boop"); //word matches edge but is shorter
    r.insert("b", "test"); //inserting single character that matches beginning of edge
    r.insert("pennnnn", "extra"); //word matches edge but is longer; but all characters after are same
    r.insert("pet", "feenicks"); //splitting edge again, adding 2 nodes
    r.insert("xyz", "abc"); //inserting word does not match any edges
    r.insert("he", "him"); //splitting edge again
    r.insert("this is a really long sentence", "1"); //multiple words
    r.insert("porcupine", "Racoon"); //splitting yet again
    r.insert("porcelain", "fire"); //splitting again
    r.insert("Porcupine", "cat"); //case sensitive- two same words, one upper case one lower
    r.insert("PORCUPINE", "dog"); //case sensitive again
    r.insert("hello", "au revoir"); //replacing old value
    r.insert("carey nachenberg", "nerd");
    r.insert("carey smallberg", "nerd"); //word with one space
    r.insert("port", "boat"); //splitting yet another time!
    r.insert("porc", "llll"); //word matches edge perfectly
    r.insert("porccc", "teehee"); //word matches edge but is longer, in middle of tree
    r.print(); //prints in order traversal of tree
    
    string keys[] = {"hello", "pencil", "balls", "help", "ballsyyy", "pen", "b", "pet", "xyz", "porcelain", "port", "porc", "porccc", "carey nachenberg"};
    r.search("porcelain");
    for (int i = 0; i < 14; i++)
        cout << *(r.search(keys[i])) << endl;
    
    assert(r.search("pencils") == nullptr);
    assert(r.search("phoenix") == nullptr);
    assert(r.search("porcc") == nullptr);
    string* v = r.search("hello");
    *v = "modified!";
    cout << *(r.search("hello")) << endl; //making sure caller is free to modify value in radix tree
    cout << "all tests succeeded" << endl;
}
