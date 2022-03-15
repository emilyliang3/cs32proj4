//
//  AttributeTranslator.cpp
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#include "AttributeTranslator.h"
#include <fstream>
using namespace std;

bool AttributeTranslator::Load(string filename)
{
    ifstream data(filename);
    if (!data)
        return false; //unable to load
    string str;
    while (getline(data, str)) {
        if (!str.empty()) {
            int firstComma = (int) str.find(',');
            int secondComma = (int) str.find(',', firstComma+1);
            string sourcePair = str.substr(0, secondComma);
            int thirdComma = (int) str.find(',', secondComma+1);
            string compAtt = str.substr(secondComma+1, thirdComma-secondComma-1);
            string compVal = str.substr(thirdComma+1);
            AttValPair avp = AttValPair(compAtt, compVal);
            vector<AttValPair> v;
            if (m_translationData.search(sourcePair) != nullptr)
                v = *m_translationData.search(sourcePair);
            v.insert(v.begin(), avp);
            m_translationData.insert(sourcePair, v);
        }
    }
    if (data.is_open())
        data.close();
    return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    string sourcestr = source.attribute + "," + source.value;
    vector<AttValPair> v;
    if (m_translationData.search(sourcestr) != nullptr)
        v = *m_translationData.search(sourcestr);
    return v;
}

void AttributeTranslator::print()
{
    m_translationData.print();
}


