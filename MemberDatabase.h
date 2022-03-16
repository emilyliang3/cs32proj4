//
//  MemberDatabase.h
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

class MemberDatabase {
public:
    MemberDatabase() {};
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    void print() { m_emails.print(); }
private:
    std::vector<PersonProfile*> m_profileptrs;
    RadixTree<std::set<std::string>> m_emails; //atv pair to emails
    RadixTree<PersonProfile*> m_members; //email to personprofile
};

#endif /* MemberDatabase_h */
