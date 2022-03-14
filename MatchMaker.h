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
class MemberDatabase;
class AttributeTranslator;

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
};

#endif /* MatchMaker_h */
