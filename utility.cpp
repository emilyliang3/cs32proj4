//
//  utility.cpp
//  Unhinged
//
//  Created by Emily Liang on 3/15/22.
//

#include "utility.h"

bool operator<(const AttValPair &a, const AttValPair &b)
{
    if (a.attribute < b.attribute)
        return true;
    if (a.attribute == b.attribute)
        return a.value < b.value;
    return false;
}
