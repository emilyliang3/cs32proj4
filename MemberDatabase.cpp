//
//  MemberDatabase.cpp
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#include "MemberDatabase.h"
#include <fstream>
using namespace std;

bool MemberDatabase::LoadDatabase(std::string filename)
{
    ifstream data(filename);
    if (!data)
        return false;
    //the following variables are to loop thru each member's data
    string str, curName, curEmail;
    int remainingPairs;
    bool readingPairs = false;
    bool readingName = true;
    bool readingEmail = false;
    bool readingNum = false;
    PersonProfile* curMember;
    
    while (getline(data, str)) {
        if (readingName) {
            curName = str;
            readingEmail = true;
            readingName = false;
        }
        else if(readingEmail) {
            curEmail = str;
            curMember = new PersonProfile(curName, curEmail);
            readingNum = true;
            readingEmail = false;
        }
        else if(readingNum) {
            remainingPairs = stoi(str);
            readingPairs = true;
            readingNum = false;
        }
        else if(readingPairs) {
            int comma = (int) str.find(',');
            string attribute = str.substr(0, comma);
            string value = str.substr(comma+1);
            AttValPair avp(attribute, value);
            curMember->AddAttValPair(avp); //add avp and email to database
            m_emails.insert(str, curEmail);
            remainingPairs--;
            if (remainingPairs == 0) { //done reading input of current member
                readingPairs = false;
                m_members.insert(curEmail, *curMember); //add member's profile to database
            }
        }
        else if(str.empty()) //in btwn members, starting the loop over for next member
            readingName = true;
    }
    return true;
}
