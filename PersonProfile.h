//
//  PersonProfile.h
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include "provided.h"
#include <string>
#include "RadixTree.h"

class PersonProfile {
public:
    PersonProfile(std::string name, std::string email) : m_name(name), m_email(email) {}
    ~PersonProfile();
    std::string GetName() const { return m_name; }
    std::string GetEmail() const { return m_email; }
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    int m_paircount;
    RadixTree<std::string> m_attValPairs;
};

#endif /* PersonProfile_h */
