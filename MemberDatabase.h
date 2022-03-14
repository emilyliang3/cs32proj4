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
#include "provided.h"
class PersonProfile;

class MemberDatabase {
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
};

#endif /* MemberDatabase_h */
