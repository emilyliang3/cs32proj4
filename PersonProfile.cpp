//
//  PersonProfile.cpp
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#include "PersonProfile.h"
using namespace std;

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    string attribute = attval.attribute;
    string value = attval.value;
    vector<string> values;
    bool duplicate = false;
    if (m_attValPairsRT.search(attribute) != nullptr) {
        values = *m_attValPairsRT.search(attribute);
        //checking for duplicates
        vector<string>::iterator it;
        it = values.begin();
        while (it != values.end()) { //only searching vector so time complexity is fine
            if (*it == attribute)
                duplicate = true;
            it++;
        }
    }
    if (duplicate)
        return; //if duplicate do nothing
    values.insert(values.begin(), value);
    m_attValPairsRT.insert(attribute, values);
    m_attValPairsVector.insert(m_attValPairsVector.begin(), attval);
    m_paircount++;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num < 0 || attribute_num >= GetNumAttValPairs())
        return false;
    attval = m_attValPairsVector[attribute_num];
    return true;
}
