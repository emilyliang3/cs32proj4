//
//  MatchMaker.h
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include <string>
#include <vector>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : m_mdb(mdb), m_at(at) {};
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    MemberDatabase m_mdb;
    AttributeTranslator m_at;
};

#endif /* MatchMaker_h */
