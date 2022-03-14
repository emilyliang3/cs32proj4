//
//  AttributeTranslator.h
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include "provided.h"
#include <vector>
#include <stdio.h>

class AttributeTranslator {
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
};

#endif /* AttributeTranslator_h */
