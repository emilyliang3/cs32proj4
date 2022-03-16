//
//  MatchMaker.cpp
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#include "MatchMaker.h"
#include <algorithm>
#include <unordered_map>
#include "utility.h"
using namespace std;

//support function used only by matchmaker
bool sortEmail(const EmailCount &a, const EmailCount &b) {
    if (a.count > b.count)
        return true;
    if (b.count > a.count)
        return false;
    if (a.email < b.email)
        return true;
    return false;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const
{
    //obtaining member's attribute value pairs
    const PersonProfile* p = m_mdb.GetMemberByEmail(email);
    AttValPair avp;
    vector<AttValPair> avplist;
    for (int i = 0; i < p->GetNumAttValPairs(); i++) {
        if (p->GetAttVal(i, avp))
            avplist.insert(avplist.begin(), avp);
    }
    //obtaining list of compatible av pairs
    set<AttValPair> compatiblePairs;
    vector<AttValPair>::iterator it;
    it = avplist.begin();
    while (it != avplist.end()) {
        vector<AttValPair> v;
        v = m_at.FindCompatibleAttValPairs(*it);
        vector<AttValPair>::iterator vit;
        vit = v.begin();
        while (vit != v.end()) {
            compatiblePairs.insert(*vit);
        }
    }
    //obtaining list of members with compatible pairs
    unordered_map<string, int> matches;
    set<AttValPair>::iterator itcp;
    itcp = compatiblePairs.begin();
    while (itcp != compatiblePairs.end()) {
        vector<string> emails = m_mdb.FindMatchingMembers(*itcp);
        vector<string>::iterator its;
        its = emails.begin();
        while (its != emails.end()) {
            int count = 0;
            if (matches.find(*its) != matches.end())
                count = matches.find(*its)->second;
            count++;
            matches.insert_or_assign(*its, count);
        }
    }
    //compacting list to only members that meet the threshold
    vector<EmailCount> finalemails;
    unordered_map<string,int>::iterator itum;
    itum = matches.begin();
    while (itum != matches.end()) {
        int numMatches = itum->second;
        if (itum->first != email && numMatches >= threshold) {
            EmailCount ec(itum->first, itum->second);
            finalemails.insert(finalemails.begin(), ec);
        }
    }
    //sorting final list
    sort(finalemails.begin(), finalemails.end(), sortEmail);
    return finalemails;
}
